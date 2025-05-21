#pragma once

#include "../include/form_ids.h"
#include "../include/DDNG_API.h"

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

    bool CheckRapeTattoos() {
        RE::TESForm* form = StaticDataHolder::GetSingleton()->LookupForm(0xd62, "RapeTattoos.esp");
        if (form == nullptr) {
            return false;
        }
        return true;
    }

    bool CheckUD() {
        RE::TESForm* form = StaticDataHolder::GetSingleton()->LookupForm(0x5901, "UnforgivingDevices.esp");
        if (form == nullptr) {
            return false;
        }
        return true;
    }

    bool CheckSimpleSlavery() {
        RE::TESForm* form = StaticDataHolder::GetSingleton()->LookupForm(0x492e, "SimpleSlavery.esp");
        if (form == nullptr) {
            return false;
        }
        return true;
    }

    RE::BSScript::Variable* GetMCMSetting(std::string name) {
        
        RE::TESForm* form = StaticDataHolder::GetSingleton()->LookupForm(DCURSES_MCM, "Devious Curses.esp");
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

    bool IsModDisabled() {
        auto v = GetMCMSetting("ModSuspended");
        if (v && v->IsBool()) {
            return v->GetBool();
        }
        return false;
    }

    void SetMCMSetting(std::string name, RE::BSScript::Variable& value) {

        RE::TESForm* form = StaticDataHolder::GetSingleton()->LookupForm(DCURSES_MCM, "Devious Curses.esp");
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

    void StartMCMTimer() {
        RE::TESForm* form = StaticDataHolder::GetSingleton()->LookupForm(DCURSES_MCM, "Devious Curses.esp");
        auto handle = GetHP()->GetHandleForObject(RE::FormType::Quest, form);
        RE::BSTSmartPointer<RE::BSScript::Object> mcmObject;
        GetVM()->FindBoundObject(handle, "DCurses_MCM", mcmObject);

        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        RE::BSScript::IFunctionArguments* args = new RE::BSScript::ZeroFunctionArguments;
        GetVM()->DispatchMethodCall(mcmObject, "StartTimer", args, callback);
        delete args;
    }

    int GetActorArousal(RE::Actor* actor) {
        auto faction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x03fc36, "SexLabAroused.esm");
        return actor->GetFactionRank(faction, actor == RE::PlayerCharacter::GetSingleton());
    }

    void StartSex(RE::Actor* aggressor) {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*>(std::move(aggressor));
        GetVM()->DispatchStaticCall("DCursesLib", "StartSex", args, result);
        delete args;
    }

    void SlowStrip(RE::Actor* actor) {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*>(std::move(actor));
        GetVM()->DispatchStaticCall("DCursesLib", "SlowStrip", args, result);
        delete args;
    }

    void SendModEventDevices(RE::Actor* who, std::string what, int device_count, std::string devices, std::string device_ids) {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, std::string, int, std::string, std::string>(std::move(who), std::move(what), std::move(device_count), std::move(devices), std::move(device_ids));
        GetVM()->DispatchStaticCall("DCursesLib", "SendModEventDevices", args, result);
        delete args;
    }

    void SendModEventMark(RE::Actor* who, std::string what, std::string mark_name, int mark_id) {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, std::string, std::string, int>(std::move(who), std::move(what), std::move(mark_name), std::move(mark_id));
        GetVM()->DispatchStaticCall("DCursesLib", "SendModEventMark", args, result);
        delete args;
    }

    void SendModEventTattoo(RE::Actor* who, std::string what, int tattoo_count) {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, std::string, int>(std::move(who), std::move(what), std::move(tattoo_count));
        GetVM()->DispatchStaticCall("DCursesLib", "SendModEventTattoo", args, result);
        delete args;
    }

    void SendModEventContraption(RE::Actor* who, std::string what) {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, std::string>(std::move(who), std::move(what));
        GetVM()->DispatchStaticCall("DCursesLib", "SendModEventContraption", args, result);
        delete args;
    }

    void SetArousal(RE::Actor* actor, int arousal) {
        RE::TESForm* aroused = StaticDataHolder::GetSingleton()->LookupForm(0x4290f, "SexLabAroused.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, aroused);
        RE::BSTSmartPointer<RE::BSScript::Object> arousedObject;
        GetVM()->FindBoundObject(hand, "slaFrameworkScr", arousedObject);

        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, int>(std::move(actor), std::move(arousal));
        GetVM()->DispatchMethodCall(arousedObject, "SetActorExposure", args, result);
        delete args;
    }

    void ModifyArousal(RE::Actor* actor, int arousal) {
        RE::TESForm* aroused = StaticDataHolder::GetSingleton()->LookupForm(0x4290f, "SexLabAroused.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, aroused);
        RE::BSTSmartPointer<RE::BSScript::Object> arousedObject;
        GetVM()->FindBoundObject(hand, "slaFrameworkScr", arousedObject);

        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, int, std::string>(std::move(actor), std::move(arousal), std::move(""));
        GetVM()->DispatchMethodCall(arousedObject, "UpdateActorExposure", args, result);
        delete args;
    }

    void LockDevice(RE::Actor* akActor, RE::TESObjectARMO* deviceInventory, bool force = false) {
        RE::TESForm* libs = StaticDataHolder::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, libs);
        RE::BSTSmartPointer<RE::BSScript::Object> zadlibsObject;
        GetVM()->FindBoundObject(hand, "zadLibs", zadlibsObject);

        if (akActor == nullptr || deviceInventory == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, RE::TESObjectARMO*, bool>(std::move(akActor), std::move(deviceInventory), std::move(force));
        GetVM()->DispatchMethodCall(zadlibsObject, "LockDevice", args, callback);
        delete args;
    }

    void UnlockDevice(RE::Actor* akActor, RE::TESObjectARMO* deviceInventory, RE::TESObjectARMO* deviceRendered = nullptr, RE::BGSKeyword* zad_DeviousDevice = nullptr, bool destroyDevice = false, bool genericonly = true) {
        if (deviceRendered == nullptr) {
            deviceRendered = DeviousDevicesAPI::g_API->GetDeviceRender(deviceInventory);
        }
        RE::TESForm* libs = StaticDataHolder::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, libs);
        RE::BSTSmartPointer<RE::BSScript::Object> zadlibsObject;
        GetVM()->FindBoundObject(hand, "zadLibs", zadlibsObject);

        if (akActor == nullptr || deviceInventory == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, RE::TESObjectARMO*, RE::TESObjectARMO*, RE::BGSKeyword*, bool, bool>(std::move(akActor), std::move(deviceInventory), std::move(deviceRendered), std::move(zad_DeviousDevice), std::move(destroyDevice), std::move(genericonly));
        GetVM()->DispatchMethodCall(zadlibsObject, "UnlockDevice", args, callback);
        delete args;
    }

    void RemoveQuestDevice(RE::Actor* akActor, RE::TESObjectARMO* deviceInventory, RE::TESObjectARMO* deviceRendered, bool destroyDevice = false) {
        auto removalToken = RE::TESForm::LookupByEditorID("DCurses_QuestItem")->As<RE::BGSKeyword>();
        RE::TESForm* libs = StaticDataHolder::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, libs);
        RE::BSTSmartPointer<RE::BSScript::Object> zadlibsObject;
        GetVM()->FindBoundObject(hand, "zadLibs", zadlibsObject);

        if (akActor == nullptr || deviceInventory == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, RE::TESObjectARMO*, RE::TESObjectARMO*, RE::BGSKeyword*, RE::BGSKeyword*, bool, bool>(std::move(akActor), std::move(deviceInventory), std::move(deviceRendered), std::move(nullptr), std::move(removalToken), std::move(destroyDevice), std::move(false));
        GetVM()->DispatchMethodCall(zadlibsObject, "RemoveQuestDevice", args, callback);
        delete args;
    }

    void SwapDevices(RE::Actor* akActor, RE::TESObjectARMO* deviceInventory, RE::BGSKeyword* zad_DeviousDevice = nullptr, bool destroyDevice = false, bool genericonly = true) {
        RE::TESForm* libs = StaticDataHolder::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, libs);
        RE::BSTSmartPointer<RE::BSScript::Object> zadlibsObject;
        GetVM()->FindBoundObject(hand, "zadLibs", zadlibsObject);

        if (akActor == nullptr || deviceInventory == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, RE::TESObjectARMO*, RE::BGSKeyword*, bool, bool>(std::move(akActor), std::move(deviceInventory), std::move(zad_DeviousDevice), std::move(destroyDevice), std::move(genericonly));
        GetVM()->DispatchMethodCall(zadlibsObject, "SwapDevices", args, callback);
        delete args;
    }

    void VibrateEffect(RE::Actor* akActor, int vibStrength, int duration, bool teaseOnly = false, bool silent = false) {
        RE::TESForm* libs = StaticDataHolder::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, libs);
        RE::BSTSmartPointer<RE::BSScript::Object> zadlibsObject;
        GetVM()->FindBoundObject(hand, "zadLibs", zadlibsObject);

        if (akActor == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, int, int, bool, bool>(std::move(akActor), std::move(vibStrength), std::move(duration), std::move(teaseOnly), std::move(silent));
        GetVM()->DispatchMethodCall(zadlibsObject, "VibrateEffect", args, callback);
        delete args;
    }

    void ShockActor(RE::Actor* akActor) {
        RE::TESForm* libs = StaticDataHolder::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, libs);
        RE::BSTSmartPointer<RE::BSScript::Object> zadlibsObject;
        GetVM()->FindBoundObject(hand, "zadLibs", zadlibsObject);

        if (akActor == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*>(std::move(akActor));
        GetVM()->DispatchMethodCall(zadlibsObject, "ShockActor", args, callback);
        delete args;
    }

    void UnequipItem(RE::Actor* akActor, RE::TESForm* item) {

        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::ActorCharacter, akActor);
        RE::BSTSmartPointer<RE::BSScript::Object> obj;
        GetVM()->FindBoundObject(hand, "Actor", obj);
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::TESForm*, bool, bool>(std::move(item), std::move(false), std::move(true));
        GetVM()->DispatchMethodCall(obj, "UnequipItem", args, callback);
        delete args;
    }

    void UnequipSpell(RE::Actor* akActor, RE::TESForm* spell, int akSource) {

        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::ActorCharacter, akActor);
        RE::BSTSmartPointer<RE::BSScript::Object> obj;
        GetVM()->FindBoundObject(hand, "Actor", obj);
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::TESForm*, int>(std::move(spell), std::move(akSource));
        GetVM()->DispatchMethodCall(obj, "UnequipSpell", args, callback);
        delete args;
    }

    void UpdateArousal(RE::Actor* akActor) {
        RE::BSTSmartPointer<RE::BSScript::Object> slaObject;
        RE::TESForm* sla = StaticDataHolder::GetSingleton()->LookupForm(std::stoi("4290f", 0, 16), "SexLabAroused.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, sla);
        GetVM()->FindBoundObject(hand, "slaFrameworkScr", slaObject);

        if (akActor == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*>(std::move(akActor));
        GetVM()->DispatchMethodCall(slaObject, "GetActorArousal", args, callback);
        delete args;
    }

    void RTDoTattooEvent(RE::Actor* akActor, int count) {
        RE::BSTSmartPointer<RE::BSScript::Object> rapeTatsObject;
        RE::TESForm* form = StaticDataHolder::GetSingleton()->LookupForm(0xd62, "RapeTattoos.esp");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, form);
        GetVM()->FindBoundObject(hand, "rapeTattoos", rapeTatsObject);

        if (akActor == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, int>(std::move(akActor), std::move(count));
        GetVM()->DispatchMethodCall(rapeTatsObject, "doTattooActionFor", args, callback);
        delete args;
    }

    RE::BSTSmartPointer<RE::BSScript::Object> ContraptionsGetRefScript(RE::TESObjectREFR* furniture) {
        auto handle = GetHP()->GetHandleForObject(RE::FormType::Reference, furniture);
        RE::BSTSmartPointer<RE::BSScript::Object> scriptObject;
        GetVM()->FindBoundObject(handle, "zadcFurnitureScript", scriptObject);

        if (!scriptObject) {
            return nullptr;
        }

        return scriptObject;
    }

    void ContraptionsLockActor(RE::Actor* akActor, RE::TESObjectREFR* furniture) {
        RE::TESForm* clibs = StaticDataHolder::GetSingleton()->LookupForm(0x22fd, "Devious Devices - Contraptions.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, clibs);
        RE::BSTSmartPointer<RE::BSScript::Object> zadclibsObject;
        GetVM()->FindBoundObject(hand, "zadcLibs", zadclibsObject);

        if (akActor == nullptr || furniture == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, RE::TESObjectREFR*, RE::TESPackage*, bool>(std::move(akActor), std::move(furniture), nullptr, false);
        GetVM()->DispatchMethodCall(zadclibsObject, "LockActorV2", args, callback);
        delete args;
    }

    void ContraptionsUnlockActor(RE::Actor* akActor) {
        RE::TESForm* clibs = StaticDataHolder::GetSingleton()->LookupForm(0x22fd, "Devious Devices - Contraptions.esm");
        RE::VMHandle hand = GetHP()->GetHandleForObject(RE::FormType::Quest, clibs);
        RE::BSTSmartPointer<RE::BSScript::Object> zadclibsObject;
        GetVM()->FindBoundObject(hand, "zadcLibs", zadclibsObject);

        if (akActor == nullptr) { return; }
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*>(std::move(akActor));
        GetVM()->DispatchMethodCall(zadclibsObject, "UnlockActor", args, callback);
        delete args;
    }

    void ForceThirdPerson() {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        RE::BSScript::IFunctionArguments* args = new RE::BSScript::ZeroFunctionArguments;
        GetVM()->DispatchStaticCall("Game", "ForceThirdPerson", args, result);
        delete args;
    }

    void DisableMenus() {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<bool, bool, bool, bool, bool, bool, bool, bool, int>(std::move(false), std::move(false), std::move(false), std::move(false), std::move(false), std::move(true), std::move(true), std::move(false), std::move(0));
        GetVM()->DispatchStaticCall("Game", "DisablePlayerControls", args, result);
        delete args;
    }

    void EnableMenus() {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<bool, bool, bool, bool, bool, bool, bool, bool, int>(std::move(false), std::move(false), std::move(false), std::move(false), std::move(false), std::move(true), std::move(true), std::move(false), std::move(0));
        GetVM()->DispatchStaticCall("Game", "EnablePlayerControls", args, result);
        delete args;
    }

    void CloseContinerMenus() {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<std::string, std::string, std::string>("HUD Menu", "_global.skse.CloseMenu", "InventoryMenu");
        GetVM()->DispatchStaticCall("UI", "InvokeString", args, result);
        delete args;
        args = RE::MakeFunctionArguments<std::string, std::string, std::string>("HUD Menu", "_global.skse.CloseMenu", "ContainerMenu");
        GetVM()->DispatchStaticCall("UI", "InvokeString", args, result);
        delete args;
        args = RE::MakeFunctionArguments<std::string, std::string, std::string>("HUD Menu", "_global.skse.CloseMenu", "Lockpicking Menu");
        GetVM()->DispatchStaticCall("UI", "InvokeString", args, result); 
        delete args;
    }

    void DBGMessageBox(std::string message) {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<std::string>(std::move(message));
        GetVM()->DispatchStaticCall("Debug", "MessageBox", args, result);
        delete args;
    }

    void DBGNotification(std::string message) {
        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> result;
        RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<std::string>(std::move(message));
        GetVM()->DispatchStaticCall("Debug", "Notification", args, result);
        delete args;
    }
}