#pragma once

#include "Utils.hpp"

using namespace SKSE;

namespace DCURSES {
	namespace ModEventInternal {

		class CallbackFunctor : public RE::BSScript::IStackCallbackFunctor {
		public:
			RE::BSTSmartPointer<CallbackFunctor> nextCallback = nullptr;
			int _handle = -1;

			virtual void dispatch(int handle) = 0;

			// Inherited via IStackCallbackFunctor
			virtual void operator()(RE::BSScript::Variable a_result) override
			{
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

			virtual void SetObject(const RE::BSTSmartPointer<RE::BSScript::Object>&) override {}

			void SetNextCallback(RE::BSTSmartPointer<CallbackFunctor> next) {
				nextCallback = next;
			}
		};

		class SendFunctor : public CallbackFunctor {
		public:
			virtual void dispatch(int handle) override {
				_handle = handle;
				RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>(this);
				GetVM()->DispatchStaticCall("ModEvent", "Send", RE::MakeFunctionArguments<int>(std::move(_handle)), callback);
			}
		};

		class CreateFunctor : public CallbackFunctor {
		public:
			std::string _data;
			virtual void dispatch(int) override {
				RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>(this);
				GetVM()->DispatchStaticCall("ModEvent", "Create", RE::MakeFunctionArguments<std::string>(std::move(_data)), callback);
			}

			CreateFunctor(std::string eventName) {
				_data = eventName;
			}
		};

		class StringFunctor : public CallbackFunctor {
		public:
			std::string _data;
			virtual void dispatch(int handle) override {
				_handle = handle;
				RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>(this);
				GetVM()->DispatchStaticCall("ModEvent", "PushString", RE::MakeFunctionArguments<int, std::string>(std::move(_handle), std::move(_data)), callback);
			}

			StringFunctor(std::string value) {
				_data = value;
			}
		};

		class IntFunctor : public CallbackFunctor {
		public:
			int _data;
			virtual void dispatch(int handle) override {
				_handle = handle;
				RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>(this);
				GetVM()->DispatchStaticCall("ModEvent", "PushInt", RE::MakeFunctionArguments<int, int>(std::move(_handle), std::move(_data)), callback);
			}

			IntFunctor(int value) {
				_data = value;
			}
		};

		class FloatFunctor : public CallbackFunctor {
		public:
			float _data;
			virtual void dispatch(int handle) override {
				_handle = handle;
				RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>(this);
				GetVM()->DispatchStaticCall("ModEvent", "PushFloat", RE::MakeFunctionArguments<int, float>(std::move(_handle), std::move(_data)), callback);
			}

			FloatFunctor(float value) {
				_data = value;
			}
		};

		class BoolFunctor : public CallbackFunctor {
		public:
			bool _data;
			virtual void dispatch(int handle) override {
				_handle = handle;
				RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>(this);
				GetVM()->DispatchStaticCall("ModEvent", "PushBool", RE::MakeFunctionArguments<int, bool>(std::move(_handle), std::move(_data)), callback);
			}

			BoolFunctor(bool value) {
				_data = value;
			}
		};

		class FormFunctor : public CallbackFunctor {
		public:
			RE::TESForm* _data;
			virtual void dispatch(int handle) override {
				_handle = handle;
				RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>(this);
				GetVM()->DispatchStaticCall("ModEvent", "PushForm", RE::MakeFunctionArguments<int, RE::TESForm*>(std::move(_handle), std::move(_data)), callback);
			}

			FormFunctor(RE::TESForm* value) {
				_data = value;
			}
		};
	}

	class CustomModEvent {
	public:
		std::vector<ModEventInternal::CallbackFunctor*> toDispatch = std::vector<ModEventInternal::CallbackFunctor*>();

		CustomModEvent(std::string eventName) {
			using namespace ModEventInternal;

			CreateFunctor* func = new CreateFunctor(eventName);
			toDispatch.push_back(func);
		}

		void Send() {
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

		CustomModEvent& PushString(std::string value) {
			using namespace ModEventInternal;

			StringFunctor* func = new StringFunctor(value);
			toDispatch.push_back(func);
			return *this;
		}

		CustomModEvent& PushInt(int value) {
			using namespace ModEventInternal;

			IntFunctor* func = new IntFunctor(value);
			toDispatch.push_back(func);
			return *this;
		}

		CustomModEvent& PushFloat(float value) {
			using namespace ModEventInternal;

			FloatFunctor* func = new FloatFunctor(value);
			toDispatch.push_back(func);
			return *this;
		}

		CustomModEvent& PushBool(bool value) {
			using namespace ModEventInternal;

			BoolFunctor* func = new BoolFunctor(value);
			toDispatch.push_back(func);
			return *this;
		}

		CustomModEvent& PushForm(RE::TESForm* value) {
			using namespace ModEventInternal;

			FormFunctor* func = new FormFunctor(value);
			toDispatch.push_back(func);
			return *this;
		}
	};

	void test() {
		auto event = CustomModEvent("test_event");
		event.PushBool(true);
		event.PushInt(12);
		event.Send();
	}
}