#pragma once

#include "Devices.hpp"
#include "Sex.hpp"

namespace DCURSES {

	std::string GetPronoun(RE::Actor* actor, std::string format) {
		if (!actor) return "ERROR BAD ACTOR";

		auto sex = static_cast<int32_t>(actor->GetActorBase()->GetSex());

		if (format == "herself") {
			return sex == 0 ? "himself" : "herself";
		}
		else if (format == "she") {
			return sex == 0 ? "he" : "she";
		}
		log::error("Could not match pronoun for actor {} with format {}", actor->GetName(), format);
		return "ERROR ON PRONOUN";
	}

	RE::Actor* GetClosestActor(RE::Actor* target) {
		if (!target) return nullptr;

		auto targetPosition = target->GetPosition();

		RE::Actor* result = nullptr;
		if (const auto processLists = RE::ProcessLists::GetSingleton(); processLists) {
			RE::BSSimpleList<RE::ActorHandle>* arr = &(processLists->aliveActorList);
			if (arr) {
				for (auto& actorHandle : *arr) {
					auto actorPtr = actorHandle.get();
					auto actor = actorPtr.get();
					if (actor && actor != RE::PlayerCharacter::GetSingleton() && actor->Is3DLoaded() && !actor->IsDead()) {
						if (!result) {
							result = actor;
						}
						if (actor->GetPosition().GetDistance(targetPosition) < result->GetPosition().GetDistance(targetPosition)) {
							result = actor;
						}
					}
				}
			}
		}

		return result;
	}

	enum consequenceSource {
		kSex,
		kNude,
		kRestrained,
	};

	bool ConsRandomDevice(RE::Actor* actor, consequenceSource source) {
		if (!actor) return false;

		auto player = RE::PlayerCharacter::GetSingleton();
		if (GetWornDeviceCount(player) > settings.restraintCap) {
			return false;
		}
		std::vector<std::string> skip = GetKeywordsCantEquip(player);
		if (!settings.consRandomHeavyBondage) {
			skip.push_back("zad_DeviousHeavyBondage");
		}
		auto item = GetRandomEquipableDevice(player, skip);
		if (item.has_value()) {
			auto equip = item.value();
			LockDevice(player, equip.inv);
			if (source == consequenceSource::kSex) {
				PlayerMessage(fmt::format("Now that {} is done with you, {} forces a {} on you before you can react!", actor->GetName(), GetPronoun(actor, "she"), equip.inv->GetName()));
			}
			else {
				PlayerMessage(fmt::format("Before you can talk to {} {} forces a {} on you before you can react!", actor->GetName(), GetPronoun(actor, "she"), equip.inv->GetName()));
			}
			return true;
		}
		return false;
	}

	bool SexActorFilter(RE::Actor* actor);
	int GetDeviceMask(RE::Actor* actor);

	bool ConsSex(RE::Actor* actor, consequenceSource source) {
		if (!actor) return false;

		if ((GetDeviceMask(RE::PlayerCharacter::GetSingleton()) & 0b0111) != 0 && SexActorFilter(actor)) {
			if (source == consequenceSource::kSex) {
				StartSex(actor);
				PlayerMessage(fmt::format("{} wasn't satisfied with your performance and goes in for another round!", actor->GetName()));
			}
			else {
				StartSex(actor);
				PlayerMessage(fmt::format("Before you can talk to {} {} grabs you and takes of your clothes!", actor->GetName(), GetPronoun(actor, "she")));
			}
			return true;
		}
		return false;
	}

	bool ConsFine(RE::Actor* actor, consequenceSource source) {
		if (!actor) return false;

		auto targetPosition = actor->GetPosition();

		RE::Actor* guard = nullptr;
		if (const auto processLists = RE::ProcessLists::GetSingleton(); processLists) {
			RE::BSSimpleList<RE::ActorHandle>* arr = &(processLists->aliveActorList);
			if (arr) {
				for (auto& actorHandle : *arr) {
					auto actorPtr = actorHandle.get();
					auto actor_g = actorPtr.get();
					if (actor_g) {
					}
					if (actor_g && actor_g != RE::PlayerCharacter::GetSingleton() && actor_g->Is3DLoaded() && !actor_g->IsDead() && std::string(actor_g->GetName()).find("Guard") != std::string::npos && actor_g->GetCrimeFaction()) {
						guard = actor_g;
						break;
					}
				}
			}
		}
		if (!guard) {
			log::trace("No guard nearby");
			return false;
		}
		auto faction = guard->GetCrimeFaction();

		if (faction) {
			RE::PlayerCharacter::GetSingleton()->ModCrimeGoldValue(faction, false, settings.consFineAmount);
			if (source == consequenceSource::kSex) {
				PlayerMessage(fmt::format("Someone saw you having sex with {} and reported you to the guard!", actor->GetName()));
			}
			else {
				PlayerMessage(fmt::format("Before you can talk to {} {} calls a guard and reports you!", actor->GetName(), GetPronoun(actor, "she")));
			}
		}
		return true;
	}

