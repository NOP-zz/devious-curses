#pragma once

#include "jcontainers.hpp"
#include "Settings.hpp"
#include "MGEF_Controller.hpp"
#include "MinAI.hpp"
#include "sex.hpp"

#include "../include/SlaveTatsNG_Interface.h"

using namespace SKSE;

namespace slavetats_ng {
	const SlaveTatsNG::Addresses* iface = nullptr;

	void messaging_hook(SKSE::MessagingInterface::Message* a_msg)
	{
		if (a_msg && a_msg->type == SlaveTatsNG::MessageType::Interface) {
			iface = SlaveTatsNG::Addresses::from_void(a_msg->data);
			log::info("SlaveTatsNG Interface found: address = {}", (void*)iface);
		}
	}

	inline bool query_available_tattoos(int a_template, int matches, int applied = 0, RE::BSFixedString domain = "default") {
		if (!iface) return true;
		return iface->query_available_tattoos(a_template, matches, applied, domain);
	}
	inline bool query_applied_tattoos(RE::Actor* target, int a_template, int matches, RE::BSFixedString except_area = "", int except_slot = -1) {
		if (!iface) return true;
		return iface->query_applied_tattoos(target, a_template, matches, except_area, except_slot);
	}
	inline bool simple_remove_tattoo(RE::Actor* target, RE::BSFixedString section, RE::BSFixedString name, bool last = true, bool silent = false) {
		if (!iface) return true;
		return iface->simple_remove_tattoo(target, section, name, last, silent);
	}
	inline bool remove_tattoos(RE::Actor* target, int a_template, bool ignore_lock = false, bool silent = false) {
		if (!iface) return true;
		return iface->remove_tattoos(target, a_template, ignore_lock, silent);
	}
	inline bool add_tattoo(RE::Actor* target, int tattoo, int slot = -1, bool ignore_lock = false, bool silent = false) {
		if (!iface) return true;
		return iface->add_tattoo(target, tattoo, slot, ignore_lock, silent);
	}
	inline bool synchronize_tattoos(RE::Actor* target, bool silent = false) {
		if (!iface) return true;
		return iface->synchronize_tattoos(target, silent);
	}
}

namespace DCURSES {
	enum class MARK : int64_t {
		TAT_NONE = 0,
		TAT_HEAT = 11,
		TAT_ALLURE = 13,
		TAT_BONDAGE = 71,
		TAT_BRANDING = 74,
		TAT_HEALSLUT = 76,
		TAT_NUDITY = 79,
	};

	int GetTattooCount(RE::Actor* actor) {
		if (!actor) return 0;
		if (!slavetats_ng::iface) return 0;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return 0;

		using namespace jcontainers;

		int a_template = JValue::addToPool(JMap::object(), "DCURSES");
		int matches = JValue::addToPool(JArray::object(), "DCURSES");

		JArray::clear(matches);

		if (slavetats_ng::query_applied_tattoos(actor, a_template, matches)) {
			JValue::cleanPool("DCURSES");
			return -1;
		}

		return JArray::count(matches);
	}

	bool CheckLewdMarksInstalled() {
		if (!slavetats_ng::iface) return false;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return false;

		using namespace jcontainers;

		int a_template = JValue::addToPool(JMap::object(), "DCURSES");
		int matches = JValue::addToPool(JArray::object(), "DCURSES");

		JMap::setStr(a_template, "section", "LewdMarks");

		if (slavetats_ng::query_available_tattoos(a_template, matches)) {
			JValue::cleanPool("DCURSES");
			return false;
		}

		if (JArray::count(matches) == 0) {
			JValue::cleanPool("DCURSES");
			return false;
		}

		JValue::cleanPool("DCURSES");
		return true;
	}

	MARK GetLewdMark() {
		return static_cast<MARK>(counters.ActiveLewdMark);
	}

