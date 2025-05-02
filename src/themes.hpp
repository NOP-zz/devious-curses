#pragma once

#include "Devices.hpp"

using namespace SKSE;

constexpr auto THEMES_FILE = "Data/SKSE/Plugins/DeviousCursesThemes.json";

namespace DCURSES {
	std::string GetRandomTheme() {
		nlohmann::json j = nlohmann::json::array();

		if (!std::filesystem::exists(THEMES_FILE)) {
			log::warn("Unable to load themes file. Recreating file.");
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
			o << j << std::endl;
		}
		else {
			std::ifstream i(THEMES_FILE);

			try {
				i >> j;
			}
			catch (...) {
				log::error("Themes file has garbled data.");
				return "";
			}
		}

		auto themes = j.get<std::vector<std::string>>();
		std::vector<std::string> out;

		for (auto theme : themes) {
			if (TestTheme(theme)) {
				out.push_back(theme);
			}
		}

		if (out.size() == 0) {
			log::warn("Unable to find theme.");
			return "";
		}

		auto theme = out[Util::randomInt(static_cast<int>(out.size()))];
		log::info("Got random theme {}", theme);
		return theme;
	}
}