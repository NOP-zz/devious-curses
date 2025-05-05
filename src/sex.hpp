#pragma once

#include "Devices.hpp"
#include "tats.hpp"
#include "Consequences.hpp"
#include "../include/SexLabPPFunctions.h"

using namespace SKSE;

namespace DCURSES {

	bool getIsPlayerCommandedActor(RE::Actor* actor) {
		if (!actor) {
			return false;
		}

		return actor->IsCommandedActor() && actor->GetCommandingActor().get() == RE::PlayerCharacter::GetSingleton();
	}

	bool SexActorFilter(RE::Actor* actor) {
		if (!settings.sexEnabled || !actor) {
			return false;
		}
		auto player = RE::PlayerCharacter::GetSingleton();
		//RE::TESFaction* arousalFaction = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("03FC36", 0, 16), "SexLabAroused.esm");
		//RE::TESFaction* SexlabGenderFaction = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("043A43", 0, 16), "SexLab.esm");
		//RE::TESFaction* PlayerMarriedFaction = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("0C6472", 0, 16), "Skyrim.esm");
		RE::TESFaction* SexlabAnimatingFaction = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("00E50F", 0, 16), "SexLab.esm");
		RE::TESFaction* ZadAnimatingFaction = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("029567", 0, 16), "Devious Devices - Integration.esm");

		if (actor->IsInCombat() || actor->IsInFaction(SexlabAnimatingFaction) || actor->IsInFaction(ZadAnimatingFaction) || actor->IsInWater() || actor->IsInRagdollState() || actor->IsChild() || actor->AsActorState()->GetSitSleepState() == RE::SIT_SLEEP_STATE::kIsSleeping || actor->IsHostileToActor(player)) {
			return false;
		}

		bool isCreature = !actor->GetRace()->HasKeywordString("ActorTypeNPC") && (actor->GetRace()->HasKeywordString("ActorTypeCreature") || actor->GetRace()->HasKeywordString("ActorTypeDwarven") || actor->GetRace()->HasKeywordString("ActorTypeAnimal"));

		int actorSex = actor->GetActorBase()->GetSex();

		bool isFuta = false;

		bool isMale = false;
		bool isFemale = false;

		if (!isCreature) {
			auto sex = SexLab::GetSex(actor);
			isMale = sex == 0;
			isFemale = sex == 1;
			isFuta = sex == 2;
		}
		else {
			isMale = actorSex == 0;
			isFemale = actorSex == 1;
		}


		log::trace("Gender testing actor {}: {} ({})", actor->GetName(), isFuta ? "futa" : isFemale ? "female" : isMale ? "male" : isCreature ? "creature" : "unknown", GetActorArousal(actor));

		if ((isMale && settings.sexAllowMale) ||
			(isFemale && settings.sexAllowFemale) ||
			(isFuta && settings.sexAllowFuta) ||
			(isCreature && settings.sexAllowCreature)) {
			return true;
		}
		return false;

	}

	std::vector<std::pair<RE::Actor*, std::string>> getAllAvailableActors() {
		auto player = RE::PlayerCharacter::GetSingleton();
		auto playerPosition = player->GetPosition();

		auto playerTattooCount = GetTattooCount(player);
		auto playerLewdMark = GetLewdMark(player);

		auto playerNumDevices = numDevicesVisible(player);
		auto playerWornDeviceKeywords = GetWornDeviceKeywords(player);
		auto playerIsNude = player->GetWornArmor((RE::BIPED_MODEL::BipedObjectSlot::kBody)) == nullptr;
		auto playerIsWearingCollar = vectorContains(playerWornDeviceKeywords, "zad_DeviousCollar");
		auto playerIsWearingHeavyBondage = vectorContains(playerWornDeviceKeywords, "zad_DeviousHeavyBondage");
		auto playerIsWearingBlindfold = vectorContains(playerWornDeviceKeywords, "zad_DeviousBlindfold");
		auto playerIsWearingBoots = vectorContains(playerWornDeviceKeywords, "zad_DeviousBoots");

		RE::TESObjectARMO* summoner_collar = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESObjectARMO>(SUMMONER_COLLAR, "Devious Curses.esp");
		auto playerHasSummonerCollar = ActorIsWearingDevice(player, summoner_collar);

		RE::TESFaction* PlayerMarriedFaction = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("0C6472", 0, 16), "Skyrim.esm");
		RE::TESGlobal* GameHour = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESGlobal>(std::stoi("38", 0, 16), "Skyrim.esm");

		int playerArousal = GetActorArousal(player);

		std::vector<std::pair<RE::Actor*, std::string>> result;
		if (const auto processLists = RE::ProcessLists::GetSingleton(); processLists) {
			RE::BSSimpleList<RE::ActorHandle>* arr = &(processLists->aliveActorList);
			if (arr) {
				for (auto& actorHandle : *arr) {
					auto actorPtr = actorHandle.get();
					auto actor = actorPtr.get();
					if (actor && actor->Is3DLoaded() && !actor->IsDead() && actor->GetPosition().GetDistance(playerPosition) <= settings.sexSearchRadius) {

						bool actorIsCreature = !actor->GetRace()->HasKeywordString("ActorTypeNPC") && (actor->GetRace()->HasKeywordString("ActorTypeCreature") || actor->GetRace()->HasKeywordString("ActorTypeDwarven") || actor->GetRace()->HasKeywordString("ActorTypeAnimal"));
						//log::info("testing actor {}", actor->GetName());
						//Check aggressor against normal filters
						if (SexActorFilter(actor)) {
							//Check aggressor enabled
							bool enabled = false;
							if (actor->IsPlayerTeammate() && !getIsPlayerCommandedActor(actor) && settings.sexAlwaysAllowFollowers) {
								enabled = true;
							}
							else if (playerLewdMark == TAT_ALLURE) {
								enabled = true;
							}
							else if (actor->IsInFaction(PlayerMarriedFaction) && settings.sexAlwaysAllowSpouse) {
								enabled = true;
							}
							else if (getIsPlayerCommandedActor(actor) && (settings.sexAlwaysAllowSummons || playerHasSummonerCollar)) {
								enabled = true;
							}
							else if (settings.sexRequireAll) {
								enabled = (!settings.sexRequireBindings || playerNumDevices > 0) &&
									(!settings.sexRequireCollar || playerIsWearingCollar) &&
									(!settings.sexRequireHeavy || playerIsWearingHeavyBondage) &&
									(!settings.sexRequireNude || playerIsNude) &&
									(!(settings.sexRequiredPlayerTattoos > 0) || playerTattooCount >= settings.sexRequiredPlayerTattoos) &&
									(!(settings.sexRequiredPlayerArousal > 0) || playerArousal >= settings.sexRequiredPlayerArousal);
							}
							else {
								enabled = (!settings.sexRequireBindings && !settings.sexRequireCollar && !settings.sexRequireHeavy && !settings.sexRequireNude && !(settings.sexRequiredPlayerArousal > 0) && !(settings.sexRequiredPlayerTattoos > 0)) || (
									(settings.sexRequireBindings && playerNumDevices > 0) ||
									(settings.sexRequireCollar && playerIsWearingCollar) ||
									(settings.sexRequireHeavy && playerIsWearingHeavyBondage) ||
									(settings.sexRequireNude && playerIsNude) ||
									((settings.sexRequiredPlayerTattoos > 0) && playerTattooCount >= settings.sexRequiredPlayerTattoos) ||
									((settings.sexRequiredPlayerArousal > 0) && playerArousal >= settings.sexRequiredPlayerArousal));
							}

							log::trace("Actor enabled: {}", enabled);

							if (enabled) {
								//Check aggressor arousal
								int actorArousal = GetActorArousal(actor);

								//if (actorArousal <= 0) {
								//UpdateArousal(actor);
								//}

								UpdateArousal(actor);

								float arousal = static_cast<float>(settings.sexBaseArousal);
								int chance = settings.sexChance;
								if (actorIsCreature) chance = settings.sexChanceCreature;

								std::string logMessage = "";

								if (GameHour->value < 5.0 || GameHour->value > 22.0) {
									arousal -= settings.sexArousalNightModifier;
									if (settings.sexArousalNightModifier > 0) logMessage += fmt::format("(night {}) ", settings.sexArousalNightModifier);
								}
								if (playerIsNude) {
									arousal -= settings.sexArousalNudeModifier;
									if (settings.sexArousalNudeModifier > 0) logMessage += fmt::format("(nude {}) ", settings.sexArousalNudeModifier);
								}
								if (playerIsWearingCollar) {
									arousal -= settings.sexArousalCollarModifier;
									if (settings.sexArousalCollarModifier > 0) logMessage += fmt::format("(collar {}) ", settings.sexArousalCollarModifier);
								}
								if (playerIsWearingHeavyBondage) {
									arousal -= settings.sexArousalHeavyModifier;
									if (settings.sexArousalHeavyModifier > 0) logMessage += fmt::format("(heavy {}) ", settings.sexArousalHeavyModifier);
								}
								if (playerIsWearingBlindfold) {
									arousal -= settings.sexArousalBlindModifier;
									if (settings.sexArousalBlindModifier > 0) logMessage += fmt::format("(blind {}) ", settings.sexArousalBlindModifier);
								}
								if (playerIsWearingBoots) {
									arousal -= settings.sexArousalBootsModifier;
									if (settings.sexArousalBootsModifier > 0) logMessage += fmt::format("(boots {}) ", settings.sexArousalBootsModifier);
								}
								if (player->IsOverEncumbered()) {
									arousal -= settings.sexArousalHobbleModifier;
									if (settings.sexArousalHobbleModifier > 0) logMessage += fmt::format("(hobble {}) ", settings.sexArousalHobbleModifier);
								}
								if (playerNumDevices > 0) {
									arousal -= settings.sexArousalVisibleModifier;
									if (settings.sexArousalVisibleModifier > 0) logMessage += fmt::format("(device {}) ", settings.sexArousalVisibleModifier);
								}
								if (playerTattooCount > 0) {
									auto mod = settings.sexArousalTattooModifier * playerTattooCount;
									arousal -= mod;
									if (mod > 0) logMessage += fmt::format("(tattoo {:.2f}) ", mod);
								}
								if (actorIsCreature) {
									arousal -= settings.sexArousalCreatureModifier;
									if (settings.sexArousalCreatureModifier > 0) logMessage += fmt::format("(creature {}) ", settings.sexArousalCreatureModifier);
								}
								if (actor->IsPlayerTeammate() && !getIsPlayerCommandedActor(actor)) {
									arousal -= settings.sexArousalFollowerModifier;
									if (settings.sexArousalFollowerModifier > 0) logMessage += fmt::format("(team {}) ", settings.sexArousalFollowerModifier);
									if (settings.sexChanceFollower >= 0) {
										chance = settings.sexChanceFollower;
									}
								}
								if (actor->IsInFaction(PlayerMarriedFaction)) {
									arousal -= settings.sexArousalSpouseModifier;
									if (settings.sexArousalSpouseModifier > 0) logMessage += fmt::format("(spouse {}) ", settings.sexArousalSpouseModifier);
									if (settings.sexChanceSpouse >= 0) {
										chance = settings.sexChanceSpouse;
									}
								}
								if (getIsPlayerCommandedActor(actor)) {
									arousal -= settings.sexArousalSummonModifier;
									if (settings.sexArousalSummonModifier > 0) logMessage += fmt::format("(summon {}) ", settings.sexArousalSummonModifier);
									if (settings.sexChanceSummon >= 0) {
										chance = settings.sexChanceSummon;
									}
								}

								if (!logMessage.empty()) logMessage.pop_back();

								int r = Util::randomInt();


								log::trace("Actor Info {}: {} > {}({}) [{}]", actor->GetName(), actorArousal, arousal, settings.sexBaseArousal, logMessage);

								if (actorArousal >= arousal && r < chance) {
									auto msg = fmt::format("[sex] {}: {} > {}({}) [{}] ({}%, {})", actor->GetName(), actorArousal, arousal, settings.sexBaseArousal, logMessage, chance, r);
									result.push_back(std::make_pair(actor, msg));
								}
							}
						}
					}
				}
			}
		}

		return result;
	}

	std::vector<RE::Actor*> getPlayerCommandedActors() {
		auto playerPosition = RE::PlayerCharacter::GetSingleton()->GetPosition();
		std::vector<RE::Actor*> result;
		if (const auto processLists = RE::ProcessLists::GetSingleton(); processLists) {
			RE::BSSimpleList<RE::ActorHandle>* arr = &(processLists->aliveActorList);
			if (arr) {
				for (auto& actorHandle : *arr) {
					auto actorPtr = actorHandle.get();
					if (auto actor = actorPtr.get(); actor && actor->Is3DLoaded() && !actor->IsDead()) {
						if (getIsPlayerCommandedActor(actor)) {
							result.push_back(actor);
						}
					}
				}
			}
		}
		return result;
	}

	int GetDeviceMask(RE::Actor* actor) {
		if (!actor) return 0;
		int canAnal = 1;
		int canVaginal = 1;
		int canOral = 1;
		int canBoobjob = 1;

		for (auto const& [k, v] : actor->GetInventory()) {
			if (v.second.get()->IsWorn()) {
				RE::TESObjectARMO* wornArmor = k->As<RE::TESObjectARMO>();
				if (!wornArmor) {
					continue;
				}

				if (wornArmor->HasKeywordString("zad_DeviousBelt") && !wornArmor->HasKeywordString("zad_PermitVaginal")) {
					canVaginal = 0;
				}
				if (wornArmor->HasKeywordString("zad_DeviousSuit") && !wornArmor->HasKeywordString("zad_PermitVaginal")) {
					canVaginal = 0;
				}
				if (wornArmor->HasKeywordString("zad_DeviousPlugVaginal") && !wornArmor->HasKeywordString("zad_PermitVaginal")) {
					canVaginal = 0;
				}

				if (wornArmor->HasKeywordString("zad_DeviousBelt") && !wornArmor->HasKeywordString("zad_PermitAnal")) {
					canAnal = 0;
				}
				if (wornArmor->HasKeywordString("zad_DeviousSuit") && !wornArmor->HasKeywordString("zad_PermitAnal")) {
					canAnal = 0;
				}
				if (wornArmor->HasKeywordString("zad_DeviousPlugAnal") && !wornArmor->HasKeywordString("zad_PermitAnal")) {
					canAnal = 0;
				}

				if (wornArmor->HasKeywordString("zad_DeviousGag") && !wornArmor->HasKeywordString("zad_DeviousGagPanel") && !wornArmor->HasKeywordString("zad_PermitOral")) {
					canOral = 0;
				}

				if (wornArmor->HasKeywordString("zad_DeviousBra") || wornArmor->HasKeywordString("zad_DeviousSuit")) {
					canBoobjob = 0;
				}
			}
		}
		auto mask = canAnal | (canVaginal << 1) | (canOral << 2) | (canBoobjob << 3);
		//log::trace("Device mask: {:b}", mask);
		return mask;
	}

	void SexUpdate() {
		if (!settings.sexEnabled || !settings.sexRandomEnabled) {
			return;
		}
		RE::TESFaction* SexlabAnimatingFaction = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("00E50F", 0, 16), "SexLab.esm");
		RE::TESFaction* ZadAnimatingFaction = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("029567", 0, 16), "Devious Devices - Integration.esm");

		auto player = RE::PlayerCharacter::GetSingleton();

		if (player->IsInFaction(SexlabAnimatingFaction)) {
			counters.clock_lastSex = 0;
			return;
		}

		if (counters.clock_lastSex < settings.sexCooldown) {
			return;
		}

		if (counters.clock_SexTimeout <= 0) {
			return;
		}

		if (player->IsInCombat() || player->IsInFaction(ZadAnimatingFaction) || player->IsInWater() || player->IsInRagdollState() || RE::UI::GetSingleton()->IsMenuOpen("Dialogue Menu") || RE::UI::GetSingleton()->IsMenuOpen("Crafting Menu")) {
			return;
		}

		if ((GetDeviceMask(RE::PlayerCharacter::GetSingleton()) & 0b0111) == 0) {
			return;
		}

		//log::info("Attempting random sex event.");

		auto actors = getAllAvailableActors();

		if (actors.size() == 0) {
			return;
		}

		//log::info("Got actors for event.");

		int r = Util::randomInt(static_cast<int>(actors.size()));
		auto const& actorData = (actors)[r];

		log::info("{}", actorData.second);

		StartSex(actorData.first);

		counters.clock_lastSex = -10;
		counters.clock_SexTimeout = -2;
	}

	std::string P_GetAnimationFilterTags(RE::StaticFunctionTag*, RE::Actor* akActor) {
		int mask = GetDeviceMask(akActor);

		std::string tagsToRemove;

		if (!(mask & 0b0100)) {
			tagsToRemove = "Oral," + tagsToRemove;
		}
		if (!(mask & 0b0001)) {
			tagsToRemove = "Anal," + tagsToRemove;
		}
		if (!(mask & 0b0010)) {
			tagsToRemove = "Vaginal,Fisting,Fingering,Masturbation," + tagsToRemove;
		}
		if (!(mask & 0b1000)) {
			tagsToRemove = "Boobjob," + tagsToRemove;
		}
		return tagsToRemove;
	}

	std::string P_GetAnimationFilterTagsP(RE::StaticFunctionTag*, RE::Actor* akActor) {
		int mask = GetDeviceMask(akActor);

		std::string tagsToRemove;

		if (!(mask & 0b0100)) {
			tagsToRemove = "-Oral," + tagsToRemove;
		}
		if (!(mask & 0b0001)) {
			tagsToRemove = "-Anal," + tagsToRemove;
		}
		if (!(mask & 0b0010)) {
			tagsToRemove = "-Vaginal,-Fisting,-Fingering,-Masturbation," + tagsToRemove;
		}
		if (!(mask & 0b1000)) {
			tagsToRemove = "-Boobjob," + tagsToRemove;
		}
		return tagsToRemove;
	}

	

	void P_SexStarted(RE::StaticFunctionTag*, RE::BSTArray<RE::Actor*> actors) {
		for (auto actor : actors) {
			if (actor && actor != RE::PlayerCharacter::GetSingleton()) {
				log::trace("Sex started with {}", actor->GetName());
				break;
			}
		}
	}

	void P_SexEnded(RE::StaticFunctionTag*, RE::BSTArray<RE::Actor*> actors) {
		for (auto actor : actors) {
			if (actor && actor != RE::PlayerCharacter::GetSingleton()) {
				log::trace("Sex ended with {}", actor->GetName());
				IncrementCounterForMark(RE::PlayerCharacter::GetSingleton(), TAT_ALLURE);
				ConsSexEnded(actor);
				break;
			}
		}
	}

	bool PapyrusFunctionsSex(RE::BSScript::IVirtualMachine* ivm) {
		ivm->RegisterFunction("GetAnimationFilterTags", "DCursesLib", P_GetAnimationFilterTags);
		ivm->RegisterFunction("GetAnimationFilterTagsP", "DCursesLib", P_GetAnimationFilterTagsP);
		ivm->RegisterFunction("SexStarted", "DCursesLib", P_SexStarted);
		ivm->RegisterFunction("SexEnded", "DCursesLib", P_SexEnded);
		return true;
	}
}