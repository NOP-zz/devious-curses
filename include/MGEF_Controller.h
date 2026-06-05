#pragma once

#include "Translation.h"

namespace DCURSES {
	RE::ActiveEffect* GetEffectByFormID(uint32_t effect_formid);

	float GetEffectMagnitude(uint32_t effect_formid);

	void ModifyEffectMagnitude(uint32_t effect_formid, float amount);

	void SetEffectMagnitude(uint32_t effect_formid, float value);

	void SetEffectVisible(uint32_t effect_formid, bool visible = true);

	void SetEffectDescription(uint32_t effect_formid, Translator trans);

	void MGEFOnGameLoad();
}