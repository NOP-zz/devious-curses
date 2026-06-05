#include "../include/Consequences.h"

#pragma warning(default : 4062)

#include "Devices.h"
#include "tats.h"
#include "form_ids.h"
#include "Settings.h"
#include "Scripting.h"
#include "Translation.h"
#include "Utils.h"
#include "Consequences.h"
#include "Serializer.h"
#include "Locations.h"
#include "Sex.h"

namespace DCURSES {
	bool getIsNude(RE::Actor* actor, bool isConsequence) {
		bool is_player = actor == RE::PlayerCharacter::GetSingleton();
		auto settings = Settings::GetSingleton();

		if (CheckAND()) {
			RE::TESFaction* AND_ToplessFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x832, "Advanced Nudity Detection.esp");
			RE::TESFaction* AND_BottomlessFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x833, "Advanced Nudity Detection.esp");
			RE::TESFaction* AND_ShowingAssFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x82E, "Advanced Nudity Detection.esp");
			RE::TESFaction* AND_ShowingChestFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x82F, "Advanced Nudity Detection.esp");
			RE::TESFaction* AND_ShowingGenitalFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x830, "Advanced Nudity Detection.esp");
			RE::TESFaction* AND_ShowingBraFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x834, "Advanced Nudity Detection.esp");
			RE::TESFaction* AND_ShowingUnderwearFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x835, "Advanced Nudity Detection.esp");

			bool topless = actor->GetFactionRank(AND_ToplessFaction, is_player) > 0;
			bool bottomless = actor->GetFactionRank(AND_BottomlessFaction, is_player) > 0;
			bool showing_ass = actor->GetFactionRank(AND_ShowingAssFaction, is_player) > 0;
			bool showing_chest = actor->GetFactionRank(AND_ShowingChestFaction, is_player) > 0;
			bool showing_genitals = actor->GetFactionRank(AND_ShowingGenitalFaction, is_player) > 0;
			bool showing_bra = actor->GetFactionRank(AND_ShowingBraFaction, is_player) > 0;
			bool showing_underwear = actor->GetFactionRank(AND_ShowingUnderwearFaction, is_player) > 0;

			if (!isConsequence && (
				(settings->ANDSexTopless && topless) ||
				(settings->ANDSexBottomless && bottomless) ||
				(settings->ANDSexShowingAss && showing_ass) ||
				(settings->ANDSexShowingChest && showing_chest) ||
				(settings->ANDSexShowingGenitals && showing_genitals) ||
				(settings->ANDSexShowingBra && showing_bra) ||
				(settings->ANDSexShowingUnderwear && showing_underwear)
				)) {
				return true;
			}
			else if (isConsequence && (
				(settings->ANDConsTopless && topless) ||
				(settings->ANDConsBottomless && bottomless) ||
				(settings->ANDConsShowingAss && showing_ass) ||
				(settings->ANDConsShowingChest && showing_chest) ||
				(settings->ANDConsShowingGenitals && showing_genitals) ||
				(settings->ANDConsShowingBra && showing_bra) ||
				(settings->ANDConsShowingUnderwear && showing_underwear)
				)) {
				return true;
			}
		}
		else {
			auto body = actor->GetWornArmor((RE::BIPED_MODEL::BipedObjectSlot::kBody));
			return body == nullptr || (body != nullptr && body->HasKeywordString("zad_Lockable"));
		}
		return false;
	}

	bool ConsRandomDevice(RE::Actor* actor, consequenceSource source) {
		if (!actor) return false;

		auto player = RE::PlayerCharacter::GetSingleton();
		auto scriptManager = ScriptingManager();
		auto deviceCount = GetWornDeviceCount(player);
		auto settings = Settings::GetSingleton();

		log::trace("Attempting Device Consequence.");
		if (deviceCount > settings->restraintCap && !settings->consBondageIgnoreMax) {
			return false;
		}
		std::set<std::string> skip = GetKeywordsCantEquip(player);
		if (!settings->consRandomHeavyBondage) {
			skip.insert("zad_DeviousHeavyBondage");
		}
		auto item = GetRandomEquipableDevice(player, skip);
		if (item.has_value()) {			
			auto equip = item.value();

			switch (source) {
			case consequenceSource::kSeenHavingSex: {
				PlayerMessage(Translator(Translation::ConsequenceRandomDevice_Sex, actor->GetName(), equip.inv->GetName()));
				break;
			}
			case consequenceSource::kSeenNude:
			case consequenceSource::kTalkedNude: {
				PlayerMessage(Translator(Translation::ConsequenceRandomDevice_Nude, actor->GetName(), equip.inv->GetName()));
				break;
			}
			case consequenceSource::kSeenRestrained:
			case consequenceSource::kTalkedRestrained: {
				PlayerMessage(Translator(Translation::ConsequenceRandomDevice_Restrained, actor->GetName(), equip.inv->GetName()));
				break;
			}
			case consequenceSource::kSeenWithHeavy:
			case consequenceSource::kTalkedWithHeavy: {
				PlayerMessage(Translator(Translation::ConsequenceRandomDevice_Heavy, actor->GetName(), equip.inv->GetName()));
				break;
			}
			case consequenceSource::kSeenTattoos:
			case consequenceSource::kTalkedTattoos: {
				PlayerMessage(Translator(Translation::ConsequenceRandomDevice_Tattoo, actor->GetName(), equip.inv->GetName()));
				break;
			}
			case consequenceSource::kSeenTrespassing: {
				PlayerMessage(Translator(Translation::ConsequenceRandomDevice_Trespass, actor->GetName(), equip.inv->GetName()));
				break;
			}
			case consequenceSource::kUnknown: {
				log::error("Unknown consequence source {} for Restraint, no message to show.", static_cast<int>(source));
				return false;
			}
			}

			scriptManager.LockDevice(player, equip.inv);

			return true;
		}
		return false;
	}

	bool ConsSex(RE::Actor* actor, consequenceSource source) {
		auto mask = GetDeviceMask(RE::PlayerCharacter::GetSingleton());
		auto scriptManager = ScriptingManager();
		auto settings = Settings::GetSingleton();

		log::trace("Attempting Sex Consequence. Mask: {:04b}", mask);

		if (!actor || !settings->sexEnabled) return false;

		if ((mask & 0b0111) != 0 && SexActorFilter(actor, false)) {

			switch (source) {
			case consequenceSource::kSeenHavingSex: {
				PlayerMessage(Translator(Translation::ConsequenceSex_Sex, actor->GetName()));
				break;
			}
			case consequenceSource::kTalkedNude:
			case consequenceSource::kSeenNude: {
				PlayerMessage(Translator(Translation::ConsequenceSex_Nude, actor->GetName()));
				break;
			}
			case consequenceSource::kTalkedRestrained:
			case consequenceSource::kSeenRestrained: {
				PlayerMessage(Translator(Translation::ConsequenceSex_Restrained, actor->GetName()));
				break;
			}
			case consequenceSource::kTalkedWithHeavy:
			case consequenceSource::kSeenWithHeavy: {
				PlayerMessage(Translator(Translation::ConsequenceSex_Heavy, actor->GetName()));
				break;
			}
			case consequenceSource::kTalkedTattoos:
			case consequenceSource::kSeenTattoos: {
				PlayerMessage(Translator(Translation::ConsequenceSex_Tattoos, actor->GetName()));
				break;
			}
			case consequenceSource::kSeenTrespassing: {
				PlayerMessage(Translator(Translation::ConsequenceSex_Trespass, actor->GetName()));
				break;
			}
			case consequenceSource::kUnknown: {
				log::error("Unknown consequence source {} for Sex, no message to show.", static_cast<int>(source));
				return false;
			}
			}

			scriptManager.StartSex(actor, settings->sexAggressiveAnims);

			return true;
		}
		return false;
	}

	bool ActorIsGuard(RE::Actor* actor) {
		auto settings = Settings::GetSingleton();
		RE::TESFaction* guardFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x86EEE, "Skyrim.esm");
		if (std::string(actor->GetName()).find("Guard") != std::string::npos || (settings->consFineGuardFaction && actor->GetFactionRank(guardFaction, false) >= 0)) {
			return true;
		}
		else {
			return false;
		}
	}

	bool ConsFine(RE::Actor* actor, consequenceSource source) {
		if (!actor) return false;

		if (Util::ActorIsCreature(actor)) {
			return false;
		}

		log::trace("Attempting Fine Consequence for {}.", actor->GetName());

		if (!ActorIsGuard(actor)) {
			return false;
		}

		auto settings = Settings::GetSingleton();
		auto targetLocation = actor->GetCurrentLocation();
		auto locationType = GetLocationType(targetLocation);
		if (locationType == LocationType::PlayerHome) {
			return false;
		}

		int fine = 0;

		switch (source) {
		case consequenceSource::kSeenHavingSex: {
			fine = settings->consFineForSex;
			break;
		}
		case consequenceSource::kSeenNude:
		case consequenceSource::kTalkedNude: {
			fine = settings->consFineForNudity;
			break;
		}
		case consequenceSource::kSeenRestrained:
		case consequenceSource::kTalkedRestrained:
		case consequenceSource::kSeenWithHeavy:
		case consequenceSource::kTalkedWithHeavy: {
			fine = settings->consFineForRestraints;
			break;
		}
		case consequenceSource::kSeenTattoos:
		case consequenceSource::kTalkedTattoos: {
			fine = settings->consFineForTattoos;
			break;
		}
		case consequenceSource::kSeenTrespassing:
		case consequenceSource::kUnknown: {
			return false;
		}
		}

		if (fine <= 0) {
			return false;
		}

		RE::TESFaction* crimeFaction = actor->GetCrimeFaction();

		while (crimeFaction == nullptr && targetLocation != nullptr) {
			crimeFaction = targetLocation->unreportedCrimeFaction;
			targetLocation = targetLocation->parentLoc;
		}

		if (crimeFaction) {
			
			switch (source) {
			case consequenceSource::kSeenHavingSex: {
				PlayerMessage(Translator(Translation::ConsequenceFine_Sex, actor->GetName()));
				break;
			}
			case consequenceSource::kSeenNude: {
				PlayerMessage(Translator(Translation::ConsequenceFine_SeenNude, actor->GetName()));
				break;
			}
			case consequenceSource::kTalkedNude: {
				PlayerMessage(Translator(Translation::ConsequenceFine_TalkedNude));
				break;
			}
			case consequenceSource::kSeenWithHeavy:
			case consequenceSource::kSeenRestrained: {
				PlayerMessage(Translator(Translation::ConsequenceFine_SeenRestrained, actor->GetName()));
				break;
			}
			case consequenceSource::kTalkedWithHeavy:
			case consequenceSource::kTalkedRestrained: {
				PlayerMessage(Translator(Translation::ConsequenceFine_TalkedRestrained));
				break;
			}
			case consequenceSource::kSeenTattoos: {
				PlayerMessage(Translator(Translation::ConsequenceFine_SeenTattoos, actor->GetName()));
				break;
			}
			case consequenceSource::kTalkedTattoos: {
				PlayerMessage(Translator(Translation::ConsequenceFine_TalkedTattoos));
				break;
			}
			case consequenceSource::kSeenTrespassing:
			case consequenceSource::kUnknown: {
				log::error("Invalid source for Fine, no message to show.");
				return false;
			}
			}

			RE::PlayerCharacter::GetSingleton()->ModCrimeGoldValue(crimeFaction, false, fine);

			return true;
		}
		return false;
	}

	bool ConsTattoo(RE::Actor* actor, consequenceSource source) {
		if (!actor) return false;

		auto scriptManager = ScriptingManager();
		auto settings = Settings::GetSingleton();
		auto player = RE::PlayerCharacter::GetSingleton();

		log::trace("Attempting Tattoo Consequence.");

		if (GetTattooCount(player) > settings->eventTattooCap) {
			return false;
		}

		int tattoo_count = 1;
		if (settings->consTattooCurseNumbers) {
			tattoo_count = Util::random(settings->eventTattooMin, settings->eventTattooMax);
		}

		switch (source) {
		case consequenceSource::kSeenHavingSex: {
			if (tattoo_count == 1) {
				PlayerMessage(Translator(Translation::ConsequenceTattoo_Sex, actor->GetName()));
			}
			else {
				PlayerMessage(Translator(Translation::ConsequenceTattoo_SexMultiple, actor->GetName()));
			}
			break;
		}
		case consequenceSource::kSeenTrespassing: {
			if (tattoo_count == 1) {
				PlayerMessage(Translator(Translation::ConsequenceTattoo_Trespass, actor->GetName()));
			}
			else {
				PlayerMessage(Translator(Translation::ConsequenceTattoo_TrespassMultiple, actor->GetName()));
			}
			break;
		}
		case consequenceSource::kSeenNude: 
		case consequenceSource::kTalkedNude:
		case consequenceSource::kSeenRestrained:
		case consequenceSource::kTalkedRestrained:
		case consequenceSource::kSeenWithHeavy:
		case consequenceSource::kTalkedWithHeavy:
		case consequenceSource::kTalkedTattoos:
		case consequenceSource::kSeenTattoos:
		{
			if (tattoo_count == 1) {
				PlayerMessage(Translator(Translation::ConsequenceTattoo_Other, actor->GetName()));
			}
			else {
				PlayerMessage(Translator(Translation::ConsequenceTattoo_OtherMultiple, actor->GetName()));
			}
			break;
		}
		case consequenceSource::kUnknown: {
			log::error("Unknown consequence source {} for Tattoo, no message to show.", static_cast<int>(source));
			return false;
		}
		}

		ScriptingManager().RTDoTattooEvent(player, tattoo_count);


		return true;
	}

	bool ConsMercy(RE::Actor* actor, consequenceSource source) {
		if (!actor) return false;

		log::trace("Attempting Mercy Consequence.");

		if (source == consequenceSource::kSeenHavingSex) {
			return false;
		}

		auto player = RE::PlayerCharacter::GetSingleton();
		auto scriptManager = ScriptingManager();

		auto heavy = GetWornInventoryDeviceByKeyword(player, "zad_DeviousHeavyBondage");
		if (heavy && DeviceInventoryIsGeneric(heavy)) {
			scriptManager.UnlockDevice(player, heavy);
			PlayerMessage(Translator(Translation::ConsequenceMercy_Unlock, actor->GetName()));
			return true;
		}

		auto deviceCount = GetVisibleDeviceCount(player);

		if (deviceCount > 0) {
			auto keys = GenerateKeys(player, true, true);
			if (keys.size() > 0) {
				PlayerMessage(Translator(Translation::ConsequenceMercy_Key, actor->GetName(), keys[0]->GetName()));
				return true;
			}
		}

		return false;
	}

	bool DoConsequence(RE::Actor* actor, consequenceSource source) {
		if (!actor) return false;
		auto settings = Settings::GetSingleton();
		auto player = RE::PlayerCharacter::GetSingleton();

		if (actor->IsPlayerTeammate() && !settings->consAllowFollowers) {
			return false;
		}

		if (Util::ActorIsCreature(actor)) {
			return false;
		}

		if (actor->IsHostileToActor(player)) {
			//log::trace("Skipping actor due to hostility");
			return false;
		}

		if (player->IsInCombat()) {
			return false;
		}

		double consRandomBondageWeight = settings->consRandomBondageWeight;
		double consSexWeight = settings->consSexWeight;
		double consTattooWeight = settings->consTattooWeight;
		double consMercyWeight = settings->consMercyWeight;

		if (settings->consUseRelationships) {
			int relationship_rank = 0;
			auto actor_base = actor->GetActorBase();
			if (actor_base) {
				auto relationship = RE::BGSRelationship::GetRelationship(actor_base, RE::PlayerCharacter::GetSingleton()->GetActorBase());
				if (relationship) {
					relationship_rank = 4 - static_cast<int>(relationship->level.get());
					log::trace("Got relationship rank with {}: {}", actor->GetName(), relationship_rank);
				}
			}

			consSexWeight = settings->consSexWeight * (8.0 - relationship_rank) / 8.0;
			consTattooWeight = settings->consTattooWeight * (8.0 - relationship_rank) / 8.0;
			if (settings->consRelationBondage) {
				consRandomBondageWeight = settings->consRandomBondageWeight * (8.0 + relationship_rank) / 8.0;
			}
			else {
				consRandomBondageWeight = settings->consRandomBondageWeight * (8.0 - relationship_rank) / 8.0;
			}

			consMercyWeight = settings->consMercyWeight * (8.0 + relationship_rank) / 8.0;
		}

		std::vector<std::pair<bool (*)(RE::Actor* actor, consequenceSource source), double>> consequences;
		consequences.push_back({ ConsSex, consSexWeight });
		consequences.push_back({ ConsRandomDevice, consRandomBondageWeight });
		consequences.push_back({ ConsTattoo, consTattooWeight });
		consequences.push_back({ ConsMercy, consMercyWeight });

		if (Util::VectorGetWeightsSum(consequences) <= 0.0) {
			return false;
		}

		Util::ShuffleVector(consequences);

		while (!consequences.empty()) {
			auto pair = Util::VectorSelectWeighted(consequences);
			if (!pair.has_value()) {
				return false;
			}
			if (pair.value().first(actor, source)) {
				return true;
			}
			else if (!settings->consFallthrough) {
				return false;
			}
			consequences.erase(std::remove(consequences.begin(), consequences.end(), pair), consequences.end());
		}
		return false;
	}

	void CheckConsequenceDialogue(RE::Actor* actor) {
		if (!actor) return;

		auto settings = Settings::GetSingleton();

		if (!settings->consEnable) {
			return;
		}

		if (settings->consFollowersBlock && Util::GetFollowers().size() > 0) {
			return;
		}

		if (IsConsequenceTargetKnown(actor->formID)) {
			return;
		}

		if (actor->IsPlayerTeammate() && !settings->consAllowFollowers) {
			return;
		}

		auto player = RE::PlayerCharacter::GetSingleton();
		//log::trace("Checking consequence dialogue");
		
		bool isNude = getIsNude(player, true);
		auto keywords = GetWornDeviceKeywords(player);
		bool isChastity = settings->consTolerableChastity && keywords.contains("zad_DeviousBelt") && keywords.contains("zad_DeviousBra");
		bool isGagged = keywords.contains("zad_DeviousGag");
		float gaggedMod = isGagged ? settings->consGaggedMultiplier : 1;
		bool isHeavy = keywords.contains("zad_DeviousHeavyBondage");
		bool isRestrained = GetVisibleDeviceCount(player) >= settings->consRestrainedCount;
		bool isTattooed = GetTattooCount(player) >= settings->consTattooCount;

		bool actorIsGuard = ActorIsGuard(actor);

		if (isNude && !settings->LMNuditySkipGagged || !isGagged && Serialized::GetLewdMarkCounters()->nudityCounter > 0) {
			Serialized::GetLewdMarkCounters()->nudityCounter -= 1;
		}

		auto source = consequenceSource::kUnknown;
		float chance = 0;
		float guard_chance = settings->consGuardTalkMult;

		if (isHeavy) {
			source = consequenceSource::kTalkedWithHeavy;
			chance = settings->consTalkHeavy;
			guard_chance *= settings->consGuardScanRestrained;
		}
		else {
			if (isRestrained) {
				source = consequenceSource::kTalkedRestrained;
				chance = settings->consTalkRestrained;
				guard_chance *= settings->consGuardScanRestrained;
			}
			if (isNude && !isChastity) {
				source = consequenceSource::kTalkedNude;
				chance = settings->consTalkNude;
				guard_chance *= settings->consGuardScanNude;
			}
			if (isTattooed) {
				source = consequenceSource::kTalkedTattoos;
				chance = settings->consTalkTattoo;
				guard_chance *= settings->consGuardScanTattoo;
			}
		}

		if (source == consequenceSource::kUnknown) {
			return;
		}

		if (actorIsGuard) {
			if (Util::random<float>() < guard_chance * gaggedMod || settings->consGuardTalkMult >= 100) {
				if (ConsFine(actor, source)) {
					SetConsequenceTargetKnown(actor->formID);
					return;
				}
			}
		}
		if (!actorIsGuard || settings->consGuardNormal) {
			if (Util::random<float>() < chance * gaggedMod) {
				if (DoConsequence(actor, source)) {
					SetConsequenceTargetKnown(actor->formID);
					return;
				}
			}
		}
	}

	void ConsSexEnded(RE::Actor* sex_with) {
		auto settings = Settings::GetSingleton();
		if (!settings->consEnable) {
			return;
		}
		if (settings->consFollowersBlock && Util::GetFollowers().size() > 0) {
			return;
		}

		auto player = RE::PlayerCharacter::GetSingleton();
		//log::trace("Consequence Sex end trigger.");
		auto watchingActors = Util::GetWatchingActors(player, !settings->consAllowFollowers, settings->consScanRadius);
		Util::ShuffleVector(watchingActors);
		for (auto actor : watchingActors) {
			if (IsConsequenceTargetKnown(actor->formID) || actor == sex_with) {
				continue;
			}

			bool actorIsGuard = ActorIsGuard(actor);
			if (actorIsGuard) {
				if (Util::random<float>() < settings->consGuardScanSex) {
					if (ConsFine(actor, consequenceSource::kSeenHavingSex)) {
						SetConsequenceTargetKnown(actor->formID);
						return;
					}
				}
			}
			if (!actorIsGuard || settings->consGuardNormal) {
				if (Util::random<float>() < settings->consScanSex) {
					if (DoConsequence(actor, consequenceSource::kSeenHavingSex)) {
						SetConsequenceTargetKnown(actor->formID);
						return;
					}
				}
			}
		}
	}

	void ConsUpdate() {
		auto player = RE::PlayerCharacter::GetSingleton();
		auto settings = Settings::GetSingleton();

		if (!settings->consEnable || Serialized::GetCounters()->clock_GlobalTicker % settings->consScanInterval != 0) {
			return;
		}

		if (settings->consFollowersBlock && Util::GetFollowers().size() > 0) {
			return;
		}

		auto watchingActors = Util::GetWatchingActors(player, !settings->consAllowFollowers, settings->consScanRadius);
		if (watchingActors.empty()) {
			return;
		}

		bool isNude = getIsNude(player, true);
		auto keywords = GetWornDeviceKeywords(player);
		bool isChastity = settings->consTolerableChastity && keywords.contains("zad_DeviousBelt") && keywords.contains("zad_DeviousBra");
		bool isHeavy = keywords.contains("zad_DeviousHeavyBondage");
		bool isRestrained = GetVisibleDeviceCount(player) >= settings->consRestrainedCount;
		bool isTattooed = GetTattooCount(player) >= settings->consTattooCount;

		auto source = consequenceSource::kUnknown;
		float chance = 0;
		float guard_chance = 0;

		if (isHeavy) {
			source = consequenceSource::kSeenWithHeavy;
			chance = settings->consScanHeavy;
			guard_chance = settings->consGuardScanRestrained;
		}
		else {
			if (isRestrained) {
				source = consequenceSource::kSeenRestrained;
				chance = settings->consScanRestrained;
				guard_chance = settings->consGuardScanRestrained;
			}
			if (isNude && !isChastity) {
				source = consequenceSource::kSeenNude;
				chance = settings->consScanNude;
				guard_chance = settings->consGuardScanNude;
			}
			if (isTattooed) {
				source = consequenceSource::kSeenTattoos;
				chance = settings->consScanTattoo;
				guard_chance = settings->consGuardScanTattoo;
			}
		}

		if (source == consequenceSource::kUnknown) {
			return;
		}

		//log::trace("Checking consequence scan");

		Util::ShuffleVector(watchingActors);

		for (auto actor : watchingActors) {
			if (IsConsequenceTargetKnown(actor->formID)) {
				continue;
			}

			bool actorIsGuard = ActorIsGuard(actor);
			if (actorIsGuard) {
				if (Util::random<float>() < guard_chance) {
					if (ConsFine(actor, source)) {
						SetConsequenceTargetKnown(actor->formID);
						return;
					}
				}
			}
			if (!actorIsGuard || settings->consGuardNormal) {
				if (Util::random<float>() < chance) {
					if (DoConsequence(actor, source)) {
						SetConsequenceTargetKnown(actor->formID);
						return;
					}
				}
			}
		}
	}
}