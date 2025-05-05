#pragma once

#include "O_Devices.hpp"

using namespace SKSE;

namespace DCURSES {
	void QIMeridiaInteraction() {
		CloseContinerMenus();
		auto player = RE::PlayerCharacter::GetSingleton();
		auto mark = GetLewdMark(player);
		if (mark > 0) {
			RemoveLewdMark(player);
		}

		AddLewdMark(player, TAT_MERIDIA);
		counters.clock_QIMeridia = static_cast<uint64_t>(Util::randomDouble(10, 15) * -60.0);
		PlayerMessage("As you kill Malkoran he curses you with an unknown mark!");
		SendModEventMark(player, "Malkoran", "Malkoran", TAT_MERIDIA);
	}

	void QISanguineInteraction1() {
		auto player = RE::PlayerCharacter::GetSingleton();

		auto belt = GetWornDeviceByKeyword(player, "zad_DeviousBelt");
		if (belt) {
			UnlockDevice(player, belt);
		}

		auto plug = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESObjectARMO>(DDX_RUSTY_PEAR_ANAL_SIGN, "Devious Devices - Expansion.esm");
		LockDevice(player, plug, true);
		plug = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESObjectARMO>(DDX_RUSTY_PEAR_VAGINAL, "Devious Devices - Expansion.esm");
		LockDevice(player, plug, true);

		DoStandardEvent(false, "", "(rust | (iron & belt))", 20, { "zad_DeviousGag", "zad_DeviousHeavyBondage", "zad_DeviousBondageMittens", "zad_DeviousPlugVaginal", "zad_DeviousPlugAnal" });
		AddLewdMark(player, TAT_NUDITY);
		SendModEventMark(player, "Sanguine", "Nudity", TAT_NUDITY);
		counters.LMPeopleTalked = -100;
	}

	void QISanguineInteractionEnd() {
		RE::TESKey* magic_key = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESKey>(MAGIC_KEY, "Devious Curses.esp");
		auto player = RE::PlayerCharacter::GetSingleton();

		player->AddObjectToContainer((RE::TESBoundObject*)magic_key, nullptr, 1, nullptr);

		auto mark = GetLewdMark(player);
		if (mark == TAT_NUDITY) {
			RemoveLewdMark(player);
		}
		PlayerMessage("Now that your wild adventure with Sanguine is over, he gives you a magic key!");
	}

	void QIPotemaInteraction(); // Add a curse during the potema questline. Sugestion was to have a curse that periodically summons devices. Gets stronger when fighting potema??

	void QIMGInteraction1() {
		RE::TESObjectARMO* amulet = RE::TESForm::LookupByID(0x233D0)->As<RE::TESObjectARMO>();
		auto player = RE::PlayerCharacter::GetSingleton();

		player->RemoveItem(amulet, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr, nullptr, nullptr);
		OppSummonerCollarEvent("", false);

		PlayerMessage("Strange magic interacts with the amulet transforming it into a collar!");
	}

	void QICheckQuestStage(RE::FormID quest_id, uint16_t stage) {
		if (!settings.enableQuestInteractions) { return; }

		auto quest = RE::TESForm::LookupByID(quest_id)->As<RE::TESQuest>();


		if (quest == RE::TESForm::LookupByID(0x4E4E1)->As<RE::TESQuest>()) {
			if (stage == 410) QIMeridiaInteraction();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_DA14)->As<RE::TESQuest>()) {
			if (stage == 5) QISanguineInteraction1();
			if (stage == 200) QISanguineInteractionEnd();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_MG07)->As<RE::TESQuest>()) {
			if (stage == 20) QIMGInteraction2();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_MG08)->As<RE::TESQuest>()) {
			if (stage == 200) QIMGInteractionEnd();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_TG02)->As<RE::TESQuest>()) {
			if (stage == 50) QITGInteraction1();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_TG03)->As<RE::TESQuest>()) {
			if (stage == 100) QITGInteraction2();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_TG04)->As<RE::TESQuest>()) {
			if (stage == 60) QITGInteraction3();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_TG06)->As<RE::TESQuest>()) {
			if (stage == 50) QITGInteraction4();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_TG07)->As<RE::TESQuest>()) {
			if (stage == 60) QITGInteraction5();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_TG08A)->As<RE::TESQuest>()) {
			if (stage == 57) QITGInteraction6();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_TG09)->As<RE::TESQuest>()) {
			if (stage == 50) QITGInteractionEnd();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_C01)->As<RE::TESQuest>()) {
			if (stage == 50) QITGInteractionEnd();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_C05)->As<RE::TESQuest>()) {
			log::info("stage {}", stage);
			if (stage == 20) QICInteraction2();
		}
	}

	void QICheckObjectActivation(RE::TESObjectREFR* object) {
		if (!settings.enableQuestInteractions) { return; }

		RE::TESObjectARMO* amulet = RE::TESForm::LookupByID(0x233D0)->As<RE::TESObjectARMO>();
		if (object->formID == 0xbc8b8 && object->GetBaseObject()->formID == 0x21513 && ActorIsWearingDevice(RE::PlayerCharacter::GetSingleton(), amulet)) {
			QIMGInteraction1();
		}

		if (object->formID == 0x236f5 && object->GetBaseObject()->formID == 0x21513 && !IsObjectRefKnown(object->formID) && !RE::TESForm::LookupByID(QUEST_C01)->As<RE::TESQuest>()->IsCompleted()) {
			QICInteraction1();
			SetObjectRefKnown(object->formID);
		}
	}
}