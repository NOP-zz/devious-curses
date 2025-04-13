#pragma once

#include "tats.hpp"

namespace DCURSES {
	
	constexpr auto QUEST_MG04 = 0x1F254;
	constexpr auto QUEST_MG07 = 0x1F257;
	constexpr auto QUEST_MG08 = 0x1F258;

	constexpr auto QUEST_TG02 = 0x2154E;
	constexpr auto QUEST_TG03 = 0x2154F;
	constexpr auto QUEST_TG04 = 0x21550;
	constexpr auto QUEST_TG06 = 0x21552;
	constexpr auto QUEST_TG07 = 0x21553;
	constexpr auto QUEST_TG08A = 0x57F99;
	constexpr auto QUEST_TG09 = 0x21555;

	constexpr auto QUEST_C01 = 0x6E803;
	constexpr auto QUEST_C05 = 0x6e805;

	constexpr auto QUEST_DA14 = 0x1BB9B;

	void QIMeridiaInteraction() {
		CloseContinerMenus();
		auto player = RE::PlayerCharacter::GetSingleton();
		auto mark = GetLewdMark(player);
		if (mark > 0) {
			RemoveLewdMark(player, mark);
		}

		AddLewdMark(player, TAT_MERIDIA, 0x220022);
		counters.clock_QIMeridia = static_cast<uint64_t>(Util::randomDouble(10, 15) * -60.0);
		PlayerMessage("As you kill Malkoran he curses you with an unknown mark!");
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

		DoStandardEvent(false, "", "(rust | (iron & belt))", 20, {"zad_DeviousGag", "zad_DeviousHeavyBondage", "zad_DeviousBondageMittens", "zad_DeviousPlugVaginal", "zad_DeviousPlugAnal"});
		AddLewdMark(player, TAT_NUDITY, 0x990000);
		counters.LMPeopleTalked = -100;
	}

	void QISanguineInteractionEnd() {
		RE::TESKey* magic_key = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESKey>(MAGIC_KEY, "Devious Curses.esp");
		auto player = RE::PlayerCharacter::GetSingleton();

		player->AddObjectToContainer((RE::TESBoundObject*)magic_key, nullptr, 1, nullptr);

		auto mark = GetLewdMark(player);
		if (mark == TAT_NUDITY) {
			RemoveLewdMark(player, mark);
		}
		PlayerMessage("Now that your wild adventure with Sanguine is over, he gives you a magic key!");
	}

	RE::Actor* QIMGGetSummonedAtronach();

