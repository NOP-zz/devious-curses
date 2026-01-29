#pragma once
#pragma warning(4:4061)

#include "tats.hpp"
#include "devices.hpp"
#include "Consequences.hpp"
#include "themes.hpp"
#include "Contraptions.hpp"
#include "O_Devices.hpp"
#include "MinAI.hpp"

#include "../include/DDNG_API.h"
#include "../include/form_ids.h"

namespace DCURSES {
    static bool DCURSES_QLIE_LOADED = false;

    void GenerateRandomDevices(RE::TESObjectREFR* activatedObject) {
        if (!(activatedObject && activatedObject->HasContainer())) {
            return;
        }
        bool hasBondageMark = GetLewdMark() == MARK::TAT_BONDAGE;
        bool isLucky = PlayerIsLucky();
        float chance = settings.rDeviceBaseChance;
        if (hasBondageMark) {
            chance += 2.5f;
        }
        if (isLucky) {
            chance *= settings.rDeviceLuckyBonus;
        }
        for (int i = 0; i < 2 + ((hasBondageMark || isLucky) * 2); i++) {
            if (Util::randomDouble() < chance) {
                auto dev = GetRandomDevice(&devices.anything);
                if (dev) {
                    activatedObject->AddObjectToContainer((RE::TESBoundObject*)dev.value().inv, nullptr, 1, nullptr);
                }
            }
        }
    }

