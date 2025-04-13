#pragma once

#include "tats.hpp"
#include "devices.hpp"
#include "Consequences.hpp"
#include "SGO.hpp"

#include "../include/DDNG_API.h"
#include "../include/form_ids.h"

/*
Event ideas:
Gag of endless hunger: ring gag, can only be removed after a lot of oral sex.
Plugs of endless hunger: plugs with allow, can only be removed after a lot of anal / vaginal sex.
*/

namespace DCURSES {

    void UndressActor(RE::Actor* akActor) {
        if (!akActor) return;

        for (uint32_t i = 1; i < (1 << 31); i = i << 1) {
            RE::TESObjectARMO* equipped = akActor->GetWornArmor((RE::BIPED_MODEL::BipedObjectSlot)i);
            if (i == (uint32_t)RE::BIPED_MODEL::BipedObjectSlot::kAmulet || i == (uint32_t)RE::BIPED_MODEL::BipedObjectSlot::kRing || i == (uint32_t)RE::BIPED_MODEL::BipedObjectSlot::kCirclet) {
                continue;
            }
            if (equipped == nullptr) { continue; }
            if (equipped->HasKeywordString("SexLabNoStrip")) {
                continue;
            }
            UnequipItem(akActor, equipped);
        }
        auto inventory = akActor->GetInventory();
        for (auto const& [k, v] : inventory) {
            if (v.second.get()->IsWorn()) {
                RE::TESAmmo* ammo = k->As<RE::TESAmmo>();
                if (!ammo) {
                    continue;
                }
                UnequipItem(akActor, ammo);
            }
        }
        auto rightHand = akActor->GetEquippedObject(false);
        //UnequipSpell(akActor, rightHand, 1);
        UnequipItem(akActor, rightHand);
        auto leftHand = akActor->GetEquippedObject(true);
        //UnequipSpell(akActor, leftHand, 0);
        UnequipItem(akActor, leftHand);
        akActor->DrawWeaponMagicHands(false);
    }

    void GenerateRandomDevices(RE::TESObjectREFR* activatedObject) {
        if (!(activatedObject && activatedObject->HasContainer())) {
            return;
        }
        bool hasBondageMark = GetLewdMark(RE::PlayerCharacter::GetSingleton()) == TAT_BONDAGE;
        float chance = settings.rDeviceBaseChance + (hasBondageMark * 2.5f);
        for (int i = 0; i < 2 + (hasBondageMark * 2); i++) {
            if (Util::randomDouble() < chance) {
                auto dev = GetRandomDevice(&devices.anything);
                //activatedObject->GetContainer()->AddObjectToContainer((RE::TESBoundObject*)pair->first, 1, GetPlayer());
                if (dev) {
                    activatedObject->AddObjectToContainer((RE::TESBoundObject*)dev.value().inv, nullptr, 1, nullptr);
                }
            }
        }
    }