	bool ConsMercy(RE::Actor* actor, consequenceSource source) {
		if (!actor) return false;

		auto player = RE::PlayerCharacter::GetSingleton();

		auto heavy = GetWornDeviceByKeyword(player, "zad_DeviousHeavyBondage");
		if (heavy && !(source == consequenceSource::kSex)) {
			UnlockDevice(player, heavy);
			PlayerMessage(fmt::format("{} feels bad for you and unlocks your restraints.", actor->GetName()));
			return true;
		}

		auto key = GenerateKeys(player, true);
		if (key) {
			PlayerMessage(fmt::format("{} feels bad for you and gives you a {}.", actor->GetName(), key->GetName()));
			return true;
		}

		if (numDevicesVisible(player) == 0) {
			auto dev = GetRandomDevice(&devices.anything, GetKeywordsCantEquip(player));
			if (dev) {
				player->AddObjectToContainer((RE::TESBoundObject*)dev.value().inv, nullptr, 1, nullptr);
			}
			PlayerMessage(fmt::format("{} thinks you look bored and gives you a {}.", actor->GetName(), dev.value().inv->GetName()));
		}
		return true;
	}

	bool DoConsequence(RE::Actor* actor, consequenceSource source) {
		if (!actor) return false;

		if (actor->IsPlayerTeammate() && !settings.consAllowFollowers) {
			return false;
		}

		double consFineWeight = settings.consFineWeight;
		double consRandomBondageWeight = settings.consRandomBondageWeight;
		double consSexWeight = settings.consSexWeight;
		double consMercyWeight = settings.consMercyWeight;

		if (settings.consUseRelationships) {
			int relationship_rank = 0;
			auto actor_base = actor->GetActorBase();
			if (actor_base) {
				auto relationship = RE::BGSRelationship::GetRelationship(actor_base, RE::PlayerCharacter::GetSingleton()->GetActorBase());
				if (relationship) {
					relationship_rank = 4 - static_cast<int>(relationship->level.get());
					log::trace("Got relationship rank with {}: {}", actor->GetName(), relationship_rank);
				}
			}

			consFineWeight = settings.consFineWeight * (8.0 - relationship_rank) / 8.0;
			consSexWeight = settings.consSexWeight * (8.0 - relationship_rank) / 8.0;
			consRandomBondageWeight = settings.consRandomBondageWeight * (8.0 - relationship_rank) / 8.0;
			
			consMercyWeight = settings.consMercyWeight * (8.0 + relationship_rank) / 8.0;
		}

		double weightTotal = consFineWeight + consRandomBondageWeight + consSexWeight + consMercyWeight;
		if (weightTotal <= 0.0) return false;
		
		double r = Util::randomDouble(weightTotal);

		std::vector<std::pair<bool (*)(RE::Actor* actor, consequenceSource source), double>> consequences;
		consequences.push_back(std::make_pair(ConsFine, consFineWeight));
		consequences.push_back(std::make_pair(ConsSex, consSexWeight));
		consequences.push_back(std::make_pair(ConsRandomDevice, consRandomBondageWeight));
		consequences.push_back(std::make_pair(ConsMercy, consMercyWeight));

		Util::ShuffleVector(consequences);

		for (size_t i = 0; i < consequences.size(); i++) {
			auto pair = consequences[i];
			if (r < pair.second) {
				if (pair.first(actor, source)) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				r -= pair.second;
			}
		}
		return false;
	}

	void CheckConsequenceDialogue(RE::Actor* actor) {
		if (!actor) return;

		if (IsConsequenceTargetKnown(actor->formID)) {
			return;
		}
		SetConsequenceTargetKnown(actor->formID);
		auto player = RE::PlayerCharacter::GetSingleton();
		log::trace("Checking consequence dialogue");
		if (player->GetWornArmor((RE::BIPED_MODEL::BipedObjectSlot::kBody)) == nullptr) {
			DecrementCounterForMark(TAT_NUDITY);
			if (Util::randomDouble() < settings.consTriggerNude) {
				log::trace("Nude Trigger");
				if (DoConsequence(actor, consequenceSource::kNude)) {
					//actor->EndDialogue();
				}
			}
		}
		if (GetWornDeviceByKeyword(player, "zad_DeviousHeavyBondage") && Util::randomDouble() < settings.consTriggerRestrained) {
			log::trace("Bondage Trigger");
			if (DoConsequence(actor, consequenceSource::kRestrained)) {
				//actor->EndDialogue();
			}
		}
	}

	void ConsSexEnded(RE::Actor* actor) {
		if (actor && counters.clock_lastSex > 0 && settings.sexEnabled) {
			if (IsConsequenceTargetKnown(actor->formID)) {
				return;
			}
			SetConsequenceTargetKnown(actor->formID);
			if (Util::randomDouble() < settings.consTriggerSex) {
				log::trace("Sex end trigger.");
				DoConsequence(actor, consequenceSource::kSex);
				actor->EndDialogue();
			}
		}
	}
}