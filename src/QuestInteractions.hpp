#pragma once

#include "O_Devices.hpp"
#include "tats.hpp"

using namespace SKSE;

namespace DCURSES {
	constexpr auto QUEST_DA14 = 0x1BB9B;

	constexpr auto QUEST_MG04 = 0x1F254;

	void QIMeridiaInteraction() {
		if (!settings.enableQIMalkoran) { return; }

		CloseContinerMenus();
		auto player = RE::PlayerCharacter::GetSingleton();
		auto mark = GetLewdMark();
		if (mark == TAT_BRANDING) {
			return;
		}
		if (mark > 0) {
			RemoveLewdMark();
		}

		AddLewdMark(TAT_BRANDING);
		SetEffectMagnitude(BRANDING_EFFECT, static_cast<float>(GetTattooCount(player)));
		PlayerMessage("As you kill Malkoran he curses you with a mark of branding!");
		SendModEventMark(player, "Malkoran", "Branding", TAT_BRANDING);
	}

	void QISanguineInteraction1() {
		if (!settings.enableQISanguine) { return; }
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

		auto mark = GetLewdMark();
		if (mark > 0) {
			RemoveLewdMark();
		}
		AddLewdMark(TAT_NUDITY);
		SetEffectMagnitude(NUDITY_EFFECT, 100);

		SendModEventMark(player, "Sanguine", "Nudity", TAT_NUDITY);
		Util::ExecuteWithDelay(4s, [] {PlayerMessage("As you awaken you notice that you're covered in chains and have a strange mark on you. Hopefully Sam can fix this..."); });
	}

	void QISanguineInteractionEnd() {
		if (!settings.enableQISanguine) { return; }
		RE::TESKey* magic_key = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESKey>(MAGIC_KEY, "Devious Curses.esp");
		auto player = RE::PlayerCharacter::GetSingleton();

		player->AddObjectToContainer((RE::TESBoundObject*)magic_key, nullptr, 1, nullptr);

		auto mark = GetLewdMark();
		if (mark == TAT_NUDITY) {
			RemoveLewdMark();
		}

		PlayerMessage(fmt::format("Now that your wild adventure with Sanguine is over, he gives you a magic key{}!", (mark == TAT_NUDITY) ? " and removes your nudity mark" : ""));
	}

	void QIPotemaInteraction(); // Add a curse during the potema questline. Sugestion was to have a curse that periodically summons devices. Gets stronger when fighting potema??

	void QIMGInteraction1() {
		if (!settings.enableQISaarthal) { return; }
		RE::TESObjectARMO* amulet = RE::TESForm::LookupByID(0x233D0)->As<RE::TESObjectARMO>();
		auto player = RE::PlayerCharacter::GetSingleton();
		if (OppSummonerCollarEvent("", false)) {
			player->RemoveItem(amulet, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr, nullptr, nullptr);
			PlayerMessage("Strange magic interacts with the amulet transforming it into a collar!");
		}
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
	}

	void QICheckObjectActivation(RE::TESObjectREFR* object) {
		if (!settings.enableQuestInteractions) { return; }

		RE::TESObjectARMO* amulet = RE::TESForm::LookupByID(0x233D0)->As<RE::TESObjectARMO>();
		if (object->formID == 0xbc8b8 && object->GetBaseObject()->formID == 0x21513 && ActorIsWearingDevice(RE::PlayerCharacter::GetSingleton(), amulet)) {
			QIMGInteraction1();
		}
	}
}