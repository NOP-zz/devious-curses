#pragma once

#include "Scripting.hpp"
#include "MGEF_Controller.hpp"

namespace DCURSES {
	bool OppSummonerCollarEvent(std::string containerName, bool doMessage = false) {
		if (!settings.sexAllowCreature || settings.sexChanceCreature == 0) {
			return false;
		}

		RE::TESObjectARMO* summoner_collar = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESObjectARMO>(SUMMONER_COLLAR, "Devious Curses.esp");
		auto player = RE::PlayerCharacter::GetSingleton();

		auto collar = GetWornDeviceByKeyword(player, "zad_DeviousCollar");
		if (collar && (collar->HasKeywordString("zad_BlockGeneric") || collar->HasKeywordString("zad_QuestItem"))) {
			return false;
		}

		SetEffectVisible(SUMMONER_COLLAR_EFFECT);
		SetEffectMagnitude(SUMMONER_COLLAR_EFFECT, static_cast<float>(settings.oppSummonerSexCount));

		auto magic = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kMagicka);
		player->AsActorValueOwner()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kMagicka, -magic);

		LockDevice(player, summoner_collar, true);
		if (doMessage) { PlayerMessage(fmt::format("As you touch the {} you feel very dizzy as a heavy collar forms around your neck and absorbs your magicka!", containerName)); };
		return true;
	}

	bool DoOppDeviceEvent(std::string containerName) {

		int weightTotal = settings.oppSummonerCollarWeight;
		if (weightTotal <= 0.0) return false;

		int r = Util::randomInt(weightTotal);

		std::vector<std::pair<bool (*)(std::string, bool), int>> events;
		events.push_back(std::make_pair(OppSummonerCollarEvent, settings.oppSummonerCollarWeight));


		Util::ShuffleVector(events);
		for (size_t i = 0; i < events.size(); i++) {
			auto pair = events[i];
			if (r < pair.second) {
				if (pair.first(containerName, true)) {
					return true;
				}
				else {
					r -= pair.second;
				}
			}
			else {
				r -= pair.second;
			}
		}
		return false;
	}

	void OppDeviceUpdate() {
		auto player = RE::PlayerCharacter::GetSingleton();

		RE::TESObjectARMO* summoner_collar = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESObjectARMO>(SUMMONER_COLLAR, "Devious Curses.esp");
		RE::TESKey* summoner_collar_key = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESKey>(SUMMONER_COLLAR_KEY, "Devious Curses.esp");

		//Summoner Collar
		bool isWearingSummonerCollar = ActorIsWearingDevice(player, summoner_collar);
		if (isWearingSummonerCollar) {
			SetEffectVisible(SUMMONER_COLLAR_EFFECT);
			auto summons_list = getPlayerCommandedActors();
			if (summons_list.empty()) {
				if (Util::randomDouble() < settings.oppSummonChance) {
					RE::SpellItem* conjure_atronach = RE::TESDataHandler::GetSingleton()->LookupForm<RE::SpellItem>(SUMMONER_SUMMON_SPELL, "Devious Curses.esp");
					//conjure_atronach->data.delivery = RE::MagicSystem::Delivery::kSelf;
					RE::MagicCaster* caster = player->GetMagicCaster(RE::MagicSystem::CastingSource::kOther);
					caster->CastSpellImmediate(conjure_atronach, false, player, 3.0f, false, 0.0f, nullptr);
					//conjure_atronach->data.delivery = RE::MagicSystem::Delivery::kTargetLocation;
					auto magic = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kMagicka);
					if (settings.oppSCollarDrainsMagicka) player->AsActorValueOwner()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kMagicka, -magic);
				}
			}
			else {
				if (settings.oppSMinSummonArousal > 0) {
					for (auto summon : summons_list) {
						if (GetActorArousal(summon) < settings.oppSMinSummonArousal) {
							SetArousal(summon, settings.oppSMinSummonArousal);
						}
					}
				}
			}
		}
		else {
			SetEffectVisible(SUMMONER_COLLAR_EFFECT, false);
		}

		if (GetEffectMagnitude(SUMMONER_COLLAR_EFFECT) <= 0) {
			SetEffectVisible(SUMMONER_COLLAR_EFFECT, false);
			if (isWearingSummonerCollar && GetItemCount(player, summoner_collar_key) == 0) {
				player->AddObjectToContainer((RE::TESBoundObject*)summoner_collar_key, nullptr, 1, nullptr);
				PlayerMessage("The Summoner Collar is now satisfied and you can unlock it!");
			}
		}

		//Next Device
		
	}

	void OppOnSexEnd(RE::Actor* actor) {
		if (getIsPlayerCommandedActor(actor)) {
			if (Util::GetFormEditorId(actor->GetActorBase()) == "DCurses_SummonAtronachFrost") {
				actor->KillImmediate();
			}
			ModifyEffectMagnitude(SUMMONER_COLLAR_EFFECT, -1.0);
		}
	}
}