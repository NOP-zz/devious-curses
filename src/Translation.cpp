#include "Translation.h"

#include <string>
#include <filesystem>
#include <codecvt>

#include "apis/JSON.hpp"
#include "Utils.h"
#include "Settings.h"

namespace DCURSES {
	TranslationsMap* Translator::GetTranslationsMap() {
		static TranslationsMap translations;
		return &translations;
	}
	TranslationsMap Translator::LoadTranslationsMap(std::string langFilename) {
		if (!std::filesystem::exists(langFilename)) {
			log::error("Unable to get translation file {}.", langFilename);
			return TranslationsMap();
		}

		std::ifstream i(langFilename);
		nlohmann::json j = nlohmann::json::parse("{}");

		try {
			i >> j;
			return j.get<TranslationsMap>();
		}
		catch (...) {
			log::error("Unable to parse Translation file {}.", langFilename);
			return TranslationsMap();
		}
	}
	std::string Translator::GetTranslationKeyName(Translation key) {
		switch (key) {
			//CODEGEN_START_KEYNAME
			case (Translation::ConsequenceRandomDevice_Sex): return "ConsequenceRandomDevice_Sex";
			case (Translation::ConsequenceRandomDevice_Nude): return "ConsequenceRandomDevice_Nude";
			case (Translation::ConsequenceRandomDevice_Restrained): return "ConsequenceRandomDevice_Restrained";
			case (Translation::ConsequenceRandomDevice_Heavy): return "ConsequenceRandomDevice_Heavy";
			case (Translation::ConsequenceRandomDevice_Tattoo): return "ConsequenceRandomDevice_Tattoo";
			case (Translation::ConsequenceRandomDevice_Trespass): return "ConsequenceRandomDevice_Trespass";
			case (Translation::ConsequenceSex_Sex): return "ConsequenceSex_Sex";
			case (Translation::ConsequenceSex_Nude): return "ConsequenceSex_Nude";
			case (Translation::ConsequenceSex_Restrained): return "ConsequenceSex_Restrained";
			case (Translation::ConsequenceSex_Heavy): return "ConsequenceSex_Heavy";
			case (Translation::ConsequenceSex_Tattoos): return "ConsequenceSex_Tattoos";
			case (Translation::ConsequenceSex_Trespass): return "ConsequenceSex_Trespass";
			case (Translation::ConsequenceFine_Sex): return "ConsequenceFine_Sex";
			case (Translation::ConsequenceFine_SeenNude): return "ConsequenceFine_SeenNude";
			case (Translation::ConsequenceFine_TalkedNude): return "ConsequenceFine_TalkedNude";
			case (Translation::ConsequenceFine_SeenRestrained): return "ConsequenceFine_SeenRestrained";
			case (Translation::ConsequenceFine_TalkedRestrained): return "ConsequenceFine_TalkedRestrained";
			case (Translation::ConsequenceFine_SeenTattoos): return "ConsequenceFine_SeenTattoos";
			case (Translation::ConsequenceFine_TalkedTattoos): return "ConsequenceFine_TalkedTattoos";
			case (Translation::ConsequenceTattoo_Sex): return "ConsequenceTattoo_Sex";
			case (Translation::ConsequenceTattoo_SexMultiple): return "ConsequenceTattoo_SexMultiple";
			case (Translation::ConsequenceTattoo_Trespass): return "ConsequenceTattoo_Trespass";
			case (Translation::ConsequenceTattoo_TrespassMultiple): return "ConsequenceTattoo_TrespassMultiple";
			case (Translation::ConsequenceTattoo_Other): return "ConsequenceTattoo_Other";
			case (Translation::ConsequenceTattoo_OtherMultiple): return "ConsequenceTattoo_OtherMultiple";
			case (Translation::ConsequenceMercy_Unlock): return "ConsequenceMercy_Unlock";
			case (Translation::ConsequenceMercy_Key): return "ConsequenceMercy_Key";
			case (Translation::ODeviceSummonerCollarStart): return "ODeviceSummonerCollarStart";
			case (Translation::ODeviceSummonerCollarRemove): return "ODeviceSummonerCollarRemove";
			case (Translation::ODeviceSummonerCollarUnlock): return "ODeviceSummonerCollarUnlock";
			case (Translation::ODeviceLivingLatexStart): return "ODeviceLivingLatexStart";
			case (Translation::ODeviceLivingLatexSpread): return "ODeviceLivingLatexSpread";
			case (Translation::ODeviceLivingLatexTrigger): return "ODeviceLivingLatexTrigger";
			case (Translation::ODeviceLivingLatexOnHit): return "ODeviceLivingLatexOnHit";
			case (Translation::ODeviceLivingLatexOnHitFrost): return "ODeviceLivingLatexOnHitFrost";
			case (Translation::ODeviceLivingLatexRemove): return "ODeviceLivingLatexRemove";
			case (Translation::ODeviceDwarvenCuirassStart): return "ODeviceDwarvenCuirassStart";
			case (Translation::ODeviceDwarvenCuirassEat): return "ODeviceDwarvenCuirassEat";
			case (Translation::ODeviceDwarvenCuirassDestroyBelt): return "ODeviceDwarvenCuirassDestroyBelt";
			case (Translation::ODeviceDwarvenCuirassMasturbate): return "ODeviceDwarvenCuirassMasturbate";
			case (Translation::ODeviceDwarvenCuirassCraft): return "ODeviceDwarvenCuirassCraft";
			case (Translation::ODeviceDwarvenCuirassRemove): return "ODeviceDwarvenCuirassRemove";
			case (Translation::ODeviceMadnessPlugStart): return "ODeviceMadnessPlugStart";
			case (Translation::ODeviceMadnessPlugPiercings): return "ODeviceMadnessPlugPiercings";
			case (Translation::ODeviceMadnessPlugDesire): return "ODeviceMadnessPlugDesire";
			case (Translation::ODeviceMadnessPlugStandard): return "ODeviceMadnessPlugStandard";
			case (Translation::ODeviceMadnessPlugBoss): return "ODeviceMadnessPlugBoss";
			case (Translation::ODeviceMadnessPlugFullTie): return "ODeviceMadnessPlugFullTie";
			case (Translation::ODeviceMadnessPlugFollowers): return "ODeviceMadnessPlugFollowers";
			case (Translation::ODeviceMadnessPlugFullTieFollowers): return "ODeviceMadnessPlugFullTieFollowers";
			case (Translation::ODeviceMadnessPlugMark): return "ODeviceMadnessPlugMark";
			case (Translation::ODeviceMadnessPlugTattoos): return "ODeviceMadnessPlugTattoos";
			case (Translation::ODeviceMadnessPlugTattooFollowers): return "ODeviceMadnessPlugTattooFollowers";
			case (Translation::ODeviceMadnessPlugStats): return "ODeviceMadnessPlugStats";
			case (Translation::ODeviceMadnessPlugGold): return "ODeviceMadnessPlugGold";
			case (Translation::ODeviceMadnessPlugCrash): return "ODeviceMadnessPlugCrash";
			case (Translation::ODeviceMadnessPlugRemove): return "ODeviceMadnessPlugRemove";
			case (Translation::ODeviceMadnessPlugHunger): return "ODeviceMadnessPlugHunger";
			case (Translation::ODeviceMadnessPlugOrgasm): return "ODeviceMadnessPlugOrgasm";
			case (Translation::ODeviceMadnessPlugLongVib): return "ODeviceMadnessPlugLongVib";
			case (Translation::ODeviceMadnessPlugMediumVib): return "ODeviceMadnessPlugMediumVib";
			case (Translation::ODeviceMadnessPlugSuperVib): return "ODeviceMadnessPlugSuperVib";
			case (Translation::ODeviceMadnessDescription): return "ODeviceMadnessDescription";
			case (Translation::ODeviceMadnessDescriptionSex): return "ODeviceMadnessDescriptionSex";
			case (Translation::ODeviceNocturnalPiercingStart): return "ODeviceNocturnalPiercingStart";
			case (Translation::ODeviceNocturnalPiercingAnger): return "ODeviceNocturnalPiercingAnger";
			case (Translation::ODeviceNocturnalPiercingRemove): return "ODeviceNocturnalPiercingRemove";
			case (Translation::ODeviceNocturnalPiercingVibrate): return "ODeviceNocturnalPiercingVibrate";
			case (Translation::ODeviceNocturnalPiercingHands): return "ODeviceNocturnalPiercingHands";
			case (Translation::ODeviceNocturnalPiercingHands2): return "ODeviceNocturnalPiercingHands2";
			case (Translation::ODeviceNocturnalPiercingHands3): return "ODeviceNocturnalPiercingHands3";
			case (Translation::ODeviceNocturnalPiercingHands4): return "ODeviceNocturnalPiercingHands4";
			case (Translation::ODeviceNocturnalPiercingHandsRecast): return "ODeviceNocturnalPiercingHandsRecast";
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
			case (Translation::EventMarkHealslut): return "EventMarkHealslut";
			case (Translation::EventMarkPainslut): return "EventMarkPainslut";
			case (Translation::EventWicked): return "EventWicked";
			case (Translation::EventAbadon): return "EventAbadon";
			case (Translation::EventAbadonWarrior): return "EventAbadonWarrior";
			case (Translation::EventAbadonScout): return "EventAbadonScout";
			case (Translation::EventAbadonWitch): return "EventAbadonWitch";
			case (Translation::MarkHeatRemove): return "MarkHeatRemove";
			case (Translation::MarkAllureRemove): return "MarkAllureRemove";
			case (Translation::MarkBondageDevice): return "MarkBondageDevice";
			case (Translation::MarkBondageRemove): return "MarkBondageRemove";
			case (Translation::MarkBondageCurse): return "MarkBondageCurse";
			case (Translation::MarkNudityEnforce): return "MarkNudityEnforce";
			case (Translation::MarkNudityRemove): return "MarkNudityRemove";
			case (Translation::MarkBrandingPunish): return "MarkBrandingPunish";
			case (Translation::MarkBrandingTattoo): return "MarkBrandingTattoo";
			case (Translation::MarkBrandingRemove): return "MarkBrandingRemove";
			case (Translation::MarkHealslutRemove): return "MarkHealslutRemove";
			case (Translation::MarkPainslutSex): return "MarkPainslutSex";
			case (Translation::MarkPainslutRemove): return "MarkPainslutRemove";
			case (Translation::QIMalkoranCurse): return "QIMalkoranCurse";
			case (Translation::QISanguineStart): return "QISanguineStart";
			case (Translation::QISanguineKey): return "QISanguineKey";
			case (Translation::QISanguineKeyMark): return "QISanguineKeyMark";
			case (Translation::QISaarthal): return "QISaarthal";
			case (Translation::QIBrelyna): return "QIBrelyna";
			case (Translation::QIDwemerMuseum): return "QIDwemerMuseum";
			case (Translation::QIDwemerMuseumCurias): return "QIDwemerMuseumCurias";
			case (Translation::QIProvingHonor): return "QIProvingHonor";
			case (Translation::QIBlackStarEquip): return "QIBlackStarEquip";
			case (Translation::QIDiplomaticImmunity): return "QIDiplomaticImmunity";
			case (Translation::QIMindOfMadness): return "QIMindOfMadness";
			case (Translation::QILaidToRest): return "QILaidToRest";
			case (Translation::QICriedWolf): return "QICriedWolf";
			case (Translation::QIRingmaker): return "QIRingmaker";
			case (Translation::QITrinityRestored): return "QITrinityRestored";
			case (Translation::QIDeliveryStart): return "QIDeliveryStart";
			case (Translation::QIDeliveryEnd): return "QIDeliveryEnd";
			case (Translation::QIDeliveryEndBad): return "QIDeliveryEndBad";
			case (Translation::ItemMagicKey): return "ItemMagicKey";
			case (Translation::ItemMagicKeyOther): return "ItemMagicKeyOther";
			case (Translation::ItemTattooCharm): return "ItemTattooCharm";
			case (Translation::ItemTattooCharmOther): return "ItemTattooCharmOther";
			case (Translation::ItemArousalPotion): return "ItemArousalPotion";
			case (Translation::ItemWardUsed): return "ItemWardUsed";
			case (Translation::EffectLivingLatexWait): return "EffectLivingLatexWait";
			case (Translation::EffectLivingLatexDormant): return "EffectLivingLatexDormant";
			case (Translation::EffectLivingLatexAwoken): return "EffectLivingLatexAwoken";
			case (Translation::EffectLivingLatexCling): return "EffectLivingLatexCling";
			case (Translation::FastTravelUnableHeavy): return "FastTravelUnableHeavy";
			case (Translation::FastTravelUnableBoots): return "FastTravelUnableBoots";
			case (Translation::FastTravelUnableBlind): return "FastTravelUnableBlind";
			case (Translation::FastTravelUnableHobble): return "FastTravelUnableHobble";
			case (Translation::FastTravelUnableVisible): return "FastTravelUnableVisible";
			case (Translation::FastTravelUnableDevices): return "FastTravelUnableDevices";
			case (Translation::FastTravelUnableNamed): return "FastTravelUnableNamed";
			case (Translation::QuestLFTrinketName): return "QuestLFTrinketName";
			//CODEGEN_END_KEYNAME
		}
		log::error("Unable to find translation key name for id {}", static_cast<uint32_t>(key));
		return "ERROR";
	}
	std::string Translator::_GetTranslation(Translation key) {
		auto translations = GetTranslationsMap();
		auto keyname = GetTranslationKeyName(key);
		if (translations->count(keyname)) {
			return translations->at(keyname);
		}
		log::error("Unable to find translation for key {}", keyname);
		return "ERROR";
	}
	Translator::Translator() {}
	Translator::Translator(Translation key) {
		translatedString = _GetTranslation(key);
	}
	std::string Translator::GetTranslation() {
		return translatedString;
	}
	void Translator::UpdateTranslations() {
		auto translations = GetTranslationsMap();
		translations->clear();

		auto languageString = Util::toupper(RE::GetINISetting("sLanguage:General")->GetString());
		TranslationData::GetSingleton()->languageFilename = fmt::format(TRANSLATIONS_PREFIX, Util::toupper(languageString));
		std::string englishFilename = fmt::format(TRANSLATIONS_PREFIX, "ENGLISH");

		if (!std::filesystem::exists(TranslationData::GetSingleton()->languageFilename)) {
			log::warn("Language file for {} does not exist, defaulting to ENGLISH.", languageString);
			languageString = "ENGLISH";
			TranslationData::GetSingleton()->languageFilename = fmt::format(TRANSLATIONS_PREFIX, "ENGLISH");
		}

		log::info("Loading language file {}", TranslationData::GetSingleton()->languageFilename);

		if (languageString == "ENGLISH") {
			*translations = LoadTranslationsMap(englishFilename);
		}
		else {
			auto lang = LoadTranslationsMap(TranslationData::GetSingleton()->languageFilename);
			auto english = LoadTranslationsMap(englishFilename);

			for (auto [key, value] : english) {
				if (!lang.count(key)) {
					lang[key] = english[key];
				}
			}

			*translations = lang;
		}
	}
	}