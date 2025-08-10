#pragma once

#include "O_Devices.hpp"
#include "tats.hpp"

using namespace SKSE;

namespace DCURSES {
	constexpr auto QUEST_DA01 = 0x28AD6;
	constexpr auto QUEST_DA09 = 0x4E4E1;
	constexpr auto QUEST_DA14 = 0x1BB9B;
	constexpr auto QUEST_DA15 = 0x2AC68;

	constexpr auto QUEST_C01 = 0x6E803;
	constexpr auto QUEST_C03 = 0x1CEF4;

	constexpr auto QUEST_MG04 = 0x1F254;

	constexpr auto QUEST_TG06 = 0x21552;

	constexpr auto QUEST_MQ201 = 0x35D5F;

	void QIMeridiaInteraction() {
		if (!settings.enableQIMalkoran) { return; }

		auto player = RE::PlayerCharacter::GetSingleton();
		auto mark = GetLewdMark();
		if (mark == MARK::TAT_BRANDING) {
			return;
		}
		if (mark != MARK::TAT_NONE) {
			RemoveLewdMark();
		}

		AddLewdMark(MARK::TAT_BRANDING);
		AIContextAddBrandingMark();
		SetEffectMagnitude(BRANDING_EFFECT, static_cast<float>(GetTattooCount(player)));
		//PlayerMessage("As you kill Malkoran he curses you with a mark of branding!");
		PlayerMessage(Translator(Translation::QIMalkoranCurse));
	}

