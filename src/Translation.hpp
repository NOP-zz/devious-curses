#pragma once

#include <string>
#include <filesystem>
#include <codecvt>

#include "JSON.hpp"
#include "Utils.hpp"

constexpr auto TRANSLATIONS_PREFIX = "Data/translations/Devious Curses_{}.json";

namespace DCURSES {
	enum class Translation : uint32_t {
		//TRNASLATIONS_START
		ConsequenceRandomDeviceSex,//Now that {} is done with you, they force a {} on you before you can react!
		ConsequenceRandomDeviceTalk,//Before you can talk to {} they force a {} on you before you can react!
		ConsequenceSexContinue,//{} wasn't satisfied with your performance and goes in for another round!
		ConsequenceSexTalk,//Before you can talk to {} they grab you and takes of your clothes!
		ConsequenceFineSex,//Someone saw you having sex with {} and reported you to the guard!
		ConsequenceFineTalk,//Before you can talk to {} they call a guard and report you!
		ConsequenceMercyUnlock,//{} feels bad for you and unlocks your restraints.
		ConsequenceMercyKey,//{} feels bad for you and gives you a {}.
		ConsequenceMercyDevice,//{} thinks you look bored and gives you a {}.

		ODeviceSummonerCollarStart,//As you touch the {} you feel very dizzy as a heavy collar forms around your neck and absorbs your magicka!
		ODeviceSummonerCollarUnlock,//The Summoner Collar is now satisfied and you can unlock it!
		ODeviceLivingLatexStart,//As you touch the {} a ball of goo jumps out at you and covers your body!
		ODeviceLivingLatexSpread,//The latex has spread over your body!
		ODeviceLivingLatexOnHit,//The latex writhes while being shocked. It seems as if it has been weakened significantly!
		ODeviceLivingLatexRemove,//The latex suit dissolves from your body!
		ODeviceDwarvenCuirassStart,//As you touch the {} you feel a dwarven automaton crawl onto your body!
		ODeviceDwarvenCuirassEat,//The dwarven cuirass pulls some parts from your bag!
		ODeviceDwarvenCuirassDestroyBelt,//You flinch as the dwarven cuirass reaches down and snaps your chastity belt in half!
		ODeviceDwarvenCuirassMasturbate,//You freeze as the dwarven cuirass takes control and starts masturbating you!
		ODeviceDwarvenCuirassCraft,//The dwarven cuirass makes a {} with some of it's parts and puts it on you!
		ODeviceDwarvenCuirassRemove,//Your skin crawls as the dwarven atomaton climbs off you and morphs into a {}!

		EventDevices,//As you touch the {} you see restraints magically appear and wrap themselves around you!
		EventSimpleSlavery,//As you touch the {} you see a flash of light and immediately pass out. Through intermittent consciousness you can feel someone carrying you somewhere...
		EventTattooOne,//As you touch the {} you feel a sharp pain as a tattoo appears on your body!
		EventTattooTwoThree,//As you touch the {} you feel a sharp pain as a few tattoos appear on your body!
		EventTattooMany,//As you touch the {} you feel a sharp pain as your body is covered in tattoos!
		EventContraption,//As you touch the {} you feel yourself get dizzy as you are strung up into some sort of contraption!
		EventMarkBranding,//After a sharp pain, you see that you have a mark of branding.
		EventMarkAllure,//After a sharp pain, you see that you have a mark of allure.
		EventMarkHeat,//After a sharp pain, you see that you have a mark of heat.
		EventMarkBondage,//After a sharp pain, you see that you have a mark of bondage.
		EventMarkNudity,//After a sharp pain, you see that you have a mark of nudity.

		MarkHeatRemove,//You feel a sense of calm as the heat mark fades from your body.
		MarkAllureRemove,//You sense that people are no longer staring at you as the allure mark fades from your body.
		MarkBondageDevice,//Your mark pulses with light as your {} appears on your body!
		MarkBondageRemove,//You feel much less oppressed as the bondage mark fades from your body.
		MarkNudityRemove,//You feel less helpless as the nudity mark fades from your body.
		MarkBrandingPunish,//You loose {} gold as punishment for loosing tattoos!
		MarkBrandingTattoo,//You feel a sharp pain as the mark brands you!
		MarkBrandingRemove,//You feel the branding mark fade from your body.

		QIMalkoranCurse,//As you kill Malkoran he curses you with a mark of branding!
		QISanguineStart,//As you awaken you notice that you're covered in chains and have a strange mark on you. Hopefully Sam can fix this...
		QISanguineKey,//Now that your wild adventure with Sanguine is over, he gives you a magic key!
		QISanguineKeyMark,//Now that your wild adventure with Sanguine is over, he gives you a magic key and removes your nudity mark!
		QISaarthal,//Strange magic interacts with the amulet transforming it into a collar!
		QIDwemerMuseum,//As you touch the stone tablet you feel a sharp pain in your crotch!
		QIDwemerMuseumCurias,//As you touch the stone tablet you feel a sharp pain in your crotch! While you're distracted, a strange dwemer creature runs up behind you and jumps on you!

