#include "ModEvents.h"

#include "Utils.h"
#include "Scripting.h"
#include "form_ids.h"

using namespace SKSE;

namespace DCURSES {
	namespace ModEventInternal {
		void CallbackFunctor::operator()(RE::BSScript::Variable a_result) {
			if (nextCallback != nullptr) {
				if (a_result.IsInt()) {
					_handle = a_result.GetSInt();
				}

				nextCallback.get()->dispatch(_handle);
				//Util::ExecuteWithDelay(3000ms, [this] {
				//	delete this;
				//});
			}
		}
		inline void CallbackFunctor::SetNextCallback(RE::BSTSmartPointer<CallbackFunctor> next) {
			nextCallback = next;
		}
		inline void SendFunctor::dispatch(int handle) {
			_handle = handle;
			RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>(this);
			GetVM()->DispatchStaticCall("ModEvent", "Send", RE::MakeFunctionArguments<int>(std::move(_handle)), callback);
		}
		inline void CreateFunctor::dispatch(int) {
			RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>(this);
			GetVM()->DispatchStaticCall("ModEvent", "Create", RE::MakeFunctionArguments<std::string>(std::move(_data)), callback);
		}
		inline CreateFunctor::CreateFunctor(std::string eventName) {
			_data = eventName;
		}
		inline void StringFunctor::dispatch(int handle) {
			_handle = handle;
			RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>(this);
			GetVM()->DispatchStaticCall("ModEvent", "PushString", RE::MakeFunctionArguments<int, std::string>(std::move(_handle), std::move(_data)), callback);
		}
		inline StringFunctor::StringFunctor(std::string value) {
			_data = value;
		}
		inline void IntFunctor::dispatch(int handle) {
			_handle = handle;
			RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>(this);
			GetVM()->DispatchStaticCall("ModEvent", "PushInt", RE::MakeFunctionArguments<int, int>(std::move(_handle), std::move(_data)), callback);
		}
		inline IntFunctor::IntFunctor(int value) {
			_data = value;
		}
		inline void FloatFunctor::dispatch(int handle) {
			_handle = handle;
			RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>(this);
			GetVM()->DispatchStaticCall("ModEvent", "PushFloat", RE::MakeFunctionArguments<int, float>(std::move(_handle), std::move(_data)), callback);
		}
		inline FloatFunctor::FloatFunctor(float value) {
			_data = value;
		}
		inline void BoolFunctor::dispatch(int handle) {
			_handle = handle;
			RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>(this);
			GetVM()->DispatchStaticCall("ModEvent", "PushBool", RE::MakeFunctionArguments<int, bool>(std::move(_handle), std::move(_data)), callback);
		}
		inline BoolFunctor::BoolFunctor(bool value) {
			_data = value;
		}
		inline void FormFunctor::dispatch(int handle) {
			_handle = handle;
			RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>(this);
			GetVM()->DispatchStaticCall("ModEvent", "PushForm", RE::MakeFunctionArguments<int, RE::TESForm*>(std::move(_handle), std::move(_data)), callback);
		}
		inline FormFunctor::FormFunctor(RE::TESForm* value) {
			_data = value;
		}
	}

	void CustomModEvent::SendModEvent(std::string eventName, std::string strArg, float numArg) {
		auto source = SKSE::GetModCallbackEventSource();
		auto sender = StaticDataHolder::GetSingleton()->LookupForm(DCURSES_MCM, "Devious Curses.esp");
		SKSE::ModCallbackEvent* event = new SKSE::ModCallbackEvent{ eventName, strArg, numArg, sender };
		source->SendEvent(event);
	}

	CustomModEvent::CustomModEvent(std::string eventName) {
		using namespace ModEventInternal;

		CreateFunctor* func = new CreateFunctor(eventName);
		toDispatch.push_back(func);
	}

	void CustomModEvent::Send() {
		using namespace ModEventInternal;

		SendFunctor* func = new SendFunctor();
		toDispatch.push_back(func);

		RE::BSTSmartPointer<CallbackFunctor> dispatch = RE::BSTSmartPointer(toDispatch[0]);

		for (int i = static_cast<int>(toDispatch.size() - 2); i >= 0; i--) {
			RE::BSTSmartPointer<CallbackFunctor> callback = RE::BSTSmartPointer<CallbackFunctor>(toDispatch[i + 1]);
			toDispatch[i]->SetNextCallback(callback);
		}

		dispatch->dispatch(0);
	}

	CustomModEvent& CustomModEvent::PushString(std::string value) {
		using namespace ModEventInternal;

		StringFunctor* func = new StringFunctor(value);
		toDispatch.push_back(func);
		return *this;
	}

	CustomModEvent& CustomModEvent::PushInt(int value) {
		using namespace ModEventInternal;

		IntFunctor* func = new IntFunctor(value);
		toDispatch.push_back(func);
		return *this;
	}

	CustomModEvent& CustomModEvent::PushFloat(float value) {
		using namespace ModEventInternal;

		FloatFunctor* func = new FloatFunctor(value);
		toDispatch.push_back(func);
		return *this;
	}

	CustomModEvent& CustomModEvent::PushBool(bool value) {
		using namespace ModEventInternal;

		BoolFunctor* func = new BoolFunctor(value);
		toDispatch.push_back(func);
		return *this;
	}

	CustomModEvent& CustomModEvent::PushForm(RE::TESForm* value) {
		using namespace ModEventInternal;

		FormFunctor* func = new FormFunctor(value);
		toDispatch.push_back(func);
		return *this;
	}

	void SendCurseModEvent(std::string eventName, std::string eventSource, RE::Actor* akActor, std::string otherEventData) {
		auto modevent = CustomModEvent("DCurses_EventTriggered");
		modevent.PushString(eventName);
		modevent.PushString(eventSource);
		modevent.PushForm(akActor);
		modevent.PushString(otherEventData);
		modevent.Send();
	}
}