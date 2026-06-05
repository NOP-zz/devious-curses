#include "Themes.h"

#include "Devices.h"
#include "apis/JSON.hpp"
#include "Utils.h"

using namespace SKSE;

constexpr auto THEMES_FILE = "Data/SKSE/Plugins/DeviousCursesThemes.json";

namespace DCURSES {
	void CreateThemesFileIfNeeded() {
		nlohmann::json j = nlohmann::json::array();

		if (!std::filesystem::exists(THEMES_FILE)) {
			log::warn("Unable to load themes file. Creating default file.");
			std::ofstream o(THEMES_FILE);
			j = nlohmann::json::array({
				"red & (ebonite | rubber)",
				"red & leather",
				"black & (ebonite | rubber)",
				"black & leather",
				"white & (ebonite | rubber)",
				"white & leather",
				"iron | rust | steel",
				"rope & !(white | red | black)",
				"rope & white",
				"rope & red",
				"rope & black"
				});
			o << std::setw(4) << j << std::endl;
		}
	}
	std::string GetRandomTheme() {
		CreateThemesFileIfNeeded();

		nlohmann::json j = nlohmann::json::array();
		std::ifstream i(THEMES_FILE);

		try {
			i >> j;
		}
		catch (...) {
			log::error("Themes file has garbled data.");
			return "";
		}

		auto themes = j.get<std::vector<std::string>>();

		if (themes.size() == 0) {
			log::warn("Unable to find theme.");
			return "";
		}

		Util::ShuffleVector(themes);

		for (auto theme : themes) {
			if (TestTheme(theme)) {
				log::info("Got random theme {}", theme);
				return theme;
			}
		}

		log::trace("Unable to find theme based on equipped devices.");
		return "";
	}


	bool TestTheme(std::string theme, std::vector<std::string> skipKeywords) {
		RE::Actor* player = RE::PlayerCharacter::GetSingleton();

		std::string device_names = "";
		std::string device_ids = "";

		std::set<std::string> usedKeys = GetKeywordsCantEquip(player);

		for (auto kw : skipKeywords) {
			usedKeys.insert(kw);
		}

		for (int i = 0; i < 100; i++) {
			auto dev = GetRandomEquipableDevice(player, usedKeys, theme);
			if (dev) {
				//return true;
				continue;
			}
		}

		return false;
	}
}