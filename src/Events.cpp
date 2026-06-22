#include "Events.h"

//#pragma warning(4:4061)

#include "tats.h"
#include "Devices.h"
#include "Locations.h"
#include "Consequences.h"
#include "themes.h"
#include "Contraptions.h"
#include "OppDevices.h"
#include "ModEvents.h"
#include "Settings.h"
#include "Serializer.h"
#include "Scripting.h"
#include "MGEF_Controller.h"
#include "Translation.h"

#include "SexLabPPFunctions.h"
#include "apis/SlaveTatsNG_Interface.h"
#include "apis/DDNG_API.h"
#include "form_ids.h"
#include "Tats.h"

namespace DCURSES {
    void GenerateRandomDevices(RE::TESObjectREFR* activatedObject) {
        if (!(activatedObject && activatedObject->HasContainer())) {
            return;
        }
        auto settings = Settings::GetSingleton();
        bool hasBondageMark = GetLewdMark() == MARK::TAT_BONDAGE;
        bool isLucky = PlayerIsLucky();
        float chance = settings->rDeviceBaseChance;
        if (hasBondageMark) {
            chance += 2.5f;
        }
        if (isLucky) {
            chance *= settings->rDeviceLuckyBonus;
        }
        for (int i = 0; i < 2 + ((hasBondageMark || isLucky) * 2); i++) {
            if (Util::random() < chance) {
                auto dev = GetRandomDevice(&Devices::GetSingleton()->anything);
                if (dev) {
                    activatedObject->AddObjectToContainer(skyrim_cast<RE::TESBoundObject*>(dev.value().inv), nullptr, 1, nullptr);
                }
            }
        }
    }