    void DoStandardEvent(bool isBoss, std::string contName, std::string editorIdRequires = "", int countOverride = -1, std::vector<std::string> skipKeywords = {}) {
        RE::Actor* player = RE::PlayerCharacter::GetSingleton();
        if (Util::randomDouble() < settings.keyLossChance) {
            RemoveKeys(player);
        }
        ForceThirdPerson();
        std::vector<std::string> usedKeys = GetKeywordsCantEquip(player);
        for (auto kw : skipKeywords) {
            usedKeys.push_back(kw);
        }
        int count = Util::randomInt(settings.minRestraints, settings.maxRestraints);
        if (countOverride > 0) {
            count = countOverride;
        }
        if (isBoss) {
            count += settings.bossAditionalRestraints;
        }
        else if (settings.bossOnlyHeavy && countOverride <= 0) {
            usedKeys.push_back("zad_DeviousHeavyBondage");
            log::trace("Not boss chest, no heavy restraints.");
        }
        UndressActor(player);
        int bailout = 10;
        int total = 0;
        std::optional<DeviceData> doLast = std::nullopt;
        for (int i = 0; i < count && bailout > 0; i++) {
            //log::trace("I: {}, B: {}", i, bailout);
            auto dev = GetRandomEquipableDevice(player, usedKeys, editorIdRequires);
            if (!dev) {
                bailout--;
                i--;
                continue;
            }
            auto rend = dev.value().rend;
            auto inv = dev.value().inv;

            if (settings.beltPlugs && rend->HasKeywordString("zad_DeviousBelt")) {
                if (std::find(usedKeys.begin(), usedKeys.end(), "zad_DeviousPlugAnal") == usedKeys.end()) {
                    std::optional<DeviceData> plug;
                    plug = GetRandomDevice(&devices.plugsABasic, usedKeys, editorIdRequires);
                    if (!plug) {
                        plug = GetRandomDevice(&devices.plugsABasic);
                    }
                    if (plug) {
                        LockDevice(player, plug.value().inv);
                        total += 1;
                    }
                }
                if (std::find(usedKeys.begin(), usedKeys.end(), "zad_DeviousPlugVaginal") == usedKeys.end()) {
                    std::optional<DeviceData> plug;
                    plug = GetRandomDevice(&devices.plugsVBasic, usedKeys, editorIdRequires);
                    if (!plug) {
                        plug = GetRandomDevice(&devices.plugsVBasic);
                    }
                    if (plug) {
                        LockDevice(player, plug.value().inv);
                        total += 1;
                    }
                }
            }
            if (settings.plugsDontCount && (rend->HasKeywordString("zad_DeviousPlugVaginal") || rend->HasKeywordString("zad_DeviousPlugAnal"))) {
                i--;
            }
            for (auto const& key : GetDeviceKeywords(rend, true)) {
                usedKeys.push_back(key);
            }
            if (rend->HasKeywordString("zad_DeviousHeavyBondage")) {
                doLast = dev;
            }
            else {
                LockDevice(player, inv);
            }
            total += 1;
        }

        if (doLast.has_value()) {
            auto inv = doLast.value().inv;
            LockDevice(player, inv);
        }

        std::string msg = "";
        for (auto const& i : usedKeys) { msg += (i + ", "); }
        msg.pop_back(); msg.pop_back();
        log::trace("usedKeys: {}", msg);

        if (bailout == 0) {
            log::trace("Ran out of devices to equip.");
        }
        if (total > 0 && !contName.empty()) {
            PlayerMessage(fmt::format("As you touch the {} you see restraints magically appear and wrap themselves around you!", contName));
        }
    }

    bool DoSimpleSlaveryEvent(std::string contName) {
        auto player = RE::PlayerCharacter::GetSingleton();
        UndressActor(player);
        if (!RE::TESDataHandler::GetSingleton()->LookupModByName("SimpleSlavery.esp")) {
            return false;
        }
        if (GetWornDeviceCount(player) < settings.eventSSMinRestraints) {
            return false;
        }
        auto inventory = player->GetInventory();
        for (auto const& [k, v] : inventory) {
            auto armor = k->As<RE::TESObjectARMO>();
            if (armor && armor->HasKeywordString("zad_BlockGeneric")) {
                return false;
            }
        }

        auto modevent = SKSE::ModCallbackEvent{ "SSLV Entry", "", 0, 0 };
        SKSE::GetModCallbackEventSource()->SendEvent(&modevent);
        PlayerMessage(fmt::format("As you touch the {} you see a flash of light and immediately pass out. Through intermittent consciousness you can feel someone carrying you somewhere...", contName));
        return true;

    }

