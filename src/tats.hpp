#pragma once

#include "jcontainers.hpp"
#include "Settings.hpp"

#include "../include/SlaveTatsNG_Interface.h"

using namespace SKSE;

namespace slavetats_ng {
	const SlaveTatsNG::Addresses* iface = nullptr;

	void messaging_hook(SKSE::MessagingInterface::Message* a_msg)
	{
		if (a_msg && a_msg->type == SlaveTatsNG::MessageType::Interface) {
			iface = SlaveTatsNG::Addresses::from_void(a_msg->data);
			log::info("SlaveTatsNG Interface found: address = {}", (void*)iface);
		}
	}

	inline bool query_available_tattoos(int a_template, int matches, int applied = 0, RE::BSFixedString domain = "default") {
		if (!iface) return true;
		return iface->query_available_tattoos(a_template, matches, applied, domain);
	}
	inline bool query_applied_tattoos(RE::Actor* target, int a_template, int matches, RE::BSFixedString except_area = "", int except_slot = -1) {
		if (!iface) return true;
		return iface->query_applied_tattoos(target, a_template, matches, except_area, except_slot);
	}
	inline bool simple_remove_tattoo(RE::Actor* target, RE::BSFixedString section, RE::BSFixedString name, bool last = true, bool silent = false) {
		if (!iface) return true;
		return iface->simple_remove_tattoo(target, section, name, last, silent);
	}
	inline bool remove_tattoos(RE::Actor* target, int a_template, bool ignore_lock = false, bool silent = false) {
		if (!iface) return true;
		return iface->remove_tattoos(target, a_template, ignore_lock, silent);
	}
	inline bool add_tattoo(RE::Actor* target, int tattoo, int slot = -1, bool ignore_lock = false, bool silent = false) {
		if (!iface) return true;
		return iface->add_tattoo(target, tattoo, slot, ignore_lock, silent);
	}
	inline bool synchronize_tattoos(RE::Actor* target, bool silent = false) {
		if (!iface) return true;
		return iface->synchronize_tattoos(target, silent);
	}
}

namespace DCURSES {
	static const int TAT_ALLURE = 13;
	static const int TAT_HEAT = 11;
	static const int TAT_BONDAGE = 71;
	static const int TAT_NUDITY = 79;

	static const int TAT_MERIDIA = 74;

	int GetTattooCount(RE::Actor* actor) {
		if (!actor) return 0;
		if (!slavetats_ng::iface) return 0;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return 0;

		using namespace jcontainers;

		int a_template = JValue::addToPool(JMap::object(), "DCURSES");
		int matches = JValue::addToPool(JArray::object(), "DCURSES");

		JArray::clear(matches);

		if (slavetats_ng::query_applied_tattoos(actor, a_template, matches)) {
			JValue::cleanPool("DCURSES");
			return -1;
		}

		return JArray::count(matches);
	}

	bool CheckLewdMarksInstalled() {
		if (!slavetats_ng::iface) return false;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return false;

		using namespace jcontainers;

		int a_template = JValue::addToPool(JMap::object(), "DCURSES");
		int matches = JValue::addToPool(JArray::object(), "DCURSES");

		JMap::setStr(a_template, "section", "LewdMarks");

		if (slavetats_ng::query_available_tattoos(a_template, matches)) {
			JValue::cleanPool("DCURSES");
			return false;
		}

		if (JArray::count(matches) == 0) {
			JValue::cleanPool("DCURSES");
			return false;
		}

		JValue::cleanPool("DCURSES");
		return true;
	}

	class MarkEffectVisitor : public RE::MagicTarget::ForEachActiveEffectVisitor {
	public:
		RE::EffectSetting* match = nullptr;
		RE::ActiveEffect* markEffect = nullptr;
		// Inherited via ForEachActiveEffectVisitor
		virtual RE::BSContainer::ForEachResult Accept(RE::ActiveEffect* a_effect) override
		{
			if (a_effect->GetBaseObject() == match) {
				markEffect = a_effect;
				return RE::BSContainer::ForEachResult::kStop;
			}
			return RE::BSContainer::ForEachResult::kContinue;
		}

