#pragma once

#include "form_ids.h"
#include "Translation.h"

typedef int color;
typedef int keycode;
typedef std::string text;
typedef int menu;

namespace DCURSES::Quest {

	constexpr auto MCMQUEST = 0x800;

	class QuestSettings {
	private:
		QuestSettings() {}
	public:
		std::filesystem::file_time_type lastSettingsEditTime = std::chrono::clock_cast<std::filesystem::file_time_type::clock>(std::chrono::system_clock::now());

		QuestSettings(QuestSettings const&) = delete;
		void operator=(QuestSettings const&) = delete;

		static QuestSettings* GetSingleton() {
			static QuestSettings instance;
			return &instance;
		};

		//MCM_START
		
		//Page Radiant
		//Header Lost and Found
		float radLFFindChance = 15.0f;			//Trinket find Chance//Chance to find a random trinket in a bandit boss chest.//{1}//(0,100,0.1)
		int radLFBaseReward = 500;				//Trinket Base Reward//Gold paid by the Court Mage upon returning the trinket.//{0}//(10,1000,10)
		int radLFLeveledReward = 0;				//Trinket Leveled Reward//Extra gold paid by the Court Mage per player level.//{0}//(0,1000,10)

		//MCM_END
	};

	void PlayerMessage(Translator trans, bool useSurpriseMode = false);

	void ResetMCMSettings();

	void SaveMCMSettings();

	bool LoadSettingsFile();

	void PushSettingsToMCM();

	bool PapyrusFunctionsSettigns(RE::BSScript::IVirtualMachine* ivm);

}