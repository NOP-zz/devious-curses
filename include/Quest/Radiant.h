#pragma once

namespace DCURSES::Quest {
	constexpr auto RAD_LOSTANDFOUND = 0x801;
	constexpr auto RAD_LOSTANDFOUND_TRIGGERITEM = 0x803;

	constexpr auto RAD_LF_PLUGVTEMPLATE = 0x80F;
	constexpr auto RAD_LF_PLUGVTEMPLATE_R = 0x80E;
	constexpr auto RAD_LF_PLUGATEMPLATE = 0x811;
	constexpr auto RAD_LF_PLUGATEMPLATE_R = 0x810;
	constexpr auto RAD_LF_COLLARTEMPLATE = 0x814;
	constexpr auto RAD_LF_COLLARTEMPLATE_R = 0x813;
	constexpr auto RAD_LF_PIERCINGVTEMPLATE = 0x816;
	constexpr auto RAD_LF_PIERCINGVTEMPLATE_R = 0x815;
	constexpr auto RAD_LF_PIERCINGNTEMPLATE = 0x818;
	constexpr auto RAD_LF_PIERCINGNTEMPLATE_R = 0x817;

	bool LostAndFoundTrinketEvent(RE::TESObjectREFR* container);

	void LostAndFoundRewardEvent();

	void RadOnGameLoaded();
}