		ItemMagicKey,//All of the devices you were wearing have magically dissapeared!
		ItemTattooCharm,//All of your tattoos have faded from your body!

		EffectLivingLatexWait,//The latex suit seems to be dormant. You will probably have to wait for a while.
		EffectLivingLatexDormant,//The latex suit seems to be dormant. Maybe it would do something if it was attacked.
		EffectLivingLatexAwoken,//The latex has awoken! Maybe you can weaken it by shocking it.
		EffectLivingLatexCling,//The latex is clinging to you only by your other devices, removing them should do the trick!
		//TRNASLATIONS_END
	};

	typedef std::map<std::string, std::string> TranslationsMap;

	class Translator {
	private:
		static TranslationsMap* GetTranslationsMap() {
			static TranslationsMap translations;
			return &translations;
		}

		static TranslationsMap LoadTranslationsMap(std::string languageFilename) {
			if (!std::filesystem::exists(languageFilename)) {
				log::error("Unable to get translation file {}.", languageFilename);
				return TranslationsMap();
			}

			std::ifstream i(languageFilename);
			nlohmann::json j = nlohmann::json::parse("{}");

			try {
				i >> j;
				return j.get<TranslationsMap>();
			}
			catch (...) {
				log::error("Unable to parse Translation file {}.", languageFilename);
				return TranslationsMap();
			}
		}

		static std::string GetTranslationKeyName(Translation key) {
			switch (key) {
				//CODEGEN_START_KEYNAME
				case (Translation::ConsequenceRandomDeviceTalk): return "ConsequenceRandomDeviceTalk";
				case (Translation::ConsequenceSexContinue): return "ConsequenceSexContinue";
				case (Translation::ConsequenceSexTalk): return "ConsequenceSexTalk";
				case (Translation::ConsequenceFineSex): return "ConsequenceFineSex";
				case (Translation::ConsequenceFineTalk): return "ConsequenceFineTalk";
				case (Translation::ConsequenceMercyUnlock): return "ConsequenceMercyUnlock";
				case (Translation::ConsequenceMercyKey): return "ConsequenceMercyKey";
				case (Translation::ConsequenceMercyDevice): return "ConsequenceMercyDevice";
				case (Translation::ODeviceSummonerCollarStart): return "ODeviceSummonerCollarStart";
				case (Translation::ODeviceSummonerCollarUnlock): return "ODeviceSummonerCollarUnlock";
				case (Translation::ODeviceLivingLatexStart): return "ODeviceLivingLatexStart";
				case (Translation::ODeviceLivingLatexSpread): return "ODeviceLivingLatexSpread";
				case (Translation::ODeviceLivingLatexOnHit): return "ODeviceLivingLatexOnHit";
				case (Translation::ODeviceLivingLatexRemove): return "ODeviceLivingLatexRemove";
				case (Translation::ODeviceDwarvenCuirassStart): return "ODeviceDwarvenCuirassStart";
				case (Translation::ODeviceDwarvenCuirassEat): return "ODeviceDwarvenCuirassEat";
				case (Translation::ODeviceDwarvenCuirassDestroyBelt): return "ODeviceDwarvenCuirassDestroyBelt";
				case (Translation::ODeviceDwarvenCuirassMasturbate): return "ODeviceDwarvenCuirassMasturbate";
				case (Translation::ODeviceDwarvenCuirassCraft): return "ODeviceDwarvenCuirassCraft";
				case (Translation::ODeviceDwarvenCuirassRemove): return "ODeviceDwarvenCuirassRemove";
				case (Translation::EventDevices): return "EventDevices";
				case (Translation::EventSimpleSlavery): return "EventSimpleSlavery";
				case (Translation::EventTattooOne): return "EventTattooOne";
				case (Translation::EventTattooTwoThree): return "EventTattooTwoThree";
				case (Translation::EventTattooMany): return "EventTattooMany";
				case (Translation::EventContraption): return "EventContraption";
				case (Translation::EventMarkBranding): return "EventMarkBranding";
				case (Translation::EventMarkAllure): return "EventMarkAllure";
				case (Translation::EventMarkHeat): return "EventMarkHeat";
				case (Translation::EventMarkBondage): return "EventMarkBondage";
				case (Translation::EventMarkNudity): return "EventMarkNudity";
				case (Translation::MarkHeatRemove): return "MarkHeatRemove";
				case (Translation::MarkAllureRemove): return "MarkAllureRemove";
				case (Translation::MarkBondageDevice): return "MarkBondageDevice";
				case (Translation::MarkBondageRemove): return "MarkBondageRemove";
				case (Translation::MarkNudityRemove): return "MarkNudityRemove";
				case (Translation::MarkBrandingPunish): return "MarkBrandingPunish";
				case (Translation::MarkBrandingTattoo): return "MarkBrandingTattoo";
				case (Translation::MarkBrandingRemove): return "MarkBrandingRemove";
				case (Translation::QIMalkoranCurse): return "QIMalkoranCurse";
				case (Translation::QISanguineStart): return "QISanguineStart";
				case (Translation::QISanguineKey): return "QISanguineKey";
				case (Translation::QISanguineKeyMark): return "QISanguineKeyMark";
				case (Translation::QISaarthal): return "QISaarthal";
				case (Translation::QIDwemerMuseum): return "QIDwemerMuseum";
				case (Translation::QIDwemerMuseumCurias): return "QIDwemerMuseumCurias";
				case (Translation::ItemMagicKey): return "ItemMagicKey";
				case (Translation::ItemTattooCharm): return "ItemTattooCharm";
				case (Translation::EffectLivingLatexWait): return "EffectLivingLatexWait";
				case (Translation::EffectLivingLatexDormant): return "EffectLivingLatexDormant";
				case (Translation::EffectLivingLatexAwoken): return "EffectLivingLatexAwoken";
				case (Translation::EffectLivingLatexCling): return "EffectLivingLatexCling";
				//CODEGEN_END_KEYNAME
			}
			log::error("Unable to find translation key name");
			return "ERROR";
		}

