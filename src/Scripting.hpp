#pragma once

#include "../include/form_ids.h"


using namespace SKSE;

namespace DCURSES {

    RE::BSScript::IVirtualMachine* GetVM() {
        return RE::BSScript::Internal::VirtualMachine::GetSingleton();
    }

    RE::BSScript::IObjectHandlePolicy* GetHP() {
        auto vm = GetVM();
        return vm->GetObjectHandlePolicy();
    }

    bool CheckESPLoaded() {
        RE::TESForm* form = RE::TESDataHandler::GetSingleton()->LookupForm(DCURSES_MCM, "Devious Curses.esp");
        if (form == nullptr) {
            return false;
        }
        return true;
    }

    RE::BSScript::Variable* GetMCMSetting(std::string name) {
        
        RE::TESForm* form = RE::TESDataHandler::GetSingleton()->LookupForm(DCURSES_MCM, "Devious Curses.esp");
        auto handle = GetHP()->GetHandleForObject(RE::FormType::Quest, form);
        RE::BSTSmartPointer<RE::BSScript::Object> mcmObject;
        GetVM()->FindBoundObject(handle, "DCurses_MCM", mcmObject);

        RE::BSScript::Variable* variable = mcmObject->GetProperty(name);
        if (!variable) {
            log::error("MCM setting {} not found. Do you need to build papyrus?", name);
            return nullptr;
        }
        return variable;
    }

    void SetMCMSetting(std::string name, RE::BSScript::Variable& value) {

        RE::TESForm* form = RE::TESDataHandler::GetSingleton()->LookupForm(DCURSES_MCM, "Devious Curses.esp");
        auto handle = GetHP()->GetHandleForObject(RE::FormType::Quest, form);
        RE::BSTSmartPointer<RE::BSScript::Object> mcmObject;
        GetVM()->FindBoundObject(handle, "DCurses_MCM", mcmObject);
        
        GetVM()->SetPropertyValue(mcmObject, name.c_str(), value);
    }

    void SetMCMInt(std::string name, int value) {
        RE::BSScript::Variable var;
        var.SetSInt(value);
        SetMCMSetting(name, var);
    }

    void SetMCMFloat(std::string name, float value) {
        RE::BSScript::Variable var;
        var.SetFloat(value);
        SetMCMSetting(name, var);
    }

    void SetMCMBool(std::string name, bool value) {
        RE::BSScript::Variable var;
        var.SetBool(value);
        SetMCMSetting(name, var);
    }

    void SetMCMString(std::string name, std::string value) {
        RE::BSScript::Variable var;
        var.SetString(value);
        SetMCMSetting(name, var);
    }