	int GetColorForMark(MARK mark) {
		switch (mark) {
		case MARK::TAT_NONE:
			return 0;
		case MARK::TAT_ALLURE:
			return settings.LMAllureColor;
		case MARK::TAT_HEAT:
			return settings.LMHeatColor;
		case MARK::TAT_BONDAGE:
			return settings.LMBondageColor;
		case MARK::TAT_NUDITY:
			return settings.LMNudityColor;
		case MARK::TAT_BRANDING:
			return settings.LMBrandingColor;
		case MARK::TAT_HEALSLUT:
			return settings.LMHealslutColor;
		}
		return 0;
	}

	void DecrementCounterForMark(MARK mark) {
		if (mark == GetLewdMark()) {
			switch (mark) {
			case MARK::TAT_NONE:
				log::warn("Decrementing counter for NONE mark.");
				break;
			case MARK::TAT_ALLURE:
				ModifyEffectMagnitude(ALLURE_EFFECT, -1);
				log::info("Decrementing counter for Allure mark.");
				break;
			case MARK::TAT_HEAT:
				ModifyEffectMagnitude(HEAT_EFFECT, -1);
				log::info("Decrementing counter for Heat mark.");
				break;
			case MARK::TAT_BONDAGE:
				ModifyEffectMagnitude(BONDAGE_EFFECT, -1);
				log::info("Decrementing counter for Bondage mark.");
				break;
			case MARK::TAT_NUDITY:
				ModifyEffectMagnitude(NUDITY_EFFECT, -1);
				log::info("Decrementing counter for Nudity mark.");
				break;
			case MARK::TAT_HEALSLUT:
				log::warn("Decrementing counter for Healslut mark.");
				break;
			case MARK::TAT_BRANDING:
				log::warn("Decrementing counter for Branding mark.");
				break;
			}
		}
	}

	void SetDefaultEffectMagnitudeForMark(MARK mark, double multiplier = 1.0) {
		switch (mark) {
		case MARK::TAT_ALLURE:
			SetEffectMagnitude(ALLURE_EFFECT, static_cast<float>(settings.LMAllureSex * Util::randomDouble(0.8, 1.2) * multiplier));
			break;
		case MARK::TAT_HEAT:
			SetEffectMagnitude(HEAT_EFFECT, static_cast<float>(settings.LMHeatContainerCount * Util::randomDouble(0.8, 1.2) * multiplier));
			break;
		case MARK::TAT_BONDAGE:
			SetEffectMagnitude(BONDAGE_EFFECT, static_cast<float>(settings.LMBondageDeviceCount * Util::randomDouble(0.8, 1.2) * multiplier));
			break;
		case MARK::TAT_NUDITY:
			SetEffectMagnitude(NUDITY_EFFECT, static_cast<float>(settings.LMNudityTalkTimes * Util::randomDouble(0.8, 1.2) * multiplier));
			break;
		case MARK::TAT_HEALSLUT:
			SetEffectMagnitude(HEALSLUT_EFFECT, static_cast<float>(settings.LMHealslutHealing * Util::randomDouble(0.8, 1.2) * multiplier));
			break;
		case MARK::TAT_BRANDING:
			SetEffectMagnitude(BRANDING_EFFECT, static_cast<float>(GetTattooCount(RE::PlayerCharacter::GetSingleton())));
			break;
		}
	}

	bool _AddLewdMarkGlow(int index, int32_t color, int32_t glow) {
		auto actor = RE::PlayerCharacter::GetSingleton();

		using namespace jcontainers;
		std::string mark = fmt::format("{:03}", index);
		log::trace("adding tattoo glow {}", mark);
		int a_template = JValue::addToPool(JMap::object(), "DCURSES");
		int matches = JValue::addToPool(JArray::object(), "DCURSES");
		int tattoo = 0;

		JMap::setStr(a_template, "section", "LewdMarks-glow");
		JMap::setStr(a_template, "name", mark);

		if (slavetats_ng::query_available_tattoos(a_template, matches)) {
			log::warn("JContainers error query_available_tattoos");
			JValue::cleanPool("DCURSES");
			return false;
		}

		if (JArray::count(matches) == 0) {
			JValue::cleanPool("DCURSES");
			log::warn("JContainers error count available");
			return false;
		}

		tattoo = JValue::addToPool(JArray::getObj(matches, 0), "DCURSES");
		JMap::setInt(tattoo, "color", color);
		JMap::setInt(tattoo, "glow", glow);
		//JMap::setInt(tattoo, "locked", 1);
		JMap::setFlt(tattoo, "invertedAlpha", 0.0f);

		JArray::clear(matches);

		if (slavetats_ng::query_applied_tattoos(actor, a_template, matches)) {
			JValue::cleanPool("DCURSES");
			log::warn("JContainers error query_applied_tattoos");
			return false;
		}

		if (JArray::count(matches) > 0) {
			JValue::cleanPool("DCURSES");
			log::warn("JContainers error count");
			return false;
		}

		if (slavetats_ng::add_tattoo(actor, tattoo, -1, false, true)) {
			JValue::cleanPool("DCURSES");
			log::warn("JContainers error add_tattoo");
			return false;
		}

		JValue::cleanPool("DCURSES");
		return true;
	}

