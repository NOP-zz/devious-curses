#include "DebugMode.h"

#include "Locations.h"
#include "Settings.h"
#include "apis/JSON.hpp"
#include "Utils.h"
#include "Events.h"
#include "Scripting.h"
#include "Themes.h"
#include "Devices.h"
#include <apis/DDNG_API.h>

using namespace SKSE;

namespace DCURSES::Debug {
	template<class T>
	T GetDebugInputAs() {
		T input = T();
		std::ifstream i(DEBUG_INPUT_FILE);
		if (i >> input) {
			log::debug("Read input as {}", input);
			return input;
		}
		i.close();

		return input;
	}

	void Test() {
		log::debug("DCURSES Test Start");
		//auto player = RE::PlayerCharacter::GetSingleton();



		log::debug("DCURSES Test End");
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
				{ "name", location->GetName() },
				{ "editorId", Util::GetFormEditorId(location) },
				{ "keywords", location_keywords },
				{ "parents", location_parents_string },
				{ "type", location_type_string }
			};
		}

		SaveLocationMap(j);
	}

	struct LocationData {
		std::vector<std::string> keywords;
		LocationType type;
	};


	//nlohmann::json locations_map;

	void CreateLocationsFileIfNeeded() {
		nlohmann::json j = nlohmann::json::parse(R"({})");

		if (!std::filesystem::exists(LOCATIONS_FILE)) {
			log::debug("Debug creating locations file.");
			std::ofstream o(LOCATIONS_FILE);
			o << j << std::endl;
		}
	}

	

	void CheckMCMTranslations() {
		log::debug("Checking MCM Translations...");
		std::ifstream englishTranslationsFile("Data/interface/translations/Devious Curses_ENGLISH.txt", std::ios::binary);
		englishTranslationsFile.ignore(2);

		std::map<std::string, std::string> englishTranslationsMap;
		{
			log::debug("Reading english translation file");
			std::string line;
			while (std::getline(englishTranslationsFile, line)) {
				if (line.find('\t') == std::string::npos) { continue; }
				auto token = line.substr(0, line.find('\t'));
				auto value = line.substr(line.find('\t') + 1);
				englishTranslationsMap.insert({ token, value });
			}
		}

		for (const auto& entry : std::filesystem::directory_iterator("Data/interface/translations/")) {
			auto filename_string = entry.path().filename().generic_string();
			if (entry.is_regular_file() && filename_string.starts_with("Devious Curses_") && !filename_string.contains("ENGLISH") && entry.path().extension() == ".txt") {
				auto languageString = Util::split(entry.path().stem().generic_string(), "_")[1];

				auto translation_filename = entry.path().filename().generic_string();
				log::debug("Found MCM Translation File {}", translation_filename);

				std::ifstream translationsFile(entry.path(), std::ios::binary);
				translationsFile.ignore(2);

				std::map<std::string, int> translationsMap;

				std::string line;
				while (std::getline(translationsFile, line)) {
					if (line.find('\t') == std::string::npos) { continue; }
					auto token = line.substr(0, line.find('\t'));
					translationsMap[token] = 0;
				}

				std::string to_log = "";

				for (auto& [token, value] : englishTranslationsMap) {
					if (!translationsMap.count(token)) {
						std::string tokenPrint;
						for (size_t i = 0; i < token.size(); i++) {
							if (token[i]) {
								tokenPrint.push_back(token[i]);
							}
						}

						std::string valuePrint;
						for (size_t i = 0; i < value.size(); i++) {
							if (value[i]) {
								valuePrint.push_back(value[i]);
							}
						}
						//log::warn("{} MCM translation is missing: {}", languageString, tokenPrint);
						to_log += fmt::format("{}\t{}\n", tokenPrint, valuePrint);
					}
				}

				std::ofstream o(fmt::format("Data/DeviousCurses_{}_MissingMCMKeys.txt", languageString));
				o << to_log << std::endl;
				o.close();
			}
		}
	}

	void CheckTranslations() {
		log::debug("Checking Translations...");
		for (const auto& entry : std::filesystem::directory_iterator("Data/Translations")) {
			auto filename_string = entry.path().filename().generic_string();
			if (entry.is_regular_file() && filename_string.starts_with("Devious Curses_") && !filename_string.contains("ENGLISH") && entry.path().extension() == ".json") {
				auto languageString = Util::split(entry.path().stem().generic_string(), "_")[1];

				nlohmann::json to_log = nlohmann::json::parse(R"({})");

				auto translation_filename = entry.path().generic_string();
				std::string english_filename = fmt::format(TRANSLATIONS_PREFIX, "ENGLISH");
				log::debug("Found Translation File {}", translation_filename);

				auto trans = Translator::LoadTranslationsMap(translation_filename);
				auto english = Translator::LoadTranslationsMap(english_filename);

				for (auto [key, value] : english) {
					if (!trans.count(key)) {
						if (Settings::GetSingleton()->debugMode) {
							//log::warn("{} translation is missing key {}", languageString, key);
							//to_log += fmt::format("{}\n", key);
							to_log[key] = value;
						}
					}
				}

				std::ofstream o(fmt::format("Data/DeviousCurses_{}_MissingTranslationKeys.json", languageString));
				o << std::setw(4) << to_log << std::endl;
				o.close();
			}
		}
	}
}