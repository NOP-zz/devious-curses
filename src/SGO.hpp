#pragma once

#include "Scripting.hpp"

namespace DCURSES {
    void SGOInseminate(RE::TESForm* whom, float loadSize, RE::TESForm* donor, int id) {
        RE::TESForm* quest = RE::TESDataHandler::GetSingleton()->LookupForm(0xD61, "Sgo4IF.esp");
        auto handle = GetHP()->GetHandleForObject(RE::FormType::Quest, quest);
        RE::BSTSmartPointer<RE::BSScript::Object> questObject;
        GetVM()->FindBoundObject(handle, "dse_sgo_QuestController_Main", questObject);

        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        GetVM()->DispatchMethodCall(questObject, "InseminateActor", RE::MakeFunctionArguments<RE::TESForm*, float, RE::TESForm*, int>(std::move(whom), std::move(loadSize), std::move(donor), std::move(id)), callback);
    }

    void SGOActorUpdate(RE::Actor* whom, bool force = false) {
        RE::TESForm* quest = RE::TESDataHandler::GetSingleton()->LookupForm(0x22ed, "Sgo4IF.esp");
        auto handle = GetHP()->GetHandleForObject(RE::FormType::Quest, quest);
        RE::BSTSmartPointer<RE::BSScript::Object> questObject;
        GetVM()->FindBoundObject(handle, "dse_sgo_QuestBody_Main", questObject);

        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        GetVM()->DispatchMethodCall(questObject, "ActorUpdate", RE::MakeFunctionArguments<RE::Actor*, bool>(std::move(whom), std::move(force)), callback);
    }

    void SGOActorGemAdd(RE::Actor* whom, float value = 0.0) {
        RE::TESForm* quest = RE::TESDataHandler::GetSingleton()->LookupForm(0x182a, "Sgo4IF.esp");
        auto handle = GetHP()->GetHandleForObject(RE::FormType::Quest, quest);
        RE::BSTSmartPointer<RE::BSScript::Object> questObject;
        GetVM()->FindBoundObject(handle, "dse_sgo_QuestDatabase_Main", questObject);

        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        GetVM()->DispatchMethodCall(questObject, "ActorGemAdd", RE::MakeFunctionArguments<RE::Actor*, float, int>(std::move(whom), std::move(value), std::move(0)), callback);
    }

    void SGOApplyGemOverrides(RE::Actor* whom, RE::Actor* from = nullptr, int id = -1, int outputMap0 = -1, int outputMap1 = -1) {
        RE::TESForm* quest = RE::TESDataHandler::GetSingleton()->LookupForm(0x182a, "Sgo4IF.esp");
        auto handle = GetHP()->GetHandleForObject(RE::FormType::Quest, quest);
        RE::BSTSmartPointer<RE::BSScript::Object> questObject;
        GetVM()->FindBoundObject(handle, "dse_sgo_QuestDatabase_Main", questObject);

        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        GetVM()->DispatchMethodCall(questObject, "ApplyGemOverrides", RE::MakeFunctionArguments<RE::Actor*, RE::Actor*, int, int, int>(std::move(whom), std::move(from), std::move(id), std::move(outputMap0), std::move(outputMap1)), callback);
    }

    bool DoSGOGemEvent(std::string contName) {
        auto player = RE::PlayerCharacter::GetSingleton();
        auto factionProduceGems = RE::TESDataHandler::GetSingleton()->LookupForm(0x48c2, "dse-soulgem-oven.esp")->As<RE::TESFaction>();
        if (player->GetActorBase()->GetSex() != RE::SEX::kFemale) { return false; }

        SGOInseminate(player, 10000, nullptr, 15);

        SGOActorUpdate(player);
        return true;
    }

    bool DoSGOEvent(std::string contName) {
        if (!RE::TESDataHandler::GetSingleton()->LookupModByName("Sgo4IF.esp")) {
            return false;
        }

        //auto player = RE::PlayerCharacter::GetSingleton();
        /*
        int weightTotal = settings.SGOInseminationWeight;

        int r = Util::randomInt(weightTotal);

        if (r < settings.SGOInseminationWeight && DoSGOGemEvent(contName)) {
            return true;
        }
        else if (r > settings.SGOInseminationWeight) {
            r -= settings.SGOInseminationWeight;
        }
        */
        return false;
    }
}