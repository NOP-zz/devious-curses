#pragma once

#include "Devices.hpp"
#include "Sex.hpp"

namespace DCURSES {

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
		auto scriptManager = ScriptingManager();
		auto deviceCount = GetWornDeviceCount(player);

		log::trace("Attempting Device Consequence.");
		if (deviceCount > settings.restraintCap && !settings.consBondageIgnoreMax) {
			return false;
		}
		std::vector<std::string> skip = GetKeywordsCantEquip(player);
		if (!settings.consRandomHeavyBondage) {
			skip.push_back("zad_DeviousHeavyBondage");
		}
		auto item = GetRandomEquipableDevice(player, skip);
		if (item.has_value()) {
			auto equip = item.value();
			scriptManager.LockDevice(player, equip.inv);
			if (source == consequenceSource::kSex) {
				//PlayerMessage(fmt::format("Now that {} is done with you, they force a {} on you before you can react!", actor->GetName(), equip.inv->GetName()));
				PlayerMessage(Translator(Translation::ConsequenceRandomDeviceSex, actor->GetName(), equip.inv->GetName()));
			}
			else {
				//PlayerMessage(fmt::format("Before you can talk to {} they force a {} on you before you can react!", actor->GetName(), equip.inv->GetName()));
				PlayerMessage(Translator(Translation::ConsequenceRandomDeviceTalk, actor->GetName(), equip.inv->GetName()));
			}
			return true;
		}
		return false;
	}

	bool SexActorFilter(RE::Actor* actor);
	int GetDeviceMask(RE::Actor* actor);

	bool ConsSex(RE::Actor* actor, consequenceSource source) {
		auto mask = GetDeviceMask(RE::PlayerCharacter::GetSingleton());
		auto scriptManager = ScriptingManager();

		log::trace("Attempting Sex Consequence. Mask: {:04b}", mask);

		if (!actor || !settings.sexEnabled) return false;

		if ((mask & 0b0111) != 0 && SexActorFilter(actor)) {
			if (source == consequenceSource::kSex) {
				scriptManager.StartSex(actor, settings.sexAggressiveAnims);
				AIEventStartSex(actor);
				//PlayerMessage(fmt::format("{} wasn't satisfied with your performance and goes in for another round!", actor->GetName()));
				PlayerMessage(Translator(Translation::ConsequenceSexContinue, actor->GetName()));
			}
			else {
				scriptManager.StartSex(actor, settings.sexAggressiveAnims);
				AIEventStartSex(actor);
				//PlayerMessage(fmt::format("Before you can talk to {} they grab you and takes of your clothes!", actor->GetName()));
				PlayerMessage(Translator(Translation::ConsequenceSexTalk, actor->GetName()));
			}
			return true;
		}
		return false;
	}

	bool ConsFine(RE::Actor* actor, consequenceSource source) {
		if (!actor) return false;

		auto targetLocation = actor->GetCurrentLocation();

		bool isGuardNearby = false;
		if (targetLocation && (targetLocation->HasKeywordString("LocTypeCity") || targetLocation->HasKeywordString("LocTypeCastle") || targetLocation->HasKeywordString("LocTypeTemple") || targetLocation->HasKeywordString("LocTypeInn") || targetLocation->HasKeywordString("LocTypeHouse") || targetLocation->HasKeywordString("LocTypeTown") || targetLocation->HasKeywordString("LocTypeHabitation") || targetLocation->HasKeywordString("LocTypeDwelling"))) {
			isGuardNearby = true;
		}

		RE::TESFaction* crimeFaction = nullptr;
		while (crimeFaction == nullptr && targetLocation != nullptr) {
			crimeFaction = targetLocation->unreportedCrimeFaction;
			targetLocation = targetLocation->parentLoc;
		}

		if (const auto processLists = RE::ProcessLists::GetSingleton(); processLists && !isGuardNearby) {
			RE::BSSimpleList<RE::ActorHandle>* arr = &(processLists->aliveActorList);
			if (arr) {
				for (auto& actorHandle : *arr) {
					auto actorPtr = actorHandle.get();
					auto actor_g = actorPtr.get();
					if (actor_g && actor_g != RE::PlayerCharacter::GetSingleton() && actor_g->Is3DLoaded() && !actor_g->IsDead() && std::string(actor_g->GetName()).find("Guard") != std::string::npos && actor_g->GetCrimeFaction()) {
						crimeFaction = actor_g->GetCrimeFaction();
						isGuardNearby = true;
						break;
					}
				}
			}
		}

		log::trace("Attempting Fine Consequence: {}, {}", isGuardNearby, crimeFaction ? Util::GetFormEditorId(crimeFaction) : "No Crime Faction");

		if (crimeFaction && isGuardNearby) {
			RE::PlayerCharacter::GetSingleton()->ModCrimeGoldValue(crimeFaction, false, settings.consFineAmount);
			if (source == consequenceSource::kSex) {
				//PlayerMessage(fmt::format("Someone saw you having sex with {} and reported you to the guard!", actor->GetName()));
				PlayerMessage(Translator(Translation::ConsequenceFineSex, actor->GetName()));
			}
			else {
				//PlayerMessage(fmt::format("Before you can talk to {} they call a guard and report you!", actor->GetName()));
				PlayerMessage(Translator(Translation::ConsequenceFineTalk, actor->GetName()));
			}
			return true;
		}
		return false;
	}

	bool ConsMercy(RE::Actor* actor, consequenceSource source) {
		if (!actor) return false;

		log::trace("Attempting Mercy Consequence.");

		auto player = RE::PlayerCharacter::GetSingleton();
		auto scriptManager = ScriptingManager();

		auto heavy = GetWornInventoryDeviceByKeyword(player, "zad_DeviousHeavyBondage");
		if (heavy && DeviceInventoryIsGeneric(heavy) && !(source == consequenceSource::kSex)) {
			scriptManager.UnlockDevice(player, heavy);
			//PlayerMessage(fmt::format("{} feels bad for you and unlocks your restraints.", actor->GetName()));
			PlayerMessage(Translator(Translation::ConsequenceMercyUnlock, actor->GetName()));
			return true;
		}

		auto deviceCount = numDevicesVisible(player);
		auto keys = GenerateKeys(player, true, true);
		if (keys.size() > 0 && deviceCount > 0) {
			//PlayerMessage(fmt::format("{} feels bad for you and gives you a {}.", actor->GetName(), keys[0]->GetName()));
			PlayerMessage(Translator(Translation::ConsequenceMercyKey, actor->GetName(), keys[0]->GetName()));
			return true;
		}

		auto dev = GetRandomDevice(&devices.anything);
		if (dev) {
			player->AddObjectToContainer((RE::TESBoundObject*)dev.value().inv, nullptr, 1, nullptr);
			//PlayerMessage(fmt::format("{} thinks you look bored and gives you a {}.", actor->GetName(), dev.value().inv->GetName()));
			PlayerMessage(Translator(Translation::ConsequenceMercyDevice, actor->GetName(), dev.value().inv->GetName()));
		}
		return true;
	}

	bool DoConsequence(RE::Actor* actor, consequenceSource source) {
		if (!actor) return false;

		if (actor->IsPlayerTeammate() && !settings.consAllowFollowers) {
			return false;
		}

		if (Util::ActorIsCreature(actor) && !settings.consAllowCreatures) {
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

		std::vector<std::pair<bool (*)(RE::Actor* actor, consequenceSource source), double>> consequences;
		consequences.push_back(std::make_pair(ConsFine, consFineWeight));
		consequences.push_back(std::make_pair(ConsSex, consSexWeight));
		consequences.push_back(std::make_pair(ConsRandomDevice, consRandomBondageWeight));
		consequences.push_back(std::make_pair(ConsMercy, consMercyWeight));

		Util::ShuffleVector(consequences);

		while (!consequences.empty()) {
			auto pair = Util::VectorSelectWeighted(consequences);
			if (pair.first(actor, source)) {
				return true;
			}
			else if (!settings.consFallthrough) {
				return false;
			}
			consequences.erase(std::remove(consequences.begin(), consequences.end(), pair), consequences.end());
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
		DecrementCounterForMark(MARK::TAT_NUDITY);
		auto body = player->GetWornArmor((RE::BIPED_MODEL::BipedObjectSlot::kBody));
		if (body == nullptr || (body != nullptr && body->HasKeywordString("zad_Lockable"))) {
			if (Util::randomDouble() <= settings.consTriggerNude) {
				log::trace("Nude Trigger");
				if (DoConsequence(actor, consequenceSource::kNude)) {
					//actor->EndDialogue();
				}
			}
		}
		if (GetWornInventoryDeviceByKeyword(player, "zad_DeviousHeavyBondage") && Util::randomDouble() < settings.consTriggerRestrained) {
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