#pragma once

namespace DCURSES {
	enum class MARK : int64_t {
		TAT_NONE = 0,
		TAT_HEAT = 11,
		TAT_ALLURE = 13,
		TAT_PAINSLUT = 63,
		TAT_BONDAGE = 71,
		TAT_BRANDING = 74,
		TAT_HEALSLUT = 76,
		TAT_NUDITY = 79,
	};

	std::string GetMarkAsString(MARK mark);

	int GetTattooCount(RE::Actor* actor);

	bool CheckLewdMarksInstalled();

	MARK GetLewdMark();

	int GetColorForMark(MARK mark);

	void SetMarkToDefaultSettings(MARK mark, double multiplier = 1.0);

	bool _AddLewdMarkGlow(int index, int32_t color, int32_t glow);

	bool _AddLewdMarkMain(int index, int32_t color, int32_t glow);

	int32_t GetLewdMarkApplied();

	bool AddLewdMark(MARK mark);

	void RemoveLewdMark(int32_t index = -1);

	void RemoveAllTattoos(RE::Actor* actor);

	void TatsOnMagicHitEvent(const RE::TESMagicEffectApplyEvent* magicEvent);

	void TatsOnPlayerHit(const RE::TESHitEvent* hitEvent);

	void TatsOnSpellCast(const RE::TESSpellCastEvent* spellEvent);

	void TatsOnSexEnd(RE::Actor* actor);

	bool DoTattooEvent(RE::Actor*, std::string, int, bool);

    void TatsUpdate();

	bool P_CheckSTNG(RE::StaticFunctionTag*);

	bool P_CheckLM(RE::StaticFunctionTag*);

	bool PapyrusFunctionsTats(RE::BSScript::IVirtualMachine* ivm);
}