		MarkEffectVisitor() {
			match = RE::TESDataHandler::GetSingleton()->LookupForm<RE::EffectSetting>(MARK_EFFECT, "Devious Curses.esp");
		}
	};

	RE::ActiveEffect* GetMarkEffect(RE::Actor* actor) {
		auto target = actor->GetMagicTarget();
		auto visitor = MarkEffectVisitor();
		target->VisitEffects(visitor);
		return visitor.markEffect;
	}

	int GetLewdMark(RE::Actor* actor) {
		auto active = GetMarkEffect(actor);
		if (active) {
			return static_cast<int>(active->magnitude);
		}
		return 0;
	}

	int GetColorForMark(int mark) {
		switch (mark) {
		case TAT_ALLURE:
			return settings.LMAllureColor;
		case TAT_HEAT:
			return settings.LMHeatColor;
		case TAT_BONDAGE:
			return settings.LMBondageColor;
		case TAT_NUDITY:
			return settings.LMNudityColor;
		case TAT_MERIDIA:
			return 0x220022;
		}
		return 0;
	}

	void SetLewdMarkForEffect(RE::Actor* actor, int mark) {
		auto active = GetMarkEffect(actor);
		if (active) {
			active->magnitude = static_cast<float>(mark);
		}
	}

	void SetMarkControlerVisible(RE::Actor* actor, bool visible = true) {
		if (actor != RE::PlayerCharacter::GetSingleton()) { return; }

		auto effect = RE::TESDataHandler::GetSingleton()->LookupForm<RE::EffectSetting>(MARK_EFFECT, "Devious Curses.esp");
		if (visible) {
			effect->data.flags.reset(RE::EffectSetting::EffectSettingData::Flag::kHideInUI);
		}
		else {
			effect->data.flags.set(RE::EffectSetting::EffectSettingData::Flag::kHideInUI);
		}
	}

	void UpdateMarkControlerInfo() {
		auto active = GetMarkEffect(RE::PlayerCharacter::GetSingleton());
		if (active) {
			auto effect = active->GetBaseObject();
			switch (static_cast<int>(active->magnitude)) {
			case TAT_ALLURE:
				effect->fullName = "Alure Mark";
				effect->magicItemDescription = fmt::format("You still need to have sex {} times!", counters.LMSexCounter * -1);
				break;
			case TAT_HEAT:
				effect->fullName = "Heat Mark";
				effect->magicItemDescription = fmt::format("You still need to open {} containers!", counters.LMContainersOpened * -1);
				break;
			case TAT_BONDAGE:
				effect->fullName = "Bondage Mark";
				effect->magicItemDescription = fmt::format("The mark still needs to equip {} devices!", counters.LMDevicesEquipped * -1);
				break;
			case TAT_NUDITY:
				effect->fullName = "Nudity Mark";
				effect->magicItemDescription = fmt::format("You still need to talk to {} different people!", counters.LMPeopleTalked * -1);
				break;
			case TAT_MERIDIA:
				effect->fullName = "Malkoran's Mark";
				effect->magicItemDescription = "You aren't sure what the mark does, but you know something will happen soon!";
				break;
			}
		}
	}

	void IncrementCounterForMark(RE::Actor* actor, int mark) {
		if (mark == GetLewdMark(actor)) {
			switch (mark) {
			case TAT_ALLURE:
				counters.LMSexCounter += 1;
				log::info("Incrementing counter for Allure mark.");
				break;
			case TAT_HEAT:
				counters.LMContainersOpened += 1;
				log::info("Incrementing counter for Heat mark.");
				break;
			case TAT_BONDAGE:
				counters.LMDevicesEquipped += 1;
				log::info("Incrementing counter for Bondage mark.");
				break;
			case TAT_NUDITY:
				counters.LMPeopleTalked += 1;
				log::info("Incrementing counter for Nudity mark.");
				break;
			}
			UpdateMarkControlerInfo();
		}
	}

