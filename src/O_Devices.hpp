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

	int RemoveDwarvenStuff() {
		auto player = RE::PlayerCharacter::GetSingleton();
		auto inventory = player->GetInventory();
		int value = 0;
		for (auto const& [k, v] : inventory) {
			if (k->GetFormType() == RE::FormType::Misc && Util::testFormComp("dwarven & (cog | gear | gyro | scrap | platemetal) & !ingot", k)) {
				value += k->GetGoldValue() * v.first;
				player->RemoveItem(k, v.first, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
			}
		}
		return value;
	}

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

		auto magic = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kMagicka);
		player->AsActorValueOwner()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kMagicka, -magic);

		AIEventSummonerCollarAdd();

		LockDevice(player, summoner_collar, true);
		if (!containerName.empty()) {
			//PlayerMessage(fmt::format("As you touch the {} you feel very dizzy as a heavy collar forms around your neck and absorbs your magicka!", containerName));
			PlayerMessage(Translator(Translation::ODeviceSummonerCollarStart, containerName));
		};
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

		auto stamina = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kStamina);
		player->AsActorValueOwner()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kStamina, -stamina / 2);

		AIEventLivingLatexAdd();

		if (settings.oppLivingLatexOpen) {
			LockDevice(player, latex_open, true);
		}
		else {
			LockDevice(player, latex, true);
		}
		
		if (!containerName.empty()) {
			//PlayerMessage(fmt::format("As you touch the {} a ball of goo jumps out at you and covers your body!", containerName));
			PlayerMessage(Translator(Translation::ODeviceLivingLatexStart, containerName));
		};
		return true;
	}

	bool OppDwarvenCuirassEvent(std::string containerName, bool skipLocation = false) {
		auto player = RE::PlayerCharacter::GetSingleton();

		if (settings.oppDwarvenRequireLoc && !skipLocation && !(player->GetCurrentLocation() && player->GetCurrentLocation()->HasKeywordString("LocTypeDwarvenAutomatons"))) {
			return false;
		}

		auto currentSuit = GetWornInventoryDeviceByKeyword(player, "zad_DeviousSuit");
		if (currentSuit && !DeviceInventoryIsGeneric(currentSuit)) {
			return false;
		}
		else {
			UnlockDevice(player, currentSuit);
		}

		auto currentHeavy = GetWornInventoryDeviceByKeyword(player, "zad_DeviousHeavyBondage");
		if (currentHeavy && !DeviceInventoryIsGeneric(currentHeavy)) {
			return false;
		}
		else {
			UnlockDevice(player, currentHeavy);
		}

		auto currentArmCuffs = GetWornInventoryDeviceByKeyword(player, "zad_DeviousArmCuffs");
		if (currentArmCuffs && !DeviceInventoryIsGeneric(currentArmCuffs)) {
			return false;
		}
		else {
			UnlockDevice(player, currentArmCuffs);
		}

		auto currentLegCuffs = GetWornInventoryDeviceByKeyword(player, "zad_DeviousLegCuffs");
		if (currentLegCuffs && !DeviceInventoryIsGeneric(currentLegCuffs)) {
			return false;
		}
		else {
			UnlockDevice(player, currentLegCuffs);
		}

		auto currentGloves = GetWornInventoryDeviceByKeyword(player, "zad_DeviousGloves");
		if (currentGloves && !DeviceInventoryIsGeneric(currentGloves)) {
			return false;
		}
		else {
			UnlockDevice(player, currentGloves);
		}

		auto currentBoots = GetWornInventoryDeviceByKeyword(player, "zad_DeviousBoots");
		if (currentBoots && !DeviceInventoryIsGeneric(currentBoots)) {
			return false;
		}
		else {
			UnlockDevice(player, currentBoots);
		}



		RE::TESObjectARMO* dwarven;
		if (settings.oppDwarvenHeavyRestraint) {
			dwarven = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DWARVEN_CURIAS_HEAVY, "Devious Curses.esp");
		}
		else {
			dwarven = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DWARVEN_CURIAS, "Devious Curses.esp");
		}

		AIEventDwarvenCuirassAdd();
		RemoveDwarvenStuff();

		Util::ExecuteWithDelay(1500ms, [player, dwarven] {
			LockDevice(player, dwarven, true);
		});

		if (!containerName.empty()) {
			PlayerMessage(Translator(Translation::ODeviceDwarvenCuirassStart, containerName));
		};
		return true;
	}

	bool DoOppDeviceEvent(std::string containerName) {

		std::vector<std::pair<bool (*)(std::string), double>> events;
		events.push_back(std::make_pair(OppSummonerCollarEvent, settings.oppSummonerCollarWeight));
		events.push_back(std::make_pair(OppLivingLatexEvent, settings.oppLivingLatexWeight));
		auto _OppDwarvenCuirassEvent = [](std::string s) {return OppDwarvenCuirassEvent(s); };
		events.push_back(std::make_pair(_OppDwarvenCuirassEvent, settings.oppDwarvenCuirassWeight));

		double sum = std::accumulate(events.begin(), events.end(), 0.0, [](double acc, std::pair<bool (*)(std::string), double> x) {return acc + x.second; });
		if (sum == 0) {
			return false;
		}

		Util::ShuffleVector(events);

		while (!events.empty()) {
			auto pair = Util::VectorSelectWeighted(events);
			if (pair.first(containerName)) {
				counters.clock_GlobalTicker -= counters.clock_GlobalTicker % ODEVICE_TICK;
				return true;
			}
			events.erase(std::remove(events.begin(), events.end(), pair), events.end());
		}
		return false;
	}

	void OppDeviceOnMagicHitEvent(const RE::TESMagicEffectApplyEvent* magicEvent) {
		auto player = RE::PlayerCharacter::GetSingleton();

		//Living Latex
		auto effect = RE::TESForm::LookupByID(magicEvent->magicEffect)->As<RE::EffectSetting>();
		if (effect &&
			magicEvent->target.get() == player &&
			(effect->HasArchetype(RE::EffectSetting::Archetype::kValueModifier) || effect->HasArchetype(RE::EffectSetting::Archetype::kDualValueModifier)) &&
			effect->IsDetrimental() &&
			(effect->data.primaryAV == RE::ActorValue::kHealth || effect->data.secondaryAV == RE::ActorValue::kHealth)) {
			if (effect->data.resistVariable == RE::ActorValue::kResistShock || Util::FormEditorIdContains(effect, "traprunelightning")) {
				RE::TESObjectARMO* latex = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LIVING_LATEX, "Devious Curses.esp");
				RE::TESObjectARMO* latex_open = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LIVING_LATEX_OPEN, "Devious Curses.esp");
				bool isWearingLatex = ActorIsWearingDevice(player, latex) || ActorIsWearingDevice(player, latex_open);
				if (isWearingLatex && oppdCounters.livingLatexCounter == 2) {
					std::vector<std::string> skips;
					if (!settings.oppLivingLatexHeavy) {
						skips.push_back("zad_DeviousHeavyBondage");
					}
					DoStandardEvent(false, "", "(black & (ebonite | rubber))", 4, skips);
					//PlayerMessage("The latex writhes while being shocked. It seems as if it has been weakened significantly!");
					PlayerMessage(Translator(Translation::ODeviceLivingLatexOnHit));
					oppdCounters.livingLatexCounter = 1;
					//SetEffectDescription(LIVING_LATEX_EFFECT, "The latex is clinging to you only by your other devices, removing them should do the trick!");
					SetEffectDescription(LIVING_LATEX_EFFECT, Translator(Translation::EffectLivingLatexCling));
				}
			}
		}
	}

	void OppDeviceUpdate() {
		if (counters.clock_GlobalTicker % ODEVICE_TICK == 0) {
			auto player = RE::PlayerCharacter::GetSingleton();

			RE::TESObjectARMO* summoner_collar = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(SUMMONER_COLLAR, "Devious Curses.esp");
			RE::TESObjectARMO* summoner_collar_r = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(SUMMONER_COLLAR, "Devious Curses.esp");
			RE::TESKey* summoner_collar_key = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(SUMMONER_COLLAR_KEY, "Devious Curses.esp");
			RE::TESObjectARMO* latex = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LIVING_LATEX, "Devious Curses.esp");
			RE::TESObjectARMO* latex_r = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LIVING_LATEX, "Devious Curses.esp");
			RE::TESObjectARMO* latex_open = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LIVING_LATEX_OPEN, "Devious Curses.esp");
			RE::TESObjectARMO* latex_open_r = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LIVING_LATEX_OPEN, "Devious Curses.esp");
			RE::TESObjectARMO* dwarven_cuirass = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DWARVEN_CURIAS, "Devious Curses.esp");
			RE::TESObjectARMO* dwarven_cuirass_r = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DWARVEN_CURIAS, "Devious Curses.esp");
			RE::TESObjectARMO* dwarven_heavy = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DWARVEN_CURIAS_HEAVY, "Devious Curses.esp");
			RE::TESObjectARMO* dwarven_heavy_r = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DWARVEN_CURIAS_HEAVY, "Devious Curses.esp");

			bool isWearingSummonerCollar = false;
			bool isWearingLatex = false;
			bool isWearingDwarven = false;

			auto playerInventory = player->GetInventory();
			for (auto const& [k, v] : playerInventory) {
				RE::TESObjectARMO* armor = k->As<RE::TESObjectARMO>();
				if (armor) {
					if (armor == summoner_collar || armor == summoner_collar_r) {
						isWearingSummonerCollar = true;
					}
					if (armor == latex || armor == latex_r || armor == latex_open || armor == latex_open_r) {
						isWearingLatex = true;
					}
					if (armor == dwarven_cuirass || armor == dwarven_cuirass_r || armor == dwarven_heavy || armor == dwarven_heavy_r) {
						isWearingDwarven = true;
					}
				}
			}

			if (isWearingSummonerCollar && oppdCounters.summonCollarCounter == INT64_MIN) {
				log::trace("Reseting summoner collar counter.");
				oppdCounters.summonCollarCounter = settings.oppSummonerSexCount;
			}
			else if (!isWearingSummonerCollar) {
				oppdCounters.summonCollarCounter = INT64_MIN;
			}

			if (isWearingLatex && oppdCounters.livingLatexCounter == INT64_MIN) {
				log::trace("Reseting living latex counter.");
				oppdCounters.livingLatexCounter = static_cast<int>(settings.oppLivingLatexStartTime * 60 * Util::randomFloat(0.9f, 1.2f));
			}
			else if (!isWearingLatex) {
				oppdCounters.livingLatexCounter = INT64_MIN;
			}

			if (isWearingDwarven && oppdCounters.dwarvenCuirassCounter == INT64_MIN) {
				log::trace("Reseting dwarven cuirass counter.");
				oppdCounters.dwarvenCuirassCounter = settings.oppDwarvenValueNeeded;
				RemoveDwarvenStuff();
			}
			else if (!isWearingDwarven) {
				oppdCounters.dwarvenCuirassCounter = INT64_MIN;
			}

			//Summoner Collar
			if (isWearingSummonerCollar) {
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
				if (oppdCounters.summonCollarCounter <= 0) {
					if (GetItemCount(player, summoner_collar_key) == 0) {
						player->AddObjectToContainer((RE::TESBoundObject*)summoner_collar_key, nullptr, 1, nullptr);
						//PlayerMessage("The Summoner Collar is now satisfied and you can unlock it!");
						PlayerMessage(Translator(Translation::ODeviceSummonerCollarUnlock));
					}
				}
				SetEffectMagnitude(SUMMONER_COLLAR_EFFECT, static_cast<float>(oppdCounters.summonCollarCounter));
			}

			//Living Latex
			
			if (isWearingLatex) {
				if (oppdCounters.livingLatexCounter >= 3) {
					//SetEffectDescription(LIVING_LATEX_EFFECT, "The latex suit seems to be dormant.");
					SetEffectDescription(LIVING_LATEX_EFFECT, Translator(Translation::EffectLivingLatexDormant));
					oppdCounters.livingLatexCounter -= ODEVICE_TICK;
					if (oppdCounters.livingLatexCounter <= 2) {
						//SetEffectDescription(LIVING_LATEX_EFFECT, "The latex suit seems to be dormant. Maybe it would do something if it was attacked.");
						SetEffectDescription(LIVING_LATEX_EFFECT, Translator(Translation::EffectLivingLatexDormant));
						oppdCounters.livingLatexCounter = 3;
						if (player->IsInCombat()) {
							std::vector<std::string> skips;
							if (!settings.oppLivingLatexHeavy) {
								skips.push_back("zad_DeviousHeavyBondage");
							}
							DoStandardEvent(false, "", "(black & (ebonite | rubber)) | plugpumps", 20, skips);
							AIEventLivingLatexActivate();
							//PlayerMessage("Suddenly the latex suit springs to life, covering you in ebonite! Is it trying to protect itself?");
							PlayerMessage(Translator(Translation::ODeviceSummonerCollarUnlock));
							//SetEffectDescription(LIVING_LATEX_EFFECT, "The latex has awoken! Maybe you can weaken it by shocking it.");
							SetEffectDescription(LIVING_LATEX_EFFECT, Translator(Translation::EffectLivingLatexDormant));
							oppdCounters.livingLatexCounter = 2;
						}
					}
				}
				else if (oppdCounters.livingLatexCounter == 2) {
					//SetEffectDescription(LIVING_LATEX_EFFECT, "The latex has awoken! Maybe you can weaken it by shocking it.");
					SetEffectDescription(LIVING_LATEX_EFFECT, Translator(Translation::EffectLivingLatexAwoken));
					if (settings.oppLivingLatexMore > 0.0f && counters.clock_GlobalTicker % static_cast<int>(settings.oppLivingLatexMore * 60) < ODEVICE_TICK) {
						std::vector<std::string> skips;
						if (!settings.oppLivingLatexHeavy) {
							skips.push_back("zad_DeviousHeavyBondage");
						}
						if (DoStandardEvent(false, "", "(black & (ebonite | rubber))", Util::randomInt(1, 2), skips)) {
							//DBGNotification("The latex has spread over your body!");
							PlayerMessage(Translator(Translation::ODeviceLivingLatexSpread));
						}
					}
				}
				else if (oppdCounters.livingLatexCounter <= 1) {
					if (GetWornDeviceCount(player) == 1 || !settings.oppLivingLatexRequireRem) {
						UnlockDevice(player, latex, nullptr, nullptr, true, false);
						UnlockDevice(player, latex_open, nullptr, nullptr, true, false);
						AIEventLivingLatexRemove();
						//PlayerMessage("The latex suit dissolves from your body!");
						PlayerMessage(Translator(Translation::ODeviceLivingLatexRemove));
					}
					else {
						//SetEffectDescription(LIVING_LATEX_EFFECT, "The latex is clinging to you only by your other devices, removing them should do the trick!");
						SetEffectDescription(LIVING_LATEX_EFFECT, Translator(Translation::EffectLivingLatexCling));
					}
				}
			}

			//Dwarven Cuirass
			
			if (isWearingDwarven) {
				float playerArousal = GetActorArousal(player);
				RE::TESObjectARMO* belt = nullptr;
				RE::TESObjectARMO* piercingN = nullptr;
				RE::TESObjectARMO* piercingV = nullptr;
				RE::TESObjectARMO* plugA = nullptr;
				RE::TESObjectARMO* plugV = nullptr;
				RE::TESObjectARMO* collar = nullptr;
				for (auto const& [k, v] : playerInventory) {
					if (v.second.get()->IsWorn()) {
						RE::TESObjectARMO* wornArmor = k->As<RE::TESObjectARMO>();
						if (!wornArmor) {
							continue;
						}
						RE::TESObjectARMO* rend = DeviousDevicesAPI::g_API->GetDeviceRender(wornArmor);
						if (!rend) {
							continue;
						}
						for (std::string kw : GetDeviceKeywords(rend, false)) {
							//log::trace("kw: {}", kw);
							if (kw == "zad_DeviousBelt") {
								belt = wornArmor;
							}
							else if (kw == "zad_DeviousPiercingsNipple") {
								piercingN = wornArmor;
							}
							else if (kw == "zad_DeviousPiercingsVaginal") {
								piercingV = wornArmor;
							}
							else if (kw == "zad_DeviousPlugAnal") {
								plugA = wornArmor;
							}
							else if (kw == "zad_DeviousPlugVaginal") {
								plugV = wornArmor;
							}
							else if (kw == "zad_DeviousCollar") {
								collar = wornArmor;
							}
						}
					}
				}
				
				if (belt && DeviceInventoryIsGeneric(belt) && Util::randomDouble() <= 10) {
					UnlockDevice(player, belt, nullptr, nullptr, true);
					PlayerMessage(Translator(Translation::ODeviceDwarvenCuirassDestroyBelt));
				}
				else if (!belt && playerArousal > settings.oppDwarvenArousal && counters.clock_lastSex > 45 && (GetDeviceMask(player) & 0b0010) != 0 && Util::randomDouble() <= 10) {
					Util::ExecuteWithDelay(500ms, [player] {
						StartMasturbation(player);
					});
					PlayerMessage(Translator(Translation::ODeviceDwarvenCuirassMasturbate));
				}
				else if (oppdCounters.dwarvenCuirassCounter <= settings.oppDwarvenValueNeeded / 2 && !(piercingN && piercingV && plugA && plugV && collar) && Util::randomDouble() <= 10) {
					DeviceList* deviceList;
					std::vector<std::pair<DeviceList*, double>> list;
					if (!piercingN) { list.push_back({ &devices.piercingsN, 10.0 }); }
					if (!piercingV) { list.push_back({ &devices.piercingsV, 10.0 }); }
					if (!plugA) { list.push_back({ &devices.plugsA, 30.0 }); }
					if (!plugV) { list.push_back({ &devices.plugsV, 30.0 }); }
					if (!collar) {
						auto collars = GetAdjustedDeviceList(&devices.collars, {}, "metal | steel | rust | lustr");
						list.push_back({ &collars, 20.0 });
					}
					deviceList = Util::VectorSelectWeighted(list).first;
					
					auto device = GetRandomDevice(deviceList);
					if (device.has_value()) {
						LockDevice(player, device->inv);

						oppdCounters.dwarvenCuirassCounter += Util::randomInt(4,20);
						PlayerMessage(Translator(Translation::ODeviceDwarvenCuirassCraft, device->inv->GetName()));
					}
				}
				else {
					if (Util::randomDouble() <= 15) {
						int value = RemoveDwarvenStuff();
						if (value > 0) {
							oppdCounters.dwarvenCuirassCounter -= value;
							DBGNotification(Translator(Translation::ODeviceDwarvenCuirassEat));
						}
					}
					else if (oppdCounters.dwarvenCuirassCounter <= 0) {
						RE::TESNPC* thing = nullptr;
						auto level = player->GetLevel();
						if (level >= 50) {
							std::vector<std::pair<RE::TESNPC*, double>> list;
							list.push_back({ StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x10ec8e, "Skyrim.esm"), 10.0 }); //Sphere Master
							list.push_back({ StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x10e753, "Skyrim.esm"), 20.0 }); //Centurion Guardian
							list.push_back({ StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x23a96, "Skyrim.esm"), 30.0 }); //Centurion Guardian
							thing = Util::VectorSelectWeighted(list).first;
						}
						else if (level >= 38) {
							std::vector<std::pair<RE::TESNPC*, double>> list;
							list.push_back({ StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x23a97, "Skyrim.esm"), 10.0 }); //Sphere Guardian
							list.push_back({ StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x10f9b9, "Skyrim.esm"), 10.0 }); //Centurion
							list.push_back({ StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x10ec8e, "Skyrim.esm"), 30.0 }); //Sphere Master
							list.push_back({ StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x10e753, "Skyrim.esm"), 30.0 }); //Centurion Guardian
							thing = Util::VectorSelectWeighted(list).first;
						}
						else if (level >= 30) {
							std::vector<std::pair<RE::TESNPC*, double>> list;
							list.push_back({ StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x10ec89, "Skyrim.esm"), 10.0 }); //Sphere
							list.push_back({ StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x10ec87, "Skyrim.esm"), 10.0 }); //Spider Guardian
							list.push_back({ StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x23a97, "Skyrim.esm"), 30.0 }); //Sphere Guardian
							list.push_back({ StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x10f9b9, "Skyrim.esm"), 30.0 }); //Centurion
							thing = Util::VectorSelectWeighted(list).first;
						}
						else if (level >= 24) {
							std::vector<std::pair<RE::TESNPC*, double>> list;
							list.push_back({ StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x23a98, "Skyrim.esm"), 10.0 }); //Spider
							list.push_back({ StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x10ec89, "Skyrim.esm"), 30.0 }); //Sphere
							list.push_back({ StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x10ec87, "Skyrim.esm"), 30.0 }); //Spider Guardian
							thing = Util::VectorSelectWeighted(list).first;
						}
						else if (level >= 16) {
							std::vector<std::pair<RE::TESNPC*, double>> list;
							list.push_back({ StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x10ec86, "Skyrim.esm"), 10.0 }); //Spider Worker
							list.push_back({ StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x23a98, "Skyrim.esm"), 20.0 }); //Spider
							thing = Util::VectorSelectWeighted(list).first;
						}
						else {
							thing = StaticDataHolder::GetSingleton()->LookupForm<RE::TESNPC>(0x10ec86, "Skyrim.esm"); //Spider Worker
						}

						Util::ExecuteWithDelay(1000ms, [player, thing] {
							player->PlaceObjectAtMe(thing, false);
						});

						PlayerMessage(Translator(Translation::ODeviceDwarvenCuirassRemove, thing->GetName()));

						UnlockDevice(player, dwarven_cuirass, nullptr, nullptr, true, false);
						UnlockDevice(player, dwarven_heavy, nullptr, nullptr, true, false);
					}
				}
				SetEffectMagnitude(DWARVEN_CUIRASS_EFFECT, static_cast<float>(oppdCounters.dwarvenCuirassCounter));
			}
		}
	}

	void OppOnSexEnd(RE::Actor* actor) {
		RE::TESObjectARMO* summoner_collar = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(SUMMONER_COLLAR, "Devious Curses.esp");
		if (getIsPlayerCommandedActor(actor) && ActorIsWearingDevice(RE::PlayerCharacter::GetSingleton(), summoner_collar)) {
			if (Util::GetFormEditorId(actor->GetActorBase()) == "DCurses_SummonAtronachFrost") {
				actor->KillImmediate();
			}
			if (oppdCounters.summonCollarCounter >= 0) {
				oppdCounters.summonCollarCounter -= 1;
				SetEffectMagnitude(SUMMONER_COLLAR_EFFECT, static_cast<float>(oppdCounters.summonCollarCounter));
			}
		}
	}
}