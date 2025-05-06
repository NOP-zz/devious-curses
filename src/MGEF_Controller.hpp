#pragma once

#include "../include/form_ids.h"

using namespace SKSE;

namespace DCURSES {
	class EffectVisitor : public RE::MagicTarget::ForEachActiveEffectVisitor {
	public:
		RE::EffectSetting* match = nullptr;
		RE::ActiveEffect* activeEffect = nullptr;
		// Inherited via ForEachActiveEffectVisitor
		virtual RE::BSContainer::ForEachResult Accept(RE::ActiveEffect* a_effect) override
		{
			if (a_effect->GetBaseObject() == match) {
				activeEffect = a_effect;
				return RE::BSContainer::ForEachResult::kStop;
			}
			return RE::BSContainer::ForEachResult::kContinue;
		}

		EffectVisitor(RE::EffectSetting* effect) {
			match = effect;
		}
	};

	RE::ActiveEffect* GetEffectByFormID(uint32_t effect_formid) {
		auto effect = StaticDataHolder::GetSingleton()->LookupForm<RE::EffectSetting>(effect_formid, "Devious Curses.esp");
		if (!effect) {
			log::warn("No EffectSetting for id {:x}", effect_formid);
			return nullptr;
		}
		auto target = RE::PlayerCharacter::GetSingleton()->GetMagicTarget();
		auto visitor = EffectVisitor(effect);
		target->VisitEffects(visitor);
		return visitor.activeEffect;
	}

	float GetEffectMagnitude(uint32_t effect_formid) {
		auto effect = GetEffectByFormID(effect_formid);
		if (effect) {
			return effect->magnitude;
		}
		log::error("Unable to get Active Effect for {:X}", effect_formid);
		return -1;
	}

	void ModifyEffectMagnitude(uint32_t effect_formid, float amount) {
		auto effect = GetEffectByFormID(effect_formid);
		if (effect) {
			effect->magnitude += amount;
			return;
		}
		log::error("Unable to get Active Effect for {:X}", effect_formid);
	}

	void SetEffectMagnitude(uint32_t effect_formid, float value) {
		auto effect = GetEffectByFormID(effect_formid);
		if (effect) {
			effect->magnitude = value;
			return;
		}
		log::error("Unable to get Active Effect for {:X}", effect_formid);
	}

	void SetEffectVisible(uint32_t effect_formid, bool visible = true) {
		auto effect = StaticDataHolder::GetSingleton()->LookupForm<RE::EffectSetting>(effect_formid, "Devious Curses.esp");
		if (!effect) {
			log::warn("No EffectSetting for id {:x}", effect_formid);
			return;
		}

		if (visible) {
			effect->data.flags.reset(RE::EffectSetting::EffectSettingData::Flag::kHideInUI);
		}
		else {
			effect->data.flags.set(RE::EffectSetting::EffectSettingData::Flag::kHideInUI);
		}
	}

	void MGEFOnGameLoad() {
		auto perk = StaticDataHolder::GetSingleton()->LookupForm<RE::BGSPerk>(DCURSES::MGEF_CONTROLLER, "Devious Curses.esp");
		auto spell = StaticDataHolder::GetSingleton()->LookupForm<RE::SpellItem>(DCURSES::MGEF_SPELL, "Devious Curses.esp");
		auto player = RE::PlayerCharacter::GetSingleton();

		if (!player->HasPerk(perk)) {
			player->AddPerk(perk);
		}

		std::list<std::pair<uint32_t, float>> list;

		auto all_effects = RE::TESDataHandler::GetSingleton()->GetFormArray<RE::EffectSetting>();

		for (auto effect : all_effects) {
			if (effect->HasKeywordString("DCurses_MenuEffect")) {
				list.push_back({ effect->formID & 0x00000fff, 0.0f });
			}
		}

		for (std::pair<uint32_t, float> &id : list) {
			float value = GetEffectMagnitude(id.first);
			id.second = value > 0.0f ? value : 0.0f;
		}
		player->GetMagicCaster(RE::MagicSystem::CastingSource::kOther)->CastSpellImmediate(spell, true, player, 1.0, false, 0.0, nullptr);
		StaticDataHolder::GetSingleton()->InvalidateCache();
		for (std::pair<uint32_t, float>& id : list) {
			SetEffectMagnitude(id.first, id.second);
			SetEffectVisible(id.first, false);
		}
	}
}