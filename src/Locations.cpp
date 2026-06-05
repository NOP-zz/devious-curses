#include "Locations.h"

#include "Settings.h"
#include "form_ids.h"
#include "Utils.h"

namespace DCURSES {
    LocationType GetLocationType(RE::BGSLocation* location) {
        auto DLC1HunterBaseIntro = StaticDataHolder::GetSingleton()->LookupForm<RE::TESQuest>(0x4E24, "Dawnguard.esm");
        auto playerIsDawnguard = DLC1HunterBaseIntro->IsActive() || DLC1HunterBaseIntro->IsCompleted();

        auto DLC1VampireBaseIntro = StaticDataHolder::GetSingleton()->LookupForm<RE::TESQuest>(0x594C, "Dawnguard.esm");
        auto playerIsVolkihar = DLC1VampireBaseIntro->IsActive() || DLC1VampireBaseIntro->IsCompleted();

        //auto location = player->GetCurrentLocation();

        if (!location) {
            return LocationType::Unknown;
        }

        else if (location->formID == 0x000130FF) { // Tamriel Location
            return LocationType::Wilderness;
        }

        else if (Util::GetFormEditorId(location) == "DLC2SolstheimLocation") {
            return LocationType::Wilderness;
        }

        else if (Util::GetFormEditorId(location) == "DLC1SoulCairnLocation") {
            return LocationType::SoulCairn;
        }

        else if (location->formID == 0x000192B2) { // Sovngard
            return LocationType::Town;
        }

        else if (location->formID == 0x00018E34 || location->formID == 0x00018E42) { // High Hrothgar & Sky Haven Temple
            return LocationType::Town;
        }

        else if (Util::GetFormEditorId(location) == "DLC1VampireCastleLocation") {
            if (playerIsDawnguard) {
                return LocationType::Vampire;
            }
            return LocationType::Town;
        }
        else if (Util::GetFormEditorId(location) == "DLC1HunterHQLocation") {
            if (playerIsVolkihar) {
                return LocationType::Bandit;
            }
            return LocationType::Town;
        }

        else if (Util::GetFormEditorId(location) == "DLC1VampireCastleDungeonLocation") {
            return LocationType::Vampire;
        }
        else if (Util::GetFormEditorId(location) == "DLC1ForebearsHoldhoutLocation") {
            return LocationType::Vampire;
        }
        else if (Util::GetFormEditorId(location) == "DLC1FalmerValleyTempleLocation") {
            return LocationType::Vampire;
        }

        else if (Util::GetFormEditorId(location) == "DLC1DarkfallPassageLocation" || // DLC1 falmer stuff
            Util::GetFormEditorId(location) == "DLC1DarkfallCaveLocation" ||
            Util::GetFormEditorId(location) == "DLC1FalmerValleyLocation") {
            return LocationType::Falmer;
        }

        else if (Util::GetFormEditorId(location) == "DLC2ApocryphaLocation") { // Apocrypha
            return LocationType::Apocrypha;
        }
        else if (location->formID == 0x0003B871) { // Ratway
            return LocationType::Bandit;
        }


        else if (location->HasKeywordString("LocTypePlayerHouse")) {
            return LocationType::PlayerHome;
        }
        else if (location->HasKeywordString("LocTypeCity") || location->HasKeywordString("LocTypeCastle") || location->HasKeywordString("LocTypeTemple") || location->HasKeywordString("LocTypeInn") || location->HasKeywordString("LocTypeHouse")) {
            return LocationType::City;
        }
        else if (location->HasKeywordString("LocTypeTown") || location->HasKeywordString("LocTypeHabitation") || location->HasKeywordString("LocTypeDwelling")) {
            return LocationType::Town;
        }
        else if (location->HasKeywordString("LocTypeDraugrCrypt") || location->HasKeywordString("LocTypeDragonPriestLair")) {
            return LocationType::Draugr;
        }
        else if (location->HasKeywordString("LocTypeDwarvenAutomatons")) {
            return LocationType::Dwarven;
        }
        else if (location->HasKeywordString("LocTypeFalmerHive")) {
            return LocationType::Falmer;
        }
        else if (location->HasKeywordString("LocTypeForswornCamp") || location->HasKeywordString("LocTypeHagravenNest")) {
            return LocationType::Forsworn;
        }
        else if (location->HasKeywordString("LocTypeVampireLair")) {
            return LocationType::Vampire;
        }
        else if (location->HasKeywordString("LocTypeWarlockLair")) {
            return LocationType::Warlock;
        }
        else if (location->HasKeywordString("LocTypeDragonLair")) {
            return LocationType::DragonLair;
        }
        else if (location->HasKeywordString("LocTypeBanditCamp") || location->HasKeywordString("LocTypeMilitaryCamp") || location->HasKeywordString("LocTypeMilitaryFort") || location->HasKeywordString("LocTypeDungeon") || location->HasKeywordString("LocTypeShip")) {
            return LocationType::Bandit;
        }
        else if (location->HasKeywordString("LocTypeMine")) {
            return LocationType::Town;
        }
        else if (location->parentLoc && location->parentLoc != location) {
            auto parent_location_type = GetLocationType(location->parentLoc);
            return parent_location_type;
        }
        else {
            return LocationType::Unknown;
        }
    }