		static std::string _GetTranslation(Translation key) {
			auto translations = GetTranslationsMap();
			auto keyname = GetTranslationKeyName(key);
			if (translations->count(keyname)) {
				return translations->at(keyname);
			}
			log::error("Unable to find translation for key {}", keyname);
			return "ERROR";
		}

		std::string translatedString;
	public:
		Translator(Translation key) {
			translatedString = _GetTranslation(key);
		}

		template<typename... Args>
		Translator(Translation key, Args... args) {
			translatedString = fmt::vformat(_GetTranslation(key), fmt::make_format_args(args...));
		}

		std::string GetTranslation() {
			return translatedString;
		}

		static void UpdateTranslations() {
			auto translations = GetTranslationsMap();
			translations->clear();

			auto languageString = Util::toupper(RE::GetINISetting("sLanguage:General")->GetString());
			std::string languageFilename = fmt::format(TRANSLATIONS_PREFIX, Util::toupper(languageString));
			std::string englishFilename = fmt::format(TRANSLATIONS_PREFIX, "ENGLISH");

			if (!std::filesystem::exists(languageFilename)) {
				log::warn("Language file for {} does not exist, defaulting to ENGLISH.", languageString);
				languageString = "ENGLISH";
				languageFilename = fmt::format(TRANSLATIONS_PREFIX, "ENGLISH");
			}

			log::info("Loading language file {}", languageFilename);

			if (languageString == "ENGLISH") {
				*translations = LoadTranslationsMap(englishFilename);
			}
			else {
				auto lang = LoadTranslationsMap(languageFilename);
				auto english = LoadTranslationsMap(englishFilename);

				for (auto [key, value] : english) {
					if (!lang.count(key)) {
						log::warn("{} translation is missing key {}", languageString, key);
						lang[key] = english[key];
					}
				}

				*translations = lang;
			}
		}

		static void CheckMCMTranslations() {
			auto languageString = Util::toupper(RE::GetINISetting("sLanguage:General")->GetString());
			if (languageString == "ENGLISH") {
				return;
			}

			std::string languageFilename = fmt::format("Data/interface/translations/Devious Curses_{}.txt", Util::toupper(languageString));
			std::string englishFilename = "Data/interface/translations/Devious Curses_ENGLISH.txt";
			if (!std::filesystem::exists(languageFilename)) {
				log::warn("MCM Translation file for {} does not exist, cloning ENGLISH.", languageString);
				std::filesystem::copy_file(englishFilename, languageFilename);
				return;
			}

			//std::filesystem::rename(languageFilename, languageFilename + ".temp");

			std::ifstream eng(englishFilename, std::ios::binary);
			eng.ignore(2);

			std::ifstream lang(languageFilename, std::ios::binary);
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

			std::ofstream out(languageFilename, std::ios::binary);

			out << "\xFF\xFE";

			for (auto& [token, value] : engMap) {
				if (langMap.count(token)) {
					out << langMap[token] << '\n';
				}
				else {
					std::string tokenPrint;
					for (size_t i = 0; i < token.size(); i++) {
						if (token[i]) {
							tokenPrint.push_back(token[i]);
						}
					}
					tokenPrint += (char)0;
					log::warn("{} MCM translation missing key {}", languageString, tokenPrint);
					out << value << '\n';
				}
			}

			
			out.close();

			//std::filesystem::remove(languageFilename + ".temp");
		}
	};
}