    bool DoLewdMarkEvent(bool doMessage = true) {
        //45 no orgasm / edging
        if (!RE::TESDataHandler::GetSingleton()->LookupModByName("LewdMarksSlaveTats.esp")) {
            return false;
        }
        auto player = RE::PlayerCharacter::GetSingleton();
        if (GetLewdMark(player) > 0) {
            return false;
        }

        UndressActor(player);

        int weightTotal = settings.LMAllureWeight + settings.LMHeatWeight + settings.LMBondageWeight + settings.LMNudityWeight;

        int r = Util::randomInt(weightTotal);

        if (r < settings.LMAllureWeight) {
            counters.LMSexCounter = static_cast<int64_t>(-1 * settings.LMAllureSex * Util::randomDouble(0.8, 1.2));
            AddLewdMark(player, TAT_ALLURE, settings.LMAllureColor);
            if (doMessage) PlayerMessage("After a sharp pain, you see that you have a mark of allure.");
            return true;
        }
        else if (r > settings.LMAllureWeight) {
            r -= settings.LMAllureWeight;
        }

        if (r < settings.LMHeatWeight) {
            counters.LMContainersOpened = static_cast<int64_t>(-1 * settings.LMHeatContainerCount * Util::randomDouble(0.8, 1.2));
            AddLewdMark(player, TAT_HEAT, settings.LMHeatColor);
            if (doMessage) PlayerMessage("After a sharp pain, you see that you have a mark of heat.");
            return true;
        }
        else if (r > settings.LMHeatWeight) {
            r -= settings.LMHeatWeight;
        }

        if (r < settings.LMBondageWeight) {
            counters.LMDevicesEquipped = static_cast<int64_t>(-1 * settings.LMBondageDeviceCount * Util::randomDouble(0.8, 1.2));
            AddLewdMark(player, TAT_BONDAGE, settings.LMBondageColor);
            if (doMessage) PlayerMessage("After a sharp pain, you see that you have a mark of bondage.");
            return true;
        }
        else if (r > settings.LMBondageWeight) {
            r -= settings.LMBondageWeight;
        }

        if (r < settings.LMNudityWeight) {
            counters.LMPeopleTalked = static_cast<int64_t>(-1 * settings.LMNudityTalkTimes * Util::randomDouble(0.8, 1.2));
            AddLewdMark(player, TAT_NUDITY, settings.LMNudityColor);
            if (doMessage) PlayerMessage("After a sharp pain, you see that you have a mark of nudity.");
            return true;
        }
        else if (r > settings.LMNudityWeight) {
            r -= settings.LMNudityWeight;
        }

        return false;
    }

    void DoEvent(bool isBoss, std::string contName) {
        CloseContinerMenus();
        //DisableMenus();
        int weightTotal = settings.eventStandardWeight + settings.eventSimpleSlaveryWeight + settings.eventLewdMarkWeight;// +settings.eventSGOWeight;
        if (isBoss) {
            weightTotal -= settings.eventStandardBossReduction;
        }
        int r = Util::randomInt(weightTotal);

        if (r < settings.eventSimpleSlaveryWeight && DoSimpleSlaveryEvent(contName)) {
            //EnableMenus();
            return;
        }
        else if (r > settings.eventSimpleSlaveryWeight) {
            r -= settings.eventSimpleSlaveryWeight;
        }

        /*
        if (r < settings.eventSGOWeight && DoSGOEvent(contName)) {
            UndressActor(RE::PlayerCharacter::GetSingleton());
            //EnableMenus();
            return;
        }
        else if (r > settings.eventSGOWeight) {
            r -= settings.eventSGOWeight;
        }
        */

        if (r < settings.eventLewdMarkWeight && DoLewdMarkEvent()) {
            //EnableMenus();
            return;
        }
        else if (r > settings.eventLewdMarkWeight) {
            r -= settings.eventLewdMarkWeight;
        }

        if (settings.eventStandardWeight > 0) {
            DoStandardEvent(isBoss, contName);
        }
        else {
            log::error("No event triggered.");
        }


        //EnableMenus();
    }

    struct ContainerData {
        bool isDeadActor = false;
        bool isPickpocket = false;
        bool isBoss = false;
        bool isLeveled = false; // also isContainer
        bool isDoor = false;
        bool isLocked = false;
        bool isDragon = false;
        int lockLevel = 0;
    };

