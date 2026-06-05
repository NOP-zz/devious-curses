#pragma once



namespace DCURSES {
	namespace ModEventInternal {
		class CallbackFunctor : public RE::BSScript::IStackCallbackFunctor {
		public:
			RE::BSTSmartPointer<CallbackFunctor> nextCallback = nullptr;
			int _handle = -1;

			virtual void dispatch(int handle) = 0;

			// Inherited via IStackCallbackFunctor
			virtual void operator()(RE::BSScript::Variable a_result) override;

			virtual void SetObject(const RE::BSTSmartPointer<RE::BSScript::Object>&) override {}

			void SetNextCallback(RE::BSTSmartPointer<CallbackFunctor> next);
		};

		class SendFunctor : public CallbackFunctor {
		public:
			virtual void dispatch(int handle) override;
		};

		class CreateFunctor : public CallbackFunctor {
		public:
			std::string _data;
			virtual void dispatch(int) override;

			CreateFunctor(std::string eventName);
		};

		class StringFunctor : public CallbackFunctor {
		public:
			std::string _data;
			virtual void dispatch(int handle) override;

			StringFunctor(std::string value);
		};

		class IntFunctor : public CallbackFunctor {
		public:
			int _data;
			virtual void dispatch(int handle) override;

			IntFunctor(int value);
		};

		class FloatFunctor : public CallbackFunctor {
		public:
			float _data;
			virtual void dispatch(int handle) override;

			FloatFunctor(float value);
		};

		class BoolFunctor : public CallbackFunctor {
		public:
			bool _data;
			virtual void dispatch(int handle) override;

			BoolFunctor(bool value);
		};

		class FormFunctor : public CallbackFunctor {
		public:
			RE::TESForm* _data;
			virtual void dispatch(int handle) override;

			FormFunctor(RE::TESForm* value);
		};
	}

	class CustomModEvent {
	public:
		std::vector<ModEventInternal::CallbackFunctor*> toDispatch = std::vector<ModEventInternal::CallbackFunctor*>();

		static void SendModEvent(std::string eventName, std::string strArg = "", float numArg = 0);

		CustomModEvent(std::string eventName);

		void Send();

		CustomModEvent& PushString(std::string value);

		CustomModEvent& PushInt(int value);

		CustomModEvent& PushFloat(float value);

		CustomModEvent& PushBool(bool value);

		CustomModEvent& PushForm(RE::TESForm* value);
	};

	void SendCurseModEvent(std::string eventName, std::string eventSource, RE::Actor* akActor, std::string otherEventData);
}