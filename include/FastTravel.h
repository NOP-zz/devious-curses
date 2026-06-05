#pragma once

namespace DCURSES {
	bool CanFastTravelMap(RE::Actor*, bool);

	bool CanFastTravelDevices();

	void InstallFastTravelHooks();

	void SetFastTravelStatePapyrus(bool can_install_fast_travel_hook);
}