    ContainerData GetContainerData(RE::TESObjectREFR* activatedObject) {
        ContainerData data;

        auto player = RE::PlayerCharacter::GetSingleton();

        RE::Actor* actor = activatedObject->As<RE::Actor>();
        if (actor && actor->IsDead() && !actor->IsChild()) {
            data.isDeadActor = true;
        }
        if (actor && !actor->IsDead() && !actor->IsChild() && player->IsSneaking() && actor->CanPickpocket()) {
            data.isPickpocket = true;
        }

        //RE::BGSLocation* location = GetPlayerLocation();
        std::string editorId = Util::GetFormEditorId(activatedObject);
        if (editorId.find("Boss") != std::string::npos) { data.isBoss = true; }
        RE::TESObjectCONT* container = activatedObject->GetObjectReference()->As<RE::TESObjectCONT>();
        if (container) {
            RE::TESModelTextureSwap* textSwap = container->GetAsModelTextureSwap();
            std::string model_path = textSwap->GetModel();
            static std::string paths[] = { "DLC01\\SoulCairn\\sc_chest02.nif", "DLC01\\Clutter\\DLC01SnowElfChest.nif", "Clutter\\Ruins\\Ruins_LargeChest.nif", "DLC02\\Dungeons\\Apocrypha\\Animated\\ApoUrn\\ApoUrn02.nif", "Clutter\\Dwemer\\DweChest01.nif", "Clutter\\Falmer\\FalmerContainer02.nif" };
            if (settings.bossChestUseModelPath) {
                for (auto const& path : paths) {
                    if (model_path == path) { data.isBoss = true; }
                }
            }

            RE::TESObjectREFR::InventoryItemMap inventory = activatedObject->GetInventory();
            for (auto const& [k, v] : inventory) {
                if (v.second->IsLeveled()) {
                    data.isLeveled = true;
                }
            }

            //WAY too many things are listed as boss chests with this
            /*for (auto const& locRef : location->specialRefs) {
                if (locRef.refData.refID == activatedObject->GetLocalFormID() && std::string(locRef.type->GetFormEditorID()) == "BossContainer") {
                    isBoss = true;
                }
            }*/
        }

        RE::TESObjectDOOR* door = activatedObject->GetObjectReference()->As<RE::TESObjectDOOR>();
        if (door) {
            data.isDoor = true;
        }

        RE::REFR_LOCK* lockref = activatedObject->GetLock();
        if (lockref) {
            //log::trace("Lock ref base {} isLocked {} isLeveled {}", lockref->baseLevel, lockref->IsLocked(), lockref->flags.all(RE::REFR_LOCK::Flag::kLocked));
            RE::LOCK_LEVEL level = activatedObject->GetLockLevel();
            bool hasKey = false;
            if (level != RE::LOCK_LEVEL::kRequiresKey && level != RE::LOCK_LEVEL::kUnlocked) {
                data.lockLevel = static_cast<int>(level) + 1;
                RE::TESObjectREFR::InventoryItemMap inventory = player->GetInventory();
                for (auto const& [k, v] : inventory) {
                    if (lockref->key == k) {
                        hasKey = true;
                        break;
                    }
                }
                if (!hasKey && level != RE::LOCK_LEVEL::kUnlocked) {
                    data.isLocked = true;
                }
            }
        }

        if (data.isDeadActor && actor->GetRace()->HasKeywordString("ActorTypeDragon") && settings.dragonHoard) {
            data.isDragon = true;
        }

        return data;
    }

    void PopulateContainer(RE::TESObjectREFR* activatedObject, ContainerData data) {
        if (!activatedObject) {
            log::warn("PopulateContainer called with a null object reference.");
            return;
        }

        if (IsObjectPopulated(activatedObject->formID)) {
            return;
        }
        else {
            log::trace("Populating object {}", activatedObject->GetName());
            SetObjectPopulated(activatedObject->formID);
        }
        auto player = RE::PlayerCharacter::GetSingleton();

        if (settings.vanishingKeys && activatedObject != player) {
            RemoveKeys(activatedObject);
        }

        RE::TESKey* addedKey = nullptr;
        if (data.isLeveled || data.isPickpocket || (data.isDeadActor && !IsPickpocketTargetKnown(activatedObject->formID))) {
            addedKey = GenerateKeys(activatedObject, false);
            GenerateRandomDevices(activatedObject);
        }

        if (data.isLeveled && data.isBoss && settings.bossExtraGold) {
            log::trace("Adding extra gold to boss chest.");
            RE::TESForm* gold = RE::TESForm::LookupByID(std::stoi("0f", 0, 16));
            activatedObject->AddObjectToContainer((RE::TESBoundObject*)gold, nullptr, (player->GetLevel()), nullptr);
        }

        if (data.isDragon) {
            log::trace("Actor is dragon and dragon hoards are on.");
            RE::TESForm* gold = RE::TESForm::LookupByID(std::stoi("0f", 0, 16));
            activatedObject->AddObjectToContainer((RE::TESBoundObject*)gold, nullptr, static_cast<int>(player->GetLevel() * 80.0 * Util::randomDouble(0.3, 1) + Util::randomDouble(50, 200)), nullptr);
        }

        if (data.isBoss) {
            RE::TESKey* magicKey = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESKey>(MAGIC_KEY, "Devious Curses.esp");
            double c2 = 10.0 + GetWornDeviceCount(player) * 0.75;
            double r2 = Util::randomDouble();
            log::trace("Magic Key: {} ({})", c2, r2);
            if (GetItemCount(player, magicKey) == 0 && !addedKey && r2 < c2) {
                activatedObject->AddObjectToContainer((RE::TESBoundObject*)magicKey, nullptr, 1, nullptr);
            }
        }
        else if (data.isDeadActor) {
            RE::TESObjectMISC* solvent = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESObjectMISC>(TATTOO_CHARM, "Devious Curses.esp");
            double c2 = 5.0 + GetTattooCount(player) * 0.5;
            double r2 = Util::randomDouble();
            log::trace("Solvent: {} ({})", c2, r2);
            if (GetItemCount(player, solvent) == 0 && !addedKey && r2 < c2) {
                activatedObject->AddObjectToContainer((RE::TESBoundObject*)solvent, nullptr, 1, nullptr);
            }
        }
    }

