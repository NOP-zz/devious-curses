#pragma once

#include "JSON.hpp"

constexpr static auto LOCATIONS_FILE = "Data/SKSE/Plugins/DeviousCursesDebugLocations.json";

namespace DCURSES::Debug {
	
	void Test() {
		log::trace("DCURSES Test");
		auto player = RE::PlayerCharacter::GetSingleton();

		log::trace("Madness Paralyze");
		RE::SpellItem* paralyze = StaticDataHolder::GetSingleton()->LookupForm<RE::SpellItem>(0x5AD5F, "Skyrim.esm");
		paralyze->data.delivery = RE::MagicSystem::Delivery::kSelf;
		RE::MagicCaster* caster = player->GetMagicCaster(RE::MagicSystem::CastingSource::kOther);
		caster->CastSpellImmediate(paralyze, false, player, 1.0f, false, 0.0f, nullptr);
		paralyze->data.delivery = RE::MagicSystem::Delivery::kAimed;
	}


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
				{"parents", location_parents_string},
				{"type", location_type_string}
			};
		}

		SaveLocationMap(j);
	}

	void CheckMCMTranslations() {
		std::ifstream englishTranslationsFile("Data/interface/translations/Devious Curses_ENGLISH.txt", std::ios::binary);
		englishTranslationsFile.ignore(2);

		std::vector<std::string> englishTranslationsMap;
		{
			log::debug("Reading english translation file");
			std::string line;
			while (std::getline(englishTranslationsFile, line)) {
				if (line.find('\t') == std::string::npos) { continue; }
				auto token = line.substr(0, line.find('\t'));
				englishTranslationsMap.push_back(token);
			}
		}

		for (const auto& entry : std::filesystem::directory_iterator("Data/interface/translations/")) {
			auto filename_string = entry.path().filename().generic_string();
			if (entry.is_regular_file() && filename_string._Starts_with("Devious Curses_") && !filename_string.contains("ENGLISH") && entry.path().extension() == ".txt") {
				auto languageString = Util::split(entry.path().stem().generic_string(), "_")[1];

				log::debug("Found Translation File {}", entry.path().filename().generic_string());

				std::ifstream translationsFile(entry.path(), std::ios::binary);
				translationsFile.ignore(2);

				std::map<std::string, int> translationsMap;

				std::string line;
				while (std::getline(translationsFile, line)) {
					if (line.find('\t') == std::string::npos) { continue; }
					auto token = line.substr(0, line.find('\t'));
					translationsMap[token] = 0;
				}

				for (auto& token : englishTranslationsMap) {
					if (!translationsMap.count(token)) {
						std::string tokenPrint;
						for (size_t i = 0; i < token.size(); i++) {
							if (token[i]) {
								tokenPrint.push_back(token[i]);
							}
						}
						log::warn("{} MCM translation is missing: {}", languageString, tokenPrint);
					}
				}
			}
		}
	}

	void CheckMCMTranslationsOLD() {
		auto languageString = Util::toupper(RE::GetINISetting("sLanguage:General")->GetString());
		if (languageString == "ENGLISH") {
			return;
		}

		std::string mcmLanguageFilename = fmt::format("Data/interface/translations/Devious Curses_{}.txt", Util::toupper(languageString));
		std::string englishFilename = "Data/interface/translations/Devious Curses_ENGLISH.txt";
		if (!std::filesystem::exists(languageFilename)) {
			log::warn("MCM Translation file for {} does not exist, cloning ENGLISH.", languageString);
			std::filesystem::copy_file(englishFilename, languageFilename);
			return;
		}

		//std::filesystem::rename(mcmLanguageFilename, mcmLanguageFilename + ".temp");

		std::ifstream eng(englishFilename, std::ios::binary);
		eng.ignore(2);

		std::ifstream lang(mcmLanguageFilename, std::ios::binary);
		lang.ignore(2);

		std::vector<std::pair<std::string, std::string>> engMap;
		std::map<std::string, std::string> langMap;

		std::string line;
		while (std::getline(eng, line)) {
			if (line.find('\t') == std::string::npos) { continue; }
			auto token = line.substr(0, line.find('\t'));
			if (token[0] == '\0') token = token.substr(1);
			engMap.push_back({ token, line });
		}
		while (std::getline(lang, line)) {
			if (line.find('\t') == std::string::npos) { continue; }
			auto token = line.substr(0, line.find('\t'));
			if (token[0] == '\0') token = token.substr(1);
			langMap[token] = line;
		}

		std::ofstream out(mcmLanguageFilename, std::ios::binary);

		out << "\xFF\xFE";

		for (auto& [token, value] : engMap) {
			std::string tokenPrint;
			for (size_t i = 0; i < token.size(); i++) {
				if (token[i]) {
					tokenPrint.push_back(token[i]);
				}
			}

			if (langMap.count(token)) {
				out << langMap[token] << '\n';
				if (langMap[token] == value) {
					log::warn("{} MCM translation matches english: {} ({})", languageString, tokenPrint, langMap[token]);
				}
			}
			else {

				tokenPrint += (char)0;
				log::warn("{} MCM translation missing key {}", languageString, tokenPrint);
				out << value << '\n';
			}
		}


		out.close();

		//std::filesystem::remove(mcmLanguageFilename + ".temp");
	}
}