#pragma once

namespace DCURSES::Quest {
	constexpr auto FAC_ENABLEDCOURTMAGES = 0x802;
	constexpr auto QUEST_COURTMAGEDIALOGUE = 0x804;

	//Return true if did something
	bool CheckObjectActivation(RE::TESObjectREFR* object);

	void CheckQuestStageChanged(RE::FormID quest_id, uint16_t stage);

	void OnLocationChanged();

	void OnGameLoaded();

	void OnSettingsChanged();
}