    int GetActorArousal(RE::Actor* actor) {
        auto faction = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("03fc36", 0, 16), "SexLabAroused.esm");
        return actor->GetFactionRank(faction, actor == RE::PlayerCharacter::GetSingleton());
    }

    void StartPapyrusTimer() {
        RE::TESForm* mcm = RE::TESDataHandler::GetSingleton()->LookupForm(DCURSES_MCM, "Devious Curses.esp");
        auto handle = GetHP()->GetHandleForObject(RE::FormType::Quest, mcm);
        RE::BSTSmartPointer<RE::BSScript::Object> mcmObject;
        GetVM()->FindBoundObject(handle, "DCurses_MCM", mcmObject);

        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        GetVM()->DispatchMethodCall(mcmObject, "OnGameStarted", new RE::BSScript::ZeroFunctionArguments, callback);
    }

    void StartSex(RE::Actor* aggressor) {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        GetVM()->DispatchStaticCall("DCursesLib", "StartSex", RE::MakeFunctionArguments<RE::Actor*>(std::move(aggressor)), result);
    }

    void SlowStrip(RE::Actor* actor) {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        GetVM()->DispatchStaticCall("DCursesLib", "SlowStrip", RE::MakeFunctionArguments<RE::Actor*>(std::move(actor)), result);
    }

    void SendModEventDevices(RE::Actor* who, int device_count, std::string devices, std::string device_ids) {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        GetVM()->DispatchStaticCall("DCursesLib", "SendModEventDevices", RE::MakeFunctionArguments<RE::Actor*, int, std::string, std::string>(std::move(who), std::move(device_count), std::move(devices), std::move(device_ids)), result);
    }

    void SendModEventMark(RE::Actor* who, std::string mark_name, int mark_id) {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        GetVM()->DispatchStaticCall("DCursesLib", "SendModEventMark", RE::MakeFunctionArguments<RE::Actor*, std::string, int>(std::move(who), std::move(mark_name), std::move(mark_id)), result);
    }

    void SendModEventTattoo(RE::Actor* who, int tattoo_count) {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        GetVM()->DispatchStaticCall("DCursesLib", "SendModEventTattoo", RE::MakeFunctionArguments<RE::Actor*, int>(std::move(who), std::move(tattoo_count)), result);
    }

    void SetArousal(RE::Actor* actor, int arousal) {
        RE::TESForm* aroused = RE::TESDataHandler::GetSingleton()->LookupForm(0x4290f, "SexLabAroused.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, aroused);
        RE::BSTSmartPointer<RE::BSScript::Object> arousedObject;
        GetVM()->FindBoundObject(hand, "slaFrameworkScr", arousedObject);

        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        GetVM()->DispatchMethodCall(arousedObject, "SetActorExposure", RE::MakeFunctionArguments<RE::Actor*, int>(std::move(actor), std::move(arousal)), result);
    }

    void ModifyArousal(RE::Actor* actor, int arousal) {
        RE::TESForm* aroused = RE::TESDataHandler::GetSingleton()->LookupForm(0x4290f, "SexLabAroused.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, aroused);
        RE::BSTSmartPointer<RE::BSScript::Object> arousedObject;
        GetVM()->FindBoundObject(hand, "slaFrameworkScr", arousedObject);

        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        GetVM()->DispatchMethodCall(arousedObject, "UpdateActorExposure", RE::MakeFunctionArguments<RE::Actor*, int, std::string>(std::move(actor), std::move(arousal), std::move("")), result);
    }

    void LockDevice(RE::Actor* akActor, RE::TESObjectARMO* deviceInventory, bool force = false) {
        RE::TESForm* libs = RE::TESDataHandler::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, libs);
        RE::BSTSmartPointer<RE::BSScript::Object> zadlibsObject;
        GetVM()->FindBoundObject(hand, "zadLibs", zadlibsObject);

        if (akActor == nullptr || deviceInventory == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        GetVM()->DispatchMethodCall(zadlibsObject, "LockDevice", RE::MakeFunctionArguments<RE::Actor*, RE::TESObjectARMO*, bool>(std::move(akActor), std::move(deviceInventory), std::move(force)), callback);
    }

    void UnlockDevice(RE::Actor* akActor, RE::TESObjectARMO* deviceInventory, RE::TESObjectARMO* deviceRendered = nullptr, RE::BGSKeyword* zad_DeviousDevice = nullptr, bool destroyDevice = false, bool genericonly = true) {
        RE::TESForm* libs = RE::TESDataHandler::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, libs);
        RE::BSTSmartPointer<RE::BSScript::Object> zadlibsObject;
        GetVM()->FindBoundObject(hand, "zadLibs", zadlibsObject);

        if (akActor == nullptr || deviceInventory == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        GetVM()->DispatchMethodCall(zadlibsObject, "UnlockDevice", RE::MakeFunctionArguments<RE::Actor*, RE::TESObjectARMO*, RE::TESObjectARMO*, RE::BGSKeyword*, bool, bool>(std::move(akActor), std::move(deviceInventory), std::move(deviceRendered), std::move(zad_DeviousDevice), std::move(destroyDevice), std::move(genericonly)), callback);
    }

    void RemoveQuestDevice(RE::Actor* akActor, RE::TESObjectARMO* deviceInventory, RE::TESObjectARMO* deviceRendered, bool destroyDevice = false) {
        auto removalToken = RE::TESForm::LookupByEditorID("DCurses_QuestItem")->As<RE::BGSKeyword>();
        RE::TESForm* libs = RE::TESDataHandler::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, libs);
        RE::BSTSmartPointer<RE::BSScript::Object> zadlibsObject;
        GetVM()->FindBoundObject(hand, "zadLibs", zadlibsObject);

        if (akActor == nullptr || deviceInventory == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        GetVM()->DispatchMethodCall(zadlibsObject, "RemoveQuestDevice", RE::MakeFunctionArguments<RE::Actor*, RE::TESObjectARMO*, RE::TESObjectARMO*, RE::BGSKeyword*, RE::BGSKeyword*, bool, bool>(std::move(akActor), std::move(deviceInventory), std::move(deviceRendered), std::move(nullptr), std::move(removalToken), std::move(destroyDevice), std::move(false)), callback);
    }

    void SwapDevices(RE::Actor* akActor, RE::TESObjectARMO* deviceInventory, RE::BGSKeyword* zad_DeviousDevice = nullptr, bool destroyDevice = false, bool genericonly = true) {
        RE::TESForm* libs = RE::TESDataHandler::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, libs);
        RE::BSTSmartPointer<RE::BSScript::Object> zadlibsObject;
        GetVM()->FindBoundObject(hand, "zadLibs", zadlibsObject);

        if (akActor == nullptr || deviceInventory == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        GetVM()->DispatchMethodCall(zadlibsObject, "SwapDevices", RE::MakeFunctionArguments<RE::Actor*, RE::TESObjectARMO*, RE::BGSKeyword*, bool, bool>(std::move(akActor), std::move(deviceInventory), std::move(zad_DeviousDevice), std::move(destroyDevice), std::move(genericonly)), callback);
    }

    void VibrateEffect(RE::Actor* akActor, int vibStrength, int duration, bool teaseOnly = false, bool silent = false) {
        RE::TESForm* libs = RE::TESDataHandler::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, libs);
        RE::BSTSmartPointer<RE::BSScript::Object> zadlibsObject;
        GetVM()->FindBoundObject(hand, "zadLibs", zadlibsObject);

        if (akActor == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        GetVM()->DispatchMethodCall(zadlibsObject, "VibrateEffect", RE::MakeFunctionArguments<RE::Actor*, int, int, bool, bool>(std::move(akActor), std::move(vibStrength), std::move(duration), std::move(teaseOnly), std::move(silent)), callback);
    }

    void ShockActor(RE::Actor* akActor) {
        RE::TESForm* libs = RE::TESDataHandler::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, libs);
        RE::BSTSmartPointer<RE::BSScript::Object> zadlibsObject;
        GetVM()->FindBoundObject(hand, "zadLibs", zadlibsObject);

        if (akActor == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        GetVM()->DispatchMethodCall(zadlibsObject, "ShockActor", RE::MakeFunctionArguments<RE::Actor*>(std::move(akActor)), callback);
    }

    void UnequipItem(RE::Actor* akActor, RE::TESForm* item) {

        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::ActorCharacter, akActor);
        RE::BSTSmartPointer<RE::BSScript::Object> obj;
        GetVM()->FindBoundObject(hand, "Actor", obj);
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        GetVM()->DispatchMethodCall(obj, "UnequipItem", RE::MakeFunctionArguments<RE::TESForm*, bool, bool>(std::move(item), std::move(false), std::move(true)), callback);
    }

    void UnequipSpell(RE::Actor* akActor, RE::TESForm* spell, int akSource) {

        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::ActorCharacter, akActor);
        RE::BSTSmartPointer<RE::BSScript::Object> obj;
        GetVM()->FindBoundObject(hand, "Actor", obj);
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        GetVM()->DispatchMethodCall(obj, "UnequipSpell", RE::MakeFunctionArguments<RE::TESForm*, int>(std::move(spell), std::move(akSource)), callback);
    }

    void UpdateArousal(RE::Actor* akActor) {
        RE::BSTSmartPointer<RE::BSScript::Object> slaObject;
        RE::TESForm* sla = RE::TESDataHandler::GetSingleton()->LookupForm(std::stoi("4290f", 0, 16), "SexLabAroused.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, sla);
        GetVM()->FindBoundObject(hand, "slaFrameworkScr", slaObject);

        if (akActor == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        GetVM()->DispatchMethodCall(slaObject, "GetActorArousal", RE::MakeFunctionArguments<RE::Actor*>(std::move(akActor)), callback);
    }

    void DoTattooEvent(RE::Actor* akActor, int count) {
        RE::BSTSmartPointer<RE::BSScript::Object> rapeTatsObject;
        RE::TESForm* sla = RE::TESDataHandler::GetSingleton()->LookupForm(std::stoi("d62", 0, 16), "RapeTattoos.esp");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, sla);
        GetVM()->FindBoundObject(hand, "rapeTattoos", rapeTatsObject);

        if (akActor == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        GetVM()->DispatchMethodCall(rapeTatsObject, "addTattooEventV2", RE::MakeFunctionArguments<RE::Actor*, int>(std::move(akActor), std::move(count)), callback);
    }

    void ForceThirdPerson() {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        GetVM()->DispatchStaticCall("Game", "ForceThirdPerson", new RE::BSScript::ZeroFunctionArguments, result);
    }

    void DisableMenus() {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        GetVM()->DispatchStaticCall("Game", "DisablePlayerControls", RE::MakeFunctionArguments<bool, bool, bool, bool, bool, bool, bool, bool, int>(std::move(false), std::move(false), std::move(false), std::move(false), std::move(false), std::move(true), std::move(true), std::move(false), std::move(0)), result);
    }

    void EnableMenus() {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        GetVM()->DispatchStaticCall("Game", "EnablePlayerControls", RE::MakeFunctionArguments<bool, bool, bool, bool, bool, bool, bool, bool, int>(std::move(false), std::move(false), std::move(false), std::move(false), std::move(false), std::move(true), std::move(true), std::move(false), std::move(0)), result);
    }

    void CloseContinerMenus() {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        GetVM()->DispatchStaticCall("UI", "InvokeString", RE::MakeFunctionArguments<std::string, std::string, std::string>("HUD Menu", "_global.skse.CloseMenu", "InventoryMenu"), result);
        GetVM()->DispatchStaticCall("UI", "InvokeString", RE::MakeFunctionArguments<std::string, std::string, std::string>("HUD Menu", "_global.skse.CloseMenu", "ContainerMenu"), result);
        GetVM()->DispatchStaticCall("UI", "InvokeString", RE::MakeFunctionArguments<std::string, std::string, std::string>("HUD Menu", "_global.skse.CloseMenu", "Lockpicking Menu"), result); 
    }

    void DBGMessageBox(std::string message) {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        GetVM()->DispatchStaticCall("Debug", "MessageBox", RE::MakeFunctionArguments<std::string>(std::move(message)), result);
    }

    void DBGNotification(std::string message) {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        GetVM()->DispatchStaticCall("Debug", "Notification", RE::MakeFunctionArguments<std::string>(std::move(message)), result);
    }
}