	bool _AddLewdMarkMain(int index, int32_t color, int32_t glow) {
		auto actor = RE::PlayerCharacter::GetSingleton();

		using namespace jcontainers;
		std::string mark = fmt::format("{:03}", index);
		log::trace("adding tattoo {}", mark);
		int a_template = JValue::addToPool(JMap::object(), "DCURSES");
		int matches = JValue::addToPool(JArray::object(), "DCURSES");
		int tattoo = 0;

		JMap::setStr(a_template, "section", "LewdMarks");
		JMap::setStr(a_template, "name", mark);

		if (slavetats_ng::query_available_tattoos(a_template, matches)) {
			JValue::cleanPool("DCURSES");
			log::warn("JContainers error query_available_tattoos");
			return false;
		}

		tattoo = JValue::addToPool(JArray::getObj(matches, 0), "DCURSES");
		JMap::setInt(tattoo, "color", color);
		JMap::setInt(tattoo, "glow", glow);
		//JMap::setInt(tattoo, "locked", 1);
		JMap::setFlt(tattoo, "invertedAlpha", 0.0f);

		JArray::clear(matches);

		if (slavetats_ng::query_applied_tattoos(actor, a_template, matches)) {
			JValue::cleanPool("DCURSES");
			log::warn("JContainers error query_applied_tattoos");
			return false;
		}

		if (JArray::count(matches) > 0) {
			JValue::cleanPool("DCURSES");
			log::warn("JContainers error count");
			return false;
		}

		if (slavetats_ng::add_tattoo(actor, tattoo, -1, false, true)) {
			JValue::cleanPool("DCURSES");
			log::warn("JContainers error add_tattoo");
			return false;
		}

		if (slavetats_ng::synchronize_tattoos(actor, true)) {
			log::warn("JContainers error synchronize_tattoos");
			JValue::cleanPool("DCURSES");
			return false;
		}

		JValue::cleanPool("DCURSES");
		return true;
	}

	int GetLewdMarkApplied() {
		if (!slavetats_ng::iface) return 0;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return 0;

		auto actor = RE::PlayerCharacter::GetSingleton();

		using namespace jcontainers;

		int a_template = JValue::addToPool(JMap::object(), "DCURSES");
		int matches = JValue::addToPool(JArray::object(), "DCURSES");

		JMap::setStr(a_template, "section", "LewdMarks");

		JArray::clear(matches);

		if (slavetats_ng::query_applied_tattoos(actor, a_template, matches)) {
			JValue::cleanPool("DCURSES");
			return 0;
		}

		if (JArray::count(matches) > 0) {
			JValue::cleanPool("DCURSES");
			return std::stoi(JMap::getStr(JArray::getObj(matches, 0), "name").c_str());
		}

		JValue::cleanPool("DCURSES");
		return 0;
	}

	bool AddLewdMark(MARK mark) {
		if (!slavetats_ng::iface) return false;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return false;
		if (!CheckLewdMarksInstalled()) return false;
		
		int index = static_cast<int>(mark);

		auto base_color = GetColorForMark(mark);
		auto glowColor = Util::ColorScale(base_color, 0.8);

		if (_AddLewdMarkGlow(index, glowColor, glowColor) && _AddLewdMarkMain(index, base_color, glowColor)) {
			counters.ActiveLewdMark = index;
			return true;
		}
		return false;
		
	}