    void CalculateEventChance(RE::TESObjectREFR* activatedObject) {
        if (!activatedObject) {
            log::warn("OnObjectActivated called with a null object reference.");
            return;
        }

        auto player = RE::PlayerCharacter::GetSingleton();

        //log::trace("Worn items: {}", GetWornDeviceCount(GetPlayer()));
        if (IsObjectRefKnown(activatedObject->formID)) {
            //log::trace("object is known");
            return;
        }
        else {
            log::trace("Activated {} type {} refID {:x} baseID {:x}", activatedObject->GetName(), RE::FormTypeToString(activatedObject->GetFormType()), activatedObject->formID, activatedObject->GetBaseObject()->GetFormID());
        }

        auto data = GetContainerData(activatedObject);

        PopulateContainer(activatedObject, data);

        RE::Actor* actor = activatedObject->As<RE::Actor>();
        if (actor && !actor->IsDead() && !actor->IsChild() && !player->IsSneaking() && actor->CanTalkToPlayer()) {
            CheckConsequenceDialogue(actor);
        }

        if (data.isPickpocket && IsPickpocketTargetKnown(activatedObject->formID)) {
            return;
        }

        /*
        log::trace("isContainer {}", isLeveled);
        log::trace("isBossChest {}", isBoss);
        log::trace("isDeadActor {}", isDeadActor);
        log::trace("isDoor {}", isDoor);
        log::trace("isLocked {}", isLocked);
        */


        if (data.isDeadActor || data.isLeveled || data.isDoor) {
            SetObjectRefKnown(activatedObject->formID);
        }
        else if (data.isPickpocket) {
            SetPickpocketTargetKnown(activatedObject->formID);
        }

        //else if (isDeadActor && IsPickpocketTargetKnown(activatedObject->formID) && settings.vanishingKeys) {
        //    RemoveKeys(actor);
        //}

        if (data.isDoor && !data.isLocked && settings.onlyLockedDoors) {
            log::trace("No event: Only locked doors.");
            return;
        }

        //RE::TESFaction* arousalFaction = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("03FC36", 0, 16), "SexLabAroused.esm");
        int playerArousal = GetActorArousal(player);

        float chance = settings.baseChance;
        std::string logMessage = "modifiers: ";

        if (settings.arousalModifier > 1.01f && playerArousal > 0) {
            float modifier = (settings.arousalModifier - 1) * playerArousal / 100.0f + 1;
            chance *= modifier;
            logMessage += fmt::format("(arousal {}) ", playerArousal);
        }


        if (data.isDeadActor) {
            chance *= settings.deadBodyModifier;
            logMessage += "(dead) ";
        }
        else if (data.isLeveled) {
            counters.LMContainersOpened += 1;
            log::info("Heat mark: {}", counters.LMContainersOpened);
            chance *= settings.containerModifier;
            logMessage += "(container) ";
        }
        else if (data.isDoor) {
            if (!settings.onlyLockedDoors || data.isLocked) {
                chance *= settings.doorModifier;
                logMessage += "(door) ";
            }
        }
        else if (data.isPickpocket) {
            chance *= settings.pickpocketModifier;
            logMessage += "(pickpocket) ";
        }
        else {
            return;
        }

        if (data.isBoss) {
            chance *= settings.bossContainerModifier;
            logMessage += "(boss) ";
        }
        if (data.isLocked) {
            chance *= settings.lockedModifier;
            if (data.lockLevel >= 0 && settings.lockDifficultyModifier > 1.0) {
                float modifier = (settings.lockDifficultyModifier - 1) * (data.lockLevel / 5.0f) + 1;
                chance *= modifier;
                logMessage += fmt::format("(locked {:.2f}) ", modifier);
            }
            else {
                logMessage += "(locked) ";
            }
        }

        float locationChance = 1.0f;
        std::string locationMessage = "";

        auto location = player->GetCurrentLocation();
        if (location) log::trace("current location: {}", location->GetName());
        if (settings.useLocationModifiers) {
            if (!location) {
                locationChance = settings.wildernessModifier;
                locationMessage = "wilderness";
            }
            else if (location->HasKeywordString("LocTypePlayerHouse")) {
                locationChance = settings.playerHomeModifier;
                locationMessage = "player home";
            }
            else if (location->HasKeywordString("LocTypeCity") || location->HasKeywordString("LocTypeCastle") || location->HasKeywordString("LocTypeTemple") || location->HasKeywordString("LocTypeInn") || location->HasKeywordString("LocTypeHouse")) {
                locationChance = settings.cityModifier;
                locationMessage = "city";
            }
            else if (location->HasKeywordString("LocTypeTown") || location->HasKeywordString("LocTypeHabitation") || location->HasKeywordString("LocTypeDwelling")) {
                locationChance = settings.townModifier;
                locationMessage = "town";
            }
            else if (location->HasKeywordString("LocTypeDraugrCrypt") || location->HasKeywordString("LocTypeDragonPriestLair")) {
                locationChance = settings.draugrModifier;
                locationMessage = "draugr";
            }
            else if (location->HasKeywordString("LocTypeDwarvenAutomatons") && location->HasKeywordString("LocTypeFalmerHive")) {
                if (settings.dwarvenModifier > settings.falmerModifier) { locationChance = settings.dwarvenModifier; locationMessage = "dwarven"; }
                else { locationChance = settings.falmerModifier; locationMessage = "falmer"; }
            }
            else if (location->HasKeywordString("LocTypeDwarvenAutomatons")) {
                locationChance = settings.dwarvenModifier;
                locationMessage = "dwarven";
            }
            else if (location->HasKeywordString("LocTypeFalmerHive")) {
                locationChance = settings.falmerModifier;
                locationMessage = "falmer";
            }
            else if (location->HasKeywordString("LocTypeForswornCamp") || location->HasKeywordString("LocTypeHagravenNest")) {
                locationChance = settings.forswornModifier;
                locationMessage = "forsworn";
            }
            else if (location->HasKeywordString("LocTypeVampireLair")) {
                locationChance = settings.vampireModifier;
                locationMessage = "vampire";
            }
            else if (location->HasKeywordString("LocTypeWarlockLair")) {
                locationChance = settings.warlockModifier;
                locationMessage = "warlock";
            }
            else if (location->HasKeywordString("LocTypeDragonLair")) {
                locationChance = settings.warlockModifier;
                locationMessage = "dragon lair";
            }
            else if (location->HasKeywordString("LocTypeApocrypha")) {
                locationChance = settings.apocryphaModifier;
                locationMessage = "apocrypha";
            }
            else if (location->HasKeywordString("LocTypeBanditCamp") || location->HasKeywordString("LocTypeMilitaryCamp") || location->HasKeywordString("LocTypeMilitaryFort") || location->HasKeywordString("LocTypeDungeon")) {
                locationChance = settings.banditModifier;
                locationMessage = "bandit";
            }
            else if (!player->GetParentCell()->IsInteriorCell()) {
                locationChance = settings.wildernessModifier;
                locationMessage = "wilderness";
            }
            else {
                log::warn("Player in unknown location {}.", location->GetName());
                std::string keys = "Keywords: ";
                for (uint32_t i = 0; i < location->numKeywords; i++) {
                    keys += Util::GetFormEditorId(location->keywords[i]) + std::string(", ");
                }
                log::warn("{}", keys);
                locationChance = settings.wildernessModifier;
                locationMessage = "wilderness";
            }
        }

        if (data.isLocked && locationChance < settings.lockedLocationBypass) {
            locationChance = settings.lockedLocationBypass;
            locationMessage += " [L]";
        }
        if (data.isDragon && locationChance < 1.0) {
            locationChance = 1.0;
            locationMessage += " [D]";
        }
        if ((player->WouldBeStealing(activatedObject) || data.isPickpocket) && locationChance < settings.theftLocationBypass) {
            locationChance = settings.theftLocationBypass;
            locationMessage += " [T]";
        }

        chance *= locationChance;
        logMessage += fmt::format("({} {}) ", locationMessage, locationChance);

        if (data.isDragon) {
            chance *= settings.bossContainerModifier * 1.2f;
            //chance *= actor->GetLevel() / 75.0f + 1;
            logMessage += "(dragon) ";
        }
        else if (settings.eventScaling) {
            float eventScaling = ((3.0f * settings.eventScalingMod) / ((-2.0f * settings.eventScalingMod) - counters.SinceLastEvent)) + 2.0f;
            logMessage += fmt::format("scaling: {:.2f}x ", eventScaling);
            chance *= eventScaling;
        }

        if (!data.isDragon && GetWornDeviceCount(player) > settings.restraintCap) {
            log::trace("No event: Too many devices.");
            chance = 0.0;
        }

        if (playerArousal < settings.minArousal && settings.minArousal > 0) {
            log::trace("No event player arousal too low {} < {}", playerArousal, settings.minArousal);
            chance = 0.0;
        }

        double r = Util::randomDouble();

        logMessage = fmt::format("Event: {} total: {:.2f}% ({:.2f})", logMessage, chance, r);
        log::info("{}", logMessage);
        if (r < chance) {
            DoEvent(data.isBoss || data.isDragon, activatedObject->GetName());
            counters.SinceLastEvent = 0;
        }
        else {
            counters.SinceLastEvent++;
        }
    }

