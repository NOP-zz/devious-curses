#pragma once

#include "Settings.hpp"

namespace DCURSES {
	inline static REL::Relocation<std::uintptr_t> Can_Fast_Travel_Map_Hook{ REL::ID(53095), 0x328 };

	bool CanFastTravelMap(RE::Actor*, bool);

	inline static REL::Relocation<decltype(CanFastTravelMap)>  _CanFastTravelMap;

	bool CanFastTravelDevices(RE::Actor* actor) {
		auto player = RE::PlayerCharacter::GetSingleton();
		auto scriptManager = ScriptingManager();

		if (settings.restrictFastTravelFull) {
			if (GetWornDeviceCount(player) > 0) {
				scriptManager.DBGNotification(Translator(Translation::FastTravelUnableDevices));
				return false;
			}
		}
		else if (settings.restrictFastTravel) {

			auto device_keywords = GetWornDeviceKeywords(player);
			for (auto keyword : device_keywords) {
				if (keyword == "zad_DeviousHeavyBondage") {
					scriptManager.DBGNotification(Translator(Translation::FastTravelUnableHeavy));
					return false;
				}
				if (keyword == "zad_DeviousBlindfold") {
					scriptManager.DBGNotification(Translator(Translation::FastTravelUnableBlind));
					return false;
				}
				if (keyword == "zad_DeviousBoots") {
					scriptManager.DBGNotification(Translator(Translation::FastTravelUnableBoots));
					return false;
				}
				if (keyword == "zad_EffectForcedWalk") {
					scriptManager.DBGNotification(Translator(Translation::FastTravelUnableHobble));
					return false;
				}
			}
		}

		return true;
	}

	bool CanFastTravelMap(RE::Actor* actor, bool a_bool) {
		auto player = RE::PlayerCharacter::GetSingleton();

		if (player->IsGodMode()) {
			return true;
		}
		
		log::trace("Running Fast Travel Code");

		return CanFastTravelDevices(actor) && _CanFastTravelMap(actor, a_bool);
	}

	void InstallFastTravelHooks() {
		auto& trampoline = SKSE::GetTrampoline();
		_CanFastTravelMap = trampoline.write_call<5>(Can_Fast_Travel_Map_Hook.address(), CanFastTravelMap);
		log::trace("Installed ft hook");
	}

	void SetFastTravelStatePapyrus() {
		if (!can_restrict_fast_travel_hook && (settings.restrictFastTravel || settings.restrictFastTravelFull)) {
			auto player = RE::PlayerCharacter::GetSingleton();
			auto scriptManager = ScriptingManager();

			scriptManager.EnableFastTravel(CanFastTravelDevices(player));
		}
	}
}