	bool _AddLewdMarkGlow(RE::Actor* actor, int index, int32_t color, int32_t glow) {
		if (!actor) return false;

		using namespace jcontainers;
		std::string mark = fmt::format("{:03}", index);
		log::trace("adding tattoo {}", mark);
		int a_template = JValue::addToPool(JMap::object(), "DCURSES");
		int matches = JValue::addToPool(JArray::object(), "DCURSES");
		int tattoo = 0;

		JMap::setStr(a_template, "section", "LewdMarks-glow");
		JMap::setStr(a_template, "name", mark);

		if (slavetats_ng::query_available_tattoos(a_template, matches)) {
			log::warn("JContainers error query_available_tattoos");
			JValue::cleanPool("DCURSES");
			return false;
		}

		if (JArray::count(matches) == 0) {
			JValue::cleanPool("DCURSES");
			log::warn("JContainers error count available");
			return false;
		}

		tattoo = JValue::addToPool(JArray::getObj(matches, 0), "DCURSES");
		JMap::setInt(tattoo, "color", color);
		JMap::setInt(tattoo, "glow", glow);
		JMap::setInt(tattoo, "locked", 1);
		JMap::setFlt(tattoo, "invertedAlpha", 0.0f);

		JArray::clear(matches);

		if (slavetats_ng::query_applied_tattoos(actor, a_template, matches)) {
			JValue::cleanPool("DCURSES");
			log::warn("JContainers error query_applied_tattoos");
			return false;
		}

		if (JArray::count(matches) > 0) {
			JValue::cleanPool("DCURSES");
			log::warn("JContainers error count");
			return false;
		}

		if (slavetats_ng::add_tattoo(actor, tattoo, -1, false, true)) {
			JValue::cleanPool("DCURSES");
			log::warn("JContainers error add_tattoo");
			return false;
		}

		JValue::cleanPool("DCURSES");
		return true;
	}

	bool _AddLewdMarkMain(RE::Actor* actor, int index, int32_t color, int32_t glow) {
		if (!actor) return false;

		using namespace jcontainers;
		std::string mark = fmt::format("{:03}", index);
		log::trace("adding tattoo glow {}", mark);
		int a_template = JValue::addToPool(JMap::object(), "DCURSES");
		int matches = JValue::addToPool(JArray::object(), "DCURSES");
		int tattoo = 0;

		JMap::setStr(a_template, "section", "LewdMarks");
		JMap::setStr(a_template, "name", mark);

		if (slavetats_ng::query_available_tattoos(a_template, matches)) {
			JValue::cleanPool("DCURSES");
			log::warn("JContainers error query_available_tattoos");
			return false;
		}

		tattoo = JValue::addToPool(JArray::getObj(matches, 0), "DCURSES");
		JMap::setInt(tattoo, "color", color);
		JMap::setInt(tattoo, "glow", glow);
		JMap::setInt(tattoo, "locked", 1);
		JMap::setFlt(tattoo, "invertedAlpha", 0.0f);

		JArray::clear(matches);

		if (slavetats_ng::query_applied_tattoos(actor, a_template, matches)) {
			JValue::cleanPool("DCURSES");
			log::warn("JContainers error query_applied_tattoos");
			return false;
		}

		if (JArray::count(matches) > 0) {
			JValue::cleanPool("DCURSES");
			log::warn("JContainers error count");
			return false;
		}

		if (slavetats_ng::add_tattoo(actor, tattoo, -1, false, true)) {
			JValue::cleanPool("DCURSES");
			log::warn("JContainers error add_tattoo");
			return false;
		}

		if (slavetats_ng::synchronize_tattoos(actor, true)) {
			log::warn("JContainers error synchronize_tattoos");
			JValue::cleanPool("DCURSES");
			return false;
		}

		JValue::cleanPool("DCURSES");
		return true;
	}

