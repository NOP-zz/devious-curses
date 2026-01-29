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

	bool SexActorFilter(RE::Actor* actor) {
		if (!settings.sexEnabled || !actor) {
			return false;
		}
		auto player = RE::PlayerCharacter::GetSingleton();
		//RE::TESFaction* arousalFaction = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("03FC36", 0, 16), "SexLabAroused.esm");
		//RE::TESFaction* SexlabGenderFaction = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("043A43", 0, 16), "SexLab.esm");
		//RE::TESFaction* PlayerMarriedFaction = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("0C6472", 0, 16), "Skyrim.esm");
		RE::TESFaction* SexlabAnimatingFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x00E50F, "SexLab.esm");
		RE::TESFaction* ZadAnimatingFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x029567, "Devious Devices - Integration.esm");

		RE::TESRace* ManakinRace = StaticDataHolder::GetSingleton()->LookupForm<RE::TESRace>(0x10760a, "Skyrim.esm");
		RE::TESRace* ChickenRace = StaticDataHolder::GetSingleton()->LookupForm<RE::TESRace>(0xa919d, "Skyrim.esm");
		RE::TESRace* GoatRace = StaticDataHolder::GetSingleton()->LookupForm<RE::TESRace>(0x131fa, "Skyrim.esm");
		RE::TESRace* CowRace = StaticDataHolder::GetSingleton()->LookupForm<RE::TESRace>(0x4e785, "Skyrim.esm");
		RE::TESRace* HareRace = StaticDataHolder::GetSingleton()->LookupForm<RE::TESRace>(0x6dc99, "Skyrim.esm");
		//RE::TESRace* OldPeopleRace = StaticDataHolder::GetSingleton()->LookupForm<RE::TESRace>(0x67cd8, "Skyrim.esm");

		auto actorRace = actor->GetRace();

		if (actor->IsInCombat() || actor->IsInFaction(SexlabAnimatingFaction) || actor->IsInFaction(ZadAnimatingFaction) || actor->IsInWater() || actor->IsInRagdollState() || actor->IsChild() || actor->AsActorState()->GetSitSleepState() == RE::SIT_SLEEP_STATE::kIsSleeping || actor->IsHostileToActor(player) || actorRace == ManakinRace) {
			return false;
		}

		if (!settings.sexAllowFarmAnimals && (actorRace == ChickenRace || actorRace == GoatRace || actorRace == CowRace || actorRace == HareRace)) {
			return false;
		}

		bool isCreature = Util::ActorIsCreature(actor);

		bool isFuta = false;

		bool isMale = false;
		bool isFemale = false;

		if (!isCreature) {
			auto sex = SexLab::GetSex(actor);
			isMale = sex == 0;
			isFemale = sex == 1;
			isFuta = sex == 2;
		}
		//log::info("Actor {} is {}", actor->GetName(), isMale ? "Male" : (isFemale ? "Female" : (isFuta ? "Futa" : isCreature ? "Creature" : "Unknown Gender")));
		//else {
		//	isMale = actorSex == 0;
		//	isFemale = actorSex == 1;
		//}

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
		auto playerLewdMark = GetLewdMark();

		auto playerNumDevices = numDevicesVisible(player);
		auto playerWornDeviceKeywords = GetWornDeviceKeywords(player);
		auto playerIsNude = getIsNude(player);
		auto playerIsWearingCollar = vectorContains(playerWornDeviceKeywords, "zad_DeviousCollar");
		auto playerIsWearingHeavyBondage = vectorContains(playerWornDeviceKeywords, "zad_DeviousHeavyBondage");
		auto playerIsWearingBlindfold = vectorContains(playerWornDeviceKeywords, "zad_DeviousBlindfold");
		auto playerIsWearingBoots = vectorContains(playerWornDeviceKeywords, "zad_DeviousBoots");

		RE::TESObjectARMO* summoner_collar = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(SUMMONER_COLLAR, "Devious Curses.esp");
		auto playerHasSummonerCollar = ActorIsWearingDevice(player, summoner_collar);

		RE::TESFaction* PlayerMarriedFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("0C6472", 0, 16), "Skyrim.esm");
		RE::TESGlobal* GameHour = StaticDataHolder::GetSingleton()->LookupForm<RE::TESGlobal>(std::stoi("38", 0, 16), "Skyrim.esm");

		RE::TESFaction* zadDisable = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x4653B, "Devious Devices - Integration.esm");
		
		auto scriptManager = ScriptingManager();

		int playerArousal = scriptManager.GetArousal(player);
		bool playerEnabled = false;

		if (settings.sexRequireAll) {
			playerEnabled = (!settings.sexRequireBindings || playerNumDevices > 0) &&
				(!settings.sexRequireCollar || playerIsWearingCollar) &&
				(!settings.sexRequireHeavy || playerIsWearingHeavyBondage) &&
				(!settings.sexRequireNude || playerIsNude) &&
				(!(settings.sexRequiredPlayerTattoos > 0) || playerTattooCount >= settings.sexRequiredPlayerTattoos) &&
				(!(settings.sexRequiredPlayerArousal > 0) || playerArousal >= settings.sexRequiredPlayerArousal);
		}
		else {
			playerEnabled = (!settings.sexRequireBindings && !settings.sexRequireCollar && !settings.sexRequireHeavy && !settings.sexRequireNude && !(settings.sexRequiredPlayerArousal > 0) && !(settings.sexRequiredPlayerTattoos > 0)) || (
				(settings.sexRequireBindings && playerNumDevices > 0) ||
				(settings.sexRequireCollar && playerIsWearingCollar) ||
				(settings.sexRequireHeavy && playerIsWearingHeavyBondage) ||
				(settings.sexRequireNude && playerIsNude) ||
				((settings.sexRequiredPlayerTattoos > 0) && playerTattooCount >= settings.sexRequiredPlayerTattoos) ||
				((settings.sexRequiredPlayerArousal > 0) && playerArousal >= settings.sexRequiredPlayerArousal));
		}

		std::vector<std::pair<RE::Actor*, std::string>> result;
		if (const auto processLists = RE::ProcessLists::GetSingleton(); processLists) {
			RE::BSSimpleList<RE::ActorHandle>* arr = &(processLists->aliveActorList);
			if (arr) {
				for (auto& actorHandle : *arr) {
					auto actorPtr = actorHandle.get();
					auto actor = actorPtr.get();
					if (actor && actor->Is3DLoaded() && !actor->IsDead() && actor->GetPosition().GetSquaredDistance(playerPosition) <= settings.sexSearchRadius * settings.sexSearchRadius) {
						if (actor->IsInFaction(zadDisable)) {
							log::trace("Ignoring NPC {}.", actor->GetName());
							continue;
						}
						if ((GetDeviceMask(actor) & 0b0011) == 0) {
							continue;
						}
						bool actorIsCreature = Util::ActorIsCreature(actor);
						auto isPlayerCommandedActor = getIsPlayerCommandedActor(actor);

						int r = Util::randomInt();
						int chance = settings.sexChance;
						if (actorIsCreature) chance = settings.sexChanceCreature;

						if (actor->IsPlayerTeammate() && !isPlayerCommandedActor) {
							if (settings.sexChanceFollower >= 0) {
								chance = settings.sexChanceFollower;
							}
						}
						if (actor->IsInFaction(PlayerMarriedFaction)) {
							if (settings.sexChanceSpouse >= 0) {
								chance = settings.sexChanceSpouse;
							}
						}
						if (isPlayerCommandedActor) {
							if (settings.sexChanceSummon >= 0) {
								chance = settings.sexChanceSummon;
							}
						}

						//log::info("testing actor {}", actor->GetName());
						//Check aggressor against normal filters
						if (r < chance && SexActorFilter(actor)) {
							//Check aggressor enabled
							bool enabled = playerEnabled;

							if (actor->IsPlayerTeammate() && !getIsPlayerCommandedActor(actor) && settings.sexAlwaysAllowFollowers) {
								enabled = true;
							}
							else if (playerLewdMark == MARK::TAT_ALLURE) {
								enabled = true;
							}
							else if (actor->IsInFaction(PlayerMarriedFaction) && settings.sexAlwaysAllowSpouse) {
								enabled = true;
							}
							else if (getIsPlayerCommandedActor(actor) && (settings.sexAlwaysAllowSummons || playerHasSummonerCollar)) {
								enabled = true;
							}
							

							if (enabled) {
								//Check aggressor arousal
								float actorArousal = static_cast<float>(scriptManager.GetArousal(actor));

								//if (actorArousal <= 0) {
								//UpdateArousal(actor);
								//}

								float arousal = static_cast<float>(settings.sexBaseArousal);

								std::string logMessage = "";

								if (settings.sexArousalNightModifier > 0 && (GameHour->value < 5.0 || GameHour->value > 22.0)) {
									arousal -= settings.sexArousalNightModifier;
									logMessage += fmt::format("(night {}) ", settings.sexArousalNightModifier);
								}
								if (settings.sexArousalNudeModifier > 0 && playerIsNude) {
									arousal -= settings.sexArousalNudeModifier;
									logMessage += fmt::format("(nude {}) ", settings.sexArousalNudeModifier);
								}
								if (settings.sexArousalCollarModifier > 0 && playerIsWearingCollar) {
									arousal -= settings.sexArousalCollarModifier;
									logMessage += fmt::format("(collar {}) ", settings.sexArousalCollarModifier);
								}
								if (settings.sexArousalHeavyModifier > 0 && playerIsWearingHeavyBondage) {
									arousal -= settings.sexArousalHeavyModifier;
									logMessage += fmt::format("(heavy {}) ", settings.sexArousalHeavyModifier);
								}
								if (settings.sexArousalBlindModifier > 0 && playerIsWearingBlindfold) {
									arousal -= settings.sexArousalBlindModifier;
									logMessage += fmt::format("(blind {}) ", settings.sexArousalBlindModifier);
								}
								if (settings.sexArousalBootsModifier > 0 && playerIsWearingBoots) {
									arousal -= settings.sexArousalBootsModifier;
									logMessage += fmt::format("(boots {}) ", settings.sexArousalBootsModifier);
								}
								if (settings.sexArousalHobbleModifier > 0 && player->IsOverEncumbered()) {
									arousal -= settings.sexArousalHobbleModifier;
									logMessage += fmt::format("(hobble {}) ", settings.sexArousalHobbleModifier);
								}
								if (settings.sexArousalVisibleModifier > 0 && playerNumDevices > 0) {
									arousal -= settings.sexArousalVisibleModifier;
									logMessage += fmt::format("(device {}) ", settings.sexArousalVisibleModifier);
								}
								if (playerTattooCount > 0) {
									auto mod = settings.sexArousalTattooModifier * playerTattooCount;
									arousal -= mod;
									if (mod > 0) logMessage += fmt::format("(tattoo {:.2f}) ", mod);
								}
								if (settings.sexArousalCreatureModifier > 0 && actorIsCreature) {
									arousal -= settings.sexArousalCreatureModifier;
									logMessage += fmt::format("(creature {}) ", settings.sexArousalCreatureModifier);
								}
								if (settings.sexArousalFollowerModifier > 0 && actor->IsPlayerTeammate() && !isPlayerCommandedActor) {
									arousal -= settings.sexArousalFollowerModifier;
									logMessage += fmt::format("(team {}) ", settings.sexArousalFollowerModifier);
								}
								if (settings.sexArousalSpouseModifier > 0 && actor->IsInFaction(PlayerMarriedFaction)) {
									arousal -= settings.sexArousalSpouseModifier;
									logMessage += fmt::format("(spouse {}) ", settings.sexArousalSpouseModifier);
								}
								if (settings.sexArousalSummonModifier > 0 && isPlayerCommandedActor) {
									arousal -= settings.sexArousalSummonModifier;
									logMessage += fmt::format("(summon {}) ", settings.sexArousalSummonModifier);
								}

								if (!logMessage.empty()) logMessage.pop_back();

								


								log::trace("Actor Info {}: {} > {}({}) [{}]", actor->GetName(), actorArousal, arousal, settings.sexBaseArousal, logMessage);

								if (actorArousal >= arousal) {
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
		tagsToRemove.pop_back();
		return tagsToRemove;
	}

	std::string P_GetAnimationFilterTagsP(RE::StaticFunctionTag*, RE::Actor* akActor) {
		int mask = GetDeviceMask(akActor);

		std::string tags;

		if (!(mask & 0b0100)) {
			tags = "-Oral," + tags;
		}
		//else {
		//	tags = "~Oral," + tags;
		//}
		if (!(mask & 0b0001)) {
			tags = "-Anal," + tags;
		}
		//else {
		//	tags = "~Anal," + tags;
		//}
		if (!(mask & 0b0010)) {
			tags = "-Vaginal,-Fisting,-Fingering,-Masturbation," + tags;
		}
		//else {
		//	tags = "~Vaginal," + tags;
		//}
		if (!(mask & 0b1000)) {
			tags = "-Boobjob," + tags;
		}
		//else {
		//	tags = "~Boobjob," + tags;
		//}
		tags.pop_back();
		return tags;
	}

	void StartMasturbationImpl() {
		auto scriptManager = ScriptingManager();
		RE::TESForm* sexlab = StaticDataHolder::GetSingleton()->LookupForm(0x0D62, "SexLab.esm");

		auto intent = ScriptIntent(sexlab, RE::FormType::Quest, "SexLabFramework", "GetVersion");
		scriptManager.RunIntentWithResult<int>(intent, [sexlab](std::optional<int> version) {
			if (version.value() <= 16601) {
				auto args = RE::MakeFunctionArguments<RE::Actor*, RE::Actor*, RE::Actor*, RE::Actor*, RE::Actor*, RE::Actor*, std::string, std::string>(std::move(RE::PlayerCharacter::GetSingleton()), nullptr, nullptr, nullptr, nullptr, nullptr, "", "");
				auto intent = ScriptIntent(sexlab, RE::FormType::Quest, "SexLabFramework", "QuickStart", args);
				return RE::BSTSmartPointer(new ScriptCallbackFunctor(intent));
			}
			std::vector<RE::Actor*> vec = { RE::PlayerCharacter::GetSingleton() };
			auto tags = P_GetAnimationFilterTagsP(nullptr, RE::PlayerCharacter::GetSingleton());
			auto args = RE::MakeFunctionArguments<std::vector<RE::Actor*>, std::string, RE::Actor*, RE::TESObjectREFR*, int, std::string>(std::move(vec), std::move(tags), nullptr, nullptr, 1, "");
			auto intent = ScriptIntent(sexlab, RE::FormType::Quest, "SexLabFramework", "StartScene", args);
			return RE::BSTSmartPointer(new ScriptCallbackFunctor(intent));
		});
	}

	void SexUpdate() {
		auto player = RE::PlayerCharacter::GetSingleton();

		if (!settings.sexEnabled || !settings.sexRandomEnabled) {
			return;
		}

		if (counters.clock_lastSex < settings.sexCooldown) {
			return;
		}

		if (counters.clock_SexTimeout <= settings.sexSearchInterval) {
			return;
		}

		if (player->IsInCombat() || player->IsInWater() || player->IsInRagdollState() || RE::UI::GetSingleton()->IsMenuOpen("Dialogue Menu") || RE::UI::GetSingleton()->IsMenuOpen("Crafting Menu")) {
			return;
		}

		if ((GetDeviceMask(RE::PlayerCharacter::GetSingleton()) & 0b0111) == 0) {
			return;
		}

		//log::info("Attempting random sex event.");

		auto actors = getAllAvailableActors();

		counters.clock_SexTimeout = 0;

		if (actors.size() == 0) {
			return;
		}

		//log::info("Got actors for event.");

		int r = Util::randomInt(static_cast<int>(actors.size()));
		auto const& actorData = (actors)[r];

		log::info("{}", actorData.second);

		ScriptingManager().StartSex(actorData.first, settings.sexAggressiveAnims);

		counters.clock_lastSex = -10;
	}

	
	class EffectVisitor2 : public RE::MagicTarget::ForEachActiveEffectVisitor {
	public:
		RE::Actor* match = nullptr;
		// Inherited via ForEachActiveEffectVisitor
		virtual RE::BSContainer::ForEachResult Accept(RE::ActiveEffect* a_effect) override
		{
			if (a_effect->GetBaseObject()->data.associatedForm) {
				RE::TESNPC* actor_base = a_effect->GetBaseObject()->data.associatedForm->As<RE::TESNPC>();
				if (actor_base && actor_base == match->GetActorBase()) {
					log::info("Increasing summon time for {}", match->GetName());
					a_effect->duration += 180;
				}
			}
			return RE::BSContainer::ForEachResult::kContinue;
		}

		EffectVisitor2(RE::Actor* actor) {
			match = actor;
		}
	};


	void P_SexStarted(RE::StaticFunctionTag*, RE::BSTArray<RE::Actor*> actors) {
		for (auto actor : actors) {
			if (actor && actor != RE::PlayerCharacter::GetSingleton()) {
				log::trace("Sex started with {}", actor->GetName());
				if (getIsPlayerCommandedActor(actor)) {
					EffectVisitor2 temp(actor);
					RE::PlayerCharacter::GetSingleton()->AsMagicTarget()->VisitEffects(temp);
				}
				break;
			}
		}
	}

	void OppOnSexEnd(RE::Actor* actor);
	void OppMadnessPlayerOrgasm();
	void OppNocturnalPlayerSex();

	void P_SexEnded(RE::StaticFunctionTag*, RE::BSTArray<RE::Actor*> actors) {
		if (IsModDisabled()) {
			log::trace("Sex ended skipped, mod is disabled.");
			return;
		}
		for (auto actor : actors) {
			if (actor && actor != RE::PlayerCharacter::GetSingleton()) {
				log::trace("Sex ended with {}", actor->GetName());
				OppOnSexEnd(actor);
				ConsSexEnded(actor);
				TatsOnSexEnd(actor);
				break;
			}
		}
		if (settings.oppMadnessAllOrgasms) {
			OppMadnessPlayerOrgasm(); 
		}
		OppNocturnalPlayerSex();
	}

	void P_DDPlayerOrgasm(RE::StaticFunctionTag*) {
		log::trace("Player device orgasm");
		OppMadnessPlayerOrgasm();
		//OppNocturnalPlayerOrgasm();
	}

	bool PapyrusFunctionsSex(RE::BSScript::IVirtualMachine* ivm) {
		ivm->RegisterFunction("GetAnimationFilterTags", "DCursesLib", P_GetAnimationFilterTags);
		ivm->RegisterFunction("GetAnimationFilterTagsP", "DCursesLib", P_GetAnimationFilterTagsP);
		ivm->RegisterFunction("SexStarted", "DCursesLib", P_SexStarted);
		ivm->RegisterFunction("SexEnded", "DCursesLib", P_SexEnded);
		ivm->RegisterFunction("DDPlayerOrgasm", "DCursesLib", P_DDPlayerOrgasm);
		return true;
	}
}