#pragma once

#include "Scripting.hpp"

namespace DCURSES {
	constexpr auto ZADC_CONTRAPTIONS = { 0x12c7, 0x1d96, 0x5904, 0x63f7, 0x63f9, 0x6963, 0x7db9, 0x7ef5, 0x8324, 0x8325, 0x845d, 0x89c4, 0xd997, 0xe9e6, 0xe9e7, 0xe9e8, 0xe9e9, 0xe9ea, 0x1001f, 0x1002a, 0x10033, 0x1003d, 0x10047 };


	RE::TESObjectACTI* GetRandomContraption() {
		std::vector<RE::TESObjectACTI*> contraptions;
		for (auto acti_id : ZADC_CONTRAPTIONS) {
			auto activator = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectACTI>(acti_id, "Devious Devices - Contraptions.esm");
			if (!activator) {
				log::warn("Unable to get activator for form {:x}", acti_id);
			}
			else {
				contraptions.push_back(activator);
			}
		}

		return contraptions[Util::randomInt(static_cast<int>(contraptions.size()))];
	}

	RE::TESObjectREFR* GetContraptionForActor(RE::Actor* actor) {
		if (!actor) return nullptr;
		RE::TESObjectREFR* ref = nullptr;

		actor->GetParentCell()->ForEachReferenceInRange(actor->GetPosition(), 500, [&](RE::TESObjectREFR& akRef) {
			RE::TESObjectREFR* refr = &akRef;

			auto scriptObject = ContraptionsGetRefScript(refr);

			if (!scriptObject) {
				return RE::BSContainer::ForEachResult::kContinue;
			}

			RE::BSScript::Variable* user = scriptObject->GetProperty("User");
			if (!user) {
				return RE::BSContainer::ForEachResult::kContinue;
			}

			auto user_actor = user->Unpack<RE::Actor*>();

			if (actor == user_actor) {
				log::info("Found furniture {} for actor {}", refr->GetName(), actor->GetName());
				ref = refr;
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return ref;
	}

	void CreateAndLockContraption(RE::Actor* actor) {
		ForceThirdPerson();
		SKSE::GetTaskInterface()->AddTask([actor]() {
			auto ptr = actor->PlaceObjectAtMe(GetRandomContraption(), false);
			auto object = ptr.get();

			auto scriptObject = ContraptionsGetRefScript(object);
			if (scriptObject) {
				scriptObject.get()->GetProperty("DestroyOnRemove")->SetBool(true);
				if (settings.eventContraptionTime > 0.0) {
					scriptObject.get()->GetProperty("isSelfBondage")->SetBool(true);
					scriptObject.get()->GetProperty("ForceTimer")->SetBool(true);
					scriptObject.get()->GetProperty("SelfBondageReleaseTimer")->SetFloat(settings.eventContraptionTime);
				}
			}

			object->data.angle = RE::NiPoint3(0, actor->GetAngleY(), actor->GetAngleZ());

			std::thread{ [actor, object] {
				std::this_thread::sleep_for(250ms);
				SKSE::GetTaskInterface()->AddTask([actor, object]() {
					ContraptionsLockActor(actor, object);
				});
			} }.detach();
			
			//ContraptionsLockActor(actor, object);
		});
	}
}