	void QISanguineInteraction1() {
		if (!settings.enableQISanguine) { return; }
		auto player = RE::PlayerCharacter::GetSingleton();

		auto scriptManager = ScriptingManager();

		auto belt = GetWornInventoryDeviceByKeyword(player, "zad_DeviousBelt");
		if (belt) {
			scriptManager.UnlockDevice(player, belt);
		}

		auto plug = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DDX_RUSTY_PEAR_ANAL_SIGN, "Devious Devices - Expansion.esm");
		scriptManager.LockDevice(player, plug, true);
		plug = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DDX_RUSTY_PEAR_VAGINAL, "Devious Devices - Expansion.esm");
		scriptManager.LockDevice(player, plug, true);

		DoStandardEvent(player, false, "", "(rust | (iron & belt))", 20, { "zad_DeviousGag", "zad_DeviousHeavyBondage", "zad_DeviousBondageMittens", "zad_DeviousPlugVaginal", "zad_DeviousPlugAnal" });

		auto mark = GetLewdMark();
		if (mark != MARK::TAT_NONE) {
			RemoveLewdMark();
		}
		AddLewdMark(MARK::TAT_NUDITY);
		AIContextAddNudityMark();
		SetEffectMagnitude(NUDITY_EFFECT, static_cast<float>(settings.LMNudityTalkTimes));

		Util::ExecuteWithDelay(4s, [] {
			//PlayerMessage("As you awaken you notice that you're covered in chains and have a strange mark on you. Hopefully Sam can fix this..."); 
			PlayerMessage(Translator(Translation::QISanguineStart));
		});
	}

	void QISanguineInteractionEnd() {
		if (!settings.enableQISanguine) { return; }
		RE::TESKey* magic_key = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(MAGIC_KEY, "Devious Curses.esp");
		auto player = RE::PlayerCharacter::GetSingleton();

		player->AddObjectToContainer((RE::TESBoundObject*)magic_key, nullptr, 1, nullptr);

		auto mark = GetLewdMark();
		if (mark == MARK::TAT_NUDITY) {
			RemoveLewdMark();
			AIContextRemoveLewdMark();
		}

		//PlayerMessage(fmt::format("Now that your wild adventure with Sanguine is over, he gives you a magic key{}!", (mark == MARK::TAT_NUDITY) ? " and removes your nudity mark" : ""));
		if (mark == MARK::TAT_NUDITY) {
			PlayerMessage(Translator(Translation::QISanguineKeyMark));
		}
		else {
			PlayerMessage(Translator(Translation::QISanguineKey));
		}
	}

	void QIBlackStarTouch() {
		if (!settings.enableQIBlackStar) { return; }

		if (DoStandardEvent(RE::PlayerCharacter::GetSingleton(), false, "", "(plug & (chaos | black | filled | grand)) | (belt & (iron | rust)) | (piercing & gem)", 20, {})) {
			PlayerMessage(Translator(Translation::QIBlackStarEquip));
		}
	}

	void QIMindOfMadness() {
		if (!settings.enableQIMindOfMadness) { return; }

		if (OppMadnessPlugEvent("")) {
			Util::ExecuteWithDelay(2s, [] {
				PlayerMessage(Translator(Translation::QIMindOfMadness));
			});
		}
	}

	//void QIPotemaInteraction(); // Add a curse during the potema questline. Sugestion was to have a curse that periodically summons devices. Gets stronger when fighting potema??

	void QIMainDiplomaticImmunity() {
		if (!settings.enableQIThalmorEmbassy) { return; }

		RE::TESObjectARMO* clothes = RE::TESForm::LookupByID(0xE40DF)->As<RE::TESObjectARMO>();
		RE::TESObjectARMO* boots = RE::TESForm::LookupByID(0xE40DE)->As<RE::TESObjectARMO>();
		auto player = RE::PlayerCharacter::GetSingleton();

		if (
			DoStandardEvent(player, false, "", "leather & red & (dress | cuffs | boots | gloves | collar)) & !pony", 20, {"zad_DeviousHeavyBondage", "zad_DeviousBondageMittens", "zad_DeviousGag", "zad_DeviousBlindfold"}) || 
			DoStandardEvent(player, false, "", "", 20, { "zad_DeviousHeavyBondage", "zad_DeviousBondageMittens", "zad_DeviousGag", "zad_DeviousBlindfold" })
			) {
			player->RemoveItem(clothes, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr, nullptr, nullptr);
			player->RemoveItem(boots, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr, nullptr, nullptr);
			PlayerMessage(Translator(Translation::QIDiplomaticImmunity));
		}
	}

	void QIMGInteraction1() {
		if (!settings.enableQISaarthal) { return; }
		RE::TESObjectARMO* amulet = RE::TESForm::LookupByID(0x233D0)->As<RE::TESObjectARMO>();
		auto player = RE::PlayerCharacter::GetSingleton();

		if (OppSummonerCollarEvent("")) {
			player->RemoveItem(amulet, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr, nullptr, nullptr);
			//PlayerMessage("Strange magic interacts with the amulet transforming it into a collar!");
			PlayerMessage(Translator(Translation::QISaarthal));
		}
	}

	void QIDwemerMuseum() {
		if (!settings.enableQIDwemerMuseum) { return; }

		auto mark = GetLewdMark();
		if (mark != MARK::TAT_NONE) {
			RemoveLewdMark();
		}
		AddLewdMark(MARK::TAT_HEAT);

		if (OppDwarvenCuirassEvent("", true)) {
			PlayerMessage(Translator(Translation::QIDwemerMuseumCurias));
		}
		else {
			PlayerMessage(Translator(Translation::QIDwemerMuseum));
		}
	}

	void QICompanionsProvingHonor() {
		if (!settings.enableQIProvingHonor) { return; }

		if (DoStandardEvent(RE::PlayerCharacter::GetSingleton(), false, "", "silver", 20, {"zad_DeviousHeavyBondage"})) {
			PlayerMessage(Translator(Translation::QIProvingHonor));
		}
	}

	void QICompanionsCollarJoke() {
		auto player = RE::PlayerCharacter::GetSingleton();

		auto collar = GetWornInventoryDeviceByKeyword(player, "zad_DeviousCollar");
		if (!collar) {
			auto puppy = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DDX_PUPPY_COLLAR, "Devious Devices - Expansion.esm");
			ScriptingManager().LockDevice(player, puppy, true);
		}
	}

	void QICheckQuestStage(RE::FormID quest_id, uint16_t stage) {
		if (!settings.enableQuestInteractions) { return; }

		auto quest = RE::TESForm::LookupByID(quest_id)->As<RE::TESQuest>();

		if (quest == RE::TESForm::LookupByID(QUEST_DA09)->As<RE::TESQuest>()) {
			if (stage == 410) QIMeridiaInteraction();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_DA14)->As<RE::TESQuest>()) {
			if (stage == 5) QISanguineInteraction1();
			if (stage == 200) QISanguineInteractionEnd();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_TG06)->As<RE::TESQuest>()) {
			if (stage == 50) QIDwemerMuseum();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_C03)->As<RE::TESQuest>()) {
			if (stage == 25) QICompanionsCollarJoke();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_DA01)->As<RE::TESQuest>()) {
			if (stage == 50) QIBlackStarTouch();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_MQ201)->As<RE::TESQuest>()) {
			if (stage == 100) QIMainDiplomaticImmunity();
		}
		if (quest == RE::TESForm::LookupByID(QUEST_DA15)->As<RE::TESQuest>()) {
			if (stage == 90) QIMindOfMadness();
		}
	}

	void QICheckObjectActivation(RE::TESObjectREFR* object) {
		if (!settings.enableQuestInteractions) { return; }

		RE::TESObjectARMO* amulet = RE::TESForm::LookupByID(0x233D0)->As<RE::TESObjectARMO>();
		if (object->formID == 0xbc8b8 && object->GetBaseObject()->formID == 0x21513 && ActorIsWearingDevice(RE::PlayerCharacter::GetSingleton(), amulet)) {
			QIMGInteraction1();
		}

		if (object->formID == 0x236f5 && object->GetBaseObject()->formID == 0x21513 && !IsObjectRefKnown(object->formID) && !RE::TESForm::LookupByID(QUEST_C01)->As<RE::TESQuest>()->IsCompleted()) {
			QICompanionsProvingHonor();
			SetObjectRefKnown(object->formID);
		}
	}
}