	int GetLewdMarkApplied(RE::Actor* actor) {
		if (!actor) return 0;
		if (!slavetats_ng::iface) return 0;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return 0;

		using namespace jcontainers;

		int a_template = JValue::addToPool(JMap::object(), "DCURSES");
		int matches = JValue::addToPool(JArray::object(), "DCURSES");

		JMap::setStr(a_template, "section", "LewdMarks");

		JArray::clear(matches);

		if (slavetats_ng::query_applied_tattoos(actor, a_template, matches)) {
			JValue::cleanPool("DCURSES");
			return 0;
		}

		if (JArray::count(matches) > 0) {
			JValue::cleanPool("DCURSES");
			return std::stoi(JMap::getStr(JArray::getObj(matches, 0), "name").c_str());
		}

		JValue::cleanPool("DCURSES");
		return 0;
	}

	void SetMarkColor(RE::Actor* actor, int32_t color, int32_t glow) {
		if (!actor) return;
		if (!slavetats_ng::iface) return;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return;
		if (!CheckLewdMarksInstalled()) return;

		using namespace jcontainers;

		int index = GetLewdMark(actor);
		slavetats_ng::simple_remove_tattoo(actor, "LewdMarks", fmt::format("{:03}", index), false);
		_AddLewdMarkMain(actor, index, color, glow);
		return;
	}

	bool AddLewdMark(RE::Actor* actor, int index) {
		if (!actor) return false;
		if (!slavetats_ng::iface) return false;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return false;
		if (!CheckLewdMarksInstalled()) return false;
		
		auto base_color = GetColorForMark(index);
		auto glowColor = Util::ColorScale(base_color, 0.8);

		if (_AddLewdMarkGlow(actor, index, glowColor, glowColor) && _AddLewdMarkMain(actor, index, base_color, glowColor)) {
			SetLewdMarkForEffect(actor, index);
			UpdateMarkControlerInfo();
			SetMarkControlerVisible(actor);
			return true;
		}
		return false;
		
	}

	void RemoveLewdMark(RE::Actor* actor, int index = -1) {
		if (!actor) return;
		if (!slavetats_ng::iface) return;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return;
		if (!CheckLewdMarksInstalled()) return;

		if (index == -1) {
			index = GetLewdMark(actor);
		}

		SetLewdMarkForEffect(actor, 0);
		SetMarkControlerVisible(actor, false);

		slavetats_ng::simple_remove_tattoo(actor, "LewdMarks", fmt::format("{:03}", index), false);
		slavetats_ng::simple_remove_tattoo(actor, "LewdMarks-glow", fmt::format("{:03}", index), true);
	}

	void RemoveAllTattoos(RE::Actor* actor) {
		if (!actor) return;
		if (!slavetats_ng::iface) return;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return;

		using namespace jcontainers;
		int a_template = JValue::addToPool(JMap::object(), "DCURSES");
		slavetats_ng::remove_tattoos(actor, a_template);
		slavetats_ng::synchronize_tattoos(actor, true);
		JValue::cleanPool("DCURSES");
		RemoveLewdMark(actor);
	}

	void MarkControllerUpdate() {
		auto player = RE::PlayerCharacter::GetSingleton();
		auto mark = GetLewdMark(player);
		auto applied = GetLewdMarkApplied(player);

		if (applied != mark) {
			log::trace("Resolving mark discrepancy, expected {}, had {}", mark, applied);
			if (mark == -1) {
				RemoveLewdMark(player, applied);
			}
			else if (applied > 0) {
				RemoveLewdMark(player, applied);
				AddLewdMark(player, mark);
			}
			else {
				AddLewdMark(player, mark);
			}
		}

		if (mark > 0) {
			SetMarkControlerVisible(player);
		}
		else {
			SetMarkControlerVisible(player, false);
		}
	}

	bool P_CheckSTNG(RE::StaticFunctionTag*) {
		return slavetats_ng::iface;
	}

	bool P_CheckLM(RE::StaticFunctionTag*) {
		return CheckLewdMarksInstalled();
	}

	bool PapyrusFunctionsTats(RE::BSScript::IVirtualMachine* ivm) {
		ivm->RegisterFunction("CheckSTNG", "DCurses_MCM", P_CheckSTNG);
		ivm->RegisterFunction("CheckLM", "DCurses_MCM", P_CheckLM);
		return true;
	}
}