	void QIMGSummonAtronach(bool drainMagic = true) {
		if (!settings.enableQuestInteractions) { return; }
		auto player = RE::PlayerCharacter::GetSingleton();

		auto summon = QIMGGetSummonedAtronach();
		if (summon) {
			summon->KillImmediate();
		}

		RE::SpellItem* conjure_atronach = RE::TESDataHandler::GetSingleton()->LookupForm<RE::SpellItem>(SAARTHAL_SUMMON_SPELL, "Devious Curses.esp");
		//conjure_atronach->data.delivery = RE::MagicSystem::Delivery::kSelf;
		RE::MagicCaster* caster = player->GetMagicCaster(RE::MagicSystem::CastingSource::kOther);
		caster->CastSpellImmediate(conjure_atronach, false, player, 5.0f, false, 0.0f, nullptr);
		//conjure_atronach->data.delivery = RE::MagicSystem::Delivery::kTargetLocation;
		auto magic = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kMagicka);
		if (drainMagic) player->AsActorValueOwner()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kMagicka, -magic);
	}

	RE::Actor* QIMGGetSummonedAtronach() {
		if (!settings.enableQuestInteractions) { return nullptr; }
		auto commandedActors = getPlayerCommandedActors();
		for (auto summon : commandedActors) {
			if (summon->HasKeywordString("DCurses_MGSummoned")) {
				auto playerDistance = RE::PlayerCharacter::GetSingleton()->GetPosition().GetDistance(summon->GetPosition());
				if (playerDistance > 10000) {
					QIMGSummonAtronach(false);
				}
				if (playerDistance < 250) {
					summon->SetCollision(false);
				}
				else {
					summon->SetCollision(true);
				}
				summon->SetAlpha(0.5f);
				return summon;
			}
		}
		return nullptr;
	}

	void QIMGInteraction1() {
		RE::TESObjectARMO* collar = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESObjectARMO>(SAARTHAL_COLLAR, "Devious Curses.esp");
		RE::TESObjectARMO* amulet = RE::TESForm::LookupByID(0x233D0)->As<RE::TESObjectARMO>();
		auto player = RE::PlayerCharacter::GetSingleton();

		player->RemoveItem(amulet, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr, nullptr, nullptr);
		LockDevice(player, collar, true);
		PlayerMessage("Strange magic interacts with the amulet transforming it into a collar!");
	}

	void QIMGInteraction2() {
		RE::TESObjectARMO* collar = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESObjectARMO>(SAARTHAL_COLLAR, "Devious Curses.esp");
		RE::TESObjectARMO* collarM = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESObjectARMO>(SAARTHAL_MCOLLAR, "Devious Curses.esp");
		auto player = RE::PlayerCharacter::GetSingleton();
		
		if (!ActorIsWearingDevice(player, collar)) { return; }

		RemoveQuestDevice(player, collar, DeviousDevicesAPI::g_API->GetDeviceRender(collar), true);
		LockDevice(player, collarM, true);
		PlayerMessage("As you enter Labyrinthian you feel your collar surge with power.");
	}

	void QIMGInteractionEnd() {
		RE::TESKey* collar_key = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESKey>(SAARTHAL_KEY, "Devious Curses.esp");
		//RE::TESObjectARMO* amulet = RE::TESForm::LookupByID(0x233D0)->As<RE::TESObjectARMO>();
		auto player = RE::PlayerCharacter::GetSingleton();

		RE::TESObjectARMO* collar = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESObjectARMO>(SAARTHAL_COLLAR, "Devious Curses.esp");
		RE::TESObjectARMO* collarM = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESObjectARMO>(SAARTHAL_MCOLLAR, "Devious Curses.esp");
		bool hasACollar = ActorIsWearingDevice(player, collarM) || ActorIsWearingDevice(player, collar);
		if (!hasACollar) { return; }

		player->AddObjectToContainer(collar_key, nullptr, 1, nullptr);
		//player->AddObjectToContainer(amulet, nullptr, 1, nullptr);
		PlayerMessage("As the magic from the Eye of Magnus fades you feel the power of the collar weaken.");
	}

	void QITGInteraction1() {
		CloseContinerMenus();
		auto player = RE::PlayerCharacter::GetSingleton();

		UndressActor(player);

		DoStandardEvent(false, "", "white", 3, {"zad_DeviousHeavyBondage", "zad_DeviousBelt", "zad_DeviousHarness", "zad_DeviousGag", "zad_DeviousBlindfold"});

		PlayerMessage("As you touch the note in the safe you feel a curse emerge from it!");
	}

	void QITGInteraction2() {
		CloseContinerMenus();
		auto player = RE::PlayerCharacter::GetSingleton();

		UndressActor(player);

		DoStandardEvent(true, "", "white | piercing", 6, { "zad_DeviousHeavyBondage", "zad_DeviousBelt", "zad_DeviousHarness"});

		PlayerMessage("Yet again as you touch the note you feel a curse emerge from it!");
	}

	void QITGInteraction3() {
		CloseContinerMenus();
		auto player = RE::PlayerCharacter::GetSingleton();

		UndressActor(player);

		DoStandardEvent(false, "", "white | (piercing & !chastity)", 8);

		PlayerMessage("As you touch the note you feel the same curse from before but even stronger!");
	}

	void QITGInteraction4() {
		CloseContinerMenus();
		auto player = RE::PlayerCharacter::GetSingleton();

		UndressActor(player);

		DoStandardEvent(false, "", "steel | (shock & piercing) | grand", 20, {"zad_DeviousHeavyBondage"});

		auto yoke = RE::TESDataHandler::GetSingleton()->LookupForm(DDX_STEEL_YOKE, "Devious Devices - Expansion.esm")->As<RE::TESObjectARMO>();
		LockDevice(player, yoke, true);

		PlayerMessage("You triggered a magic rune set by Calcelmo!");
	}

	void QITGInteraction5() {
		CloseContinerMenus();
		auto player = RE::PlayerCharacter::GetSingleton();

		UndressActor(player);

		auto hood = GetRandomDevice(&devices.hoodsBlockAll, {}, "red & (ebonite | rubber)");
		if (hood.has_value()) LockDevice(player, hood.value().inv, true);

		DoStandardEvent(false, "", "red & ebonite", 20, { "zad_DeviousHeavyBondage", "zad_DeviousHood", "zad_DeviousSuit"});

		auto catsuit = RE::TESDataHandler::GetSingleton()->LookupForm(DDX_RED_CATSUIT, "Devious Devices - Expansion.esm")->As<RE::TESObjectARMO>();
		LockDevice(player, catsuit, true);
		auto armbinder = RE::TESDataHandler::GetSingleton()->LookupForm(DDX_RED_ARMBINDER, "Devious Devices - Expansion.esm")->As<RE::TESObjectARMO>();
		LockDevice(player, armbinder, true);

		PlayerMessage("As you grab Mercer's plans, a strange red goo covers your body and solidifies!");
	}

	void QITGInteraction6() {
		CloseContinerMenus();
		auto player = RE::PlayerCharacter::GetSingleton();

		auto plug = RE::TESDataHandler::GetSingleton()->LookupForm(NOCTURNAL_PLUG1, "Devious Curses.esp")->As<RE::TESObjectARMO>();
		LockDevice(player, plug, true);

		PlayerMessage("Nocturnal summons a plug directly inside of you!");
	}

	void QITGInteractionEnd() {
		CloseContinerMenus();
		auto player = RE::PlayerCharacter::GetSingleton();

		auto plug1 = RE::TESDataHandler::GetSingleton()->LookupForm(NOCTURNAL_PLUG1, "Devious Curses.esp")->As<RE::TESObjectARMO>();
		auto plug2 = RE::TESDataHandler::GetSingleton()->LookupForm(NOCTURNAL_PLUG2, "Devious Curses.esp")->As<RE::TESObjectARMO>();
		if (ActorIsWearingDevice(player, plug1)) {
			RemoveQuestDevice(player, plug1, DeviousDevicesAPI::g_API->GetDeviceRender(plug1), true);
			player->AddObjectToContainer(reinterpret_cast<RE::TESBoundObject*>(plug2), nullptr, 1, nullptr);
		}
	}

	void QICInteraction1() {
		auto player = RE::PlayerCharacter::GetSingleton();
		
		UndressActor(player);

		DoStandardEvent(false, "", "rope & !(white | red | black)", 8, {"zad_DeviousBelt"});

		PlayerMessage("After pulling the lever ropes shoot out from behind you and wrap you up!");
	}

	void QICInteraction2() {
		auto player = RE::PlayerCharacter::GetSingleton();

		UndressActor(player);

		DoStandardEvent(false, "", "iron | chain | rusty | ironpear | peargag", 15, { "zad_DeviousBelt" });

		PlayerMessage("Touching the fragments cause chains to animate and bind you!");
	}

    void QIUpdate() {
		if (!settings.enableQuestInteractions) { return; }

		auto player = RE::PlayerCharacter::GetSingleton();
		RE::TESObjectARMO* plug = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESObjectARMO>(NOCTURNAL_PLUG1, "Devious Curses.esp");
		if (counters.clock_QINocturnal > 150) {
			if (ActorIsWearingDevice(player, plug)) {
				int r = Util::randomInt();
				if (r < 2) {
					ShockActor(player);
					auto health = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kHealth);
					auto damage = health * 0.9f;
					player->AsActorValueOwner()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kHealth, -damage);
				}
				else if (r < 10) {
					ShockActor(player);
					auto magic = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kMagicka);
					player->AsActorValueOwner()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kMagicka, -magic * 0.8f);

					auto stamina = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kStamina);
					player->AsActorValueOwner()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kStamina, -stamina * 0.8f);
				}
				else if (r < 30) {
					VibrateEffect(player, 1, 30, true);
				}
				else if (r < 33) {
					VibrateEffect(player, 1, 60, true);
				}
				else if (r < 35) {
					VibrateEffect(player, 5, 10, true);
					ModifyArousal(player, 100);
				}
			}

			counters.clock_QINocturnal = static_cast<int64_t>(Util::randomInt(-15, 0));
		}

        int mark = GetLewdMark(player);
		if (mark > 0) {
			switch (mark) {
			case (TAT_MERIDIA):
				if (!player->IsInCombat() && counters.clock_QIMeridia > 0) {
					RemoveLewdMark(player, TAT_MERIDIA);
					DoStandardEvent(false, "", "(black & (ebonite | _LS_ | plug)) | piercing", 20);
					PlayerMessage("You feel a surge of energy as Malkoran's mark activates!");
				}
			}
		}

		RE::TESObjectARMO* collar = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESObjectARMO>(SAARTHAL_COLLAR, "Devious Curses.esp");
		RE::TESObjectARMO* collarM = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESObjectARMO>(SAARTHAL_MCOLLAR, "Devious Curses.esp");
		bool hasACollar = ActorIsWearingDevice(player, collarM) || ActorIsWearingDevice(player, collar);
		auto atronach = QIMGGetSummonedAtronach();
		if (ActorIsWearingDevice(player, collarM) && atronach && Util::FormEditorIdContains(atronach->GetRace(), "frost")) {
			atronach->KillImmediate();
			QIMGSummonAtronach();
		}
		else if (ActorIsWearingDevice(player, collar) && atronach && Util::FormEditorIdContains(atronach->GetRace(), "storm")) {
			atronach->KillImmediate();
			QIMGSummonAtronach();
		}
		if (hasACollar) {
			if (atronach) {
				if (GetActorArousal(atronach) < 95) {
					ModifyArousal(atronach, 100);
				}
			}
			else {
				QIMGSummonAtronach();
			}
		}
		else {
			if (atronach) {
				atronach->KillImmediate();
			}
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

	void QICheckMagicEffect(RE::TESObjectREFR* caster, RE::TESObjectREFR* target, RE::EffectSetting* effect) {
		
	}
}