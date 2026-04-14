#pragma once

#include "../include/form_ids.h"
#include "DebugMode.hpp"
#include "events.hpp"
#include "QuestInteractions.hpp"

using namespace SKSE;

namespace DCURSES {

    class QuestStageEventSink : public RE::BSTEventSink<RE::TESQuestStageEvent> {
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESQuestStageEvent* questEvent, RE::BSTEventSource<RE::TESQuestStageEvent>*) override {
            if (!questEvent) return RE::BSEventNotifyControl::kContinue;
            QICheckQuestStage(questEvent->formID, questEvent->stage);
            return RE::BSEventNotifyControl::kContinue;
        }
    public:
        static void RegisterEvent() {
            static QuestStageEventSink eventSink;
            auto ScriptEventSource = RE::ScriptEventSourceHolder::GetSingleton();
            if (!ScriptEventSource) {
                return;
            }
            ScriptEventSource->AddEventSink(&eventSink);
        }
    };

    class ActivateEventSink : public RE::BSTEventSink<RE::TESActivateEvent> {
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESActivateEvent* activateEvent, RE::BSTEventSource<RE::TESActivateEvent>*) override {
            if (!activateEvent) return RE::BSEventNotifyControl::kContinue;
            auto activatedObject = activateEvent->objectActivated.get();
            auto activatingActor = activateEvent->actionRef.get();

            if (activatedObject && activatingActor && activatingActor == RE::PlayerCharacter::GetSingleton()) {
                if (counters.clock_SexTimeout >= settings.sexSearchInterval - 1) {
                    counters.clock_SexTimeout = settings.sexSearchInterval - 3;
                }
                QICheckObjectActivation(activatedObject); // Must do first!
                if (IsModDisabled()) {
                    log::trace("Activate skipped, mod is disabled.");
                    //return RE::BSEventNotifyControl::kContinue;
                }
                CalculateEventChance(activatedObject);
                OppNocturnalTryRecast();
                //return RE::BSEventNotifyControl::kContinue;
            }
            return RE::BSEventNotifyControl::kContinue;
        }
    public:
        static void RegisterEvent() {
            static ActivateEventSink eventSink;
            auto ScriptEventSource = RE::ScriptEventSourceHolder::GetSingleton();
            if (!ScriptEventSource) {
                return;
            }
            ScriptEventSource->PrependEventSink(&eventSink);
        }
    };

    class ContainerChangedEventSink : public RE::BSTEventSink<RE::TESContainerChangedEvent> {
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESContainerChangedEvent* containerEvent, RE::BSTEventSource<RE::TESContainerChangedEvent>*) override {
            //auto source = RE::TESForm::LookupByID(containerEvent->oldContainer)->As<RE::TESObjectREFR>();
            
            if (containerEvent->oldContainer == 0x14) {
                RE::TESKey* magicKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(MAGIC_KEY, "Devious Curses.esp");
                RE::TESObjectMISC* tattooCharm = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectMISC>(TATTOO_CHARM, "Devious Curses.esp");

                auto dest = RE::TESForm::LookupByID(containerEvent->newContainer);
                if (dest) {
                    auto actor = dest->As<RE::Actor>();
                    if (actor) {
                        auto movedForm = RE::TESForm::LookupByID(containerEvent->baseObj);
                        if (movedForm == magicKey) {
                            RemoveAllRestraints(actor, true);

                            actor->RemoveItem((RE::TESBoundObject*)magicKey, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
                            PlayerMessage(Translator(Translation::ItemMagicKeyOther, actor->GetName()));
                        }

                        else if (movedForm == tattooCharm) {
                            RemoveAllTattoos(actor);

                            actor->RemoveItem((RE::TESBoundObject*)tattooCharm, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
                            PlayerMessage(Translator(Translation::ItemTattooCharmOther, actor->GetName()));
                        }
                    }
                }
            }

            return RE::BSEventNotifyControl::kContinue;
        }
    public:
        static void RegisterEvent() {
            static ContainerChangedEventSink eventSink;
            auto ScriptEventSource = RE::ScriptEventSourceHolder::GetSingleton();
            if (!ScriptEventSource) {
                return;
            }
            ScriptEventSource->PrependEventSink(&eventSink);
        }
    };

    class EquipEventSink : public RE::BSTEventSink<RE::TESEquipEvent>
    {
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESEquipEvent* equipEvent, RE::BSTEventSource<RE::TESEquipEvent>*) override {
            if (!equipEvent || !equipEvent->actor || !equipEvent->baseObject) {
                return RE::BSEventNotifyControl::kContinue;
            }
            auto equipActor = equipEvent->actor.get();
            auto equipmentForm = RE::TESForm::LookupByID(equipEvent->baseObject);
            auto player = RE::PlayerCharacter::GetSingleton();
            if (equipActor == player && equipmentForm) {
                auto armor = equipmentForm->As<RE::TESObjectARMO>();
                if (armor && armor->HasKeywordString("zad_DeviousHeavyBondage") && equipEvent->equipped) {
                	UnequipItems(player);
                }

                RE::TESKey* magicKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(MAGIC_KEY, "Devious Curses.esp");
                RE::TESObjectMISC* tattooCharm = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectMISC>(TATTOO_CHARM, "Devious Curses.esp");
                RE::TESObjectMISC* volatileGem = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectMISC>(VOLATILE_GEM, "Devious Curses.esp");
                RE::AlchemyItem* arouaslPotion = StaticDataHolder::GetSingleton()->LookupForm<RE::AlchemyItem>(AROUSAL_POTION, "Devious Curses.esp");

                if (equipmentForm == magicKey) {
                    RemoveAllRestraints(player, true);

                    if (settings.magicKeyOppressive) {
                        RE::TESObjectARMO* summoner_collar = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(SUMMONER_COLLAR, "Devious Curses.esp");
                        RE::TESObjectARMO* latex = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LIVING_LATEX, "Devious Curses.esp");
                        RE::TESObjectARMO* latex_open = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LIVING_LATEX_OPEN, "Devious Curses.esp");
                        RE::TESObjectARMO* dwarven_cuirass = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DWARVEN_CURIAS, "Devious Curses.esp");
                        RE::TESObjectARMO* dwarven_heavy = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DWARVEN_CURIAS_HEAVY, "Devious Curses.esp");
                        RE::TESObjectARMO* madness_plug = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(MADNESS_PLUG, "Devious Curses.esp");
                        RE::TESObjectARMO* madness_piercings = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(MADNESS_PIERCINGS, "Devious Curses.esp");
                        RE::TESObjectARMO* nocturnal_piercing = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(NOCTURNAL_PIERCING, "Devious Curses.esp");

                        std::vector<RE::TESObjectARMO*> list = { summoner_collar, latex, latex_open, dwarven_cuirass, dwarven_heavy, madness_plug, nocturnal_piercing };

                        Util::ShuffleVector(list);

                        auto scriptManager = ScriptingManager();
                        for (auto device : list) {
                            if (ActorIsWearingDevice(player, device)) {
                                scriptManager.UnlockDevice(player, device, nullptr, nullptr, true, false);
                                if (device == madness_plug) {
                                    scriptManager.UnlockDevice(player, madness_piercings, nullptr, nullptr, true, false);
                                }
                                break;
                            }
                        }
                    }

                    player->RemoveItem((RE::TESBoundObject*)magicKey, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
                    PlayerMessage(Translator(Translation::ItemMagicKey));
                }
                else if (equipmentForm == tattooCharm) {
                    RemoveAllTattoos(player);

                    player->RemoveItem((RE::TESBoundObject*)tattooCharm, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
                    PlayerMessage(Translator(Translation::ItemTattooCharm));
                }
                else if (equipmentForm == arouaslPotion) {
                    ScriptingManager().ModifyArousal(player, -1000);
                    ScriptingManager().OSL_ModifyLibido(player, -settings.arousalPotionLibido);

                    PlayerMessage(Translator(Translation::ItemArousalPotion));
                }
                else if (equipmentForm == volatileGem) {
                    player->RemoveItem((RE::TESBoundObject*)volatileGem, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
                    ScriptingManager().RunOnMenuClose([player] {
                        Util::ExecuteWithDelay(10ms, [player] {
                            RE::Explosion* explosion = StaticDataHolder::GetSingleton()->LookupForm<RE::Explosion>(0xD13E8, "Skyrim.esm");
                            player->PlaceObjectAtMe((RE::TESBoundObject*)explosion, false);
                            player->SetGraphVariableFloat("StaggerMagnitude", 0.5f);
                            player->NotifyAnimationGraph("staggerStart");
                        });
                        Util::ExecuteWithDelay(500ms, [] {
                            OppLatexMagicEvent();
                        });
                    });
                }
            }
            return RE::BSEventNotifyControl::kContinue;
        }

    public:
        static void RegisterEvent() {
            static EquipEventSink eventSink;
            auto ScriptEventSource = RE::ScriptEventSourceHolder::GetSingleton();
            if (!ScriptEventSource) {
                return;
            }
            ScriptEventSource->AddEventSink(&eventSink);
        }
    };

    class MGEFEventSink : public RE::BSTEventSink<RE::TESMagicEffectApplyEvent>
    {
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESMagicEffectApplyEvent* magicEvent, RE::BSTEventSource<RE::TESMagicEffectApplyEvent>*) override {
            if (magicEvent) {
                OppDeviceOnMagicHitEvent(magicEvent);
                TatsOnMagicHitEvent(magicEvent);
            }
            return RE::BSEventNotifyControl::kContinue;
        }

    public:
        static void RegisterEvent() {
            static MGEFEventSink eventSink;
            auto ScriptEventSource = RE::ScriptEventSourceHolder::GetSingleton();
            if (!ScriptEventSource) {
                return;
            }
            ScriptEventSource->AddEventSink(&eventSink);
        }
    };

    class SpellEventSink : public RE::BSTEventSink<RE::TESSpellCastEvent>
    {
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESSpellCastEvent* spellEvent, RE::BSTEventSource<RE::TESSpellCastEvent>*) override {
            TatsOnSpellCast(spellEvent);
            QIOnSpellCast(spellEvent);

            auto player = RE::PlayerCharacter::GetSingleton();
            auto actor = spellEvent->object->As<RE::Actor>();
            if (actor && actor == player) {
                OppNocturnalTryRecast();
            }

            return RE::BSEventNotifyControl::kContinue;
        }

    public:
        static void RegisterEvent() {
            static SpellEventSink eventSink;
            auto ScriptEventSource = RE::ScriptEventSourceHolder::GetSingleton();
            if (!ScriptEventSource) {
                return;
            }
            ScriptEventSource->AddEventSink(&eventSink);
        }
    };

    class HitEventSink : public RE::BSTEventSink<RE::TESHitEvent>
    {
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESHitEvent* hitEvent, RE::BSTEventSource<RE::TESHitEvent>*) override {
            auto cause = hitEvent->cause.get();
            if (cause && cause == RE::PlayerCharacter::GetSingleton()) {
                auto target = hitEvent->target.get();
                //log::trace("player hit {} ({})", target->GetName(), Util::GetFormEditorId(target));
                /*Util::ExecuteWithDelay(10ms, [target] {
                    target->Disable();
                    target->SetDelete(true);
                });*/

                RE::TESObjectMISC* volatileGem = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectMISC>(VOLATILE_GEM, "Devious Curses.esp");
                if (target->GetBaseObject() == volatileGem && target->GetPosition().GetDistance(cause->GetPosition()) <= 200) {
                    Util::ExecuteWithDelay(10ms, [target] {
                        RE::Explosion* explosion = StaticDataHolder::GetSingleton()->LookupForm<RE::Explosion>(0xD13E8, "Skyrim.esm");
                        target->PlaceObjectAtMe((RE::TESBoundObject*)explosion, false);
                        target->Disable();
                        target->SetDelete(true);
                    });
                    Util::ExecuteWithDelay(1s, [] {
                        OppLatexMagicEvent();
                    });
                }

                OppNocturnalTryRecast();
            }

            return RE::BSEventNotifyControl::kContinue;
        }

    public:
        static void RegisterEvent() {
            static HitEventSink eventSink;
            auto ScriptEventSource = RE::ScriptEventSourceHolder::GetSingleton();
            if (!ScriptEventSource) {
                return;
            }
            ScriptEventSource->AddEventSink(&eventSink);
        }
    };

    typedef RE::InputEvent* InputEventPTR;

    class InputEventSink : public RE::BSTEventSink<InputEventPTR>
    {
        virtual RE::BSEventNotifyControl ProcessEvent(const InputEventPTR* inputEventPtr, RE::BSTEventSource<InputEventPTR>*) override {
            if (RE::UI::GetSingleton()->GameIsPaused()) {
                return RE::BSEventNotifyControl::kContinue;
            }

            if (auto inputEvent = *inputEventPtr) {
                if (auto buttonEvent = inputEvent->AsButtonEvent()) {
                    auto device = static_cast<std::underlying_type_t<RE::INPUT_DEVICE>>(buttonEvent->GetDevice());
                    if (buttonEvent->IsDown() && (device == 0 || device == 3 || device == 9)) {
                        auto idCode = static_cast<int>(buttonEvent->GetIDCode());

                        if (idCode <= 0) {
                            return RE::BSEventNotifyControl::kContinue;
                        }
                        else if (idCode == 55 && settings.debugMode) {
                            Debug::Test();
                        }
                        else if (idCode == settings.setDebugKey) {
                            ScriptingManager().OpenDebugMenu();
                        }
                    }
                }
            }

            return RE::BSEventNotifyControl::kContinue;
        }

    public:
        static void RegisterEvent() {
            static InputEventSink eventSink;
            auto InputEventSource = RE::BSInputDeviceManager::GetSingleton();
            if (!InputEventSource) {
                return;
            }
            InputEventSource->AddEventSink(&eventSink);
        }
    };

    class ModEventSink : public RE::BSTEventSink<SKSE::ModCallbackEvent>
    {
        virtual RE::BSEventNotifyControl ProcessEvent(const SKSE::ModCallbackEvent* modEvent, RE::BSTEventSource<SKSE::ModCallbackEvent>*) override {
            std::string name = Util::trim(Util::tolower(std::string(modEvent->eventName)));
            std::string strArg = Util::trim(Util::tolower(std::string(modEvent->strArg)));
            int numArg = static_cast<int>(modEvent->numArg);
            auto player = RE::PlayerCharacter::GetSingleton();

            if (name._Starts_with("dcurses_")) {
                log::trace("Received Mod Event {}: {}, '{}'", name, numArg, strArg);
                auto event = Util::trim(name.substr(8));
                if (event == "doevent") {
                    auto argParts = Util::split(strArg, "~");
                    if (argParts.size() > 2) {
                        log::warn("Received bad theme {}. Should only have one ~", strArg);
                        return RE::BSEventNotifyControl::kContinue;
                    }

                    auto arg = Util::trim(argParts[0]);
                    log::trace("arg: {}", arg);
                    auto theme = argParts.size() >= 2 ? argParts[1] : "";
                    log::trace("theme: {}", theme);

                    if (arg == "bondage") {
                        if (DoStandardEvent(player, false, "", theme, numArg)) {
                            log::info("Running Bondage Event: theme: {}, count: {}", theme, numArg);
                        }
                        else {
                            log::warn("Unable to run Bondage event: too many devices equipped or too restrictive exclusions.");
                        }
                    }
                    else if (arg == "oppressive") {
                        if (!DoOppDeviceEvent("")) {
                            log::warn("Unable to run Oppressive Event");
                        }
                    }
                    else if (arg == "contraption") {
                        if (!DoContraptionEvent("", player, theme)) {
                            log::warn("Unable to run Contraption Event");
                        }
                    }
                    else if (arg == "tattoo") {
                        if (!DoTattooEvent(player, "", numArg)) {
                            log::warn("Unable to run Tattoo event");
                        }
                    }
                    else if (arg == "mark") {
                        if (!DoLewdMarkEvent("")) {
                            log::warn("Unable to run Mark event, player already has mark.");
                        }
                    }
                    else if (arg.empty()) {
                        if (!DoEvent(false, "")) {
                            log::warn("Unable to run Event. Player has all weights set to 0.");
                        }
                    }
                    else {
                        log::warn("Bad ModEvent strArg: {}", strArg);
                        return RE::BSEventNotifyControl::kContinue;
                    }
                }
                else if (event == "setlewdmark") {
                    MARK mark = MARK::TAT_NONE;
                    uint32_t effect = 0;
                    int32_t* assign = nullptr;
                    if (strArg == "heat") {
                        mark = MARK::TAT_HEAT;
                        effect = HEAT_EFFECT;
                        assign = &lewdMarkCounters.heatCounter;
                    }
                    else if (strArg == "allure") {
                        mark = MARK::TAT_ALLURE;
                        effect = ALLURE_EFFECT;
                        assign = &lewdMarkCounters.allureCounter;
                    }
                    else if (strArg == "bondage") {
                        mark = MARK::TAT_BONDAGE;
                        effect = BONDAGE_EFFECT;
                        assign = &lewdMarkCounters.bondageCounter;
                    }
                    else if (strArg == "branding") {
                        mark = MARK::TAT_BRANDING;
                        effect = BRANDING_EFFECT;
                    }
                    else if (strArg == "healslut") {
                        mark = MARK::TAT_HEALSLUT;
                        effect = HEALSLUT_EFFECT;
                        assign = &lewdMarkCounters.healslutCounter;
                    }
                    else if (strArg == "nudity") {
                        mark = MARK::TAT_NUDITY;
                        effect = NUDITY_EFFECT;
                        assign = &lewdMarkCounters.nudityCounter;
                    }
                    else if (strArg != "none") {
                        log::warn("Bad ModEvent strArg: {}", strArg);
                        return RE::BSEventNotifyControl::kContinue;
                    }

                    auto oldMark = GetLewdMark();
                    if (oldMark != mark) {
                        RemoveLewdMark();
                        if (mark != MARK::TAT_NONE) {
                            AddLewdMark(mark);
                            SetMarkToDefaultSettings(mark);
                        }
                    }

                    if (numArg > 0 && assign != nullptr) {
                        log::info("Updating lewd mark to {} ({})", strArg, numArg);
                        *assign = numArg;
                        SetEffectMagnitude(effect, static_cast<float>(numArg));
                    }
                    else {
                        log::info("Updating lewd mark to {}", strArg);
                    }
                }
                else if (event == "equipoppressivedevice") {
                    if (strArg == "summonercollar") {
                        if (OppSummonerCollarEvent("")) {
                            log::info("Equipping player with Summoner Collar");
                        }
                        else {
                            log::warn("Unable to equip player with Summoner Collar");
                        }
                    }
                    else if (strArg == "dwarvencuirass") {
                        if (OppDwarvenCuirassEvent("", true)) {
                            log::info("Equipping player with Dwarven Cuirass");
                        }
                        else {
                            log::warn("Unable to equip player with Dwarven Cuirass");
                        }
                    }
                    else if (strArg == "livinglatex") {
                        if (OppLivingLatexEvent("")) {
                            log::info("Equipping player with Living Latex");
                        }
                        else {
                            log::warn("Unable to equip player with Living Latex");
                        }
                    }
                    else if (strArg == "madnessplug") {
                        if (OppMadnessPlugEvent("")) {
                            log::info("Equipping player with Madness Plug");
                        }
                        else {
                            log::warn("Unable to equip player with Madness Plug");
                        }
                    }
                    else if (strArg == "nocturnalpiercing") {
                        if (OppNocturnalPiercingEvent("")) {
                            log::info("Equipping player with Nocturnal Piercing");
                        }
                        else {
                            log::warn("Unable to equip player with Nocturnal Piercing");
                        }
                    }
                    else {
                        log::warn("Bad ModEvent strArg: {}", strArg);
                        return RE::BSEventNotifyControl::kContinue;
                    }
                }
                else if (event == "removeallrestraints") {
                    RemoveAllRestraints(player);
                }
                else if (event == "removealloppressive") {
                    RE::TESObjectARMO* summoner_collar = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(SUMMONER_COLLAR, "Devious Curses.esp");
                    RE::TESObjectARMO* latex = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LIVING_LATEX, "Devious Curses.esp");
                    RE::TESObjectARMO* latex_open = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LIVING_LATEX_OPEN, "Devious Curses.esp");
                    RE::TESObjectARMO* dwarven_cuirass = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DWARVEN_CURIAS, "Devious Curses.esp");
                    RE::TESObjectARMO* dwarven_heavy = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DWARVEN_CURIAS_HEAVY, "Devious Curses.esp");
                    RE::TESObjectARMO* madness_plug = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(MADNESS_PLUG, "Devious Curses.esp");
                    RE::TESObjectARMO* madness_piercings = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(MADNESS_PIERCINGS, "Devious Curses.esp");
                    RE::TESObjectARMO* nocturnal_piercing = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(NOCTURNAL_PIERCING, "Devious Curses.esp");
                    
                    auto scriptManager = ScriptingManager();
                    scriptManager.UnlockDevice(player, summoner_collar, nullptr, nullptr, true, false);
                    scriptManager.UnlockDevice(player, latex, nullptr, nullptr, true, false);
                    scriptManager.UnlockDevice(player, latex_open, nullptr, nullptr, true, false);
                    scriptManager.UnlockDevice(player, dwarven_cuirass, nullptr, nullptr, true, false);
                    scriptManager.UnlockDevice(player, dwarven_heavy, nullptr, nullptr, true, false);
                    scriptManager.UnlockDevice(player, madness_plug, nullptr, nullptr, true, false);
                    scriptManager.UnlockDevice(player, madness_piercings, nullptr, nullptr, true, false);
                    scriptManager.UnlockDevice(player, nocturnal_piercing, nullptr, nullptr, true, false);
                }
                else {
                    log::warn("Received bad ModEvent name {}", name);
                }
            }
            return RE::BSEventNotifyControl::kContinue;
        }

    public:
        static void RegisterEvent() {
            static ModEventSink eventSink;
            SKSE::GetModCallbackEventSource()->AddEventSink(&eventSink);
        }
    };

    void RegisterEventSinks() {
        log::trace("Attaching Event Sinks");
        ActivateEventSink::RegisterEvent();
        ContainerChangedEventSink::RegisterEvent();
        EquipEventSink::RegisterEvent();
        QuestStageEventSink::RegisterEvent();
        MGEFEventSink::RegisterEvent();
        SpellEventSink::RegisterEvent();
        HitEventSink::RegisterEvent();
        InputEventSink::RegisterEvent();
        ModEventSink::RegisterEvent();
    }
}