    bool DoStandardEvent(RE::Actor* actor, bool isBoss, std::string contName, std::string theme, int countOverride, int minDevices, std::vector<std::string> skipKeywords) {
        auto settings = Settings::GetSingleton();

        if (Util::random() < settings->keyLossChance) {
            RemoveKeys(actor);
        }

        auto devices = Devices::GetSingleton();

        std::list<RE::TESObjectARMO*> to_equip;
        RE::TESObjectARMO* heavy = nullptr;

        std::string device_names = "";
        std::string device_ids = "";

        std::set<std::string> usedKeys = GetKeywordsCantEquip(actor);
        for (auto kw : skipKeywords) {
            usedKeys.insert(kw);
        }
        int count = Util::random(settings->minRestraints, settings->maxRestraints);
        if (countOverride > 0) {
            count = countOverride;
        }
        if (isBoss) {
            count += settings->bossAditionalRestraints;
        }
        else if (settings->bossOnlyHeavy && countOverride <= 0) {
            usedKeys.insert("zad_DeviousHeavyBondage");
            log::trace("Not boss chest, no heavy restraints.");
        }

        if (minDevices < 1) {
            minDevices = 1;
        }

        if (!actor->IsPlayerRef()) {
            if (!settings->followerHeavyRestraints) {
                usedKeys.insert("zad_DeviousHeavyBondage");
            }
            if (!settings->followerGags) {
                usedKeys.insert("zad_DeviousGag");
            }
            for (auto keyword : Util::split(settings->followerSkipKeywords, ",")) {
                usedKeys.insert(Util::trim(keyword));
            }

            count = static_cast<int>(count * settings->followerDeviceMult + Util::random<float>(0, 1));
            count += settings->followerDeviceModifier;
        }

        if (count < minDevices) { count = minDevices; }

        if (theme.empty() && settings->useThemes) {
            theme = GetRandomTheme();
        }

        auto sex = SexLab::GetSex(actor);

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

            if (settings->beltPlugs && rend->HasKeywordString("zad_DeviousBelt")) {
                if (!usedKeys.contains("zad_DeviousPlugAnal") && !rend->HasKeywordString("zad_PermitAnal")) {
                    std::optional<DeviceData> plug;
                    plug = GetRandomDevice(&devices->plugsABasic, {}, theme);
                    if (!plug) {
                        plug = GetRandomDevice(&devices->plugsABasic);
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
                if (!usedKeys.contains("zad_DeviousPlugVaginal") && !rend->HasKeywordString("zad_PermitVaginal") && (!settings->useGenderedPlugs || sex == 1)) {
                    std::optional<DeviceData> plug;
                    plug = GetRandomDevice(&devices->plugsVBasic, {}, theme);
                    if (!plug) {
                        plug = GetRandomDevice(&devices->plugsVBasic);
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
            if (settings->plugsDontCount && (rend->HasKeywordString("zad_DeviousPlugVaginal") || rend->HasKeywordString("zad_DeviousPlugAnal"))) {
                i--;
            }
            for (auto const& key : GetDeviceKeywords(rend, true)) {
                usedKeys.insert(key);
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
        else if (settings->stripPlayerOnEvent) {
            UndressActor(actor, false);
        }
        auto scriptManager = ScriptingManager();

        if (!settings->disableForce3rdPerson) scriptManager.ForceThirdPerson();

        if (!contName.empty() && actor->IsPlayerRef()) {
            //PlayerMessage(fmt::format("As you touch the {} you see restraints magically appear and wrap themselves around you!", contName));
            //Util::ExecuteWithDelay(4s, [contName] {
            PlayerMessage(Translator(Translation::EventDevices, contName), settings->surpriseMode);
            //});
        }
        if (settings->eventVisualEffects) {
            scriptManager.PlaySummonVFX(actor);
        }

        for (auto device : to_equip) {
            log::trace("Locking device {} on {}", device->GetName(), actor->GetName());
            scriptManager.LockDevice(actor, device, false);
        }

        std::string msg = "";
        for (auto const& i : usedKeys) { msg += (i + ", "); }
        msg.pop_back(); msg.pop_back();
        log::trace("usedKeys: {}", msg);

        SendCurseModEvent("Bondage", contName, actor, theme);

        if (actor->IsPlayerRef() && GetLewdMark() == MARK::TAT_BONDAGE && Serialized::GetLewdMarkCounters()->bondageCounter > 0) {
            Serialized::GetLewdMarkCounters()->bondageCounter -= static_cast<int32_t>(to_equip.size());
        }

        return true;
    }

    bool DoSimpleSlaveryEvent(std::string contName) {
        auto player = RE::PlayerCharacter::GetSingleton();
        if (!CheckSimpleSlavery()) {
            return false;
        }
        if (GetWornDeviceCount(player) < Settings::GetSingleton()->eventSSMinRestraints) {
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
        PlayerMessage(Translator(Translation::EventSimpleSlavery, contName), Settings::GetSingleton()->surpriseMode);
        if (Settings::GetSingleton()->eventVisualEffects) {
            ScriptingManager().PlaySummonVFX(player);
        }
        SendCurseModEvent("SimpleSlavery", contName, player, "");

        return true;

    }

    bool DoTattooEvent(RE::Actor* actor, std::string containerName, int num_tattoos, bool skipMax) {
        auto settings = Settings::GetSingleton();

        if (settings->eventTattooWeight == 0) {
            return false;
        }

        if (!skipMax && GetTattooCount(actor) > settings->eventTattooCap) {
            return false;
        }

        if (num_tattoos < 1) {
            num_tattoos = Util::random(settings->eventTattooMin, settings->eventTattooMax);
        }
        ScriptingManager().RTDoTattooEvent(actor, num_tattoos);

        if (!containerName.empty() && actor->IsPlayerRef()) {
            if (num_tattoos == 1) {
                PlayerMessage(Translator(Translation::EventTattooOne, containerName), Settings::GetSingleton()->surpriseMode);
            }
            else if (num_tattoos <= 3) {
                PlayerMessage(Translator(Translation::EventTattooTwoThree, containerName), Settings::GetSingleton()->surpriseMode);
            }
            else {
                PlayerMessage(Translator(Translation::EventTattooMany, containerName), Settings::GetSingleton()->surpriseMode);
            }
        }
        if (settings->eventVisualEffects) {
            ScriptingManager().PlaySummonVFX(actor);
        }

        SendCurseModEvent("Tattoo", containerName, actor, "");

        return true;
    }

    bool P_CheckSTNG(RE::StaticFunctionTag*) {
        return slavetats_ng::iface;
    }

    bool P_CheckLM(RE::StaticFunctionTag*) {
        return CheckLewdMarksInstalled();
    }

    bool PapyrusFunctionsTats(RE::BSScript::IVirtualMachine* ivm) {
        ivm->RegisterFunction("CheckSTNG", "DCurses_MCM", P_CheckSTNG);
        ivm->RegisterFunction("CheckLM", "DCurses_MCM", P_CheckLM);
        return true;
    }

    bool DoContraptionEvent(std::string containerName, RE::Actor* target, std::string theme) {
        //auto player = RE::PlayerCharacter::GetSingleton();
        target = target == nullptr ? RE::PlayerCharacter::GetSingleton() : target;
        auto settings = Settings::GetSingleton();

        if (settings->eventContAllDevices) {
            DoStandardEvent(target, false, "", theme, settings->eventContDeviceOverride, 1, { "zad_DeviousHeavyBondage" });
        }
        else if (settings->eventContDevices) {
            DoStandardEvent(target, false, "", theme, settings->eventContDeviceOverride, 1, { "zad_DeviousHeavyBondage", "zad_DeviousBelt", "zad_DeviousBra", "zad_DeviousHarness", "zad_DeviousBlindfold", "zad_DeviousHood", "zad_DeviousBoots", "zad_DeviousGloves", "zad_DeviousSuit", "zad_DeviousCorset" });
        }

        auto contraption = CreateAndLockContraption(target);

        Serialized::GetCounters()->clock_SexTimeout -= 5;

        //PlayerMessage(fmt::format("As you touch the {} you feel yourself get dizzy as you are strung up into some sort of contraption!", containerName));
        PlayerMessage(Translator(Translation::EventContraption, containerName), Settings::GetSingleton()->surpriseMode);

        if (settings->eventVisualEffects) {
            ScriptingManager().PlaySummonVFX(target);
        }

        SendCurseModEvent("Contraption", containerName, RE::PlayerCharacter::GetSingleton(), contraption->GetName());

        return true;
    }

    bool DoLewdMarkEvent(std::string containerName, double multiplier) {
        if (!CheckLewdMarksInstalled()) {
            return false;
        }
        auto player = RE::PlayerCharacter::GetSingleton();
        if (GetLewdMark() != MARK::TAT_NONE) {
            return false;
        }

        auto settings = Settings::GetSingleton();

        std::vector<std::pair<std::function<MARK()>, double>> marks;

        if (GetTattooCount(player) < settings->LMBrandingTotal / 2) marks.push_back({ [player, containerName] {
            if (!containerName.empty()) { PlayerMessage(Translator(Translation::EventMarkBranding), Settings::GetSingleton()->surpriseMode); }
            return MARK::TAT_BRANDING;
        } , settings->LMBrandingWeight });

        if (settings->sexEnabled) marks.push_back({ [player, containerName] {
            if (!containerName.empty()) { PlayerMessage(Translator(Translation::EventMarkAllure), Settings::GetSingleton()->surpriseMode); }
            return MARK::TAT_ALLURE;
        } , settings->LMAllureWeight });

        marks.push_back({ [player, containerName] {
            if (!containerName.empty()) { PlayerMessage(Translator(Translation::EventMarkHeat), Settings::GetSingleton()->surpriseMode); }
            return MARK::TAT_HEAT;
        } , settings->LMHeatWeight });

        marks.push_back({ [player, containerName] {
            if (!containerName.empty()) { PlayerMessage(Translator(Translation::EventMarkBondage), Settings::GetSingleton()->surpriseMode); }
            return MARK::TAT_BONDAGE;
        } , settings->LMBondageWeight });

        marks.push_back({ [player, containerName] {
            if (!containerName.empty()) { PlayerMessage(Translator(Translation::EventMarkNudity), Settings::GetSingleton()->surpriseMode); }
            return MARK::TAT_NUDITY;
        } , settings->LMNudityWeight });

        marks.push_back({ [player, containerName] {
           if (!containerName.empty()) { PlayerMessage(Translator(Translation::EventMarkHealslut), Settings::GetSingleton()->surpriseMode); }
           return MARK::TAT_HEALSLUT;
        } , settings->LMHealslutWeight });

        if (settings->sexEnabled) marks.push_back({ [player, containerName] {
           if (!containerName.empty()) { PlayerMessage(Translator(Translation::EventMarkPainslut), Settings::GetSingleton()->surpriseMode); }
           return MARK::TAT_PAINSLUT;
        } , settings->LMPainslutWeight });

        auto pair = Util::VectorSelectWeighted(marks);
        if (!pair.has_value()) {
            return false;
        }
        auto mark = pair.value().first();

        AddLewdMark(mark);
        SetMarkToDefaultSettings(mark, multiplier);

        if (settings->eventVisualEffects) {
            ScriptingManager().PlaySummonVFX(player);
        }

        SendCurseModEvent("LewdMark", containerName, player, GetMarkAsString(mark));

        return true;
    }

    void DoWickedEvent(std::string containerName) {
        CustomModEvent::SendModEvent("DwdEquipDeviceWithMcmChances", "", 1);
        PlayerMessage(Translator(Translation::EventWicked, containerName), Settings::GetSingleton()->surpriseMode);

        if (Settings::GetSingleton()->eventVisualEffects) {
            ScriptingManager().PlaySummonVFX(RE::PlayerCharacter::GetSingleton());
        }

        SendCurseModEvent("WickedDevices", containerName, RE::PlayerCharacter::GetSingleton(), "");
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
            plug = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(UD_ABADONPLUG_INVENTORY, "Unforgivingdevices.esp");
        }
        else if (!canVaginal) {
            plug = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(UD_ABADONPLUGANAL_INVENTORY, "Unforgivingdevices.esp");
        }
        else {
            plug = Util::random() < 50.0 ?
                StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(UD_ABADONPLUG_INVENTORY, "Unforgivingdevices.esp") :
                StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(UD_ABADONPLUGANAL_INVENTORY, "Unforgivingdevices.esp");
        }

        if (!plug) {
            log::warn("Unable to find Abadon plug to lock, aboting");
            return false;
        }

        scriptManager.LockDevice(player, plug, true);
        if (!containerName.empty()) {
            PlayerMessage(Translator(Translation::EventAbadon, containerName), Settings::GetSingleton()->surpriseMode);
        }

        if (Settings::GetSingleton()->eventVisualEffects) {
            ScriptingManager().PlaySummonVFX(player);
        }

        SendCurseModEvent("AbadonPlug", containerName, player, "");

        return true;
    }

    bool DoAbadonSetEvent(std::string containerName, RE::Actor* actor, AbadonEventType type) {
        if (GetWornDeviceCount(actor) > 6) {
            return false;
        }

        auto settings = Settings::GetSingleton();

        std::vector<uint32_t> set = {};

        int count = -1;
        switch (type) {
        case AbadonEventType::Warrior: {
            set = UD_ARMORSET01;
            count = settings->eventAbadonWarriorCount;
            break;
        }
        case AbadonEventType::Scout: {
            set = UD_ARMORSET02;
            count = settings->eventAbadonScoutCount;
            break;
        }
        case AbadonEventType::Witch: {
            set = UD_ARMORSET03;
            count = settings->eventAbadonWitchCount;
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
            auto to_equip = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(form_id, "Unforgivingdevices->esp");
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

        std::string typeString = "";

        switch (type) {
        case AbadonEventType::Warrior: {
            PlayerMessage(Translator(Translation::EventAbadonWarrior, containerName), Settings::GetSingleton()->surpriseMode);
            typeString = "Warrior";
            break;
        }
        case AbadonEventType::Scout: {
            PlayerMessage(Translator(Translation::EventAbadonScout, containerName), Settings::GetSingleton()->surpriseMode);
            typeString = "Scout";
            break;
        }
        case AbadonEventType::Witch: {
            PlayerMessage(Translator(Translation::EventAbadonWitch, containerName), Settings::GetSingleton()->surpriseMode);
            typeString = "Witch";
            break;
        }
        default:
            return false;
        }

        if (Settings::GetSingleton()->eventVisualEffects) {
            ScriptingManager().PlaySummonVFX(actor);
        }

        SendCurseModEvent("AbadonSet", containerName, actor, typeString);

        return true;
    }

    std::vector<RE::Actor*> GetFollowersForEvent() {
        std::vector<RE::Actor*> result;
        auto settings = Settings::GetSingleton();

        for (auto follower : Util::GetFollowers()) {
            if (settings->onlyFemaleFollowers && follower->GetActorBase()->GetSex() != RE::SEX::kFemale) {
                continue;
            }
            if (settings->excludedFollowers != "") {
                bool useFollower = true;
                auto names = Util::split(settings->excludedFollowers, ",");
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
        auto settings = Settings::GetSingleton();

        std::vector<std::pair<bool(*)(bool, std::string, RE::Actor*), double>> events;

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoSimpleSlaveryEvent(contName)) {
                log::info("Ran event Simple Slavery");
                UndressAndUnequipActor(player);
                return true;
            }
            return false;
        }, settings->eventSimpleSlaveryWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoContraptionEvent(contName)) {
                log::info("Ran event Contraption");
                UnequipItems(player);
                if (Settings::GetSingleton()->stripPlayerOnEvent) {
                    UndressActor(player, true);
                }
                return true;
            }
            return false;
        }, settings->eventContraptionWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoOppDeviceEvent(contName)) {
                log::info("Ran event Oppressive Device");
                if (Settings::GetSingleton()->stripPlayerOnEvent) {
                    UndressActor(player, false);
                }
                return true;
            }
            return false;
        }, settings->eventOppressiveWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoTattooEvent(player, contName)) {
                log::info("Ran event Tattoo");
                if (Settings::GetSingleton()->stripPlayerOnEvent) {
                    UndressActor(player, false);
                }
                if (Settings::GetSingleton()->followerTattooEvent) {
                    log::info("Applying tattoos to followers...");
                    for (auto follower : GetFollowersForEvent()) {
                        DoTattooEvent(follower, contName);
                    }
                }
                return true;
            }
            return false;
        }, settings->eventTattooWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoLewdMarkEvent(contName)) {
                log::info("Ran event Mark");
                if (Settings::GetSingleton()->stripPlayerOnEvent) {
                    UndressActor(player, false);
                }
                return true;
            }
            return false;
        }, settings->eventLewdMarkWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            DoWickedEvent(contName);
            log::info("Ran event Wicked");
            if (Settings::GetSingleton()->stripPlayerOnEvent) {
                UndressActor(player, false);
            }
            return true;
        }, settings->eventWickedWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoAbadonEvent(contName)) {
                log::info("Ran event Abadon");
                if (Settings::GetSingleton()->stripPlayerOnEvent) {
                    UndressActor(player, false);
                }
                return true;
            }
            return false;
        }, settings->eventAbadonWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoAbadonSetEvent(contName, player, AbadonEventType::Warrior)) {
                log::info("Ran event Abadon Warrior");
                if (Settings::GetSingleton()->stripPlayerOnEvent) {
                    UndressActor(player, false);
                }
                return true;
            }
            return false;
        }, settings->eventAbadonWarriorWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoAbadonSetEvent(contName, player, AbadonEventType::Scout)) {
                log::info("Ran event Abadon Scout");
                if (Settings::GetSingleton()->stripPlayerOnEvent) {
                    UndressActor(player, false);
                }
                return true;
            }
            return false;
        }, settings->eventAbadonScoutWeight });

        events.push_back({ [](bool, std::string contName, RE::Actor* player) {
            if (DoAbadonSetEvent(contName, player, AbadonEventType::Witch)) {
                log::info("Ran event Abadon Witch");
                if (Settings::GetSingleton()->stripPlayerOnEvent) {
                    UndressActor(player, false);
                }
                return true;
            }
            return false;
        }, settings->eventAbadonWitchWeight });

        events.push_back({ [](bool isBoss, std::string contName, RE::Actor* player) {
            if (DoStandardEvent(player, isBoss, contName)) {
                log::info("Ran event Standard");
                if (Settings::GetSingleton()->followerBondageEvent) {
                    log::info("Adding Devices to followers...");
                    for (auto follower : GetFollowersForEvent()) {
                        DoStandardEvent(follower, isBoss, contName, Settings::GetSingleton()->followerOverrideTheme);
                    }
                }
                return true;
           }
           return false;
        }, settings->eventStandardWeight });

        Util::ShuffleVector(events);

        while (!events.empty()) {
            auto pair = Util::VectorSelectWeighted(events);
            if (!pair.has_value()) {
                log::error("No valid event triggered!");
                return false;
            }
            if (pair.value().first(isBoss, contName, player)) {
                return true;
            }
            events.erase(std::remove(events.begin(), events.end(), pair), events.end());
        }

        log::error("No valid event triggered!");

        return false;

        //EnableMenus();
    }

    void PlayWardEffect() {
        if (Settings::GetSingleton()->eventVisualEffects) {
            auto player = RE::PlayerCharacter::GetSingleton();
            SKSE::GetTaskInterface()->AddTask([player]() {
                RE::Explosion* test = StaticDataHolder::GetSingleton()->LookupForm<RE::Explosion>(0x225AF, "Skyrim.esm");
                auto ptr = player->PlaceObjectAtMe(skyrim_cast<RE::TESBoundObject*>(test), false);
                Util::ExecuteWithDelay(10s, [ptr] {
                    if (ptr) {
                        ptr->Disable();
                        ptr->DeleteThis();
                    }
                });
            });
        }
    }

    ContainerData GetContainerData(RE::TESObjectREFR* activatedObject) {
        ContainerData data;

        auto player = RE::PlayerCharacter::GetSingleton();
        auto settings = Settings::GetSingleton();

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
            for (auto const& path : paths) {
                if (model_path == path) { data.isBoss = true; }
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

        if (data.isDeadActor && actor->GetRace()->HasKeywordString("ActorTypeDragon") && settings->dragonHoard) {
            data.isDragon = true;
        }

        if (actor && (data.isDeadActor && !Util::ActorIsCreature(actor))) {
            auto actor_base = actor->GetActorBase();
            if (settings->oppLivingLatexGemAll) {
                data.isMage = true;
            }
            if (actor_base && actor_base->npcClass) {
                auto class_data = actor_base->npcClass->data;
                if (class_data.skillWeights.destruction >= 3 || class_data.skillWeights.restoration >= 3 || class_data.skillWeights.conjuration >= 3) {
                    data.isMage = true;
                }
            }
            else {
                RE::TESFaction* warlockFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x26724, "Skyrim.esm");
                RE::TESFaction* necromancerFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x34B74, "Skyrim.esm");
                if ((actor->IsInFaction(warlockFaction) || actor->IsInFaction(necromancerFaction))) {
                    data.isMage = true;
                }
            }
        }

        return data;
    }

    void PopulateContainer(RE::TESObjectREFR* activatedObject, ContainerData data) {
        auto settings = Settings::GetSingleton();

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

        if (settings->vanishingKeys && activatedObject != player) {
            RemoveKeys(activatedObject);
        }

        std::vector<RE::TESKey*> addedKeys;
        if (data.isLeveled || data.isDeadActor || (data.isPickpocket)) {
            addedKeys = GenerateKeys(activatedObject, false);
            GenerateRandomDevices(activatedObject);
        }

        if (data.isLeveled && data.isBoss && settings->bossExtraGold) {
            log::trace("Adding extra gold to boss chest.");
            RE::TESForm* gold = RE::TESForm::LookupByID(std::stoi("0f", 0, 16));
            activatedObject->AddObjectToContainer(skyrim_cast<RE::TESBoundObject*>(gold), nullptr, (player->GetLevel()), nullptr);
        }

        if (data.isDragon) {
            log::trace("Actor is dragon and dragon hoards are on.");
            RE::TESForm* gold = RE::TESForm::LookupByID(std::stoi("0f", 0, 16));
            activatedObject->AddObjectToContainer(skyrim_cast<RE::TESBoundObject*>(gold), nullptr, static_cast<int>(player->GetLevel() * 80.0 * Util::random(0.3, 1.0) + Util::random(50, 200)), nullptr);
        }

        if (data.isMage && IsWearingOppLatex() && Serialized::GetOppDeviceCounters()->livingLatexCounter == 2) {
            double r = Util::random();
            RE::TESObjectMISC* volatileGem = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectMISC>(VOLATILE_GEM, "Devious Curses.esp");
            if (GetItemCount(player, volatileGem) == 0 && r <= settings->oppLivingLatexGem) {
                log::trace("Adding volatile gem to Mage.");
                activatedObject->AddObjectToContainer(skyrim_cast<RE::TESBoundObject*>(volatileGem), nullptr, 1, nullptr);
            }
        }

        //Only one past this point
        if (addedKeys.empty()) {
            if (settings->wardingCharmChance > 0) {
                RE::TESObjectMISC* ward = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectMISC>(WARDING_CHARM, "Devious Curses.esp");
                double chance = settings->wardingCharmChance * 1.0 / (1.0 * pow(GetItemCount(player, ward), 2.0) + 1);
                double r = Util::random();
                log::trace("Warding: {:.2f} ({:.2f})", chance, r);
                if (r < chance) {
                    activatedObject->AddObjectToContainer(skyrim_cast<RE::TESBoundObject*>(ward), nullptr, 1, nullptr);
                    return;
                }
            }
            if (data.isBoss && settings->magicKeyChance > 0) {
                RE::TESKey* magicKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(MAGIC_KEY, "Devious Curses.esp");
                double c2 = settings->magicKeyChance * pow(1.5, (GetWornDeviceCount(player) - 1.0) / 9.0);
                double r2 = Util::random();
                if (GetItemCount(player, magicKey) == 0) {
                    log::trace("Magic Key: {:.2f} ({:.2f})", c2, r2);
                    if (r2 < c2) {
                        activatedObject->AddObjectToContainer(skyrim_cast<RE::TESBoundObject*>(magicKey), nullptr, 1, nullptr);
                        return;
                    }
                }
            }
            if (data.isDeadActor && settings->tatSolventChance > 0) {
                RE::TESObjectMISC* solvent = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectMISC>(TATTOO_CHARM, "Devious Curses.esp");
                double c2 = settings->tatSolventChance * pow(1.5, (GetTattooCount(player) - 1.0) / 9.0);
                double r2 = Util::random();
                if (GetItemCount(player, solvent) == 0) {
                    log::trace("Solvent: {:.2f} ({:.2f})", c2, r2);
                    if (r2 < c2) {
                        activatedObject->AddObjectToContainer(skyrim_cast<RE::TESBoundObject*>(solvent), nullptr, 1, nullptr);
                        return;
                    }
                }
            }
            if (data.isLeveled && settings->arousalPotionChance > 0) {
                RE::AlchemyItem* arouaslPotion = StaticDataHolder::GetSingleton()->LookupForm<RE::AlchemyItem>(AROUSAL_POTION, "Devious Curses.esp");
                double c2 = settings->arousalPotionChance * pow(1.5, (ScriptingManager().GetArousal(player) - 50.0) / 50.0);
                double r2 = Util::random();
                if (GetItemCount(player, arouaslPotion) <= 2) {
                    log::trace("Arousal Potion: {:.2f} ({:.2f})", c2, r2);
                    if (r2 < c2) {
                        activatedObject->AddObjectToContainer(skyrim_cast<RE::TESBoundObject*>(arouaslPotion), nullptr, 1, nullptr);
                        return;
                    }
                }
            }
        }
    }

    void CalculateEventChance(RE::TESObjectREFR* activatedObject) {
        if (!activatedObject) {
            log::warn("CalculateEventChance called with a null object reference.");
            return;
        }

        log::trace("Activated {} type {} refID {:x} baseID {:x}", activatedObject->GetName(), RE::FormTypeToString(activatedObject->GetFormType()), activatedObject->formID, activatedObject->GetBaseObject()->GetFormID());
        auto lastObject = Serialized::GetRefLists()->lastActivatedObjectREFR;
        Serialized::GetRefLists()->lastActivatedObjectREFR = activatedObject->formID;

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
        auto playerMark = GetLewdMark();
        auto settings = Settings::GetSingleton();
        auto data = GetContainerData(activatedObject);

        if (!(data.isDeadActor || data.isLeveled || data.isPickpocket || data.isTalking || data.isDoor)) {
            return;
        }

        if (data.isPickpocket && IsPickpocketTargetKnown(activatedObject->formID)) {
            return;
        }

        //log::trace("Worn items: {}", GetWornDeviceCount(GetPlayer()));
        if (IsObjectRefKnown(activatedObject->formID)) {
            if (settings->vanishingKeys && activatedObject != player && lastObject && activatedObject->formID != lastObject) {
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

        //else if (isDeadActor && IsPickpocketTargetKnown(activatedObject->formID) && settings->vanishingKeys) {
        //    RemoveKeys(actor);
        //}

        if (data.isDoor && !data.isLocked && settings->onlyLockedDoors) {
            log::trace("No event: Only locked doors.");
            return;
        }

        if (data.isDeadActor || data.isLeveled || data.isPickpocket) {
            if (data.goldValue < settings->minGoldRequired) {
                log::trace("No event: Not enough gold value ({} < {})", data.goldValue, settings->minGoldRequired);
                return;
            }
            else {
                PopulateContainer(std::move(activatedObject), data);
            }
        }

        //RE::TESFaction* arousalFaction = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("03FC36", 0, 16), "SexLabAroused.esm");
        int playerArousal = ScriptingManager().GetArousal(player);

        float chance = settings->baseChance;
        std::string logMessage = fmt::format("{}% -> ", settings->baseChance);

        if (settings->arousalModifier > 1.01f && playerArousal > 0) {
            float modifier = (settings->arousalModifier - 1) * playerArousal / 100.0f + 1;
            chance *= modifier;
            logMessage += fmt::format("(arousal {} {:.2f}) ", playerArousal, modifier);
        }


        if (data.isDeadActor) {
            chance *= settings->deadBodyModifier;
            logMessage += fmt::format("(dead {}) ", settings->deadBodyModifier);
        }
        else if (data.isLeveled) {
            if (Serialized::GetLewdMarkCounters()->heatCounter > 0) {
                Serialized::GetLewdMarkCounters()->heatCounter -= 1;
            }
            chance *= settings->containerModifier;
            logMessage += fmt::format("(container {}) ", settings->containerModifier);
        }
        else if (data.isDoor) {
            if (!settings->onlyLockedDoors || data.isLocked) {
                chance *= settings->doorModifier;
                logMessage += fmt::format("(door {}) ", settings->doorModifier);
            }
        }
        else if (data.isPickpocket) {
            chance *= settings->pickpocketModifier;
            logMessage += fmt::format("(pickpocket {}) ", settings->pickpocketModifier);
        }
        else {
            return;
        }

        if (data.isBoss) {
            chance *= settings->bossContainerModifier;
            logMessage += fmt::format("(boss {}) ", settings->bossContainerModifier);
        }
        if (data.isLocked) {
            chance *= settings->lockedModifier;
            if (data.lockLevel >= 0 && settings->lockDifficultyModifier > 1.0) {
                float modifier = (settings->lockDifficultyModifier - 1) * (data.lockLevel / 5.0f) + 1;
                chance *= modifier;
                logMessage += fmt::format("(locked {:.2f}) ", modifier * settings->lockedModifier);
            }
            else {
                logMessage += fmt::format("(locked {}) ", settings->lockedModifier);
            }
        }

        auto location_type = GetPlayerLocationType();

        float location_chance = GetLocationTypeEventModifier(location_type);
        std::string location_name = GetLocationTypeString(location_type);

        if (data.isLocked) {
            location_name += " [L]";
            if (location_chance < settings->lockedLocationBypass) {
                location_chance = settings->lockedLocationBypass;
            }
        }
        if (data.isDragon) {
            location_name += " [D]";
            if (location_chance < 1.0) {
                location_chance = 1.0;
            }
        }
        if ((player->WouldBeStealing(activatedObject) || data.isPickpocket)) {
            location_name += " [T]";
            if (location_chance < settings->theftLocationBypass) {
                location_chance = settings->theftLocationBypass;
            }
        }

        chance *= location_chance;
        logMessage += fmt::format("({} {}) ", location_name, location_chance);

        if (data.isDragon) {
            chance *= settings->bossContainerModifier * 1.2f;
            //chance *= actor->GetLevel() / 75.0f + 1;
            logMessage += fmt::format("(dragon {:.2f}) ", settings->bossContainerModifier * 1.2f);
        }
        else if (settings->eventScaling) {
            float eventScaling = ((3.0f * settings->eventScalingMod) / ((-2.0f * settings->eventScalingMod) - Serialized::GetCounters()->SinceLastEvent)) + 2.0f;
            logMessage += fmt::format("(scaling {:.2f}) ", eventScaling);
            chance *= eventScaling;
        }

        if (!data.isDragon && GetWornDeviceCount(player) > settings->restraintCap + (playerMark == MARK::TAT_BONDAGE ? settings->LMBondageDeviceCapAdd : 0)) {
            log::trace("No event: Too many devices.");
            chance = 0.0;
        }
        else if (data.isDragon) {
            log::trace("Device count restriction skipped: Dragon hoard.");
        }

        if (playerArousal < settings->minArousal && settings->minArousal > 0) {
            log::trace("No event player arousal too low {} < {}", playerArousal, settings->minArousal);
            chance = 0.0;
        }

        double r = Util::random();

        auto EventMessage = fmt::format("Event: {} Total: {:.2f}%", logMessage, chance);

        if (playerMark == MARK::TAT_BONDAGE) {
            EventMessage += fmt::format(" ({:.2f}%)", chance * settings->LMBondageModifier);
        }

        log::info("{}", EventMessage);
        if (r < chance) {
            auto objectName = activatedObject->GetName();

            RE::TESObjectMISC* ward = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectMISC>(WARDING_CHARM, "Devious Curses.esp");
            if (GetItemCount(player, ward) > 0) {
                PlayWardEffect();
                player->RemoveItem(skyrim_cast<RE::TESBoundObject*>(ward), 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
                ScriptingManager().DBGNotification(Translator(Translation::ItemWardUsed, objectName));
                return;
            }

            for (int i = 0; i < 6; i++) {
                Util::ExecuteWithDelay(200ms * i, [] {
                    ScriptingManager().CloseContainerMenus();
                    });
            }
            DoEvent(data.isBoss || data.isDragon, objectName);
            Serialized::GetCounters()->SinceLastEvent = 0;
        }
        else if (GetLewdMark() == MARK::TAT_BONDAGE && r < chance * settings->LMBondageModifier) {
            auto objectName = activatedObject->GetName();

            RE::TESObjectMISC* ward = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectMISC>(WARDING_CHARM, "Devious Curses.esp");
            if (GetItemCount(player, ward) > 0) {
                PlayWardEffect();
                player->RemoveItem(skyrim_cast<RE::TESBoundObject*>(ward), 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
                ScriptingManager().DBGNotification(Translator(Translation::ItemWardUsed, objectName));
                return;
            }

            for (int i = 0; i < 6; i++) {
                Util::ExecuteWithDelay(200ms * i, [] {
                    ScriptingManager().CloseContainerMenus();
                    });
            }
            DoStandardEvent(player, data.isBoss || data.isDragon, "");
            PlayerMessage(Translator(Translation::MarkBondageCurse, objectName), settings->surpriseMode);
            Serialized::GetCounters()->SinceLastEvent = 0;
        }
        else {
            Serialized::GetCounters()->SinceLastEvent++;
        }
    }

    void EventsCheckModIntergations() {
        auto settings = Settings::GetSingleton();

        if (!CheckSimpleSlavery()) {
            if (settings->eventSimpleSlaveryWeight != 0) {
                settings->eventSimpleSlaveryWeight = 0;
                RE::BSScript::Variable var;
                var.SetSInt(0);
                SetMCMSetting("eventSimpleSlaveryWeight", var, "Devious Curses.esp", "DCurses_MCM");
            }
        }
        if (!CheckUD()) {
            if (settings->eventAbadonWeight != 0) {
                settings->eventAbadonWeight = 0;
                RE::BSScript::Variable var;
                var.SetSInt(0);
                SetMCMSetting("eventAbadonWeight", var, "Devious Curses.esp", "DCurses_MCM");
            }

            if (settings->eventAbadonWarriorWeight != 0) {
                settings->eventAbadonWarriorWeight = 0;
                RE::BSScript::Variable var;
                var.SetSInt(0);
                SetMCMSetting("eventAbadonWarriorWeight", var, "Devious Curses.esp", "DCurses_MCM");
            }

            if (settings->eventAbadonScoutWeight != 0) {
                settings->eventAbadonScoutWeight = 0;
                RE::BSScript::Variable var;
                var.SetSInt(0);
                SetMCMSetting("eventAbadonScoutWeight", var, "Devious Curses.esp", "DCurses_MCM");
            }

            if (settings->eventAbadonWitchWeight != 0) {
                settings->eventAbadonWitchWeight = 0;
                RE::BSScript::Variable var;
                var.SetSInt(0);
                SetMCMSetting("eventAbadonWitchWeight", var, "Devious Curses.esp", "DCurses_MCM");
            }
        }
        if (!CheckLewdMarksInstalled()) {
            if (settings->eventLewdMarkWeight != 0) {
                settings->eventLewdMarkWeight = 0;
                RE::BSScript::Variable var;
                var.SetSInt(0);
                SetMCMSetting("eventLewdMarkWeight", var, "Devious Curses.esp", "DCurses_MCM");
            }
        }
        if (!CheckRapeTattoos()) {
            if (settings->eventTattooWeight != 0) {
                settings->eventTattooWeight = 0;
                RE::BSScript::Variable var;
                var.SetSInt(0);
                SetMCMSetting("eventTattooWeight", var, "Devious Curses.esp", "DCurses_MCM");
            }

            if (settings->LMBrandingChance != 0) {
                settings->LMBrandingChance = 0;
                RE::BSScript::Variable var;
                var.SetFloat(0);
                SetMCMSetting("LMBrandingChance", var, "Devious Curses.esp", "DCurses_MCM");
            }
        }
        if (!CheckWickedDevices()) {
            if (settings->eventWickedWeight != 0) {
                settings->eventWickedWeight = 0;
                RE::BSScript::Variable var;
                var.SetSInt(0);
                SetMCMSetting("eventWickedWeight", var, "Devious Curses.esp", "DCurses_MCM");
            }
        }
    }
}