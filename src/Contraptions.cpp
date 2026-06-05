#include "Contraptions.h"

#include "Settings.h"
#include "form_ids.h"
#include "Utils.h"
#include "Scripting.h"

namespace DCURSES {
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

		return contraptions[Util::random(contraptions.size())];
	}

	RE::TESObjectREFR* GetContraptionForActor(RE::Actor* actor) {
		if (!actor) return nullptr;
		RE::TESObjectREFR* ref = nullptr;

		actor->GetParentCell()->ForEachReferenceInRange(actor->GetPosition(), 500, [&](RE::TESObjectREFR* refr) {
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
				//log::info("Found furniture {} for actor {}", refr->GetName(), actor->GetName());
				ref = refr;
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return ref;
	}

	RE::TESObjectACTI* CreateAndLockContraption(RE::Actor* actor) {
		auto contraption = GetRandomContraption();
		if (!Settings::GetSingleton()->disableForce3rdPerson) { ScriptingManager().ForceThirdPerson(); }
		SKSE::GetTaskInterface()->AddTask([actor, contraption]() {
			auto ptr = actor->PlaceObjectAtMe(contraption, false);
			auto object = ptr.get();
			auto settings = Settings::GetSingleton();

			auto scriptObject = ContraptionsGetRefScript(object);
			if (scriptObject) {
				scriptObject.get()->GetProperty("DestroyOnRemove")->SetBool(true);
				if (settings->eventContraptionTime > 0.0) {
					scriptObject.get()->GetProperty("isSelfBondage")->SetBool(true);
					scriptObject.get()->GetProperty("ForceTimer")->SetBool(true);
					scriptObject.get()->GetProperty("SelfBondageReleaseTimer")->SetFloat(settings->eventContraptionTime);
				}
			}

			object->data.angle = RE::NiPoint3(0, actor->GetAngleY(), actor->GetAngleZ());
			Util::ExecuteWithDelay(1500ms, [actor, object] {
				ScriptingManager().ContraptionsLockActor(actor, object);
				});
			});
		return contraption;
	}
}