#pragma once

#include "../include/form_ids.h"
#include "../include/DDNG_API.h"

#include "Translation.hpp"

#undef GetObject

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

    bool CheckAND() {
        RE::TESForm* form = StaticDataHolder::GetSingleton()->LookupForm(0x837, "Advanced Nudity Detection.esp");
        if (form == nullptr) {
            return false;
        }
        return true;
    }

    class ScriptIntent {
    public:
        std::string script_name;
        std::string function;
        RE::TESForm* form = nullptr;
        RE::FormType type;

        RE::BSScript::IFunctionArguments* args;

        ScriptIntent(std::string script_name, std::string function, RE::BSScript::IFunctionArguments* args) {
            this->script_name = script_name;
            this->function = function;
            this->args = args;
        }
        ScriptIntent(std::string script_name, std::string function) {
            this->script_name = script_name;
            this->function = function;
            this->args = new RE::BSScript::ZeroFunctionArguments;
        }
        ScriptIntent(RE::TESForm* form, RE::FormType type, std::string script_name, std::string function, RE::BSScript::IFunctionArguments* args) {
            this->script_name = script_name;
            this->function = function;
            this->form = form;
            this->type = type;
            this->args = args;
        }
        ScriptIntent(RE::TESForm* form, RE::FormType type, std::string script_name, std::string function) {
            this->script_name = script_name;
            this->function = function;
            this->form = form;
            this->type = type;
            this->args = new RE::BSScript::ZeroFunctionArguments;
        }
    };

    class VirtualScriptCallbackFunctor : public RE::BSScript::IStackCallbackFunctor {
    public:
        RE::BSTSmartPointer<VirtualScriptCallbackFunctor> nextCallback = nullptr;
        ScriptIntent intent = ScriptIntent("", "", nullptr);

        void dispatch() {
            RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>(this);
            if (intent.form == nullptr) {
                GetVM()->DispatchStaticCall(intent.script_name, intent.function, intent.args, callback);
                delete intent.args;
            }
            else {
                RE::VMHandle hand = GetHP()->GetHandleForObject(intent.type, intent.form);
                RE::BSTSmartPointer<RE::BSScript::Object> obj;
                GetVM()->FindBoundObject(hand, intent.script_name.c_str(), obj);
                GetVM()->DispatchMethodCall(obj, intent.function, intent.args, callback);
                delete intent.args;
            }

        }

        virtual void SetObject(const RE::BSTSmartPointer<RE::BSScript::Object>&) override {}

        VirtualScriptCallbackFunctor(ScriptIntent intent) {
            this->intent = intent;
        }

        void SetNextCallback(RE::BSTSmartPointer<VirtualScriptCallbackFunctor> next) {
            nextCallback = next;
        }

        RE::BSTSmartPointer<VirtualScriptCallbackFunctor> PushNewCallback(RE::BSTSmartPointer<VirtualScriptCallbackFunctor> next) {
            auto tempCallback = nextCallback;
            nextCallback = next;
            next->nextCallback = tempCallback;
            return next;
        }
    };

    class ScriptCallbackFunctor : public VirtualScriptCallbackFunctor {
    public:
        ScriptCallbackFunctor(ScriptIntent intent) : VirtualScriptCallbackFunctor(intent) {}

        virtual void operator()(RE::BSScript::Variable) override
        {
            if (nextCallback != nullptr) {
                nextCallback->dispatch();
            }
        }
    };

    typedef RE::BSTSmartPointer<VirtualScriptCallbackFunctor> ScriptCallback;

    template<class T>
    class ScriptCallbackFunctor_R : public VirtualScriptCallbackFunctor {
        std::function<void(std::optional<T>, ScriptCallback)> onCallback;
    public:
        ScriptCallbackFunctor_R(ScriptIntent intent, std::function<void(std::optional<T>, ScriptCallback)> onCallbackFunction) : VirtualScriptCallbackFunctor(intent) {
            onCallback = onCallbackFunction;
        }

        virtual void operator()(RE::BSScript::Variable a_result) override
        {
            std::optional<T> data;
            if (a_result.IsNoneObject()) {
                data = std::nullopt;
            }
            else if constexpr (std::is_integral_v<T> && std::is_signed_v<T>) {
                data = a_result.GetSInt();
            }
            else if constexpr (std::is_same_v<RE::BGSRefAlias*, T>) {
                data = a_result.Unpack<T>();
            }
            else {
                static_assert(std::is_same_v<RE::TESForm*, T>);
                data = a_result.Unpack<T>();
            }

            onCallback(data, ScriptCallback(this));

            if (nextCallback != nullptr) {
                nextCallback->dispatch();
            }
        }
    };

    template<class V>
    class ScriptCallbackFunctor_R<RE::BSTArray<V>> : public VirtualScriptCallbackFunctor {
        std::function<void(RE::BSTArray<V>, ScriptCallback)> onCallback;
    public:
        ScriptCallbackFunctor_R(ScriptIntent intent, std::function<void(RE::BSTArray<V>, ScriptCallback)> onCallbackFunction) : VirtualScriptCallbackFunctor(intent) {
            onCallback = onCallbackFunction;
        }

        virtual void operator()(RE::BSScript::Variable a_result) override
        {
            RE::BSTArray<V> result;

            if (!a_result.IsNoneObject() && !a_result.IsNoneArray()) {
 
                result = a_result.Unpack<RE::BSTArray<V>>();
            }

            onCallback(result, ScriptCallback(this));

            if (nextCallback != nullptr) {
                nextCallback->dispatch();
            }
        }
    };

    class ScriptingManager {
    private:
        typedef std::vector<std::pair<ScriptIntent, ScriptCallback>> IntentList;
        static IntentList* intents() {
            static IntentList intents;
            return &intents;
        }

        static uint32_t refCount;

        static void DoSequential(IntentList intents) {
            RE::BSTSmartPointer <VirtualScriptCallbackFunctor> dispatch = intents[0].second;

            for (int i = static_cast<int>(intents.size()) - 2; i >= 0; i--) {
                intents[i].second->SetNextCallback(intents[i+1].second);
            }

            dispatch->dispatch();
        }

        static void RunOrderedIntent() {
            if (!intents()->empty()) {
                DoSequential(*intents());
                intents()->clear();
            }
        }

    public:
        ScriptingManager(ScriptingManager const&) = delete;
        void operator=(ScriptingManager const&) = delete;

        ScriptingManager() {
            ScriptingManager::refCount += 1;
        }

        ~ScriptingManager() {
            ScriptingManager::refCount -= 1;
            if (ScriptingManager::refCount == 0) {
                ScriptingManager::RunOrderedIntent();
            }
        }

        void RunIntent(ScriptIntent intent) {
            intents()->push_back({ intent, ScriptCallback(new ScriptCallbackFunctor(intent)) });
        }

        template<class T>
        void RunIntentWith(ScriptIntent intent, std::function<void(std::optional<T>, ScriptCallback)> onCallback) {
            intents()->push_back({ intent, ScriptCallback(new ScriptCallbackFunctor_R<T>(intent, onCallback)) });
        }

        template<class T>
        void RunIntentWithResult(ScriptIntent intent, std::function<ScriptCallback(std::optional<T>)> onCallback) {
            std::function<void(std::optional<T>, ScriptCallback)> newCallbackFunction = [onCallback](std::optional<T> data, ScriptCallback firstCallback) {
                auto newCallback = onCallback(data);
                auto tempCallback = firstCallback->nextCallback;
                firstCallback->nextCallback = newCallback;
                newCallback->nextCallback = tempCallback;
            };
            intents()->push_back({ intent, ScriptCallback(new ScriptCallbackFunctor_R<T>(intent, newCallbackFunction)) });
        }

        template<class T>
        void RunIntentWithResultSimple(ScriptIntent intent, std::function<void(T)> onCallback) {
            std::function<void(T, ScriptCallback, ScriptCallback)> newCallbackFunction = [onCallback](T data, ScriptCallback firstCallback, ScriptCallback nextCallback) {
                onCallback(data);
            };
            RunIntentWithResult(intent, newCallbackFunction);
        }

        void RunOnMenuClose(std::function<void()> onCallback) {
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<float>(0.1f);
            auto intent = ScriptIntent("Utility", "WaitMenuMode", args);
            RunIntent(intent);
            RE::BSScript::IFunctionArguments* args2 = RE::MakeFunctionArguments<float>(0.01f);
            auto intent2 = ScriptIntent("Utility", "Wait", args2);
            RunIntentWith<int>(intent2, [onCallback](std::optional<int>, ScriptCallback) {
                onCallback();
            });
        }

        void StartMCMTimer() {
            RE::TESForm* form = StaticDataHolder::GetSingleton()->LookupForm(DCURSES_MCM, "Devious Curses.esp");
            auto intent = ScriptIntent(form, RE::FormType::Quest, "DCurses_MCM", "StartTimer");
            RunIntent(intent);
        }

        void StartSex(RE::Actor* aggressor, bool preferAggressive) {
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, bool>(std::move(aggressor), std::move(preferAggressive));
            auto intent = ScriptIntent("DCursesLib", "StartSex", args);
            RunIntent(intent);
        }

        void SlowStrip(RE::Actor* actor) {
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*>(std::move(actor));
            auto intent = ScriptIntent("DCursesLib", "SlowStrip", args);
            RunIntent(intent);
        }

        int GetArousal(RE::Actor* actor) {
            RE::TESFaction* sla_arousal = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x3FC36, "SexLabAroused.esm");
            return actor->GetFactionRank(sla_arousal, actor == RE::PlayerCharacter::GetSingleton());
        }

        void ModifyArousal(RE::Actor* actor, int arousal) {
            RE::TESForm* aroused = StaticDataHolder::GetSingleton()->LookupForm(0x4290f, "SexLabAroused.esm");
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, int, std::string>(std::move(actor), std::move(arousal), "");
            auto intent = ScriptIntent(aroused, RE::FormType::Quest, "slaFrameworkScr", "UpdateActorExposure", args);
            RunIntent(intent);
        }

        void LockDevice(RE::Actor* akActor, RE::TESObjectARMO* deviceInventory, bool force = false) {
            if (akActor == nullptr || deviceInventory == nullptr) { return; }

            RE::TESForm* libs = StaticDataHolder::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, RE::TESObjectARMO*, bool>(std::move(akActor), std::move(deviceInventory), std::move(force));
            auto intent = ScriptIntent(libs, RE::FormType::Quest, "zadLibs", "LockDevice", args);
            RunIntent(intent);
        }

        void UnlockDevice(RE::Actor* akActor, RE::TESObjectARMO* deviceInventory, RE::TESObjectARMO* deviceRendered = nullptr, RE::BGSKeyword* zad_DeviousDevice = nullptr, bool destroyDevice = false, bool genericonly = true) {
            if (deviceRendered == nullptr) {
                deviceRendered = DeviousDevicesAPI::g_API->GetDeviceRender(deviceInventory);
            }
            if (akActor == nullptr || deviceInventory == nullptr) { return; }
            
            RE::TESForm* libs = StaticDataHolder::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, RE::TESObjectARMO*, RE::TESObjectARMO*, RE::BGSKeyword*, bool, bool>(std::move(akActor), std::move(deviceInventory), std::move(deviceRendered), std::move(zad_DeviousDevice), std::move(destroyDevice), std::move(genericonly));
            auto intent = ScriptIntent(libs, RE::FormType::Quest, "zadLibs", "UnlockDevice", args);
            RunIntent(intent);
        }

        void SwapDevices(RE::Actor* akActor, RE::TESObjectARMO* deviceInventory, RE::BGSKeyword* zad_DeviousDevice = nullptr, bool destroyDevice = false, bool genericonly = true) {
            if (akActor == nullptr || deviceInventory == nullptr) { return; }

            RE::TESForm* libs = StaticDataHolder::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, RE::TESObjectARMO*, RE::BGSKeyword*, bool, bool>(std::move(akActor), std::move(deviceInventory), std::move(zad_DeviousDevice), std::move(destroyDevice), std::move(genericonly));
            auto intent = ScriptIntent(libs, RE::FormType::Quest, "zadLibs", "SwapDevices", args);
            RunIntent(intent);
        }

        void VibrateEffect(RE::Actor* akActor, int vibStrength, int duration, bool teaseOnly = false, bool silent = false) {
            if (akActor == nullptr) { return; }

            RE::TESForm* libs = StaticDataHolder::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, int, int, bool, bool>(std::move(akActor), std::move(vibStrength), std::move(duration), std::move(teaseOnly), std::move(silent));
            auto intent = ScriptIntent(libs, RE::FormType::Quest, "zadLibs", "VibrateEffect", args);
            RunIntent(intent);
        }

        void ShockActor(RE::Actor* akActor) {
            if (akActor == nullptr) { return; }

            RE::TESForm* libs = StaticDataHolder::GetSingleton()->LookupForm(std::stoi("f624", 0, 16), "Devious Devices - Integration.esm");
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*>(std::move(akActor));
            auto intent = ScriptIntent(libs, RE::FormType::Quest, "zadLibs", "ShockActor", args);
            RunIntent(intent);
        }

        void UnequipItem(RE::Actor* akActor, RE::TESForm* item) {
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::TESForm*, bool, bool>(std::move(item), std::move(false), std::move(true));
            auto intent = ScriptIntent(akActor, RE::FormType::ActorCharacter, "Actor", "UnequipItem", args);
            RunIntent(intent);
        }

        void UnequipSpell(RE::Actor* akActor, RE::TESForm* spell, int akSource) {
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::TESForm*, int>(std::move(spell), std::move(akSource));
            auto intent = ScriptIntent(akActor, RE::FormType::ActorCharacter, "Actor", "UnequipSpell", args);
            RunIntent(intent);
        }

        void RTDoTattooEvent(RE::Actor* akActor, int count) {
            if (akActor == nullptr) { return; }

            RE::TESForm* form = StaticDataHolder::GetSingleton()->LookupForm(0xd62, "RapeTattoos.esp");
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, int>(std::move(akActor), std::move(count));
            auto intent = ScriptIntent(form, RE::FormType::Quest, "rapeTattoos", "doTattooActionFor", args);
            RunIntent(intent);
        }

        void ContraptionsLockActor(RE::Actor* akActor, RE::TESObjectREFR* furniture) {
            if (akActor == nullptr || furniture == nullptr) { return; }

            RE::TESForm* clibs = StaticDataHolder::GetSingleton()->LookupForm(0x22fd, "Devious Devices - Contraptions.esm");
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, RE::TESObjectREFR*, RE::TESPackage*, bool>(std::move(akActor), std::move(furniture), nullptr, false);
            auto intent = ScriptIntent(clibs, RE::FormType::Quest, "zadcLibs", "LockActorV2", args);
            RunIntent(intent);
        }
        
        void ContraptionsUnlockActor(RE::Actor* akActor) {
            if (akActor == nullptr) { return; }

            RE::TESForm* clibs = StaticDataHolder::GetSingleton()->LookupForm(0x22fd, "Devious Devices - Contraptions.esm");
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*>(std::move(akActor));
            auto intent = ScriptIntent(clibs, RE::FormType::Quest, "zadcLibs", "UnlockActor", args);
            RunIntent(intent);
        }

        void ForceThirdPerson() {
            auto intent = ScriptIntent("Game", "ForceThirdPerson");
            RunIntent(intent);
        }

        void DisableMenus() {
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<bool, bool, bool, bool, bool, bool, bool, bool, int>(std::move(false), std::move(false), std::move(false), std::move(false), std::move(false), std::move(true), std::move(true), std::move(false), std::move(0));
            auto intent = ScriptIntent("Game", "DisablePlayerControls", args);
            RunIntent(intent);
        }

        void EnableMenus() {
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<bool, bool, bool, bool, bool, bool, bool, bool, int>(std::move(false), std::move(false), std::move(false), std::move(false), std::move(false), std::move(true), std::move(true), std::move(false), std::move(0));
            auto intent = ScriptIntent("Game", "EnablePlayerControls", args);
            RunIntent(intent);
        }

        void RequestSaveGame() {
            auto intent = ScriptIntent("Game", "RequestSave");
            RunIntent(intent);
        }

        void PushActorAway(RE::TESObjectREFR* object, RE::Actor* akActor, float force) {
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<RE::Actor*, float>(std::move(akActor), std::move(force));
            auto intent = ScriptIntent(object, RE::FormType::Reference, "ObjectReference", "PushActorAway", args);
            RunIntent(intent);
        }

        void DBGMessageBox(Translator trans) {
            auto message = trans.GetTranslation();
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<std::string>(std::move(message));
            auto intent3 = ScriptIntent("Debug", "MessageBox", args);
            RunIntent(intent3);
        }

        void DBGNotification(Translator trans) {
            auto message = trans.GetTranslation();
            RE::BSScript::IFunctionArguments* args = RE::MakeFunctionArguments<std::string>(std::move(message));
            auto intent3 = ScriptIntent("Debug", "Notification", args);
            RunIntent(intent3);
        }
    };

    uint32_t ScriptingManager::refCount = 0;

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

    RE::BSTSmartPointer<RE::BSScript::Object> ContraptionsGetRefScript(RE::TESObjectREFR* furniture) {
        auto handle = GetHP()->GetHandleForObject(RE::FormType::Reference, furniture);
        RE::BSTSmartPointer<RE::BSScript::Object> scriptObject;
        GetVM()->FindBoundObject(handle, "zadcFurnitureScript", scriptObject);

        if (!scriptObject) {
            return nullptr;
        }

        return scriptObject;
    }
}