#pragma once

#include "ModEvents.hpp"

using namespace SKSE;


namespace DCURSES {
	//Events

	void AIEventBondage(std::string containerName, std::string device_names) {
		auto playerName = RE::PlayerCharacter::GetSingleton()->GetName();
		auto line = fmt::format("{} has just trigger a magical trap that bound them in bondage devices. The curse was triggered when {} touched a {}. These are the devices that were equipped: {}", playerName, playerName, containerName, device_names);

		CustomModEvent("MinAI_RegisterEvent").PushString(line).PushString("info_dcurses").Send();
	}

	void AIEventContraption(std::string contraptionName) {
		auto playerName = RE::PlayerCharacter::GetSingleton()->GetName();
		auto line = fmt::format("{} has just trigger a magical trap that stripped them nude and strung them up onto a {} against their will! They will have to struggle against it to escape.", playerName, contraptionName);

		CustomModEvent("MinAI_RegisterEvent").PushString(line).PushString("info_dcurses").Send();
	}

	void AIEventTattoos(int tattoo_count) {
		auto playerName = RE::PlayerCharacter::GetSingleton()->GetName();
		auto line = fmt::format("{} has just trigger a magical trap that branded them with {} tattoos!", playerName, tattoo_count);

		CustomModEvent("MinAI_RegisterEvent").PushString(line).PushString("info_dcurses").Send();
	}

	void AIEventMagicKey() {
		auto playerName = RE::PlayerCharacter::GetSingleton()->GetName();
		auto line = fmt::format("{} used a precious magic key, resulting in all of their restraints have been removed and sent to oblivion!", playerName);

		CustomModEvent("MinAI_RegisterEvent").PushString(line).PushString("info_dcurses").Send();
	}

	void AIEventTattooCharm() {
		auto playerName = RE::PlayerCharacter::GetSingleton()->GetName();
		auto line = fmt::format("{} smeared the universal solvent on themselves, resulting in all of their tattoos fading instantly!", playerName);

		CustomModEvent("MinAI_RegisterEvent").PushString(line).PushString("info_dcurses").Send();
	}

	void AIEventAddLewdMark() {
		auto playerName = RE::PlayerCharacter::GetSingleton()->GetName();
		auto line = fmt::format("{} has just been painfully branded with a strange lewd tattoo!", playerName);

		CustomModEvent("MinAI_RegisterEvent").PushString(line).PushString("info_dcurses").Send();
	}

	void AIEventSummonerCollarAdd() {
		auto playerName = RE::PlayerCharacter::GetSingleton()->GetName();
		auto line = fmt::format("{} has just been equipped with a collar that forces them to have sex with summoned creatures!", playerName);

		CustomModEvent("MinAI_RegisterEvent").PushString(line).PushString("info_dcurses").Send();
	}

	void AIEventLivingLatexAdd() {
		auto playerName = RE::PlayerCharacter::GetSingleton()->GetName();
		auto line = fmt::format("{} has just been infected with living latex. It seems to be dormant at the moment.", playerName);

		CustomModEvent("MinAI_RegisterEvent").PushString(line).PushString("info_dcurses").Send();
	}

	void AIEventLivingLatexActivate() {
		auto playerName = RE::PlayerCharacter::GetSingleton()->GetName();
		auto line = fmt::format("The latex covering {} has just awoken, causing them to be covered in more latex and ebonite devices! The latex is now squirming and writhing around.", playerName);

		CustomModEvent("MinAI_RegisterEvent").PushString(line).PushString("info_dcurses").Send();
	}

	void AIEventLivingLatexRemove() {
		auto playerName = RE::PlayerCharacter::GetSingleton()->GetName();
		auto line = fmt::format("{} has finally escaped from the living latex that has been binding them.", playerName);

		CustomModEvent("MinAI_RegisterEvent").PushString(line).PushString("info_dcurses").Send();
	}

	//Context

	void AIContextAddAllureMark() {
		auto playerName = RE::PlayerCharacter::GetSingleton()->GetName();
		auto line = fmt::format("{} has been branded with a lewd tattoo of allure. This mark will make every nearby character very horny and over-sexual.", playerName);

		CustomModEvent("MinAI_SetContext").PushString("DeviousCurses").PushString("LewdMarks").PushString(line).PushInt(600).Send();
	}

	void AIContextAddHeatMark() {
		auto playerName = RE::PlayerCharacter::GetSingleton()->GetName();
		auto line = fmt::format("{} has been branded with a lewd tattoo of heat. This mark will make {} get very horny very fast.", playerName, playerName);

		CustomModEvent("MinAI_SetContext").PushString("DeviousCurses").PushString("LewdMarks").PushString(line).PushInt(600).Send();
	}

	void AIContextAddBondageMark() {
		auto playerName = RE::PlayerCharacter::GetSingleton()->GetName();
		auto line = fmt::format("{} has been branded with a lewd tattoo of bondage. This mark will force {} to equip bondage devices from their own inventory.", playerName, playerName);

		CustomModEvent("MinAI_SetContext").PushString("DeviousCurses").PushString("LewdMarks").PushString(line).PushInt(600).Send();
	}

	void AIContextAddNudityMark() {
		auto playerName = RE::PlayerCharacter::GetSingleton()->GetName();
		auto line = fmt::format("{} has been branded with a lewd tattoo of nudity. This mark will prevent {} from equipping any clothes, leaving them exposed to everyone.", playerName, playerName);

		CustomModEvent("MinAI_SetContext").PushString("DeviousCurses").PushString("LewdMarks").PushString(line).PushInt(600).Send();
	}

	void AIContextAddBrandingMark() {
		auto playerName = RE::PlayerCharacter::GetSingleton()->GetName();
		auto line = fmt::format("{} has been branded with a lewd tattoo of branding. This mark will brand {} with tattoos periodically.", playerName, playerName);

		CustomModEvent("MinAI_SetContext").PushString("DeviousCurses").PushString("LewdMarks").PushString(line).PushInt(600).Send();
	}

	void AIContextRemoveLewdMark() {
		auto playerName = RE::PlayerCharacter::GetSingleton()->GetName();
		auto line = fmt::format("{} does not have a lewd mark.", playerName);

		CustomModEvent("MinAI_SetContext").PushString("DeviousCurses").PushString("LewdMarks").PushString(line).PushInt(0).Send();
	}
}