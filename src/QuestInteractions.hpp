#pragma once

#include "O_Devices.hpp"
#include "tats.hpp"

using namespace SKSE;

namespace DCURSES {
	static constexpr auto QUEST_DA01 = 0x28AD6;
	static constexpr auto QUEST_DA09 = 0x4E4E1;
	static constexpr auto QUEST_DA14 = 0x1BB9B;
	static constexpr auto QUEST_DA15 = 0x2AC68;

	static constexpr auto QUEST_C01 = 0x6E803;
	static constexpr auto QUEST_C03 = 0x1CEF4;

	static constexpr auto QUEST_MG04 = 0x1F254;

	static constexpr auto QUEST_TG06 = 0x21552;
	static constexpr auto QUEST_TG08A = 0x57F99;

	static constexpr auto QUEST_MQ201 = 0x35D5F;
	static constexpr auto QUEST_MGRAppBrelyna = 0xC0416;

	static constexpr auto QUEST_MS14 = 0x25F3E;
	static constexpr auto QUEST_MS06START = 0x93807;

	static constexpr auto QUEST_FREEFORMRIFTEN18 = 0x5B3A5;

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

	void QIMGBrelyna1() {
		if (!settings.enableQIBrelyna || settings.eventLewdMarkWeight == 0) { return; }
		Util::ExecuteWithDelay(1s, [] {
			if (DoLewdMarkEvent("", Util::randomDouble(0.4, 0.9))) {
				PlayerMessage(Translator(Translation::QIBrelyna));
			}
		});
		
	}

	void QIMGBrelyna2() {
		if (!settings.enableQIBrelyna || settings.petSuitWeight == 0) { return; }
		auto player = RE::PlayerCharacter::GetSingleton();

		auto suit = GetWornInventoryDeviceByKeyword(player, "zad_DeviousSuit");
		auto bondage = GetWornInventoryDeviceByKeyword(player, "zad_DeviousHeavyBondage");
		if (!suit && !bondage) {
			auto dev = GetRandomDevice(&devices.petSuits);
			if (dev.has_value()) {
				ScriptingManager().LockDevice(player, (*dev).inv, true);
			}
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

	void QITrinityRestored() {
		if (!settings.enableQITrinityRestored) { return; }

		if (OppNocturnalPiercingEvent("")) {
			PlayerMessage(Translator(Translation::QITrinityRestored));
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

	void QILaidToRest() {
		if (!settings.enableQILaidToRest) { return; }

		auto player = RE::PlayerCharacter::GetSingleton();

		if (DoStandardEvent(player, false, "", "(red & (leather | (lustr & belt))) | (piercing & shock) | (plug & (primitive | iron))", 20, { "zad_DeviousHeavyBondage", "zad_DeviousBlindfold", "zad_DeviousHood", "zad_DeviousSuit" })) {
			PlayerMessage(Translator(Translation::QILaidToRest));
		}
	}
	void QICriedWolf() {
		if (!settings.enableQICriedWolf) { return; }

		std::thread{ [] {
			auto player = RE::PlayerCharacter::GetSingleton();
			while (player->IsInCombat()) {
				std::this_thread::sleep_for(250ms);
			}
			Util::ExecuteWithDelay(5ms, [player]{
				if (DoStandardEvent(player, false, "", "(steel | iron | rust) | (piercing & (charge | punish | common))", 20)) {
					PlayerMessage(Translator(Translation::QICriedWolf));
				}
			});
		} }.detach();
	}

	void QIRingmaker() {
		if (!settings.enableQILaidToRest) { return; }

		auto player = RE::PlayerCharacter::GetSingleton();
		auto scriptingManager = ScriptingManager();

		RE::TESObjectARMO* lucky_piercings = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LUCKY_PIERCINGS, "Devious Curses.esp");
		auto collar = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DDX_GOLDEN_COLLAR, "Devious Devices - Expansion.esm");
		auto cuffsA = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DDX_GOLDEN_CUFFS_ARMS, "Devious Devices - Expansion.esm");
		auto cuffsL = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DDX_GOLDEN_CUFFS_LEGS, "Devious Devices - Expansion.esm");
		auto piercings = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(CHASTITY_PIERCING_GOLD8, "Devious Chastity Piercing.esp");

		scriptingManager.LockDevice(player, lucky_piercings, true);
		scriptingManager.LockDevice(player, collar, true);
		scriptingManager.LockDevice(player, cuffsA, true);
		scriptingManager.LockDevice(player, cuffsL, true);
		if (piercings )scriptingManager.LockDevice(player, piercings, true);
		PlayerMessage(Translator(Translation::QIRingmaker));
	}

	void QICheckQuestStage(RE::FormID quest_id, uint16_t stage) {
		if (!settings.enableQuestInteractions) { return; }

		auto quest = RE::TESForm::LookupByID(quest_id)->As<RE::TESQuest>();
		if (!quest) { return; }

		if (quest_id == QUEST_DA09) {
			if (stage == 410) QIMeridiaInteraction();
		}
		if (quest_id == QUEST_DA14) {
			if (stage == 5) QISanguineInteraction1();
			if (stage == 200) QISanguineInteractionEnd();
		}
		if (quest_id == QUEST_TG06) {
			if (stage == 50) QIDwemerMuseum();
		}
		if (quest_id == QUEST_C03) {
			if (stage == 25) QICompanionsCollarJoke();
		}
		if (quest_id == QUEST_DA01) {
			if (stage == 50) QIBlackStarTouch();
		}
		if (quest_id == QUEST_MQ201) {
			if (stage == 100) QIMainDiplomaticImmunity();
		}
		if (quest_id == QUEST_DA15) {
			if (stage == 90) QIMindOfMadness();
		}
		if (quest_id == QUEST_MS14) {
			if (stage == 95) QILaidToRest();
		}
		if (quest_id == QUEST_MS06START) {
			if (stage == 100) QICriedWolf();
		}
		if (quest_id == QUEST_FREEFORMRIFTEN18) {
			if (stage == 200) QIRingmaker();
		}
		if (quest_id == QUEST_TG08A) {
			if (stage == 60) QITrinityRestored();
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

	void QIOnSpellCast(const RE::TESSpellCastEvent* spellEvent) {
		auto actor = spellEvent->object->As<RE::Actor>();
		auto player = RE::PlayerCharacter::GetSingleton();
		if (settings.enableQuestInteractions && actor && actor != player) {
			if (spellEvent->spell == 0xEA5EA) {
				QIMGBrelyna1();
			}
			if (spellEvent->spell == 0x106B10) {
				QIMGBrelyna2();
			}
		}
	}
}