	void RemoveLewdMark(int64_t index = -1) {
		if (!slavetats_ng::iface) return;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return;
		if (!CheckLewdMarksInstalled()) return;

		auto actor = RE::PlayerCharacter::GetSingleton();

		if (index == -1) {
			index = static_cast<int64_t>(GetLewdMark());
		}

		counters.ActiveLewdMark = 0;

		slavetats_ng::simple_remove_tattoo(actor, "LewdMarks", fmt::format("{:03}", index), true);
		slavetats_ng::simple_remove_tattoo(actor, "LewdMarks-glow", fmt::format("{:03}", index), true);
	}

	void RemoveAllTattoos(RE::Actor* actor) {
		if (!actor) return;
		if (!slavetats_ng::iface) return;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return;

		using namespace jcontainers;
		int a_template = JValue::addToPool(JMap::object(), "DCURSES");
		slavetats_ng::remove_tattoos(actor, a_template);
		slavetats_ng::synchronize_tattoos(actor, true);
		JValue::cleanPool("DCURSES");
		if (actor == RE::PlayerCharacter::GetSingleton()) {
			RemoveLewdMark();
			AIContextRemoveLewdMark();
		}
	}

	void TatsUpdateContext(MARK mark) {
		switch (mark) {
		case MARK::TAT_NONE:
			AIContextRemoveLewdMark();
			break;
		case MARK::TAT_ALLURE:
			AIContextAddAllureMark();
			break;
		case MARK::TAT_HEAT:
			AIContextAddHeatMark();
			break;
		case MARK::TAT_NUDITY:
			AIContextAddNudityMark();
			break;
		case MARK::TAT_BONDAGE:
			AIContextAddBondageMark();
			break;
		case MARK::TAT_BRANDING:
			AIContextAddBrandingMark();
			break;
		}
	}

	bool SexActorFilter(RE::Actor*);

	RE::TESSpellCastEvent healslutSpellBuffer;

	void TatsOnMagicHitEvent(const RE::TESMagicEffectApplyEvent* magicEvent) {
		auto player = RE::PlayerCharacter::GetSingleton();

		//Healslut
		auto mark = GetLewdMark();
		if (mark == MARK::TAT_HEALSLUT && magicEvent->caster && magicEvent->target) {
			auto effect = RE::TESForm::LookupByID(magicEvent->magicEffect)->As<RE::EffectSetting>();
			auto caster = magicEvent->caster->As<RE::Actor>();
			auto target = magicEvent->target->As<RE::Actor>();

			if (effect && caster && target && caster == player && target->IsPlayerTeammate() && effect->data.associatedSkill == RE::ActorValue::kRestoration && !effect->IsDetrimental() && (effect->data.primaryAV == RE::ActorValue::kHealth || effect->data.secondaryAV == RE::ActorValue::kHealth)) {
				Util::ExecuteWithDelay(100ms, [player, effect, target] {
					auto scriptManager = ScriptingManager();
					auto spellEvent = healslutSpellBuffer;
					auto actor = spellEvent.object->As<RE::Actor>();
					auto spell = RE::TESForm::LookupByID(spellEvent.spell)->As<RE::SpellItem>();
					if (actor && spell && actor == player) {
						for (auto spellEffect : spell->effects) {
							if (spellEffect && spellEffect->baseEffect == effect) {
								float mag = spellEffect->GetMagnitude() * (effect->data.castingType == RE::MagicSystem::CastingType::kConcentration ? 0.5f : 1.0f);
								ModifyEffectMagnitude(HEALSLUT_EFFECT, -spellEffect->GetMagnitude());
								log::trace("Restoration cast on follower: {} healed", mag);
								auto arousal = scriptManager.GetArousal(target);
								if (settings.sexEnabled && arousal >= 99 && SexActorFilter(target)) {
									scriptManager.StartSex(target, false);
								}
								else {
									scriptManager.ModifyArousal(target, mag / 10);
								}
								break;
							}
						}
					}
				});
			}
		}
	}

