#pragma once

namespace DCURSES {

    class QuestStageEventSink : public RE::BSTEventSink<RE::TESQuestStageEvent> {
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESQuestStageEvent* questEvent, RE::BSTEventSource<RE::TESQuestStageEvent>*) override;
    public:
        static void RegisterEvent();
    };

    class ActivateEventSink : public RE::BSTEventSink<RE::TESActivateEvent> {
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESActivateEvent* activateEvent, RE::BSTEventSource<RE::TESActivateEvent>*) override;
    public:
        static void RegisterEvent();
    };

    class ContainerChangedEventSink : public RE::BSTEventSink<RE::TESContainerChangedEvent> {
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESContainerChangedEvent* containerEvent, RE::BSTEventSource<RE::TESContainerChangedEvent>*) override;
    public:
        static void RegisterEvent();
    };

    class EquipEventSink : public RE::BSTEventSink<RE::TESEquipEvent>
    {
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESEquipEvent* equipEvent, RE::BSTEventSource<RE::TESEquipEvent>*) override;

    public:
        static void RegisterEvent();
    };

    class MGEFEventSink : public RE::BSTEventSink<RE::TESMagicEffectApplyEvent>
    {
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESMagicEffectApplyEvent* magicEvent, RE::BSTEventSource<RE::TESMagicEffectApplyEvent>*) override;

    public:
        static void RegisterEvent();
    };

    class SpellEventSink : public RE::BSTEventSink<RE::TESSpellCastEvent>
    {
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESSpellCastEvent* spellEvent, RE::BSTEventSource<RE::TESSpellCastEvent>*) override;

    public:
        static void RegisterEvent();
    };

    class HitEventSink : public RE::BSTEventSink<RE::TESHitEvent>
    {
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESHitEvent* hitEvent, RE::BSTEventSource<RE::TESHitEvent>*) override;

    public:
        static void RegisterEvent();
    };

    class DeathEventSink : public RE::BSTEventSink<RE::TESDeathEvent>
    {
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESDeathEvent* hitEvent, RE::BSTEventSource<RE::TESDeathEvent>*) override;

    public:
        static void RegisterEvent();
    };

    typedef RE::InputEvent* InputEventPTR;

    class InputEventSink : public RE::BSTEventSink<InputEventPTR>
    {
        virtual RE::BSEventNotifyControl ProcessEvent(const InputEventPTR* inputEventPtr, RE::BSTEventSource<InputEventPTR>*) override;

    public:
        static void RegisterEvent();
    };

    class ModEventSink : public RE::BSTEventSink<SKSE::ModCallbackEvent>
    {
        virtual RE::BSEventNotifyControl ProcessEvent(const SKSE::ModCallbackEvent* modEvent, RE::BSTEventSource<SKSE::ModCallbackEvent>*) override;

    public:
        static void RegisterEvent();
    };

    void RegisterEventSinks();
}