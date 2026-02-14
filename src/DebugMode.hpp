#pragma once

#include "JSON.hpp"

constexpr static auto LOCATIONS_FILE = "Data/SKSE/Plugins/DeviousCursesDebugLocations.json";

namespace DCURSES::Debug {
	struct LocationData {
		std::vector<std::string> keywords;
		LocationType type;
	};

	nlohmann::json locations_map;

	void CreateLocationsFileIfNeeded() {
		nlohmann::json j = nlohmann::json::parse(R"({})");

		if (!std::filesystem::exists(LOCATIONS_FILE)) {
			log::debug("Debug creating locations file.");
			std::ofstream o(LOCATIONS_FILE);
			o << j << std::endl;
		}
	}

	nlohmann::json GetLocationMap() {
		nlohmann::json j;
		std::ifstream i(LOCATIONS_FILE);

		try {
			i >> j;
		}
		catch (...) {
			log::debug("Debug Locations file has garbled data.");
			return nlohmann::json::parse(R"({})");
		}

		return j;
	}

	void SaveLocationMap(nlohmann::json j) {
		std::ofstream o(LOCATIONS_FILE);
		o << std::setw(4) << j << std::endl;
	}

	void AddLocationData() {
		auto j = nlohmann::json::parse(R"({})");

		auto location_data = RE::TESDataHandler::GetSingleton()->GetFormArray<RE::BGSLocation>();

		for (auto location : location_data) {
			std::vector<std::string> location_keywords;
			for (uint32_t x = 0; x < location->numKeywords; x++) {
				location_keywords.push_back(Util::GetFormEditorId(location->keywords[x]));
			}
			auto location_type = GetLocationType(location);
			auto location_type_string = GetLocationTypeString(location_type);
			
			auto temp_location = location;
			std::vector<std::string> location_parents;
			int i = 10;
			while (temp_location->parentLoc && i-- > 0) {
				temp_location = temp_location->parentLoc;
				location_parents.push_back(fmt::format("{} ({})", Util::GetFormEditorId(temp_location), GetLocationTypeString(GetLocationType(temp_location))));
			}

			auto location_parents_string = Util::join(location_parents, " -> ");

			j[location_type_string][fmt::format("Location-{:X}", location->formID)] = {
				{"name", location->GetName()},
				{"editorId", Util::GetFormEditorId(location)},
				{"keywords", location_keywords},
				{"parents", location_parents_string}
			};
		}

		SaveLocationMap(j);
	}
}