	void TatsOnSpellCast(const RE::TESSpellCastEvent* spellEvent) {
		auto player = RE::PlayerCharacter::GetSingleton();
		auto mark = GetLewdMark();
		auto actor = spellEvent->object->As<RE::Actor>();
		auto spell = RE::TESForm::LookupByID(spellEvent->spell)->As<RE::SpellItem>();
		if (mark == MARK::TAT_HEALSLUT && actor && spell && actor == player) {
			log::trace("Pushing spell to buffer");
			healslutSpellBuffer = *spellEvent;
		}
	}

	void TatsOnSexEnd(RE::Actor* actor) {
		auto mark = GetLewdMark();
		DecrementCounterForMark(MARK::TAT_ALLURE);
		if (mark == MARK::TAT_HEALSLUT && actor->IsPlayerTeammate() && !actor->IsCommandedActor()) {
			log::trace("Casting magicka spell");
			auto player = RE::PlayerCharacter::GetSingleton();
			RE::SpellItem* restoration = StaticDataHolder::GetSingleton()->LookupForm<RE::SpellItem>(HEALSLUT_RESTORATION_SPELL, "Devious Curses.esp");
			RE::MagicCaster* caster = player->GetMagicCaster(RE::MagicSystem::CastingSource::kOther);
			caster->CastSpellImmediate(restoration, false, player, 1.0f, false, 0.0f, nullptr);
		}
	}

	bool DoTattooEvent(RE::Actor*, std::string, int, bool);