    bool DoStandardEvent(RE::Actor* actor, bool isBoss, std::string contName, std::string theme = "", int countOverride = -1, int minDevices = 1, std::vector<std::string> skipKeywords = {}) {
        if (Util::randomDouble() < settings.keyLossChance) {
            RemoveKeys(actor);
        }

        std::list<RE::TESObjectARMO*> to_equip;
        RE::TESObjectARMO* heavy = nullptr;

        std::string device_names = "";
        std::string device_ids = "";

        std::vector<std::string> usedKeys = GetKeywordsCantEquip(actor);
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

        if (minDevices < 1) {
            minDevices = 1;
        }

        if (!actor->IsPlayerRef()) {
            if (!settings.followerHeavyRestraints) {
                usedKeys.push_back("zad_DeviousHeavyBondage");
            }
            count += settings.followerDeviceModifier;
        }

        if (count < minDevices) { count = minDevices; }

        if (theme.empty() && settings.useThemes) {
            theme = GetRandomTheme();
        }

        bool removeHandItems = false;

        int bailout = 10;

        for (int i = 0; i < count && bailout > 0; i++) {
            //log::trace("I: {}, C: {}, B: {}", i, count, bailout);
            //log::trace("player exists: {}", player != nullptr);
            auto dev = GetRandomEquipableDevice(actor, usedKeys, theme);
            if (!dev) {
                bailout--;
                i--;
                continue;
            }
            auto rend = dev.value().rend;
            auto inv = dev.value().inv;

            if (settings.beltPlugs && rend->HasKeywordString("zad_DeviousBelt")) {
                if (!vectorContains(usedKeys, "zad_DeviousPlugAnal") && !rend->HasKeywordString("zad_PermitAnal")) {
                    std::optional<DeviceData> plug;
                    plug = GetRandomDevice(&devices.plugsABasic, {}, theme);
                    if (!plug) {
                        plug = GetRandomDevice(&devices.plugsABasic);
                    }
                    if (plug) {
                        //LockDevice(player, plug.value().inv);
                        to_equip.push_front(plug.value().inv);
                        device_names += plug.value().inv->GetName();
                        device_names += ",";
                        device_ids += Util::GetFormEditorId(plug.value().inv);
                        device_ids += ",";
                    }
                }
                if (!vectorContains(usedKeys, "zad_DeviousPlugVaginal") && !rend->HasKeywordString("zad_PermitVaginal")) {
                    std::optional<DeviceData> plug;
                    plug = GetRandomDevice(&devices.plugsVBasic, {}, theme);
                    if (!plug) {
                        plug = GetRandomDevice(&devices.plugsVBasic);
                    }
                    if (plug) {
                        //LockDevice(player, plug.value().inv);
                        to_equip.push_front(plug.value().inv);
                        device_names += plug.value().inv->GetName();
                        device_names += ",";
                        device_ids += Util::GetFormEditorId(plug.value().inv);
                        device_ids += ",";
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
                heavy = inv;
                removeHandItems = true;
            }
            else if (rend->HasKeywordString("zad_DeviousPlugVaginal") || rend->HasKeywordString("zad_DeviousPlugAnal")) {
                to_equip.push_front(inv);
            }
            else {
                //LockDevice(player, inv);
                to_equip.push_back(inv);
            }

            device_names += inv->GetName();
            device_names += ",";
            device_ids += Util::GetFormEditorId(inv);
            device_ids += ",";
        }

        if (heavy) {
            to_equip.push_back(heavy);
        }

        if (bailout == 0) {
            log::trace("Ran out of devices to equip.");
        }
        if (to_equip.size() < minDevices) {
            return false;
        }

        if (removeHandItems) {
            UndressAndUnequipActor(actor);
        }
        else if (settings.stripPlayerOnEvent) {
            UndressActor(actor, false);
        }
        auto scriptManager = ScriptingManager();

        if (!settings.disableForce3rdPerson) scriptManager.ForceThirdPerson();

        if (!contName.empty() && actor->IsPlayerRef()) {
            //PlayerMessage(fmt::format("As you touch the {} you see restraints magically appear and wrap themselves around you!", contName));
            //Util::ExecuteWithDelay(4s, [contName] {
            PlayerMessage(Translator(Translation::EventDevices, contName));
            //});
        }

        for (auto device : to_equip) {
            log::trace("Locking device {} on {}", device->GetName(), actor->GetName());
            scriptManager.LockDevice(actor, device, false);
        }
            
        std::string msg = "";
        for (auto const& i : usedKeys) { msg += (i + ", "); }
        msg.pop_back(); msg.pop_back();
        log::trace("usedKeys: {}", msg);

        return true;
    }

    bool DoSimpleSlaveryEvent(std::string contName) {
        auto player = RE::PlayerCharacter::GetSingleton();
        if (!CheckSimpleSlavery()) {
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
        //PlayerMessage(fmt::format("As you touch the {} you see a flash of light and immediately pass out. Through intermittent consciousness you can feel someone carrying you somewhere...", contName));
        PlayerMessage(Translator(Translation::EventSimpleSlavery, contName));
        return true;

    }

    bool DoTattooEvent(RE::Actor* actor, std::string containerName, int num_tattoos = -1, bool skipMax = false) {
        if (settings.eventTattooWeight == 0) {
            return false;
        }

        if (!skipMax && GetTattooCount(actor) > settings.eventTattooCap) {
            return false;
        }

        if (num_tattoos < 1) {
            num_tattoos = Util::randomInt(settings.eventTattooMin, settings.eventTattooMax);
        }
        ScriptingManager().RTDoTattooEvent(actor, num_tattoos);

        if (!containerName.empty() && actor->IsPlayerRef()) {
            if (num_tattoos == 1) {
                PlayerMessage(Translator(Translation::EventTattooOne, containerName));
            }
            else if (num_tattoos <= 3) {
                PlayerMessage(Translator(Translation::EventTattooTwoThree, containerName));
            }
            else {
                PlayerMessage(Translator(Translation::EventTattooMany, containerName));
            }
        }

        AIEventTattoos(num_tattoos);
        return true;
    }

    bool DoContraptionEvent(std::string containerName, RE::Actor* target = nullptr, std::string theme = "") {
        //auto player = RE::PlayerCharacter::GetSingleton();
        target = target == nullptr ? RE::PlayerCharacter::GetSingleton() : target;

        if (settings.eventContAllDevices) {
            DoStandardEvent(target, false, "", theme, settings.eventContDeviceOverride, 1, { "zad_DeviousHeavyBondage" });
        }
        else if (settings.eventContDevices) {
            DoStandardEvent(target, false, "", theme, settings.eventContDeviceOverride, 1, { "zad_DeviousHeavyBondage", "zad_DeviousBelt", "zad_DeviousBra", "zad_DeviousHarness", "zad_DeviousBlindfold", "zad_DeviousHood", "zad_DeviousBoots", "zad_DeviousGloves", "zad_DeviousSuit", "zad_DeviousCorset"});
        }

        auto contraption = CreateAndLockContraption(target);
        AIEventContraption(contraption->GetName());

        counters.clock_SexTimeout -= 5;

        //PlayerMessage(fmt::format("As you touch the {} you feel yourself get dizzy as you are strung up into some sort of contraption!", containerName));
        PlayerMessage(Translator(Translation::EventContraption, containerName));

        return true;
    }

    bool DoLewdMarkEvent(std::string containerName, double multiplier = 1.0) {
        if (!CheckLewdMarksInstalled()) {
            return false;
        }
        auto player = RE::PlayerCharacter::GetSingleton();
        if (GetLewdMark() != MARK::TAT_NONE) {
            return false;
        }

        std::vector<std::pair<std::function<MARK()>, double>> marks;

        if (GetTattooCount(player) < settings.LMBrandingTotal / 2) marks.push_back({ [player, containerName] {
            if (!containerName.empty()) { PlayerMessage(Translator(Translation::EventMarkBranding)); }
            return MARK::TAT_BRANDING;
        } , settings.LMBrandingWeight });

        marks.push_back({ [player, containerName] {
            if (!containerName.empty()) { PlayerMessage(Translator(Translation::EventMarkAllure)); }
            return MARK::TAT_ALLURE;
        } , settings.LMAllureWeight });

        marks.push_back({ [player, containerName] {
            if (!containerName.empty()) { PlayerMessage(Translator(Translation::EventMarkHeat)); }
            return MARK::TAT_HEAT;
        } , settings.LMHeatWeight });

        marks.push_back({ [player, containerName] {
            if (!containerName.empty()) { PlayerMessage(Translator(Translation::EventMarkBondage)); }
            return MARK::TAT_BONDAGE;
        } , settings.LMBondageWeight });

        marks.push_back({ [player, containerName] {
            if (!containerName.empty()) { PlayerMessage(Translator(Translation::EventMarkNudity)); }
            return MARK::TAT_NUDITY;
        } , settings.LMNudityWeight });

        marks.push_back({ [player, containerName] {
           if (!containerName.empty()) { PlayerMessage(Translator(Translation::EventMarkHealslut)); }
           return MARK::TAT_HEALSLUT;
        } , settings.LMHealslutWeight });

        auto pair = Util::VectorSelectWeighted(marks);
        auto mark = pair.first();

        AddLewdMark(mark);
        SetDefaultEffectMagnitudeForMark(mark, multiplier);
        TatsUpdateContext(mark);
        AIEventAddLewdMark();

        return true;
    }

    void DoWickedEvent(std::string containerName) {
        CustomModEvent::SendModEvent("DwdEquipDeviceWithMcmChances", "", 1);
        PlayerMessage(Translator(Translation::EventWicked, containerName));
    }

    bool DoAbadonEvent(std::string containerName) {
        auto player = RE::PlayerCharacter::GetSingleton();

        auto scriptManager = ScriptingManager();

        bool canVaginal = true;
        bool canAnal = true;

        auto currentPlugA = GetWornInventoryDeviceByKeyword(player, "zad_DeviousPlugAnal");
        if (currentPlugA && !DeviceInventoryIsGeneric(currentPlugA)) {
            canAnal = false;
        }
        else if (currentPlugA) {
            scriptManager.UnlockDevice(player, currentPlugA);
        }

        auto currentPlugV = GetWornInventoryDeviceByKeyword(player, "zad_DeviousPlugVaginal");
        if (currentPlugV && !DeviceInventoryIsGeneric(currentPlugV)) {
            canVaginal = false;
        }
        else if (currentPlugV) {
            scriptManager.UnlockDevice(player, currentPlugV);
        }

        if (!canAnal && !canVaginal) {
            return false;
        }
        RE::TESObjectARMO* plug = nullptr;

        if (!canAnal) {
            plug = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(UD_ABADONPLUG_INVENTORY, "UnforgivingDevices.esp");
        }
        else if (!canVaginal) {
            plug = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(UD_ABADONPLUGANAL_INVENTORY, "UnforgivingDevices.esp");
        }
        else {
            plug = Util::randomDouble() < 50.0 ?
                StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(UD_ABADONPLUG_INVENTORY, "UnforgivingDevices.esp") :
                StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(UD_ABADONPLUGANAL_INVENTORY, "UnforgivingDevices.esp");
        }

        scriptManager.LockDevice(player, plug, true);
        if (!containerName.empty()) {
            PlayerMessage(Translator(Translation::EventAbadon, containerName));
        }
        
        return true;
    }

    enum class AbadonEventType : uint32_t {
        Warrior = 1,
        Scout = 2,
        Witch = 3
    };

    bool DoAbadonSetEvent(std::string containerName, RE::Actor* actor, AbadonEventType type) {
        if (GetWornDeviceCount(actor) > 6) {
            return false;
        }

        std::vector<uint32_t> set = {};

        int count = -1;
        switch (type) {
        case AbadonEventType::Warrior: {
            set = UD_ARMORSET01;
            count = settings.eventAbadonWarriorCount;
            break;
        }
        case AbadonEventType::Scout: {
            set = UD_ARMORSET02;
            count = settings.eventAbadonScoutCount;
            break;
        }
        case AbadonEventType::Witch: {
            set = UD_ARMORSET03;
            count = settings.eventAbadonWitchCount;
            break;
        }
        default:
            return false;
        }

        if (count <= 0) {
            return false;
        }

        Util::ShuffleVector(set);

        bool done_anything = false;

        auto scriptingManager = ScriptingManager();
        for (auto form_id : set) {
            auto to_equip = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(form_id, "UnforgivingDevices.esp");
            auto conflicts = GetDeviceKeywords(to_equip, false);
            bool can_equip = true;
            for (auto conflict : conflicts) {
                auto current = GetWornInventoryDeviceByKeyword(actor, conflict);
                if (current && !DeviceInventoryIsGeneric(current)) {
                    can_equip = false;
                }
            }
            if (can_equip) {
                scriptingManager.SwapDevices(actor, to_equip);
                count -= 1;
                done_anything = true;
            }
            if (count <= 0) {
                break;
            }
        }

        if (!done_anything) {
            return false;
        }

        switch (type) {
        case AbadonEventType::Warrior: {
            PlayerMessage(Translator(Translation::EventAbadonWarrior, containerName));
            break;
        }
        case AbadonEventType::Scout: {
            PlayerMessage(Translator(Translation::EventAbadonScout, containerName));
            break;
        }
        case AbadonEventType::Witch: {
            PlayerMessage(Translator(Translation::EventAbadonWitch, containerName));
            break;
        }
        default:
            return false;
        }

        return true;
    }

    std::vector<RE::Actor*> GetFollowersForEvent() {
        std::vector<RE::Actor*> result;

        for (auto follower : Util::GetFollowers()) {
            if (settings.onlyFemaleFollowers && follower->GetActorBase()->GetSex() != RE::SEX::kFemale) {
                continue;
            }
            if (settings.excludedFollowers != "") {
                bool useFollower = true;
                auto names = Util::split(settings.excludedFollowers, ",");
                for (auto name : names) {
                    if (follower->NameIncludes(Util::trim(name))) {
                        useFollower = false;
                        log::trace("Excluding follower {} from string {}", follower->GetName(), name);
                        break;
                    }
                }
                if (!useFollower) continue;
            }
            result.push_back(follower);
        }

        return result;
    }

    bool DoEvent(bool isBoss, std::string contName) {
        auto player = RE::PlayerCharacter::GetSingleton();

        std::vector<std::pair<bool(*)(bool, std::string, RE::Actor*), double>> events;

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoSimpleSlaveryEvent(contName)) {
                log::info("Ran event Simple Slavery");
                UndressAndUnequipActor(player);
                return true;
            }
            return false;
        }, settings.eventSimpleSlaveryWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoContraptionEvent(contName)) {
                log::info("Ran event Contraption");
                UnequipItems(player);
                if (settings.stripPlayerOnEvent) {
                    UndressActor(player, true);
                }
                return true;
            }
            return false;
        }, settings.eventContraptionWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoOppDeviceEvent(contName)) {
                log::info("Ran event Oppressive Device");
                if (settings.stripPlayerOnEvent) {
                    UndressActor(player, false);
                }
                return true;
            }
            return false;
        }, settings.eventOppressiveWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoTattooEvent(player, contName)) {
                log::info("Ran event Tattoo");
                if (settings.stripPlayerOnEvent) {
                    UndressActor(player, false);
                }
                if (settings.allowFollowerEvents) {
                    log::info("Applying tattoos to followers...");
                    for (auto follower : GetFollowersForEvent()) {
                        DoTattooEvent(follower, contName);
                    }
                }
                return true;
            }
            return false;
        }, settings.eventTattooWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoLewdMarkEvent(contName)) {
                log::info("Ran event Mark");
                if (settings.stripPlayerOnEvent) {
                    UndressActor(player, false);
                }
                return true;
            }
            return false;
        }, settings.eventLewdMarkWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            DoWickedEvent(contName);
            log::info("Ran event Wicked");
            if (settings.stripPlayerOnEvent) {
                UndressActor(player, false);
            }
            return true;
        }, settings.eventWickedWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoAbadonEvent(contName)) {
                log::info("Ran event Abadon");
                if (settings.stripPlayerOnEvent) {
                    UndressActor(player, false);
                }
                return true;
            }
            return false;
        }, settings.eventAbadonWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoAbadonSetEvent(contName, player, AbadonEventType::Warrior)) {
                log::info("Ran event Abadon Warrior");
                if (settings.stripPlayerOnEvent) {
                    UndressActor(player, false);
                }
                return true;
            }
            return false;
        }, settings.eventAbadonWarriorWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoAbadonSetEvent(contName, player, AbadonEventType::Scout)) {
                log::info("Ran event Abadon Scout");
                if (settings.stripPlayerOnEvent) {
                    UndressActor(player, false);
                }
                return true;
            }
            return false;
        }, settings.eventAbadonScoutWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoAbadonSetEvent(contName, player, AbadonEventType::Witch)) {
                log::info("Ran event Abadon Witch");
                if (settings.stripPlayerOnEvent) {
                    UndressActor(player, false);
                }
                return true;
            }
            return false;
        }, settings.eventAbadonWitchWeight });

        events.push_back({ [](bool isBoss, std::string contName, RE::Actor* player) {
            if (DoStandardEvent(player, isBoss, contName)) {
                log::info("Ran event Standard");
                if (settings.allowFollowerEvents) {
                    log::info("Adding Devices to followers...");
                    for (auto follower : GetFollowersForEvent()) {
                        DoStandardEvent(follower, isBoss, contName);
                    }
                }
                return true;
           }
           return false;
        }, settings.eventStandardWeight });

        Util::ShuffleVector(events);

        while (!events.empty()) {
            auto pair = Util::VectorSelectWeighted(events);
            if (pair.first(isBoss, contName, player)) {
                return true;
            }
            events.erase(std::remove(events.begin(), events.end(), pair), events.end());
        }

        log::error("No valid event triggered!");

        return false;

        //EnableMenus();
    }

    struct ContainerData {
        bool isDeadActor = false;
        bool isPickpocket = false;
        bool isTalking = false;
        bool isBoss = false;
        bool isLeveled = false; // also isContainer
        bool isDoor = false;
        bool isLocked = false;
        bool isDragon = false;
        bool isMage = false;
        int lockLevel = 0;
        int goldValue = 0;
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
        if (actor && !actor->IsDead() && !actor->IsChild() && !player->IsSneaking() && actor->CanTalkToPlayer()) {
            data.isTalking = true;
        }

        RE::TESObjectREFR::InventoryItemMap inventory = activatedObject->GetInventory();

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

        if (activatedObject->HasContainer()) {
            for (auto const& [k, v] : inventory) {
                if (k->GetGoldValue() > 0) {
                    data.goldValue += k->GetGoldValue() * v.first;
                }
            }
        }

        RE::TESObjectDOOR* door = activatedObject->GetObjectReference()->As<RE::TESObjectDOOR>();
        if (door) {
            RE::ExtraDataList* dataList = &activatedObject->extraList;
            auto linkedRef = dataList->GetTeleportLinkedDoor();
            if (linkedRef && linkedRef.get() && linkedRef.get().get()) {
                log::trace("Door has linked ref");
            }
            else {
                data.isDoor = true;
            }
        }

        RE::REFR_LOCK* lockref = activatedObject->GetLock();
        if (lockref) {
            //log::trace("Lock ref base {} isLocked {} isLeveled {}", lockref->baseLevel, lockref->IsLocked(), lockref->flags.all(RE::REFR_LOCK::Flag::kLocked));
            RE::LOCK_LEVEL level = activatedObject->GetLockLevel();
            bool hasKey = false;
            if (level != RE::LOCK_LEVEL::kRequiresKey && level != RE::LOCK_LEVEL::kUnlocked) {
                data.lockLevel = static_cast<int>(level) + 1;
                RE::TESObjectREFR::InventoryItemMap playerInventory = player->GetInventory();
                for (auto const& [k, v] : playerInventory) {
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

        RE::TESFaction* warlockFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x26724, "Skyrim.esm");
        RE::TESFaction* necromancerFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x34B74, "Skyrim.esm");
        if (data.isDeadActor && (actor->IsInFaction(warlockFaction) || actor->IsInFaction(necromancerFaction))) {
            log::trace("Data: Mage");
            data.isMage = true;
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

        std::vector<RE::TESKey*> addedKeys;
        if (data.isLeveled || data.isDeadActor || (data.isPickpocket)) {
            addedKeys = GenerateKeys(activatedObject, false);
            GenerateRandomDevices(activatedObject);
        }

        SKSE::GetTaskInterface()->AddTask([data, activatedObject, player, addedKeys] {
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

            if (data.isMage && IsWearingOppLatex() && oppdCounters.livingLatexCounter == 2) {
                double r = Util::randomDouble();
                RE::TESObjectMISC* volatileGem = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectMISC>(VOLATILE_GEM, "Devious Curses.esp");
                if (GetItemCount(player, volatileGem) == 0 && r <= settings.oppLivingLatexGem) {
                    log::trace("Adding volatile gem to Mage.");
                    activatedObject->AddObjectToContainer((RE::TESBoundObject*)volatileGem, nullptr, 1, nullptr);
                }
            }

            if (data.isBoss && settings.magicKeyChance > 0) {
                RE::TESKey* magicKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(MAGIC_KEY, "Devious Curses.esp");
                double c2 = settings.magicKeyChance * pow(1.5, (GetWornDeviceCount(player) - 1.0) / 9.0);
                double r2 = Util::randomDouble();
                if (GetItemCount(player, magicKey) == 0) {
                    log::trace("Magic Key: {:.2f} ({:.2f})", c2, r2);
                    if (r2 < c2) {
                        activatedObject->AddObjectToContainer((RE::TESBoundObject*)magicKey, nullptr, 1, nullptr);
                    }
                }
            }
            else if (data.isDeadActor && settings.tatSolventChance > 0) {
                RE::TESObjectMISC* solvent = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectMISC>(TATTOO_CHARM, "Devious Curses.esp");
                double c2 = settings.tatSolventChance * pow(1.5, (GetTattooCount(player) - 1.0) / 9.0);
                double r2 = Util::randomDouble();
                if (GetItemCount(player, solvent) == 0) {
                    log::trace("Solvent: {:.2f} ({:.2f})", c2, r2);
                    if (r2 < c2) {
                        activatedObject->AddObjectToContainer((RE::TESBoundObject*)solvent, nullptr, 1, nullptr);
                    }
                }
            }
            else if (data.isLeveled && settings.arousalPotionChance > 0) {
                RE::AlchemyItem* arouaslPotion = StaticDataHolder::GetSingleton()->LookupForm<RE::AlchemyItem>(AROUSAL_POTION, "Devious Curses.esp");
                double c2 = settings.arousalPotionChance * pow(1.5, (ScriptingManager().GetArousal(player) - 50.0) / 50.0);
                double r2 = Util::randomDouble();
                if (GetItemCount(player, arouaslPotion) <= 2) {
                    log::trace("Arousal Potion: {:.2f} ({:.2f})", c2, r2);
                    if (r2 < c2) {
                        activatedObject->AddObjectToContainer((RE::TESBoundObject*)arouaslPotion, nullptr, 1, nullptr);
                    }
                }
            }
        });
    }

    void CalculateEventChance(RE::TESObjectREFR* activatedObject) {
        if (!activatedObject) {
            log::warn("OnObjectActivated called with a null object reference.");
            return;
        }

        log::trace("Activated {} type {} refID {:x} baseID {:x}", activatedObject->GetName(), RE::FormTypeToString(activatedObject->GetFormType()), activatedObject->formID, activatedObject->GetBaseObject()->GetFormID());

        //if (!activatedObject->HasContainer()) {
        //    RE::ExtraDataList* dataList = &activatedObject->extraList;
        //    if (dataList->HasType(RE::ExtraDataType::kAshPileRef)) {
        //        auto pileRef = dataList->GetAshPileRef();
        //        if (pileRef && pileRef.get() && pileRef.get().get()) {
        //            activatedObject = pileRef.get().get();
        //            log::trace("switching to ash pile reference {} type {} refID {:x} baseID {:x}", activatedObject->GetName(), RE::FormTypeToString(activatedObject->GetFormType()), activatedObject->formID, activatedObject->GetBaseObject()->GetFormID());
        //        }
        //    }
        //}

        auto player = RE::PlayerCharacter::GetSingleton();

        auto data = GetContainerData(activatedObject);

        if (!(data.isDeadActor || data.isLeveled || data.isPickpocket || data.isTalking || data.isDoor)) {
            return;
        }

        if (data.isPickpocket && IsPickpocketTargetKnown(activatedObject->formID)) {
            return;
        }

        //log::trace("Worn items: {}", GetWornDeviceCount(GetPlayer()));
        if (IsObjectRefKnown(activatedObject->formID)) {
            if (settings.vanishingKeys && activatedObject != player) {
                log::trace("Removing keys from container.");
                RemoveKeys(activatedObject);
            }
            return;
        }

        if (data.isDeadActor || data.isLeveled || data.isDoor) {
            SetObjectRefKnown(activatedObject->formID);
        }
        else if (data.isPickpocket) {
            SetPickpocketTargetKnown(activatedObject->formID);
        }

        RE::TESFaction* zadDisable = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x4653B, "Devious Devices - Integration.esm");
        RE::Actor* actor = activatedObject->As<RE::Actor>();
        if (actor && actor->IsInFaction(zadDisable)) {
            log::trace("Ignoring NPC.");
            return;
        }

        if (data.isTalking) {
            CheckConsequenceDialogue(actor);
            return;
        }

        /*
        log::trace("isContainer {}", isLeveled);
        log::trace("isBossChest {}", isBoss);
        log::trace("isDeadActor {}", isDeadActor);
        log::trace("isDoor {}", isDoor);
        log::trace("isLocked {}", isLocked);
        */

        //else if (isDeadActor && IsPickpocketTargetKnown(activatedObject->formID) && settings.vanishingKeys) {
        //    RemoveKeys(actor);
        //}

        if (data.isDoor && !data.isLocked && settings.onlyLockedDoors) {
            log::trace("No event: Only locked doors.");
            return;
        }

        if (data.isDeadActor || data.isLeveled || data.isPickpocket) {
            if (data.goldValue < settings.minGoldRequired) {
                log::trace("No event: Not enough gold value ({} < {})", data.goldValue, settings.minGoldRequired);
                return;
            }
            else {
                PopulateContainer(std::move(activatedObject), data);
            }
        }

        //RE::TESFaction* arousalFaction = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("03FC36", 0, 16), "SexLabAroused.esm");
        int playerArousal = ScriptingManager().GetArousal(player);

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
            DecrementCounterForMark(MARK::TAT_HEAT);
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
            auto objectName = activatedObject->GetName();
            //WaitForEventAction(objectName, data, !(data.isDoor || data.isLocked || DCURSES_QLIE_LOADED));
            //activatedObject
            
            for (int i = 0; i < 6; i++) {
                Util::ExecuteWithDelay(250ms * i, [] {
                    ScriptingManager().CloseContainerMenus();
                });
            }
            DoEvent(data.isBoss || data.isDragon, objectName);
            counters.SinceLastEvent = 0;
        }
        else {
            counters.SinceLastEvent++;
        }
    }

    void EventsCheckModIntergations() {
        if (!CheckSimpleSlavery()) {
            if (settings.eventSimpleSlaveryWeight != 0) {
                settings.eventSimpleSlaveryWeight = 0;
                SetMCMInt("eventSimpleSlaveryWeight", 0);
            }
        }
        if (!CheckUD()) {
            if (settings.eventAbadonWeight != 0) {
                settings.eventAbadonWeight = 0;
                SetMCMInt("eventAbadonWeight", 0);
            }

            if (settings.eventAbadonWarriorWeight != 0) {
                settings.eventAbadonWarriorWeight = 0;
                SetMCMInt("eventAbadonWarriorWeight", 0);
            }

            if (settings.eventAbadonScoutWeight != 0) {
                settings.eventAbadonScoutWeight = 0;
                SetMCMInt("eventAbadonScoutWeight", 0);
            }

            if (settings.eventAbadonWitchWeight != 0) {
                settings.eventAbadonWitchWeight = 0;
                SetMCMInt("eventAbadonWitchWeight", 0);
            }
        }
        if (!CheckLewdMarksInstalled()) {
            if (settings.eventLewdMarkWeight != 0) {
                settings.eventLewdMarkWeight = 0;
                SetMCMInt("eventLewdMarkWeight", 0);
            }
        }
        if (!CheckRapeTattoos()) {
            if (settings.eventTattooWeight != 0) {
                settings.eventTattooWeight = 0;
                SetMCMInt("eventTattooWeight", 0);
            }

            if (settings.LMBrandingChance != 0) {
                settings.LMBrandingChance = 0;
                SetMCMFloat("LMBrandingChance", 0);
            }
        }
        if (!CheckWickedDevices()) {
            if (settings.eventWickedWeight != 0) {
                settings.eventWickedWeight = 0;
                SetMCMInt("eventWickedWeight", 0);
            }
        }
    }
}