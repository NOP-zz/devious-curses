#pragma once

#include "Scripting.hpp"
#include "Settings.hpp"
#include "Devices.hpp"
#include "sex.hpp"
#include "MGEF_Controller.hpp"
#include "MinAI.hpp"

using namespace SKSE;

namespace DCURSES {
	static const int ODEVICE_TICK = 5;

	bool DoStandardEvent(bool, std::string, std::string, int, std::vector<std::string>);

	bool OppSummonerCollarEvent(std::string containerName) {
		if (!settings.sexAllowCreature || settings.sexChanceCreature == 0 || !settings.sexRandomEnabled) {
			return false;
		}

		auto player = RE::PlayerCharacter::GetSingleton();

		auto currentCollar = GetWornInventoryDeviceByKeyword(player, "zad_DeviousCollar");
		if (currentCollar && !DeviceInventoryIsGeneric(currentCollar)) {
			return false;
		}

		RE::TESObjectARMO* summoner_collar = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(SUMMONER_COLLAR, "Devious Curses.esp");

		counters.clock_GlobalTicker -= counters.clock_GlobalTicker;

		auto magic = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kMagicka);
		player->AsActorValueOwner()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kMagicka, -magic);

		AIEventSummonerCollarAdd();

		LockDevice(player, summoner_collar, true);
		if (!containerName.empty()) { PlayerMessage(fmt::format("As you touch the {} you feel very dizzy as a heavy collar forms around your neck and absorbs your magicka!", containerName)); };
		return true;
	}

	bool OppLivingLatexEvent(std::string containerName) {
		auto player = RE::PlayerCharacter::GetSingleton();

		auto currentSuit = GetWornInventoryDeviceByKeyword(player, "zad_DeviousSuit");
		if (currentSuit && !DeviceInventoryIsGeneric(currentSuit)) {
			return false;
		}

		RE::TESObjectARMO* latex = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LIVING_LATEX, "Devious Curses.esp");
		RE::TESObjectARMO* latex_open = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LIVING_LATEX_OPEN, "Devious Curses.esp");

		counters.clock_GlobalTicker -= counters.clock_GlobalTicker % ODEVICE_TICK;

		auto stamina = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kStamina);
		player->AsActorValueOwner()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kStamina, -stamina / 2);

		AIEventLivingLatexAdd();

		if (settings.oppLivingLatexOpen) {
			LockDevice(player, latex_open, true);
		}
		else {
			LockDevice(player, latex, true);
		}

		//Util::ExecuteWithDelay(500ms, [] {
		//	SetEffectMagnitude(LIVING_LATEX_EFFECT, static_cast<float>(settings.oppLivingLatexStartTime) * 60 * Util::randomFloat(0.9f, 1.2f));
		//});
		
		if (!containerName.empty()) { PlayerMessage(fmt::format("As you touch the {} a ball of goo jumps out at you and covers your body!", containerName)); };
		return true;
	}

	bool DoOppDeviceEvent(std::string containerName) {

		int weightTotal = settings.oppSummonerCollarWeight + settings.oppLivingLatexWeight;
		if (weightTotal <= 0.0) return false;

		int r = Util::randomInt(weightTotal);

		std::vector<std::pair<bool (*)(std::string), int>> events;
		events.push_back(std::make_pair(OppSummonerCollarEvent, settings.oppSummonerCollarWeight));
		events.push_back(std::make_pair(OppLivingLatexEvent, settings.oppLivingLatexWeight));


		Util::ShuffleVector(events);
		for (size_t i = 0; i < events.size(); i++) {
			auto pair = events[i];
			if (r < pair.second) {
				if (pair.first(containerName)) {
					return true;
				}
				else {
					r -= pair.second;
				}
			}
			else {
				r -= pair.second;
			}
		}
		return false;
	}

	void OppDeviceOnHitEvent() {
		auto player = RE::PlayerCharacter::GetSingleton();

		//Living Latex
		RE::TESObjectARMO* latex = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LIVING_LATEX, "Devious Curses.esp");
		RE::TESObjectARMO* latex_open = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LIVING_LATEX_OPEN, "Devious Curses.esp");
		int magnitude = static_cast<int>(GetEffectMagnitude(LIVING_LATEX_EFFECT));
		bool isWearingLatex = ActorIsWearingDevice(player, latex) || ActorIsWearingDevice(player, latex_open);
		if (isWearingLatex && magnitude == 2) {
			std::vector<std::string> skips = {"zad_"};
			if (!settings.oppLivingLatexHeavy) {
				skips.push_back("zad_DeviousHeavyBondage");
			}
			DoStandardEvent(false, "", "(black & (ebonite | rubber))", 4, skips);
			PlayerMessage("The latex writhes while being shocked. It seems as if it has been weakened significantly!");
			SetEffectMagnitude(LIVING_LATEX_EFFECT, 1.0f);
			SetEffectDescription(LIVING_LATEX_EFFECT, "The latex is clinging to you only by your other devices, removing them should do the trick!");
		}
	}

	void OppDeviceUpdate() {
		if (counters.clock_GlobalTicker % ODEVICE_TICK == 0) {
			auto player = RE::PlayerCharacter::GetSingleton();

			RE::TESObjectARMO* summoner_collar = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(SUMMONER_COLLAR, "Devious Curses.esp");
			RE::TESKey* summoner_collar_key = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(SUMMONER_COLLAR_KEY, "Devious Curses.esp");

			//Summoner Collar
			bool isWearingSummonerCollar = ActorIsWearingDevice(player, summoner_collar);
			if (isWearingSummonerCollar) {
				int magnitude = static_cast<int>(GetEffectMagnitude(SUMMONER_COLLAR_EFFECT));
				if (magnitude < -10000) {
					magnitude = static_cast<int>(settings.oppSummonerSexCount);
					SetEffectMagnitude(SUMMONER_COLLAR_EFFECT, static_cast<float>(magnitude));
				}

				auto summons_list = getPlayerCommandedActors();
				if (summons_list.empty()) {
					if (Util::randomDouble() < settings.oppSummonChance) {
						RE::SpellItem* conjure_atronach = StaticDataHolder::GetSingleton()->LookupForm<RE::SpellItem>(SUMMONER_SUMMON_SPELL, "Devious Curses.esp");
						//conjure_atronach->data.delivery = RE::MagicSystem::Delivery::kSelf;
						RE::MagicCaster* caster = player->GetMagicCaster(RE::MagicSystem::CastingSource::kOther);
						caster->CastSpellImmediate(conjure_atronach, false, player, 3.0f, false, 0.0f, nullptr);
						//conjure_atronach->data.delivery = RE::MagicSystem::Delivery::kTargetLocation;
						auto magic = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kMagicka);
						if (settings.oppSCollarDrainsMagicka) player->AsActorValueOwner()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kMagicka, -magic);
					}
				}
				else {
					if (settings.oppSMinSummonArousal > 0) {
						for (auto summon : summons_list) {
							if (GetActorArousal(summon) < settings.oppSMinSummonArousal) {
								SetArousal(summon, settings.oppSMinSummonArousal);
							}
						}
					}
				}
				if (magnitude <= 0) {
					if (GetItemCount(player, summoner_collar_key) == 0) {
						player->AddObjectToContainer((RE::TESBoundObject*)summoner_collar_key, nullptr, 1, nullptr);
						PlayerMessage("The Summoner Collar is now satisfied and you can unlock it!");
					}
				}
			}

			//Living Latex
			RE::TESObjectARMO* latex = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LIVING_LATEX, "Devious Curses.esp");
			RE::TESObjectARMO* latex_open = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LIVING_LATEX_OPEN, "Devious Curses.esp");
			
			bool isWearingLatex = ActorIsWearingDevice(player, latex) || ActorIsWearingDevice(player, latex_open);
			if (isWearingLatex) {
				int magnitude = static_cast<int>(GetEffectMagnitude(LIVING_LATEX_EFFECT));
				if (magnitude <= -10000) {
					magnitude = static_cast<int>(settings.oppLivingLatexStartTime * 60 * Util::randomFloat(0.9f, 1.2f));
				}

				if (magnitude >= 3) {
					SetEffectDescription(LIVING_LATEX_EFFECT, "The latex suit seems to be dormant.");
					magnitude -= ODEVICE_TICK;
					if (magnitude <= 2) {
						SetEffectDescription(LIVING_LATEX_EFFECT, "The latex suit seems to be dormant. Maybe it would do something if it was attacked.");
						magnitude = 3;
						if (player->IsInCombat()) {
							std::vector<std::string> skips;
							if (!settings.oppLivingLatexHeavy) {
								skips.push_back("zad_DeviousHeavyBondage");
							}
							DoStandardEvent(false, "", "(black & (ebonite | rubber)) | plugpumps", 20, skips);
							AIEventLivingLatexActivate();
							PlayerMessage("Suddenly the latex suit springs to life, covering you in ebonite! Is it trying to protect itself?");
							SetEffectDescription(LIVING_LATEX_EFFECT, "The latex has awoken! Maybe you can weaken it by shocking it.");
							magnitude = 2;
						}
					}
				}
				else if (magnitude == 2) {
					SetEffectDescription(LIVING_LATEX_EFFECT, "The latex has awoken! Maybe you can weaken it by shocking it.");
					if (settings.oppLivingLatexMore > 0.0f && counters.clock_GlobalTicker % static_cast<int>(settings.oppLivingLatexMore * 60) < ODEVICE_TICK) {
						std::vector<std::string> skips;
						if (!settings.oppLivingLatexHeavy) {
							skips.push_back("zad_DeviousHeavyBondage");
						}
						if (DoStandardEvent(false, "", "(black & (ebonite | rubber))", Util::randomInt(1, 2), skips)) {
							DBGNotification("The latex has spread over your body!");
						}
					}
				}
				else if (magnitude == 1) {
					if (GetWornDeviceCount(player) == 1 || !settings.oppLivingLatexRequireRem) {
						UnlockDevice(player, latex, nullptr, nullptr, true, false);
						UnlockDevice(player, latex_open, nullptr, nullptr, true, false);
						AIEventLivingLatexRemove();
						PlayerMessage("The latex suit dissolves from your body!");
					}
					else {
						SetEffectDescription(LIVING_LATEX_EFFECT, "The latex is clinging to you only by your other devices, removing them should do the trick!");
					}
				}

				SetEffectMagnitude(LIVING_LATEX_EFFECT, static_cast<float>(magnitude));
			}
		}
	}

	void OppOnSexEnd(RE::Actor* actor) {
		RE::TESObjectARMO* summoner_collar = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(SUMMONER_COLLAR, "Devious Curses.esp");
		if (getIsPlayerCommandedActor(actor) && ActorIsWearingDevice(RE::PlayerCharacter::GetSingleton(), summoner_collar)) {
			if (Util::GetFormEditorId(actor->GetActorBase()) == "DCurses_SummonAtronachFrost") {
				actor->KillImmediate();
			}
			if (GetEffectMagnitude(SUMMONER_COLLAR_EFFECT) >= 0) {
				ModifyEffectMagnitude(SUMMONER_COLLAR_EFFECT, -1.0);
			}
		}
	}
}