	void TatsUpdate() {
		auto mark = GetLewdMark();
		auto index = static_cast<int64_t>(mark);
		auto applied = GetLewdMarkApplied();

		if (applied != index) {
			log::trace("Resolving mark discrepancy, expected {}, had {}", index, applied);
			if (mark == MARK::TAT_NONE) {
				RemoveLewdMark(applied);
			}
			else if (applied > 0) {
				RemoveLewdMark(applied);
				AddLewdMark(mark);
			}
			else {
				AddLewdMark(mark);
			}
		}

		SetEffectVisible(ALLURE_EFFECT, false);
		SetEffectVisible(HEAT_EFFECT, false);
		SetEffectVisible(NUDITY_EFFECT, false);
		SetEffectVisible(BONDAGE_EFFECT, false);
		SetEffectVisible(BRANDING_EFFECT, false);
		SetEffectVisible(HEALSLUT_EFFECT, false);

		switch (mark) {
		case MARK::TAT_NONE:
			break;
		case MARK::TAT_ALLURE:
			SetEffectVisible(ALLURE_EFFECT);
			break;
		case MARK::TAT_HEAT:
			SetEffectVisible(HEAT_EFFECT);
			break;
		case MARK::TAT_NUDITY:
			SetEffectVisible(NUDITY_EFFECT);
			break;
		case MARK::TAT_BONDAGE:
			SetEffectVisible(BONDAGE_EFFECT);
			break;
		case MARK::TAT_BRANDING:
			SetEffectVisible(BRANDING_EFFECT);
			break;
		case MARK::TAT_HEALSLUT:
			SetEffectVisible(HEALSLUT_EFFECT);
			break;
		}

		if (counters.clock_GlobalTicker % 90 == 0) {
			TatsUpdateContext(mark);
		}

		auto player = RE::PlayerCharacter::GetSingleton();
		auto scriptManager = ScriptingManager();

		RE::BGSPerk* healslut_perk = StaticDataHolder::GetSingleton()->LookupForm<RE::BGSPerk>(HEALSLUT_PERK, "Devious Curses.esp");
		if (mark == MARK::TAT_HEALSLUT && !player->HasPerk(healslut_perk)) {
			player->AddPerk(healslut_perk);
		}
		else if (mark != MARK::TAT_HEALSLUT && player->HasPerk(healslut_perk)) {
			player->RemovePerk(healslut_perk);
		}

		if (mark != MARK::TAT_NONE) {
			//int base_color = mark == 11 ? settings.LMHeatColor : (mark == 13 ? settings.LMAllureColor : (mark == 71 ? settings.LMBondageColor : (mark == 79 ? settings.LMNudityColor : 0)));
			if (counters.clock_GlobalTicker % 15 == 0) {
				log::trace("events marks update");
				switch (mark) {
				case MARK::TAT_HEAT: {
					scriptManager.ModifyArousal(player, settings.LMHeatMod / 4.0f);
					if (GetEffectMagnitude(HEAT_EFFECT) <= 0) {
						RemoveLewdMark();
						AIContextRemoveLewdMark();
						//PlayerMessage("You feel a sense of calm as the heat mark fades from your body.");
						PlayerMessage(Translator(Translation::MarkHeatRemove));
					}
					break;
				}
				case MARK::TAT_ALLURE: {
					auto playerPosition = RE::PlayerCharacter::GetSingleton()->GetPosition();

					if (const auto processLists = RE::ProcessLists::GetSingleton(); processLists) {
						RE::BSSimpleList<RE::ActorHandle>* arr = &(processLists->aliveActorList);
						if (arr) {
							for (auto const& actorHandle : *arr) {
								auto actorPtr = actorHandle.get();
								if (auto actor = actorPtr.get(); actor && actor->Is3DLoaded() && !actor->IsDead() && actor->GetPosition().GetDistance(playerPosition) <= settings.sexSearchRadius) {
									scriptManager.ModifyArousal(actor, settings.LMAllureMod / 4.0f);
								}
							}
						}
					}
					if (GetEffectMagnitude(ALLURE_EFFECT) <= 0) {
						RemoveLewdMark();
						AIContextRemoveLewdMark();
						//PlayerMessage("You sense that people are no longer staring at you as the allure mark fades from your body.");
						PlayerMessage(Translator(Translation::MarkAllureRemove));
					}
					break;
				}
				case MARK::TAT_BONDAGE: {
					if (Util::randomDouble() < settings.LMBondageChance) {
						log::trace("Attempting bondage event");
						std::vector<RE::TESObjectARMO*> equipable;

						auto inventory = player->GetInventory();
						auto keywords = GetKeywordsCantEquip(player);
						for (auto const& [k, v] : inventory) {
							RE::TESObjectARMO* armor = k->As<RE::TESObjectARMO>();
							if (armor && armor->HasKeywordString("zad_InventoryDevice") && DeviceHasGenericKey(armor) && v.second.get() && !v.second.get()->IsWorn()) {
								auto render = DeviousDevicesAPI::g_API->GetDeviceRender(armor);
								if (render) {
									bool canEquip = true;
									for (auto const& key : render->GetKeywords()) {
										if (vectorContains(keywords, Util::GetFormEditorId(key))) {
											canEquip = false;
										}
									}
									if (canEquip) {
										equipable.push_back(armor);
									}
								}
							}
						}
						log::trace("Total devices found for event: {}", equipable.size());
						if (equipable.size() == 0) {
							log::trace("Bondage mark found no items in inventory");
							break;
						}
						auto device = equipable[Util::randomInt(static_cast<int>(equipable.size()))];
						log::trace("Equipping device: {}", device->GetName());
						DecrementCounterForMark(MARK::TAT_BONDAGE);
						scriptManager.LockDevice(player, device);
						//PlayerMessage(fmt::format("Your mark pulses with light as your {} appears on your body!", device->GetName()));
						PlayerMessage(Translator(Translation::MarkBondageDevice, device->GetName()));
					}
					if (GetEffectMagnitude(BONDAGE_EFFECT) <= 0) {
						RemoveLewdMark();
						AIContextRemoveLewdMark();
						//PlayerMessage("You feel much less oppressed as the bondage mark fades from your body.");
						PlayerMessage(Translator(Translation::MarkBondageRemove));
					}
					break;
				}
				case MARK::TAT_NUDITY: {
					if (GetEffectMagnitude(NUDITY_EFFECT) <= 0) {
						RemoveLewdMark();
						AIContextRemoveLewdMark();
						//PlayerMessage("You feel less helpless as the nudity mark fades from your body.");
						PlayerMessage(Translator(Translation::MarkNudityRemove));
					}
					break;
				}
				case MARK::TAT_BRANDING: {
					int tattoo_count = GetTattooCount(player);
					float mag = GetEffectMagnitude(BRANDING_EFFECT);
					if (settings.LMBrandingPunish && mag > tattoo_count) {
						RE::TESForm* gold = RE::TESForm::LookupByID(std::stoi("0f", 0, 16));
						int goldCount = GetItemCount(player, gold);
						int toRemove = static_cast<int>(goldCount * Util::randomDouble(0.2, 0.4));
						player->RemoveItem((RE::TESBoundObject*)gold, toRemove, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
						//PlayerMessage(fmt::format("You loose {} gold as punishment for loosing tattoos!", toRemove));
						PlayerMessage(Translator(Translation::MarkBrandingPunish, toRemove));
					}

					if (Util::randomDouble() < settings.LMBrandingChance && CheckRapeTattoos()) {
						DoTattooEvent(player, "", 1, true);
						//scriptManager.RTDoTattooEvent(player, 1);
						//PlayerMessage("You feel a sharp pain as the mark brands you!");
						PlayerMessage(Translator(Translation::MarkBrandingTattoo));
					}
					if (tattoo_count >= settings.LMBrandingTotal) {
						RemoveLewdMark();
						AIContextRemoveLewdMark();
						//PlayerMessage("You feel the branding mark fade from your body.");
						PlayerMessage(Translator(Translation::MarkBrandingRemove));
					}
					else {
						Util::ExecuteWithDelay(750ms, [player] {SetEffectMagnitude(BRANDING_EFFECT, static_cast<float>(GetTattooCount(player))); });
					}
					break;
				}
				case MARK::TAT_HEALSLUT: {
					if (GetEffectMagnitude(HEALSLUT_EFFECT) <= 0) {
						RemoveLewdMark();
						AIContextRemoveLewdMark();
						PlayerMessage(Translator(Translation::MarkHealslutRemove));
					}
					break;
				}
				}
			}
			if (mark == MARK::TAT_NUDITY) {
				typedef RE::BIPED_MODEL::BipedObjectSlot BOS;

				if (settings.LMNudityChestOnly) {
					std::vector<RE::TESForm*> removes;

					RE::TESObjectARMO* equipped = player->GetWornArmor(BOS::kBody);
					if (equipped != nullptr && !equipped->HasKeywordString("SexLabNoStrip")) {
						//UnequipItem(player, equipped);
						removes.push_back(equipped);
					}
					if (!settings.LMNudityAditionalForms.empty()) {
						auto forms = Util::split(settings.LMNudityAditionalForms, ",");
						for (auto s : forms) {
							int form = -1;
							try {
								form = stoi(s);
							}
							catch (...) {
								log::warn("Bad string in LMNudityAditionalForms: {}", s);
								continue;
							}

							if (form < 30 || form > 61) {
								log::warn("Bad string in LMNudityAditionalForms, Form must be in range 30 - 61: {}", form);
								continue;
							}

							equipped = player->GetWornArmor(static_cast<BOS>(1 << (form - 30)));
							if (equipped != nullptr && !equipped->HasKeywordString("SexLabNoStrip")) {
								//UnequipItem(player, equipped);
								removes.push_back(equipped);
							}

						}
					}
					if (removes.size() > 0) {
						log::trace("Lewd Mark removed {} items", removes.size());
						for (auto item : removes) {
							scriptManager.UnequipItem(player, item);
						}
					}
				}
				else {
					UndressActor(player, false);
				}
			}
		}
	}

	bool P_CheckSTNG(RE::StaticFunctionTag*) {
		return slavetats_ng::iface;
	}

	bool P_CheckLM(RE::StaticFunctionTag*) {
		return CheckLewdMarksInstalled();
	}

	bool PapyrusFunctionsTats(RE::BSScript::IVirtualMachine* ivm) {
		ivm->RegisterFunction("CheckSTNG", "DCurses_MCM", P_CheckSTNG);
		ivm->RegisterFunction("CheckLM", "DCurses_MCM", P_CheckLM);
		return true;
	}
}