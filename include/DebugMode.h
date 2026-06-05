#pragma once

constexpr static auto LOCATIONS_FILE = "Data/SKSE/Plugins/DeviousCursesDebugLocations.json";
constexpr static auto DEBUG_INPUT_FILE = "Data/SKSE/Plugins/DeviousCursesDebugInput.txt";

namespace DCURSES::Debug {

	void Test();

	void AddLocationData();

	void CheckTranslations();

	void CheckMCMTranslations();
}