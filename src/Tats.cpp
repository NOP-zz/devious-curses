#include "Tats.h"

#pragma warning(default : 4062)

#include "apis/jcontainers.hpp"
#include "Settings.h"
#include "MGEF_Controller.h"
#include "Sex.h"
#include "Serializer.h"
#include "Utils.h"
#include "Scripting.h"
#include "Translation.h"
#include "Devices.h"

#include "apis/SlaveTatsNG_Interface.h"

using namespace SKSE;

namespace DCURSES {
	std::string GetMarkAsString(MARK mark) {
		switch (mark) {
		case MARK::TAT_HEAT: return "HEAT";
		case MARK::TAT_ALLURE: return "ALLURE";
		case MARK::TAT_PAINSLUT: return "PAINSLUT";
		case MARK::TAT_BONDAGE: return "BONDAGE";
		case MARK::TAT_BRANDING: return "BRANDING";
		case MARK::TAT_HEALSLUT: return "HEALSLUT";
		case MARK::TAT_NUDITY: return "NUDITY";
		case MARK::TAT_NONE: return "NONE";
		}
		return "NONE";
	}
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
		return static_cast<MARK>(Serialized::GetLewdMarkCounters()->currentMark);
	}
	int GetColorForMark(MARK mark) {
		auto settings = Settings::GetSingleton();

		switch (mark) {
		case MARK::TAT_NONE:
			return 0;
		case MARK::TAT_ALLURE:
			return settings->LMAllureColor;
		case MARK::TAT_HEAT:
			return settings->LMHeatColor;
		case MARK::TAT_BONDAGE:
			return settings->LMBondageColor;
		case MARK::TAT_NUDITY:
			return settings->LMNudityColor;
		case MARK::TAT_BRANDING:
			return settings->LMBrandingColor;
		case MARK::TAT_HEALSLUT:
			return settings->LMHealslutColor;
		case MARK::TAT_PAINSLUT:
			return settings->LMPainslutColor;
		}
		return 0;
	}
	void SetMarkToDefaultSettings(MARK mark, double multiplier) {
		auto settings = Settings::GetSingleton();
		auto lewdMarkCounters = Serialized::GetLewdMarkCounters();

		double rand = Util::random(0.8, 1.2);
		log::trace("Rand: {}", rand);
		switch (mark) {
		case MARK::TAT_ALLURE:
			lewdMarkCounters->allureCounter = static_cast<int32_t>(settings->LMAllureSex * rand * multiplier);
			SetEffectMagnitude(ALLURE_EFFECT, static_cast<float>(lewdMarkCounters->allureCounter));
			break;
		case MARK::TAT_HEAT:
			lewdMarkCounters->heatCounter = static_cast<int32_t>(settings->LMHeatContainerCount * rand * multiplier);
			SetEffectMagnitude(HEAT_EFFECT, static_cast<float>(lewdMarkCounters->heatCounter));
			break;
		case MARK::TAT_BONDAGE:
			lewdMarkCounters->bondageCounter = static_cast<int32_t>(settings->LMBondageDeviceCount * rand * multiplier);
			SetEffectMagnitude(BONDAGE_EFFECT, static_cast<float>(lewdMarkCounters->bondageCounter));
			break;
		case MARK::TAT_NUDITY:
			lewdMarkCounters->nudityCounter = static_cast<int32_t>(settings->LMNudityTalkTimes * rand * multiplier);
			SetEffectMagnitude(NUDITY_EFFECT, static_cast<float>(lewdMarkCounters->nudityCounter));
			break;
		case MARK::TAT_HEALSLUT:
			lewdMarkCounters->healslutCounter = static_cast<int32_t>(settings->LMHealslutHealing * rand * multiplier);
			SetEffectMagnitude(HEALSLUT_EFFECT, static_cast<float>(lewdMarkCounters->healslutCounter));
			break;
		case MARK::TAT_PAINSLUT:
			lewdMarkCounters->painslutCounter = static_cast<int32_t>(settings->LMPainslutCount * rand * multiplier);
			SetEffectMagnitude(PAINSLUT_EFFECT, static_cast<float>(lewdMarkCounters->painslutCounter));
			break;
		case MARK::TAT_BRANDING:
			SetEffectMagnitude(BRANDING_EFFECT, static_cast<float>(GetTattooCount(RE::PlayerCharacter::GetSingleton())));
			break;
		case MARK::TAT_NONE:
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
	int32_t GetLewdMarkApplied() {
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

		int index = static_cast<int32_t>(mark);

		auto base_color = GetColorForMark(mark);
		auto glowColor = Util::ColorScale(base_color, 0.9);

		if (_AddLewdMarkGlow(index, glowColor, glowColor) && _AddLewdMarkMain(index, base_color, glowColor)) {
			Serialized::GetLewdMarkCounters()->currentMark = index;
			return true;
		}
		return false;

	}
	void RemoveLewdMark(int32_t index) {
		if (!slavetats_ng::iface) return;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return;
		if (!CheckLewdMarksInstalled()) return;

		auto actor = RE::PlayerCharacter::GetSingleton();

		if (index == -1) {
			index = static_cast<int32_t>(GetLewdMark());
		}

		Serialized::GetLewdMarkCounters()->currentMark = 0;

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
		}
	}

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
								if (Serialized::GetLewdMarkCounters()->healslutCounter > 0) {
									Serialized::GetLewdMarkCounters()->healslutCounter -= static_cast<int32_t>(ceilf(mag));
								}
								SetEffectMagnitude(HEALSLUT_EFFECT, static_cast<float>(Serialized::GetLewdMarkCounters()->healslutCounter));
								auto targetAV = target->AsActorValueOwner();
								auto targetHealth = targetAV->GetActorValue(RE::ActorValue::kHealth);
								auto targetMaxHealth = targetAV->GetBaseActorValue(RE::ActorValue::kHealth);

								scriptManager.ModifyArousal(target, mag / 4.0f);
								if (Settings::GetSingleton()->LMHealslutArousal <= 100) {
									scriptManager.WithArousal(target, [targetHealth, targetMaxHealth, target, mag](float arousal) {
										auto scriptManager = ScriptingManager();
										auto settings = Settings::GetSingleton();
										if (settings->sexEnabled && (targetHealth + 1) >= targetMaxHealth && arousal > settings->LMHealslutArousal && SexActorFilter(target, false) && !RE::PlayerCharacter::GetSingleton()->IsInCombat()) {
											scriptManager.StartSex(target, false);
										}
									});
								}
								break;
							}
						}
					}
					});
			}
		}
	}
	void TatsOnPlayerHit(const RE::TESHitEvent* hitEvent) {
		auto mark = GetLewdMark();
		if (mark == MARK::TAT_PAINSLUT) {
			auto player = RE::PlayerCharacter::GetSingleton();
			auto settings = Settings::GetSingleton();
			auto source = RE::TESForm::LookupByID(hitEvent->source);
			auto aggressor = hitEvent->cause.get()->As<RE::Actor>();
			if (aggressor && source) {

				float arousalMod = static_cast<float>(settings->LMPainslutMod);
				auto chance = settings->LMPainslutSexChance;

				if (source->As<RE::SpellItem>() || source->As<RE::Explosion>()) {
					arousalMod *= 0.25f;
					chance *= 0.2f;
				}
				else if (hitEvent->flags.all(RE::TESHitEvent::Flag::kPowerAttack)) {
					arousalMod *= 1.5f;
					chance *= 1.25f;
				}

				auto scriptManager = ScriptingManager();

				scriptManager.ModifyArousal(player, arousalMod);

				scriptManager.WithArousal(player, [player, chance, aggressor](float arousal) {
					auto settings = Settings::GetSingleton();
					auto scriptManager = ScriptingManager();
					log::trace("chance: {}", chance);
					if (SexActorFilter(aggressor, true) && arousal > settings->LMPainslutArousal && Util::random<float>() < chance) {
						//log::info("Attempting to start sex with {}", aggressor->GetName());
						auto PlayerAllyFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x5A1A4, "Skyrim.esm");

						PlayerMessage(Translator(Translation::MarkPainslutSex, aggressor->GetName()));

						Util::StopPlayerCombat();

						aggressor->AddToFaction(PlayerAllyFaction, 1);
						Serialized::GetLewdMarkCounters()->painslutSexTarget = aggressor->formID;

						scriptManager.StartSex(aggressor, true);
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
		if (Serialized::GetLewdMarkCounters()->allureCounter > 0) {
			Serialized::GetLewdMarkCounters()->allureCounter -= 1;
		}
		if (mark == MARK::TAT_HEALSLUT && actor->IsPlayerTeammate() && !actor->IsCommandedActor()) {
			log::trace("Casting healslut reward spell");
			auto player = RE::PlayerCharacter::GetSingleton();
			RE::SpellItem* restoration = StaticDataHolder::GetSingleton()->LookupForm<RE::SpellItem>(HEALSLUT_RESTORATION_SPELL, "Devious Curses.esp");
			for (auto* effect : restoration->effects) {
				if (effect) {
					effect->effectItem.duration = Settings::GetSingleton()->LMHealslutDuration;
				}
			}
			RE::MagicCaster* caster = player->GetMagicCaster(RE::MagicSystem::CastingSource::kOther);
			caster->CastSpellImmediate(restoration, false, player, 1.0f, false, 0.0f, nullptr);
		}
		if (Serialized::GetLewdMarkCounters()->painslutSexTarget == actor->formID) {
			auto PlayerAllyFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x5A1A4, "Skyrim.esm");
			actor->RemoveFromFaction(PlayerAllyFaction);
			Serialized::GetLewdMarkCounters()->painslutSexTarget = 0;
		}
	}

	void TatsUpdate() {
		auto mark = GetLewdMark();
		auto index = static_cast<int32_t>(mark);
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
		SetEffectVisible(PAINSLUT_EFFECT, false);

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
		case MARK::TAT_PAINSLUT:
			SetEffectVisible(PAINSLUT_EFFECT);
			break;
		}

		auto player = RE::PlayerCharacter::GetSingleton();
		auto scriptManager = ScriptingManager();
		auto settings = Settings::GetSingleton();
		auto lewdMarkCounters = Serialized::GetLewdMarkCounters();

		RE::BGSPerk* healslut_perk = StaticDataHolder::GetSingleton()->LookupForm<RE::BGSPerk>(HEALSLUT_PERK, "Devious Curses.esp");
		if (mark == MARK::TAT_HEALSLUT && !player->HasPerk(healslut_perk)) {
			player->AddPerk(healslut_perk);
		}
		else if (mark != MARK::TAT_HEALSLUT && player->HasPerk(healslut_perk)) {
			player->RemovePerk(healslut_perk);
		}

		else {
			switch (mark) {
			case (MARK::TAT_NONE): {
				return;
			}
			case (MARK::TAT_ALLURE): {
				if (lewdMarkCounters->allureCounter <= 0) {
					lewdMarkCounters->allureCounter = INT32_MIN;
					RemoveLewdMark();
					PlayerMessage(Translator(Translation::MarkAllureRemove), Settings::GetSingleton()->surpriseMode);
					return;
				}
				if (lewdMarkCounters->allureCounter == INT32_MIN) {
					SetMarkToDefaultSettings(MARK::TAT_ALLURE);
				}

				SetEffectMagnitude(ALLURE_EFFECT, static_cast<float>(lewdMarkCounters->allureCounter));
				break;
			}
			case (MARK::TAT_BONDAGE): {
				if (lewdMarkCounters->bondageCounter <= 0) {
					lewdMarkCounters->bondageCounter = INT32_MIN;
					RemoveLewdMark();
					PlayerMessage(Translator(Translation::MarkBondageRemove), Settings::GetSingleton()->surpriseMode);
					return;
				}

				if (lewdMarkCounters->bondageCounter == INT32_MIN) {
					SetMarkToDefaultSettings(MARK::TAT_BONDAGE);
				}

				SetEffectMagnitude(BONDAGE_EFFECT, static_cast<float>(lewdMarkCounters->bondageCounter));

				break;
			}
			case (MARK::TAT_HEALSLUT): {
				if (lewdMarkCounters->healslutCounter <= 0) {
					lewdMarkCounters->healslutCounter = INT32_MIN;
					RemoveLewdMark();
					PlayerMessage(Translator(Translation::MarkHealslutRemove), Settings::GetSingleton()->surpriseMode);
					return;
				}

				if (lewdMarkCounters->healslutCounter == INT32_MIN) {
					SetMarkToDefaultSettings(MARK::TAT_HEALSLUT);
				}

				SetEffectMagnitude(HEALSLUT_EFFECT, static_cast<float>(lewdMarkCounters->healslutCounter));

				break;
			}
			case (MARK::TAT_HEAT): {
				if (lewdMarkCounters->heatCounter <= 0) {
					lewdMarkCounters->heatCounter = INT32_MIN;
					RemoveLewdMark();
					PlayerMessage(Translator(Translation::MarkHeatRemove), Settings::GetSingleton()->surpriseMode);
					return;
				}

				if (lewdMarkCounters->heatCounter == INT32_MIN) {
					SetMarkToDefaultSettings(MARK::TAT_HEAT);
				}

				SetEffectMagnitude(HEAT_EFFECT, static_cast<float>(lewdMarkCounters->heatCounter));

				break;
			}
			case (MARK::TAT_NUDITY): {
				if (lewdMarkCounters->nudityCounter <= 0) {
					lewdMarkCounters->nudityCounter = INT32_MIN;
					RemoveLewdMark();
					PlayerMessage(Translator(Translation::MarkNudityRemove), Settings::GetSingleton()->surpriseMode);
					return;
				}

				if (lewdMarkCounters->nudityCounter == INT32_MIN) {
					SetMarkToDefaultSettings(MARK::TAT_NUDITY);
				}

				SetEffectMagnitude(NUDITY_EFFECT, static_cast<float>(lewdMarkCounters->nudityCounter));

				break;
			}
			case (MARK::TAT_PAINSLUT): {
				if (lewdMarkCounters->painslutCounter <= 0) {
					lewdMarkCounters->painslutCounter = INT32_MIN;
					RemoveLewdMark();
					PlayerMessage(Translator(Translation::MarkPainslutRemove), Settings::GetSingleton()->surpriseMode);
					return;
				}

				if (lewdMarkCounters->painslutCounter == INT32_MIN) {
					SetMarkToDefaultSettings(MARK::TAT_PAINSLUT);
				}

				SetEffectMagnitude(PAINSLUT_EFFECT, static_cast<float>(lewdMarkCounters->painslutCounter));

				break;
			}
			case (MARK::TAT_BRANDING): {
				auto playerTattooCount = GetTattooCount(player);
				if (playerTattooCount >= settings->LMBrandingTotal) {
					RemoveLewdMark();
					PlayerMessage(Translator(Translation::MarkBrandingRemove), Settings::GetSingleton()->surpriseMode);
					return;
				}

				SetEffectMagnitude(BRANDING_EFFECT, static_cast<float>(playerTattooCount));

				break;
			}
			}
		}


		if (Serialized::GetCounters()->clock_GlobalTicker % 15 == 0) {
			log::trace("events marks update");
			switch (mark) {
			case MARK::TAT_HEAT: {
				scriptManager.ModifyArousal(player, settings->LMHeatMod / 4.0f);
				break;
			}
			case MARK::TAT_ALLURE: {
				auto playerPosition = RE::PlayerCharacter::GetSingleton()->GetPosition();

				if (const auto processLists = RE::ProcessLists::GetSingleton(); processLists) {
					RE::BSSimpleList<RE::ActorHandle>* arr = &(processLists->aliveActorList);
					if (arr) {
						for (auto const& actorHandle : *arr) {
							auto actorPtr = actorHandle.get();
							if (auto actor = actorPtr.get(); actor && actor->Is3DLoaded() && !actor->IsDead() && actor->GetPosition().GetDistance(playerPosition) <= settings->sexSearchRadius) {
								scriptManager.ModifyArousal(actor, settings->LMAllureMod / 4.0f);
							}
						}
					}
				}
				break;
			}
								 /*case MARK::TAT_BONDAGE: {
								 if (Util::random() < settings->LMBondageChance) {
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
								 if (Util::vectorContains<std::string>(keywords, Util::GetFormEditorId(key))) {
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
								 auto device = equipable[Util::random(equipable.size())];
								 log::trace("Equipping device: {}", device->GetName());
								 if (lewdMarkCounters->bondageCounter > 0) {
								 lewdMarkCounters->bondageCounter -= 1;
								 }
								 scriptManager.LockDevice(player, device);
								 //PlayerMessage(fmt::format("Your mark pulses with light as your {} appears on your body!", device->GetName()));
								 PlayerMessage(Translator(Translation::MarkBondageDevice, device->GetName()), Settings::GetSingleton()->surpriseMode);
								 }
								 break;
								 }*/
			case MARK::TAT_BRANDING: {
				int tattoo_count = GetTattooCount(player);
				float mag = GetEffectMagnitude(BRANDING_EFFECT);
				if (settings->LMBrandingPunish && mag > tattoo_count) {
					RE::TESForm* gold = RE::TESForm::LookupByID(std::stoi("0f", 0, 16));
					int goldCount = GetItemCount(player, gold);
					int toRemove = static_cast<int>(goldCount * Util::random(0.2, 0.4));
					player->RemoveItem(skyrim_cast<RE::TESBoundObject*>(gold), toRemove, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
					//PlayerMessage(fmt::format("You loose {} gold as punishment for loosing tattoos!", toRemove));
					PlayerMessage(Translator(Translation::MarkBrandingPunish, toRemove));
					SetEffectMagnitude(BRANDING_EFFECT, static_cast<float>(GetTattooCount(player)));
				}

				if (Util::random() < settings->LMBrandingChance && CheckRapeTattoos()) {
					DoTattooEvent(player, "", 1, true);
					PlayerMessage(Translator(Translation::MarkBrandingTattoo), Settings::GetSingleton()->surpriseMode);
				}
				else {
					Util::ExecuteWithDelay(750ms, [player] {SetEffectMagnitude(BRANDING_EFFECT, static_cast<float>(GetTattooCount(player))); });
				}
				break;
			}
			default: break;
			}
		}
		if (mark == MARK::TAT_NUDITY) {
			typedef RE::BIPED_MODEL::BipedObjectSlot BOS;

			if (settings->LMNudityChestOnly) {
				std::vector<RE::TESForm*> removes;

				RE::TESObjectARMO* equipped = player->GetWornArmor(BOS::kBody);
				if (equipped != nullptr && !equipped->HasKeywordString("SexLabNoStrip")) {
					//UnequipItem(player, equipped);
					removes.push_back(equipped);
				}
				if (!settings->LMNudityAditionalForms.empty()) {
					auto forms = Util::split(settings->LMNudityAditionalForms, ",");
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
					PlayerMessage(Translator(Translation::MarkNudityEnforce), Settings::GetSingleton()->surpriseMode);
					for (auto item : removes) {
						scriptManager.UnequipItem(player, item);
					}
				}
			}
			else {
				if (UndressActor(player, false)) {
					PlayerMessage(Translator(Translation::MarkNudityEnforce), Settings::GetSingleton()->surpriseMode);
				}
			}
		}
	}
}