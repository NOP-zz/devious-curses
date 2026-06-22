#include "QuestInteractions.h"

#include "Devices.h"
#include "Events.h"
#include "OppDevices.h"
#include "tats.h"
#include "Settings.h"
#include "Translation.h"
#include "Scripting.h"
#include "Utils.h"
#include "Serializer.h"

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

	static constexpr auto QUEST_FAVOR001 = 0x403B0;

	static constexpr auto QUEST_FREEFORMRIFTEN18 = 0x5B3A5;


	void QIMeridiaInteraction() {
		if (!Settings::GetSingleton()->enableQIMalkoran) { return; }

		auto mark = GetLewdMark();
		if (mark == MARK::TAT_BRANDING) {
			return;
		}
		if (mark != MARK::TAT_NONE) {
			RemoveLewdMark();
		}

		AddLewdMark(MARK::TAT_BRANDING);
		SetMarkToDefaultSettings(MARK::TAT_BRANDING);
		PlayerMessage(Translator(Translation::QIMalkoranCurse), Settings::GetSingleton()->surpriseMode);
		if (Settings::GetSingleton()->eventVisualEffects) { ScriptingManager().PlaySummonVFX(RE::PlayerCharacter::GetSingleton()); }
	}

	void QISanguineInteraction1() {
		if (!Settings::GetSingleton()->enableQISanguine) { return; }
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

		DoStandardEvent(player, false, "", "(rust | (iron & belt))", 20, 1, { "zad_DeviousGag", "zad_DeviousHeavyBondage", "zad_DeviousBondageMittens", "zad_DeviousPlugVaginal", "zad_DeviousPlugAnal" });

		auto mark = GetLewdMark();
		if (mark != MARK::TAT_NONE) {
			RemoveLewdMark();
		}
		AddLewdMark(MARK::TAT_NUDITY);
		SetMarkToDefaultSettings(MARK::TAT_NUDITY);

		Util::ExecuteWithDelay(4s, [] {
			//PlayerMessage("As you awaken you notice that you're covered in chains and have a strange mark on you. Hopefully Sam can fix this..."); 
			PlayerMessage(Translator(Translation::QISanguineStart), Settings::GetSingleton()->surpriseMode);
		});
	}

	void QISanguineInteractionEnd() {
		if (!Settings::GetSingleton()->enableQISanguine) { return; }
		RE::TESKey* magic_key = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(MAGIC_KEY, "Devious Curses.esp");
		auto player = RE::PlayerCharacter::GetSingleton();

		player->AddObjectToContainer(skyrim_cast<RE::TESBoundObject*>(magic_key), nullptr, 1, nullptr);

		auto mark = GetLewdMark();

		//PlayerMessage(fmt::format("Now that your wild adventure with Sanguine is over, he gives you a magic key{}!", (mark == MARK::TAT_NUDITY) ? " and removes your nudity mark" : ""));
		if (mark == MARK::TAT_NUDITY) {
			PlayerMessage(Translator(Translation::QISanguineKeyMark));
			RemoveLewdMark();
			if (Settings::GetSingleton()->eventVisualEffects) { ScriptingManager().PlaySummonVFX(player); }
		}
		else {
			PlayerMessage(Translator(Translation::QISanguineKey));
		}
	}

	void QIBlackStarTouch() {
		if (!Settings::GetSingleton()->enableQIBlackStar) { return; }

		if (DoStandardEvent(RE::PlayerCharacter::GetSingleton(), false, "", "(plug & (chaos | black | filled | grand)) | (belt & (iron | rust)) | (piercing & gem)", 20)) {
			PlayerMessage(Translator(Translation::QIBlackStarEquip), Settings::GetSingleton()->surpriseMode);
		}
	}

	void QIMindOfMadness() {
		if (!Settings::GetSingleton()->enableQIMindOfMadness) { return; }

		if (OppMadnessPlugEvent("")) {
			Util::ExecuteWithDelay(2s, [] {
				PlayerMessage(Translator(Translation::QIMindOfMadness), Settings::GetSingleton()->surpriseMode);
				});
		}
	}

	void QIMainDiplomaticImmunity() {
		if (!Settings::GetSingleton()->enableQIThalmorEmbassy) { return; }

		RE::TESObjectARMO* clothes = RE::TESForm::LookupByID(0xE40DF)->As<RE::TESObjectARMO>();
		RE::TESObjectARMO* boots = RE::TESForm::LookupByID(0xE40DE)->As<RE::TESObjectARMO>();
		auto player = RE::PlayerCharacter::GetSingleton();

		if (
			DoStandardEvent(player, false, "", "leather & red & (dress | cuffs | boots | gloves | collar)) & !pony", 20, 4, { "zad_DeviousHeavyBondage", "zad_DeviousBondageMittens", "zad_DeviousGag", "zad_DeviousBlindfold" }) ||
			DoStandardEvent(player, false, "", "", 20, 4, { "zad_DeviousHeavyBondage", "zad_DeviousBondageMittens", "zad_DeviousGag", "zad_DeviousBlindfold" }) ||
			DoStandardEvent(player, false, "", "!!", 20, 4, { "zad_DeviousHeavyBondage", "zad_DeviousBondageMittens", "zad_DeviousGag", "zad_DeviousBlindfold" })
			) {
			player->RemoveItem(clothes, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr, nullptr, nullptr);
			player->RemoveItem(boots, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr, nullptr, nullptr);
			PlayerMessage(Translator(Translation::QIDiplomaticImmunity), Settings::GetSingleton()->surpriseMode);
		}
	}

	void QIMGInteraction1() {
		if (!Settings::GetSingleton()->enableQISaarthal) { return; }
		RE::TESObjectARMO* amulet = RE::TESForm::LookupByID(0x233D0)->As<RE::TESObjectARMO>();
		auto player = RE::PlayerCharacter::GetSingleton();

		if (OppSummonerCollarEvent("")) {
			player->RemoveItem(amulet, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr, nullptr, nullptr);
			//PlayerMessage("Strange magic interacts with the amulet transforming it into a collar!");
			PlayerMessage(Translator(Translation::QISaarthal), Settings::GetSingleton()->surpriseMode);
		}
	}

	void QIMGBrelyna1() {
		if (!Settings::GetSingleton()->enableQIBrelyna || Settings::GetSingleton()->eventLewdMarkWeight == 0) { return; }
		Util::ExecuteWithDelay(1s, [] {
			if (DoLewdMarkEvent("", Util::random(0.4, 0.9))) {
				PlayerMessage(Translator(Translation::QIBrelyna), Settings::GetSingleton()->surpriseMode);
			}
		});
	}

	void QIMGBrelyna2() {
		if (!Settings::GetSingleton()->enableQIBrelyna || Settings::GetSingleton()->petSuitWeight == 0) { return; }
		auto player = RE::PlayerCharacter::GetSingleton();

		auto suit = GetWornInventoryDeviceByKeyword(player, "zad_DeviousSuit");
		auto bondage = GetWornInventoryDeviceByKeyword(player, "zad_DeviousHeavyBondage");
		if (!suit && !bondage) {
			auto dev = GetRandomDevice(&Devices::GetSingleton()->petSuits);
			if (dev.has_value()) {
				ScriptingManager().LockDevice(player, (*dev).inv, true);
			}
		}
	}

	void QIDwemerMuseum() {
		if (!Settings::GetSingleton()->enableQIDwemerMuseum) { return; }

		auto mark = GetLewdMark();
		if (mark != MARK::TAT_NONE) {
			RemoveLewdMark();
		}
		AddLewdMark(MARK::TAT_HEAT);

		if (OppDwarvenCuirassEvent("", true)) {
			PlayerMessage(Translator(Translation::QIDwemerMuseumCurias), Settings::GetSingleton()->surpriseMode);
		}
		else {
			PlayerMessage(Translator(Translation::QIDwemerMuseum), Settings::GetSingleton()->surpriseMode);
		}
	}

	void QITrinityRestored() {
		if (!Settings::GetSingleton()->enableQITrinityRestored) { return; }

		if (OppNocturnalPiercingEvent("")) {
			PlayerMessage(Translator(Translation::QITrinityRestored), Settings::GetSingleton()->surpriseMode);
		}
	}

	void QICompanionsProvingHonor() {
		if (!Settings::GetSingleton()->enableQIProvingHonor) { return; }

		if (DoStandardEvent(RE::PlayerCharacter::GetSingleton(), false, "", "silver", 20, 1, { "zad_DeviousHeavyBondage" })) {
			PlayerMessage(Translator(Translation::QIProvingHonor), Settings::GetSingleton()->surpriseMode);
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
		if (!Settings::GetSingleton()->enableQILaidToRest) { return; }

		auto player = RE::PlayerCharacter::GetSingleton();

		if (DoStandardEvent(player, false, "", "(red & (leather | (lustr & belt))) | (piercing & shock) | (plug & (primitive | iron))", 20, 1, { "zad_DeviousHeavyBondage", "zad_DeviousBlindfold", "zad_DeviousHood", "zad_DeviousSuit" })) {
			PlayerMessage(Translator(Translation::QILaidToRest), Settings::GetSingleton()->surpriseMode);
		}
	}

	void QICriedWolf() {
		if (!Settings::GetSingleton()->enableQICriedWolf) { return; }

		std::thread{ [] {
			auto player = RE::PlayerCharacter::GetSingleton();
			while (player->IsInCombat()) {
				std::this_thread::sleep_for(250ms);
			}
			Util::ExecuteWithDelay(5ms, [player] {
				if (DoStandardEvent(player, false, "", "(steel | iron | rust) | (piercing & (charge | punish | common))", 20)) {
					PlayerMessage(Translator(Translation::QICriedWolf), Settings::GetSingleton()->surpriseMode);
				}
			});
		} }.detach();
	}

	void QIRingmaker() {
		if (!Settings::GetSingleton()->enableQILaidToRest) { return; }

		auto player = RE::PlayerCharacter::GetSingleton();
		auto scriptingManager = ScriptingManager();

		RE::TESObjectARMO* lucky_piercings = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LUCKY_PIERCINGS, "Devious Curses.esp");
		auto collar = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DDX_GOLDEN_COLLAR, "Devious Devices - Expansion.esm");
		auto cuffsA = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DDX_GOLDEN_CUFFS_ARMS, "Devious Devices - Expansion.esm");
		auto cuffsL = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(DDX_GOLDEN_CUFFS_LEGS, "Devious Devices - Expansion.esm");
		auto piercings = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(CHASTITY_PIERCING_GOLD8, "Devious Chastity Piercing.esp");

		player->AddObjectToContainer(skyrim_cast<RE::TESBoundObject*>(lucky_piercings), nullptr, 1, nullptr);
		scriptingManager.LockDevice(player, lucky_piercings, true);
		scriptingManager.LockDevice(player, collar, true);
		scriptingManager.LockDevice(player, cuffsA, true);
		scriptingManager.LockDevice(player, cuffsL, true);
		if (piercings)scriptingManager.LockDevice(player, piercings, true);
		PlayerMessage(Translator(Translation::QIRingmaker));
	}

	void QIDelivery1() {
		if (!Settings::GetSingleton()->enableQIDelivery) { return; }

		auto player = RE::PlayerCharacter::GetSingleton();

		std::thread{ [player] {
			while (RE::UI::GetSingleton()->IsMenuOpen("Dialogue Menu")) {
				std::this_thread::sleep_for(100ms);
			}
			if (DoStandardEvent(player, false, "", "pony | (piercing & nipple) | plug | belt | cage", 7, 4, { "zad_DeviousHeavyBondage", "zad_DeviousBlindfold", "zad_DeviousGag", "zad_DeviousHood", "zad_DeviousSuit" }) ||
				DoStandardEvent(player, false, "", "collar | cuffs | harness | boots | (piercing & nipple) | plug | belt | cage", 7, 4, { "zad_DeviousHeavyBondage", "zad_DeviousBlindfold", "zad_DeviousGag", "zad_DeviousHood", "zad_DeviousSuit" })) {
				auto quest = StaticDataHolder::GetSingleton()->LookupForm<RE::TESQuest>(QUEST_FAVOR001, "Skyrim.esm");
				auto giver = skyrim_cast<RE::BGSRefAlias*>(quest->aliases[1])->GetActorReference();
				auto target = skyrim_cast<RE::BGSRefAlias*>(quest->aliases[2])->GetActorReference();
				player->EndDialogue();
				giver->EndDialogue();
				PlayerMessage(Translator(Translation::QIDeliveryStart, giver->GetName(), target->GetName()));
			}
		} }.detach();
	}

	void QIDelivery2() {
		if (!Settings::GetSingleton()->enableQIDelivery) { return; }

		auto player = RE::PlayerCharacter::GetSingleton();

		auto quest = StaticDataHolder::GetSingleton()->LookupForm<RE::TESQuest>(QUEST_FAVOR001, "Skyrim.esm");
		auto target_name = skyrim_cast<RE::BGSRefAlias*>(quest->aliases[2])->GetActorReference()->GetName();
		auto item_name = skyrim_cast<RE::BGSRefAlias*>(quest->aliases[4])->GetReference()->GetName();

		std::thread{ [player, target_name, item_name] {
			while (RE::UI::GetSingleton()->IsMenuOpen("Dialogue Menu")) {
				std::this_thread::sleep_for(100ms);
			}

			if (GetVisibleDeviceCount(player) >= 4) {
				RE::TESKey* magicKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(MAGIC_KEY, "Devious Curses.esp");
				player->AddObjectToContainer(skyrim_cast<RE::TESBoundObject*>(magicKey), nullptr, 1, nullptr);
				PlayerMessage(Translator(Translation::QIDeliveryEnd, item_name, target_name));
			}
			else {
				if (DoStandardEvent(player, false, "", "", 10, 5, { "zad_DeviousHeavyBondage", "zad_DeviousSuit" })) {
					PlayerMessage(Translator(Translation::QIDeliveryEndBad, target_name));
				}
			}
		} }.detach();
	}

	void QIBarenziah(RE::TESObjectREFR* object) {
		if (!Settings::GetSingleton()->enableQIBarenziah) { return; }

		auto player = RE::PlayerCharacter::GetSingleton();
		auto settings = Settings::GetSingleton();

		if (GetWornDeviceCount(player) > settings->restraintCap) { return; }

		log::trace("Activated {}", object->GetName());

		DoEvent(false, object->GetName());
	}

	void QICheckQuestStage(RE::FormID quest_id, uint16_t stage) {
		if (!Settings::GetSingleton()->enableQuestInteractions) { return; }

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
		if (quest_id == QUEST_FAVOR001) {
			if (stage == 10) QIDelivery1();
			if (stage == 20) QIDelivery2();
		}

		//log::trace("Quest {:X} stage {}", quest_id, stage);
	}

	void QICheckObjectActivation(RE::TESObjectREFR* object) {
		if (!Settings::GetSingleton()->enableQuestInteractions) { return; }

		RE::TESObjectARMO* amulet = RE::TESForm::LookupByID(0x233D0)->As<RE::TESObjectARMO>();
		if (object->formID == 0xbc8b8 && object->GetBaseObject()->formID == 0x21513 && ActorIsWearingDevice(RE::PlayerCharacter::GetSingleton(), amulet)) {
			QIMGInteraction1();
		}

		if (object->formID == 0x236f5 && object->GetBaseObject()->formID == 0x21513 && !IsObjectRefKnown(object->formID) && !RE::TESForm::LookupByID(QUEST_C01)->As<RE::TESQuest>()->IsCompleted()) {
			QICompanionsProvingHonor();
			SetObjectRefKnown(object->formID);
		}

		if (object->GetBaseObject()->formID == 0x7F8E1) {
			QIBarenziah(object);
		}
	}

	void QIOnSpellCast(const RE::TESSpellCastEvent* spellEvent) {
		auto actor = spellEvent->object->As<RE::Actor>();
		auto player = RE::PlayerCharacter::GetSingleton();
		if (Settings::GetSingleton()->enableQuestInteractions && actor && actor != player) {
			if (spellEvent->spell == 0xEA5EA) {
				QIMGBrelyna1();
			}
			if (spellEvent->spell == 0x106B10) {
				QIMGBrelyna2();
			}
		}
	}
}