    void EventsUpdate() {
        //log::trace("LM clock: {}", counters.clock_LMEventTimer);
        auto player = RE::PlayerCharacter::GetSingleton();
        int mark = GetLewdMark(player);
        if (mark > 0) {
            //int base_color = mark == 11 ? settings.LMHeatColor : (mark == 13 ? settings.LMAllureColor : (mark == 71 ? settings.LMBondageColor : (mark == 79 ? settings.LMNudityColor : 0)));
            if (counters.clock_LMEventTimer >= 15) {
                log::trace("events marks update");
                counters.clock_LMEventTimer = 0;
                switch (mark) {
                case TAT_HEAT: {
                    ModifyArousal(player, settings.LMHeatMod / 4);
                    if (counters.LMContainersOpened >= 0) {
                        RemoveLewdMark(player, mark);
                        PlayerMessage("You feel a sense of calm as the heat mark fades from your body.");
                    }
                    break;
                }
                case TAT_ALLURE: {
                    auto playerPosition = RE::PlayerCharacter::GetSingleton()->GetPosition();

                    if (const auto processLists = RE::ProcessLists::GetSingleton(); processLists) {
                        RE::BSSimpleList<RE::ActorHandle>* arr = &(processLists->aliveActorList);
                        if (arr) {
                            for (auto const& actorHandle : *arr) {
                                auto actorPtr = actorHandle.get();
                                if (auto actor = actorPtr.get(); actor && actor->Is3DLoaded() && !actor->IsDead() && actor->GetPosition().GetDistance(playerPosition) <= settings.sexSearchRadius) {
                                    ModifyArousal(actor, settings.LMAllureMod / 4);
                                }
                            }
                        }
                    }
                    if (counters.LMSexCounter >= 0) {
                        RemoveLewdMark(player, mark);
                        PlayerMessage("You sense that people are no longer staring at you as the allure mark fades from your body.");
                    }
                    break;
                }
                case TAT_BONDAGE: {
                    if (Util::randomDouble() < settings.LMBondageChance) {
                        log::trace("Attempting bondage event");
                        std::vector<RE::TESObjectARMO*> equipable;

                        auto inventory = player->GetInventory();
                        auto keywords = GetKeywordsCantEquip(player);
                        for (auto const& [k, v] : inventory) {
                            RE::TESObjectARMO* armor = k->As<RE::TESObjectARMO>();
                            if (armor && armor->HasKeywordString("zad_InventoryDevice") && DeviceHasGenericKey(armor) && v.second.get() && !v.second.get()->IsWorn()) {
                                auto render = DeviousDevicesAPI::g_API->GetDeviceRender(armor);
                                if (render) {
                                    bool canEquip = true;
                                    for (auto const& key : render->GetKeywords()) {
                                        if (vectorContains(keywords, Util::GetFormEditorId(key))) {
                                            canEquip = false;
                                        }
                                    }
                                    if (canEquip) {
                                        equipable.push_back(armor);
                                    }
                                }
                            }
                        }
                        log::trace("Total devices found for event: {}", equipable.size());
                        if (equipable.size() == 0) {
                            log::trace("Bondage mark found no items in inventory");
                            break;
                        }

                        auto device = equipable[Util::randomInt(static_cast<int>(equipable.size()))];
                        log::trace("Equipping device: {}", device->GetName());
                        counters.LMDevicesEquipped += 1;
                        log::info("Bondage mark: {}", counters.LMDevicesEquipped);
                        LockDevice(player, device);
                        PlayerMessage(fmt::format("Your mark pulses with light as your {} appears on your body!", device->GetName()));
                    }
                    if (counters.LMDevicesEquipped >= 0) {
                        RemoveLewdMark(player, mark);
                        PlayerMessage("You feel much less oppressed as the bondage mark fades from your body.");
                    }
                    break;
                }
                case TAT_NUDITY: {
                    if (counters.LMPeopleTalked >= 0) {
                        RemoveLewdMark(player, mark);
                        PlayerMessage("You feel less helpless as the nudity mark fades from your body.");
                    }
                    break;
                }}
            }
            if (mark == TAT_NUDITY) {
                bool didAnything = false;
                if (settings.LMNudityChestOnly) {
                    RE::TESObjectARMO* equipped = player->GetWornArmor(RE::BIPED_MODEL::BipedObjectSlot::kBody);
                    if (equipped != nullptr && !equipped->HasKeywordString("SexLabNoStrip")) {
                        UnequipItem(player, equipped);
                        didAnything = true;
                    }
                }
                else {
                    for (uint32_t i = 1; i < (1 << 31); i = i << 1) {
                        RE::TESObjectARMO* equipped = player->GetWornArmor((RE::BIPED_MODEL::BipedObjectSlot)i);
                        if (i == (uint32_t)RE::BIPED_MODEL::BipedObjectSlot::kAmulet || i == (uint32_t)RE::BIPED_MODEL::BipedObjectSlot::kRing || i == (uint32_t)RE::BIPED_MODEL::BipedObjectSlot::kShield) {
                            continue;
                        }
                        if (equipped == nullptr) { continue; }
                        if (equipped->HasKeywordString("SexLabNoStrip")) {
                            continue;
                        }
                        didAnything = true;
                        UnequipItem(player, equipped);
                    }
                }
                if (didAnything) {
                    auto health = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kHealth);
                    auto damage = ((health / 3) > 10) ? health / 3 : health - 10;
                    player->AsActorValueOwner()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kHealth, -damage);
                    PlayerMessage("You feel a sharp pain as your clothes are riped from your body.");
                }
            }
        }
    }

    void EventsStartup() {
        if (RE::TESDataHandler::GetSingleton()->LookupModByName("SimpleSlavery.esp") == nullptr) {
            settings.eventSimpleSlaveryWeight = 0;
            SetMCMInt("eventSimpleSlaveryWeight", 0);
        }
        /*if (RE::TESDataHandler::GetSingleton()->LookupModByName("Sgo4IF.esp") == nullptr) {
            settings.eventSGOWeight = 0;
            SetMCMInt("eventSGOWeight", 0);
        }*/
        if (GetModuleHandle(L"SlaveTatsNG") == nullptr || RE::TESDataHandler::GetSingleton()->LookupModByName("LewdMarksSlaveTats.esp") == nullptr) {
            settings.eventLewdMarkWeight = 0;
            SetMCMInt("eventLewdMarkWeight", 0);
        }
    }
}