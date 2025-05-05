#pragma once

#include "jcontainers.hpp"
#include "Settings.hpp"
#include "MGEF_Controller.hpp"

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

	int GetLewdMark() {
		return counters.ActiveLewdMark;
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

	void DecrementCounterForMark(int mark) {
		if (mark == GetLewdMark()) {
			switch (mark) {
			case TAT_ALLURE:
				ModifyEffectMagnitude(ALLURE_EFFECT, -1);
				log::info("Incrementing counter for Allure mark.");
				break;
			case TAT_HEAT:
				ModifyEffectMagnitude(HEAT_EFFECT, -1);
				log::info("Incrementing counter for Heat mark.");
				break;
			case TAT_BONDAGE:
				ModifyEffectMagnitude(BONDAGE_EFFECT, -1);
				log::info("Incrementing counter for Bondage mark.");
				break;
			case TAT_NUDITY:
				ModifyEffectMagnitude(NUDITY_EFFECT, -1);
				log::info("Incrementing counter for Nudity mark.");
				break;
			}
		}
	}

	bool _AddLewdMarkGlow(int index, int32_t color, int32_t glow) {
		auto actor = RE::PlayerCharacter::GetSingleton();

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

	bool _AddLewdMarkMain(int index, int32_t color, int32_t glow) {
		auto actor = RE::PlayerCharacter::GetSingleton();

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

	int GetLewdMarkApplied() {
		if (!slavetats_ng::iface) return 0;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return 0;

		auto actor = RE::PlayerCharacter::GetSingleton();

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

	bool AddLewdMark(int index) {
		if (!slavetats_ng::iface) return false;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return false;
		if (!CheckLewdMarksInstalled()) return false;
		
		auto base_color = GetColorForMark(index);
		auto glowColor = Util::ColorScale(base_color, 0.8);

		if (_AddLewdMarkGlow(index, glowColor, glowColor) && _AddLewdMarkMain(index, base_color, glowColor)) {
			counters.ActiveLewdMark = index;
			return true;
		}
		return false;
		
	}

	void RemoveLewdMark(int index = -1) {
		if (!slavetats_ng::iface) return;
		if (!jcontainers::JCWrapper::GetSingleton()->IsInitialized()) return;
		if (!CheckLewdMarksInstalled()) return;

		auto actor = RE::PlayerCharacter::GetSingleton();

		if (index == -1) {
			index = GetLewdMark();
		}

		counters.ActiveLewdMark = 0;

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
		if (actor == RE::PlayerCharacter::GetSingleton()) {
			RemoveLewdMark();
		}
	}

	void MarkControllerUpdate() {
		auto mark = GetLewdMark();
		auto applied = GetLewdMarkApplied();

		if (applied != mark) {
			log::trace("Resolving mark discrepancy, expected {}, had {}", mark, applied);
			if (mark == -1) {
				RemoveLewdMark(applied);
			}
			else if (applied > 0) {
				RemoveLewdMark(applied);
				AddLewdMark(mark);
			}
			else {
				AddLewdMark(mark);
			}
		}

		SetEffectVisible(ALLURE_EFFECT, false);
		SetEffectVisible(HEAT_EFFECT, false);
		SetEffectVisible(NUDITY_EFFECT, false);
		SetEffectVisible(BONDAGE_EFFECT, false);

		switch (mark) {
		case TAT_ALLURE:
			SetEffectVisible(ALLURE_EFFECT);
			break;
		case TAT_HEAT:
			SetEffectVisible(HEAT_EFFECT);
			break;
		case TAT_NUDITY:
			SetEffectVisible(NUDITY_EFFECT);
			break;
		case TAT_BONDAGE:
			SetEffectVisible(BONDAGE_EFFECT);
			break;
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