    LocationType GetPlayerLocationType() {
        auto player = RE::PlayerCharacter::GetSingleton();

        auto location = player->GetCurrentLocation();

        if (location) { log::trace("Player is in location {}", Util::GetFormEditorId(location)); }

        auto baseLocationType = GetLocationType(location);

        if (baseLocationType == LocationType::Unknown) {
            if (!player->GetParentCell()->IsInteriorCell()) {
                log::trace("Player is in exterior cell with no keywords.");
                return LocationType::Unknown;
            }
            if (location) { log::warn("Location keywords not covered.", location->GetName()); }
            return LocationType::Unknown;
        }

        return baseLocationType;
    }

    std::string GetLocationTypeString(LocationType type) {
        switch (type) {
        case(LocationType::Wilderness): return "wilderness";
        case(LocationType::PlayerHome): return "player home";
        case(LocationType::City): return "city";
        case(LocationType::Town): return "town";
        case(LocationType::Draugr): return "draugr";
        case(LocationType::Falmer): return "falmer";
        case(LocationType::Dwarven): return "dwarven";
        case(LocationType::Forsworn): return "forsworn";
        case(LocationType::Vampire): return "vampire";
        case(LocationType::Warlock): return "warlock";
        case(LocationType::DragonLair): return "dragon lair";
        case(LocationType::Apocrypha): return "apocrypha";
        case(LocationType::Bandit): return "bandit";
        case(LocationType::SoulCairn): return "soulcairn";
        case(LocationType::Unknown): return "unknown";
        }
        log::error("GetLocationTypeString received bad location type: {}", std::to_underlying(type));
        return "UNKNOWN LOCATION TYPE";
    }

    float GetLocationTypeEventModifier(LocationType type) {
        auto settings = Settings::GetSingleton();

        switch (type) {
        case(LocationType::Wilderness): return settings->wildernessModifier;
        case(LocationType::PlayerHome): return settings->playerHomeModifier;
        case(LocationType::City): return settings->cityModifier;
        case(LocationType::Town): return settings->townModifier;
        case(LocationType::Draugr): return settings->draugrModifier;
        case(LocationType::Falmer): return settings->falmerModifier;
        case(LocationType::Dwarven): return settings->dwarvenModifier;
        case(LocationType::Forsworn): return settings->forswornModifier;
        case(LocationType::Vampire): return settings->vampireModifier;
        case(LocationType::Warlock): return settings->warlockModifier;
        case(LocationType::DragonLair): return settings->dragonLairModifier;
        case(LocationType::Apocrypha): return settings->apocryphaModifier;
        case(LocationType::Bandit): return settings->banditModifier;
        case(LocationType::SoulCairn): return settings->soulCairnModifier;
        case(LocationType::Unknown): return 1.0;
        }
        log::error("GetLocationTypeEventModifier received bad location type: {}", std::to_underlying(type));
        return 0;
    }
}