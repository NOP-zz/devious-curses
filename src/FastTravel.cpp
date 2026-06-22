#include "FastTravel.h"

#include "Settings.h"
#include "Devices.h"
#include "Scripting.h"
#include "Translation.h"
#include "Utils.h"

namespace DCURSES {
	inline static REL::Relocation<decltype(CanFastTravelMap)>  _CanFastTravelMap;
	
	bool CanFastTravelMap(RE::Actor* actor, bool a_bool) {
		auto player = RE::PlayerCharacter::GetSingleton();

		if (player->IsGodMode()) {
			return true;
		}

		log::trace("Running Fast Travel Code");

		return CanFastTravelDevices() && _CanFastTravelMap(actor, a_bool);
	}

	void InstallFastTravelHooks() {
		auto& trampoline = SKSE::GetTrampoline();
		static REL::Relocation<std::uintptr_t> Can_Fast_Travel_Map_Hook{ REL::ID(53095), 0x328 };

		_CanFastTravelMap = trampoline.write_call<5>(Can_Fast_Travel_Map_Hook.address(), CanFastTravelMap);
		log::trace("Installed ft hook");
	}

	void SetFastTravelStatePapyrus(bool can_install_fast_travel_hook) {
		auto settings = Settings::GetSingleton();

		if (!can_install_fast_travel_hook && (settings->restrictFastTravel)) {
			auto scriptManager = ScriptingManager();

			scriptManager.EnableFastTravel(CanFastTravelDevices());
		}
	}

	bool CanFastTravelDevices() {
		auto player = RE::PlayerCharacter::GetSingleton();
		auto scriptManager = ScriptingManager();
		auto settings = Settings::GetSingleton();

		auto inventory = player->GetInventory();
		for (auto& [k, v] : inventory) {
			if (v.second.get()->IsWorn()) {
				RE::TESObjectARMO* wornArmor = k->As<RE::TESObjectARMO>();
				if (!wornArmor) {
					continue;
				}

				if (wornArmor->HasKeywordString("DCurses_RestrictFastTravel")) {
					log::trace("Fast travel disabled because of {} {} {}", wornArmor->GetName(), wornArmor->GetFullName(), wornArmor->fullName);
					scriptManager.DBGNotification(Translator(Translation::FastTravelUnableNamed, wornArmor->GetFullName()));
					return false;
				}
			}
		}

		if (settings->restrictFastTravelFull) {
			if (GetWornDeviceCount(player) > 0) {
				scriptManager.DBGNotification(Translator(Translation::FastTravelUnableDevices));
				return false;
			}
		}
		else if (settings->restrictFastTravelPart) {
			if (GetVisibleDeviceCount(player) > 0) {
				scriptManager.DBGNotification(Translator(Translation::FastTravelUnableVisible));
				return false;
			}
		}
		else if (settings->restrictFastTravel) {
			auto device_keywords = GetWornDeviceKeywords(player);
			for (auto& keyword : device_keywords) {
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
}