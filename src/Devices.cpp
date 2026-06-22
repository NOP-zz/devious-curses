#include "Devices.h"

#include "OppDevices.h"
#include "Settings.h"
#include "Utils.h"
#include "Scripting.h"
#include "Serializer.h"

#include "apis/DDNG_API.h"
#include "apis/JSON.hpp"
#include "SexLabPPFunctions.h"

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
#include <fstream>

using namespace SKSE;

namespace DCURSES {
	void Devices::ClearLists() {
		//CODEGEN_START_DEVICES_CLEAR
		anything.list.clear();
		belts.list.clear();
		beltsPiercings.list.clear();
		beltsCages.list.clear();
		bras.list.clear();
		plugsV.list.clear();
		plugsVBasic.list.clear();
		plugsVLock.list.clear();
		plugsVInf.list.clear();
		plugsA.list.clear();
		plugsABasic.list.clear();
		plugsALock.list.clear();
		plugsAInf.list.clear();
		collars.list.clear();
		legCuffs.list.clear();
		legCuffsStandard.list.clear();
		legCuffsShackles.list.clear();
		armCuffs.list.clear();
		piercingsN.list.clear();
		piercingsV.list.clear();
		blindfolds.list.clear();
		harnesses.list.clear();
		harnessesOpen.list.clear();
		gags.list.clear();
		gagsStandard.list.clear();
		gagsLarge.list.clear();
		gagsOpen.list.clear();
		gagsOpenLarge.list.clear();
		corsetsNoBelt.list.clear();
		corsetsBelt.list.clear();
		boots.list.clear();
		glovesMittens.list.clear();
		glovesNoMittens.list.clear();
		hoodsBlockAll.list.clear();
		hoodsBlockGag.list.clear();
		hoodsBlockEye.list.clear();
		hoodsNoBlock.list.clear();
		armbindersPlus.list.clear();
		armbinders.list.clear();
		elbowbinders.list.clear();
		yokes.list.clear();
		armShackles.list.clear();
		petSuits.list.clear();
		suitsSimple.list.clear();
		straitJackets.list.clear();
		straitJacketsAllowRun.list.clear();
		straitJacketsLegbinder.list.clear();
		hobbleSkirts.list.clear();
		hobbleSkirtsRelaxed.list.clear();
		hobbleSkirtsForcedWalk.list.clear();
		//CODEGEN_END_DEVICES_CLEAR
	}

	bool NeedUpdateForExclusions() {
		bool needsUpdate = false;
		if (lastExclusionsEditTime.has_value() && lastExclusionsEditTime != std::filesystem::last_write_time(EXCLUSIONS_FILE)) {
			needsUpdate = true;
		}
		if (lastModExclusionsEditTime.has_value() && lastModExclusionsEditTime != std::filesystem::last_write_time(MOD_EXCLUSIONS_FILE)) {
			needsUpdate = true;
		}
		return needsUpdate;
	}

	DeviceList GetAdjustedDeviceList(DeviceList* list, std::set<std::string> skipList, std::string theme) {
		DeviceList result;
		//result.list.reserve(list->list.size() / 2);
		result.name = list->name;
		for (auto x : list->list) {
			if (Util::testFormComp(theme, x.inv)) {
				bool canUse = true;
				for (auto key : skipList) {
					if (x.rend->HasKeywordString(key)) {
						canUse = false;
						continue;
					}
				}
				if (canUse) {
					result.push_back(x);
				}
			}
		}
		return result;
	}

	std::optional<DeviceData> GetRandomDevice(DeviceList* list, std::set<std::string> skipList, std::string theme) {
		if (list == nullptr) { return std::nullopt; }
		if (theme == "" && skipList.empty()) {
			if (list->list.empty()) { return std::nullopt; }
			size_t r = Util::random(list->list.size());
			return (list->list)[r];
		}

		auto adj = GetAdjustedDeviceList(list, skipList, theme);
		if (adj.list.empty()) { return std::nullopt; }
		size_t r = Util::random(static_cast<int>(adj.list.size()));
		return (adj.list)[r];
	}

	void CreateExclusionsFileIfNeeded() {
		nlohmann::json j = nlohmann::json::array();

		if (!std::filesystem::exists(EXCLUSIONS_FILE)) {
			log::warn("Unable to load exclusions file. Creating blank file.");
			std::ofstream o(EXCLUSIONS_FILE);
			o << std::setw(4) << j << std::endl;
		}
	}

	void CreateModExclusionsFileIfNeeded() {
		nlohmann::json j = nlohmann::json::array();

		if (!std::filesystem::exists(MOD_EXCLUSIONS_FILE)) {
			log::warn("Unable to load exclusions file. Creating default file.");
			std::ofstream o(MOD_EXCLUSIONS_FILE);

			j = nlohmann::json::array({
				"DeviousFollowers.esp",
				"TheTrappingsOfFate.esp",
				"DeviouslyAccessible.esp",
				});

			o << std::setw(4) << j << std::endl;
		}
	}

	std::vector<std::string> GetDeviceExclusions() {
		CreateExclusionsFileIfNeeded();

		nlohmann::json j = nlohmann::json::array();

		std::ifstream i(EXCLUSIONS_FILE);

		try {
			i >> j;
		}
		catch (...) {
			log::error("Exclusions file has garbled data.");
			return std::vector<std::string>();
		}


		return j.get<std::vector<std::string>>();
	}

	std::vector<std::string> GetModExclusions() {
		CreateModExclusionsFileIfNeeded();

		nlohmann::json j = nlohmann::json::array();

		std::ifstream i(MOD_EXCLUSIONS_FILE);

		try {
			i >> j;
		}
		catch (...) {
			log::error("Exclusions file has garbled data.");
			return std::vector<std::string>();
		}


		return j.get<std::vector<std::string>>();
	}

	bool ProcessDevice(DeviceData dev, std::vector<std::string> exclusions, std::vector<RE::TESFile*> mod_exclusions) {
		RE::TESObjectARMO* rend = dev.rend;
		if (!rend) {
			log::warn("ProcessDevice called with bad device data");
			return false;
		}

		auto devices = Devices::GetSingleton();

		//RE::TESObjectARMO* inv = dev.inv;
		// TypeCount

		int deviceTypeCount = 0;
		if (rend->HasKeywordString("zad_DeviousBelt")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousBra")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousPlugVaginal")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousPlugAnal")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousCollar")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousLegCuffs")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousArmCuffs")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousPiercingsNipple")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousPiercingsVaginal")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousBlindfold")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousHarness")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousHood")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousGag")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousBoots")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousGloves")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousSuit")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousYoke")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousArmbinder")) deviceTypeCount++;
		if (rend->HasKeywordString("zad_DeviousCorset")) deviceTypeCount++;


		// FILTERS
		if (rend->HasKeywordString("zadx_HR_ChainHarnessPart")) { // skip chain harness stuff
			return false;
		}
		if (rend->HasKeywordString("zad_DeviousPlugVaginal") && rend->HasKeywordString("zad_DeviousPlugAnal")) { // Plug Sets
			return false;
		}

		for (auto excl : exclusions) {
			if (Util::testFormComp(excl, dev.inv)) {
				return false;
			}
		}

		for (auto mod : mod_exclusions) {
			if (mod->IsFormInMod(rend->formID) || mod->IsFormInMod(dev.inv->formID)) {
				//log::trace("Skipping device {} from mod {}", dev.inv->GetName(), mod->GetFilename());
				return false;
			}
		}

		if (Util::FormEditorIdContains(rend, "DCurses_")) {
			return false;
		}

		if (deviceTypeCount > 4) { // We don't want restraints that block too much.
			return false;
		}

		devices->anything.push_back(dev);

		// Skipped Keywords: zad_HasPumps, zad_DeviousClamps, zad_PermitXXX

		// DEVICES
		if (!rend->HasKeywordString("zad_DeviousHeavyBondage")) { // No standard devices should include heavy bondage
			if (rend->HasKeywordString("zad_DeviousBelt") && !rend->HasKeywordString("zad_DeviousSuit") && !rend->HasKeywordString("zad_DeviousCorset") && !rend->HasKeywordString("zad_DeviousHarness")) { // Belts
				if (rend->HasKeywordString("zad_DeviousPiercingsVaginal")) {
					devices->beltsPiercings.push_back(dev);
				}
				else {
					if (Settings::GetSingleton()->useGenderedChastity) {
						if (dev.isCockCage) {
							devices->beltsCages.push_back(dev);
							//log::trace("Adding device as cage: {}", dev.inv->GetName());
						}
						else {
							devices->belts.push_back(dev);
							//log::trace("Adding device as belt: {}", dev.inv->GetName());
						}
					}
					else {
						devices->belts.push_back(dev);
					}
				}
			}
			if (rend->HasKeywordString("zad_DeviousBra") && !rend->HasKeywordString("zad_DeviousSuit") && !rend->HasKeywordString("zad_DeviousHarness")) { // Bras
				devices->bras.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousPlugVaginal") && deviceTypeCount <= 1) { // VPlugs
				devices->plugsV.push_back(dev);
				if (rend->HasKeywordString("zad_HasPumps")) {
					devices->plugsVInf.push_back(dev);
				}
				else if (!rend->HasKeywordString("zad_Lockable")) {
					devices->plugsVBasic.push_back(dev);
				}
				else {
					devices->plugsVLock.push_back(dev);
				}
			}
			if (rend->HasKeywordString("zad_DeviousPlugAnal") && deviceTypeCount <= 1) { // APlugs
				devices->plugsA.push_back(dev);
				if (rend->HasKeywordString("zad_HasPumps")) {
					devices->plugsAInf.push_back(dev);
				}
				else if (!rend->HasKeywordString("zad_Lockable")) {
					devices->plugsABasic.push_back(dev);
				}
				else {
					devices->plugsALock.push_back(dev);
				}
			}
			if (rend->HasKeywordString("zad_DeviousCollar") && (deviceTypeCount == 1 || (rend->HasKeywordString("zad_DeviousPiercingsNipple") && deviceTypeCount == 2))) { // Collars
				devices->collars.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousLegCuffs") && deviceTypeCount == 1) { // All Leg Cuffs
				devices->legCuffs.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousLegCuffs") && !rend->HasKeywordString("zad_DeviousAnkleShackles") && !rend->HasKeywordString("zad_EffectForcedWalk") && deviceTypeCount == 1) { // Leg Cuffs without shackles
				devices->legCuffsStandard.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousLegCuffs") && (rend->HasKeywordString("zad_DeviousAnkleShackles") || rend->HasKeywordString("zad_EffectForcedWalk")) && deviceTypeCount == 1) { // Shackles
				devices->legCuffsShackles.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousArmCuffs") && deviceTypeCount == 1) { // Arm Cuffs
				devices->armCuffs.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousPiercingsNipple") && deviceTypeCount == 1) { // Nipple Piercings
				devices->piercingsN.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousPiercingsVaginal") && deviceTypeCount == 1) { // Vaginal piercings
				devices->piercingsV.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousBlindfold") && deviceTypeCount == 1) { // Blindfolds (doesn't include hoods)
				devices->blindfolds.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousHarness") && !rend->HasKeywordString("zad_DeviousCorset") && rend->HasKeywordString("zad_DeviousBelt")) { // Harnesses
				devices->harnesses.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousHarness") && !rend->HasKeywordString("zad_DeviousCorset") && !rend->HasKeywordString("zad_DeviousBelt")) { // Harnesses without belts
				devices->harnessesOpen.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousGag") && deviceTypeCount == 1) { // All Gags (Not including hoods)
				devices->gags.push_back(dev);
				if (!rend->HasKeywordString("zad_DeviousGagLarge") && !rend->HasKeywordString("zad_PermitOral")) { // Gags not open or large
					devices->gagsStandard.push_back(dev);
				}
				if (rend->HasKeywordString("zad_DeviousGagLarge")) { // Gags large (can be open)
					if (rend->HasKeywordString("zad_PermitOral")) {
						devices->gagsOpenLarge.push_back(dev);
					}
					else {
						devices->gagsLarge.push_back(dev);
					}
				}
				if (rend->HasKeywordString("zad_PermitOral") && !rend->HasKeywordString("zad_DeviousGagLarge")) { // Gags open
					devices->gagsOpen.push_back(dev);
				}
			}
			if (rend->HasKeywordString("zad_DeviousCorset") && !rend->HasKeywordString("zad_DeviousBelt")) { // Corsets without belts
				devices->corsetsNoBelt.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousCorset") && rend->HasKeywordString("zad_DeviousBelt")) { // Corsets with belts
				devices->corsetsBelt.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousBoots") && deviceTypeCount == 1) { // Boots
				devices->boots.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousGloves") && deviceTypeCount == 1) { // All Gloves
				if (!rend->HasKeywordString("zad_DeviousBondageMittens")) { // Gloves without mittens
					devices->glovesNoMittens.push_back(dev);
				}
				if (rend->HasKeywordString("zad_DeviousBondageMittens")) { // Mittens
					devices->glovesMittens.push_back(dev);
				}
			}
			if (rend->HasKeywordString("zad_DeviousHood")) { // Hoods
				if (rend->HasKeywordString("zad_DeviousGag") && rend->HasKeywordString("zad_DeviousBlindfold")) {
					devices->hoodsBlockAll.push_back(dev);
				}
				else if (rend->HasKeywordString("zad_DeviousGag")) {
					devices->hoodsBlockGag.push_back(dev);
				}
				else if (rend->HasKeywordString("zad_DeviousBlindfold")) {
					devices->hoodsBlockEye.push_back(dev);
				}
				else {
					devices->hoodsNoBlock.push_back(dev);
				}
			}
		}



		if (rend->HasKeywordString("zad_DeviousArmbinder") || rend->HasKeywordString("zad_DeviousArmbinderElbow")) { // Armbinders and Elbowbinders
			devices->armbindersPlus.push_back(dev);
		}
		if (rend->HasKeywordString("zad_DeviousArmbinderElbow")) { // Elbowbinders
			devices->elbowbinders.push_back(dev);
		}
		if (rend->HasKeywordString("zad_DeviousArmbinder")) { // Armbinders
			devices->armbinders.push_back(dev);
		}
		if (rend->HasKeywordString("zad_DeviousYoke") || rend->HasKeywordString("zad_DeviousYokeBB")) { // Yokes (includes BB yoke)
			devices->yokes.push_back(dev);
		}
		if (rend->HasKeywordString("zad_DeviousCuffsFront") || rend->HasKeywordString("zad_DeviousElbowTie")) { // Heavy cuffs and other shackles
			devices->armShackles.push_back(dev);
		}
		if (rend->HasKeywordString("zad_DeviousPetSuit")) { // Pet Suits
			devices->petSuits.push_back(dev);
		}


		//if (rend->HasKeywordString("zad_DeviousSuit")) { // Suits (all suits, includes heavy bondage and hobble skirts)
		//	devices->suits.push_back(dev);
		//}
		if (rend->HasKeywordString("zad_DeviousSuit") && !rend->HasKeywordString("zad_DeviousHeavyBondage") && !rend->HasKeywordString("zad_DeviousHobbleSkirt")) { // Suits without heavy bondage or skirts
			devices->suitsSimple.push_back(dev);
		}
		if (rend->HasKeywordString("zad_DeviousStraitJacket")) { // All StraitJackets
			devices->straitJackets.push_back(dev);
			if (!rend->HasKeywordString("zad_EffectForcedWalk")) { // Allow running
				devices->straitJacketsAllowRun.push_back(dev);
			}
			else {
				devices->straitJacketsLegbinder.push_back(dev);
			}
		}
		else {														 // All hobble skirt lists won't contain strait jackets
			if (rend->HasKeywordString("zad_DeviousHobbleSkirt")) { // All Hobble Skirt
				devices->hobbleSkirts.push_back(dev);
				if (rend->HasKeywordString("zad_DeviousHobbleSkirtRelaxed")) { // Relaxed
					devices->hobbleSkirtsRelaxed.push_back(dev);
				}
				if (rend->HasKeywordString("zad_EffectForcedWalk")) { // Forced Walk
					devices->hobbleSkirtsForcedWalk.push_back(dev);
				}
			}
		}

		//devices->heavyBondageAll.list.insert(devices->heavyBondageAll.list.end(), devices->straitJackets.list.begin(), devices->straitJackets.list.end());
		//devices->heavyBondageAll.list.insert(devices->heavyBondageAll.list.end(), devices->armbindersPlus.list.begin(), devices->armbindersPlus.list.end());
		//devices->heavyBondageAll.list.insert(devices->heavyBondageAll.list.end(), devices->yokes.list.begin(), devices->yokes.list.end());
		//devices->heavyBondageAll.list.insert(devices->heavyBondageAll.list.end(), devices->petSuits.list.begin(), devices->petSuits.list.end());

		//devices->heavyBondageNoSuit.list.insert(devices->heavyBondageNoSuit.list.end(), devices->heavyBondageAll.list.begin(), devices->heavyBondageAll.list.end());
		//std::copy_if(devices->heavyBondageAll.begin(), devices->heavyBondageAll.end(), std::back_inserter(devices->heavyBondageNoSuit), [](DevicePair i) {return !i.second->HasKeywordString("zad_DeviousSuit"); });
		//auto x = devices->heavyBondageNoSuit | std::ranges::views::filter([](DevicePair i) {return !i.second->HasKeywordString("zad_DeviousSuit"); });
		return true;
	}

	RE::TESKey* GetDeviceKey(RE::TESObjectARMO* device) {
		if (!device) return nullptr;

		auto form = DeviousDevicesAPI::g_API->GetPropertyForm(device, "deviceKey", nullptr, 0);
		if (!form) {
			return nullptr;
		}
		return form->As<RE::TESKey>();
	}

	bool IsGenericKey(RE::TESKey* key) {
		if (!key) return false;

		auto formid = key->formID & 0x00ffffff;
		//log::info("Key {}: {:x} -> {}", key->GetName(), formid, formid == 0x008a4f || formid == 0x01775f || formid == 0x0409a4);
		return formid == 0x008a4f || formid == 0x01775f || formid == 0x0409a4;
	}

	bool DeviceHasGenericKey(RE::TESObjectARMO* device) {
		if (!device) return false;

		auto key = GetDeviceKey(device);
		if (key) {
			return IsGenericKey(key);
		}
		return true;
	}

	bool DeviceInventoryIsGeneric(RE::TESObjectARMO* inv) {
		if (!inv) { return false; }
		auto rend = DeviousDevicesAPI::g_API->GetDeviceRender(inv);
		if (!rend) { return false; }
		if (!DeviceHasGenericKey(inv)) { return false; }
		if (
			rend->HasKeywordString("zad_BlockGeneric") ||
			rend->HasKeywordString("zad_QuestItem") ||
			Util::FormEditorIdContains(rend, "FrayEQ") ||
			inv->HasKeywordString("zad_BlockGeneric") ||
			inv->HasKeywordString("zad_QuestItem") ||
			Util::FormEditorIdContains(inv, "FrayEQ")
			) {
			return false;
		}
		return true;
	}

	bool DeviceRenderedIsGeneric(RE::TESObjectARMO* rend) {
		auto inv = DeviousDevicesAPI::g_API->GetDeviceInventory(rend);
		return DeviceInventoryIsGeneric(inv);
	}

	void createDevices() {
		auto API = DeviousDevicesAPI::g_API;
		if (!API) {
			log::error("Devious Devices API not loaded");
			return;
		}

		auto settings = Settings::GetSingleton();

		int counter = 0;

		bool hasUD = CheckUD();
		if (!hasUD) {
			settings->onlyUseUnforgivingDevices = false;
			RE::BSScript::Variable var;
			var.SetBool(false);
			SetMCMSetting("onlyUseUnforgivingDevices", var, "Devious Curses.esp", "DCurses_MCM");
		}

		if (settings->onlyUseUnforgivingDevices) {
			log::info("Building device lists for Unforgiving devices.");
		}

		auto exclusions = GetDeviceExclusions();
		auto mod_exclusions = GetModExclusions();
		std::vector<RE::TESFile*> mod_excl;

		log::info("Total devices from api: {}", API->GetDatabase().size());

		for (auto mod_name : mod_exclusions) {
			for (auto file : RE::TESDataHandler::GetSingleton()->files) {
				if (Util::tolower(std::string(file->GetFilename())) == Util::tolower(Util::trim(mod_name))) {
					if (file->smallFileCompileIndex | file->compileIndex) {
						mod_excl.push_back(file);
						log::trace("Skipping mod {}", file->GetFilename());
					}
				}
			}
		}

		try {
			for (auto const& [device, dev_data] : API->GetDatabase()) {
				RE::TESObjectARMO* deviceInventory = device;

				if (!deviceInventory) {
					//log::warn("Issue processing device");
					continue;
				}

				RE::TESObjectARMO* deviceRendered = API->GetDeviceRender(device);

				if (!deviceRendered) {
					//log::warn("Issue processing device");
					continue;
				}


				RE::TESForm* deviceKey = API->GetPropertyForm(device, "deviceKey", nullptr, 0);
				if (deviceKey && !DeviceHasGenericKey(device)) {
					continue;
				}

				if (!deviceKey && API->GetPropertyFloat(device, "LockAccessDifficulty", 0.0, 0) >= 100) {
					continue;
				}

				if (hasUD) {
					if (Util::FormEditorIdContains(deviceRendered, "UD_AbadonPlug")) {
						continue;
					}
					else if (!settings->udUseAbadonSets && Util::testFormComp("UD_ArmorSet", deviceRendered)) {
						continue;
					}
					else if (!settings->udUseAbadon && Util::testFormComp("UD_&Abadon", deviceRendered)) {
						continue;
					}
					else if (Util::GetFormEditorId(deviceRendered).starts_with("UD_") && !settings->udUseMisc) {
						continue;
					}
				}

				//else {
				//	float baseEscapeChance = Util::GetDevicePropertyFloat(deviceInventory, "BaseEscapeChance");
				//	if (baseEscapeChance == 0) {
				//		continue;
				//	}
				//}

				if (
					deviceRendered->HasKeywordString("zad_BlockGeneric") ||
					deviceRendered->HasKeywordString("zad_QuestItem") ||
					deviceInventory->HasKeywordString("zad_BlockGeneric") ||
					deviceInventory->HasKeywordString("zad_QuestItem")
					) {
					continue;
				}

				/*if (Util::FormEditorIdContains(deviceRendered, "_df") || Util::FormEditorIdContains(deviceInventory, "_DF")) {
					continue;
				}
				if (Util::FormEditorIdContains(deviceRendered, "FrayEQ") || Util::FormEditorIdContains(deviceInventory, "FrayEQ")) {
					continue;
				}*/

				if (settings->onlyUseUnforgivingDevices && !(deviceRendered->HasKeywordString("UD_UnforgivingDevice") && deviceInventory->HasKeywordString("UD_InventoryDevice"))) {
					continue;
				}

				bool isCage = false;
				if (deviceRendered->HasKeywordString("zad_DeviousBelt") && ((Util::FormEditorIdContains(deviceInventory, "Cage") || Util::FormEditorIdContains(deviceRendered, "vivis")))) {
					isCage = true;
					typedef RE::BGSBipedObjectForm::BipedObjectSlot BOS;
					auto slot = static_cast<uint32_t>(deviceRendered->GetSlotMask());
					if (!(slot & (static_cast<uint32_t>(BOS::kModPelvisSecondary) | static_cast<uint32_t>(BOS::kModPelvisPrimary)))) {
						log::warn("{} does not have propper slots set.", deviceInventory->GetName());
					}
				}

				auto keyCount = API->GetPropertyInt(device, "NumberOfKeysNeeded", 1, 0);

				if (keyCount > settings->maxHeldKeys && settings->maxHeldKeys > 0) {
					continue;
				}

				bool isLockless = false;
				if (!deviceKey && API->GetPropertyFloat(device, "LockAccessDifficulty", 0.0, 0) == 0) {
					isLockless = true;
				}

				DeviceData dat{
					deviceInventory,
					deviceRendered,
					keyCount,
					isLockless,
					isCage,
				};

				if (ProcessDevice(dat, exclusions, mod_excl)) {
					counter++;
				}
			}
		}
		catch (const std::bad_alloc&) {
			stl::report_and_fail("Devious Curses was unable to allocate enough memory for device lists. Please free up system memory.");
		}

		log::info("Total accepted devices: {}", counter);

		lastExclusionsEditTime = std::filesystem::last_write_time(EXCLUSIONS_FILE);
		lastModExclusionsEditTime = std::filesystem::last_write_time(MOD_EXCLUSIONS_FILE);

		size_t totalMemoryCalc = sizeof(Devices);

		auto devices = Devices::GetSingleton();

		//CODEGEN_START_DEVICES_DATA
		devices->anything.name = "anything";
		totalMemoryCalc += devices->anything.get_memory_size();
		devices->belts.name = "belts";
		totalMemoryCalc += devices->belts.get_memory_size();
		devices->beltsPiercings.name = "beltsPiercings";
		totalMemoryCalc += devices->beltsPiercings.get_memory_size();
		devices->beltsCages.name = "beltsCages";
		totalMemoryCalc += devices->beltsCages.get_memory_size();
		devices->bras.name = "bras";
		totalMemoryCalc += devices->bras.get_memory_size();
		devices->plugsV.name = "plugsV";
		totalMemoryCalc += devices->plugsV.get_memory_size();
		devices->plugsVBasic.name = "plugsVBasic";
		totalMemoryCalc += devices->plugsVBasic.get_memory_size();
		devices->plugsVLock.name = "plugsVLock";
		totalMemoryCalc += devices->plugsVLock.get_memory_size();
		devices->plugsVInf.name = "plugsVInf";
		totalMemoryCalc += devices->plugsVInf.get_memory_size();
		devices->plugsA.name = "plugsA";
		totalMemoryCalc += devices->plugsA.get_memory_size();
		devices->plugsABasic.name = "plugsABasic";
		totalMemoryCalc += devices->plugsABasic.get_memory_size();
		devices->plugsALock.name = "plugsALock";
		totalMemoryCalc += devices->plugsALock.get_memory_size();
		devices->plugsAInf.name = "plugsAInf";
		totalMemoryCalc += devices->plugsAInf.get_memory_size();
		devices->collars.name = "collars";
		totalMemoryCalc += devices->collars.get_memory_size();
		devices->legCuffs.name = "legCuffs";
		totalMemoryCalc += devices->legCuffs.get_memory_size();
		devices->legCuffsStandard.name = "legCuffsStandard";
		totalMemoryCalc += devices->legCuffsStandard.get_memory_size();
		devices->legCuffsShackles.name = "legCuffsShackles";
		totalMemoryCalc += devices->legCuffsShackles.get_memory_size();
		devices->armCuffs.name = "armCuffs";
		totalMemoryCalc += devices->armCuffs.get_memory_size();
		devices->piercingsN.name = "piercingsN";
		totalMemoryCalc += devices->piercingsN.get_memory_size();
		devices->piercingsV.name = "piercingsV";
		totalMemoryCalc += devices->piercingsV.get_memory_size();
		devices->blindfolds.name = "blindfolds";
		totalMemoryCalc += devices->blindfolds.get_memory_size();
		devices->harnesses.name = "harnesses";
		totalMemoryCalc += devices->harnesses.get_memory_size();
		devices->harnessesOpen.name = "harnessesOpen";
		totalMemoryCalc += devices->harnessesOpen.get_memory_size();
		devices->gags.name = "gags";
		totalMemoryCalc += devices->gags.get_memory_size();
		devices->gagsStandard.name = "gagsStandard";
		totalMemoryCalc += devices->gagsStandard.get_memory_size();
		devices->gagsLarge.name = "gagsLarge";
		totalMemoryCalc += devices->gagsLarge.get_memory_size();
		devices->gagsOpen.name = "gagsOpen";
		totalMemoryCalc += devices->gagsOpen.get_memory_size();
		devices->gagsOpenLarge.name = "gagsOpenLarge";
		totalMemoryCalc += devices->gagsOpenLarge.get_memory_size();
		devices->corsetsNoBelt.name = "corsetsNoBelt";
		totalMemoryCalc += devices->corsetsNoBelt.get_memory_size();
		devices->corsetsBelt.name = "corsetsBelt";
		totalMemoryCalc += devices->corsetsBelt.get_memory_size();
		devices->boots.name = "boots";
		totalMemoryCalc += devices->boots.get_memory_size();
		devices->glovesMittens.name = "glovesMittens";
		totalMemoryCalc += devices->glovesMittens.get_memory_size();
		devices->glovesNoMittens.name = "glovesNoMittens";
		totalMemoryCalc += devices->glovesNoMittens.get_memory_size();
		devices->hoodsBlockAll.name = "hoodsBlockAll";
		totalMemoryCalc += devices->hoodsBlockAll.get_memory_size();
		devices->hoodsBlockGag.name = "hoodsBlockGag";
		totalMemoryCalc += devices->hoodsBlockGag.get_memory_size();
		devices->hoodsBlockEye.name = "hoodsBlockEye";
		totalMemoryCalc += devices->hoodsBlockEye.get_memory_size();
		devices->hoodsNoBlock.name = "hoodsNoBlock";
		totalMemoryCalc += devices->hoodsNoBlock.get_memory_size();
		devices->armbindersPlus.name = "armbindersPlus";
		totalMemoryCalc += devices->armbindersPlus.get_memory_size();
		devices->armbinders.name = "armbinders";
		totalMemoryCalc += devices->armbinders.get_memory_size();
		devices->elbowbinders.name = "elbowbinders";
		totalMemoryCalc += devices->elbowbinders.get_memory_size();
		devices->yokes.name = "yokes";
		totalMemoryCalc += devices->yokes.get_memory_size();
		devices->armShackles.name = "armShackles";
		totalMemoryCalc += devices->armShackles.get_memory_size();
		devices->petSuits.name = "petSuits";
		totalMemoryCalc += devices->petSuits.get_memory_size();
		devices->suitsSimple.name = "suitsSimple";
		totalMemoryCalc += devices->suitsSimple.get_memory_size();
		devices->straitJackets.name = "straitJackets";
		totalMemoryCalc += devices->straitJackets.get_memory_size();
		devices->straitJacketsAllowRun.name = "straitJacketsAllowRun";
		totalMemoryCalc += devices->straitJacketsAllowRun.get_memory_size();
		devices->straitJacketsLegbinder.name = "straitJacketsLegbinder";
		totalMemoryCalc += devices->straitJacketsLegbinder.get_memory_size();
		devices->hobbleSkirts.name = "hobbleSkirts";
		totalMemoryCalc += devices->hobbleSkirts.get_memory_size();
		devices->hobbleSkirtsRelaxed.name = "hobbleSkirtsRelaxed";
		totalMemoryCalc += devices->hobbleSkirtsRelaxed.get_memory_size();
		devices->hobbleSkirtsForcedWalk.name = "hobbleSkirtsForcedWalk";
		totalMemoryCalc += devices->hobbleSkirtsForcedWalk.get_memory_size();
		//CODEGEN_END_DEVICES_DATA

		log::info("Size of device lists: {:.2f}kb", (double)totalMemoryCalc / 1024.0);
	}

	void RecalculateDeviceLists() {
		Devices::GetSingleton()->ClearLists();
		createDevices();
	}

	std::set<std::string> GetDeviceKeywords(RE::TESObjectARMO* wornArmor, bool includeBlocking) {
		std::set<std::string> keys;
		if (!wornArmor) return keys;

		for (uint32_t i = 0; i < wornArmor->numKeywords; i++) {
			auto keywd = wornArmor->keywords[i];
			auto kwname = Util::GetFormEditorId(keywd);
			if (kwname.starts_with("zad_Devious") && kwname != "zad_DeviousPlug") {
				keys.insert(kwname);
				if (includeBlocking) {
					if (kwname == "zad_DeviousHarness") {
						keys.insert("zad_DeviousCorset");
					}
					if (kwname == "zad_DeviousCorset") {
						keys.insert("zad_DeviousHarness");
					}
					if (
						kwname == "zad_DeviousBelt")
					{
						if (!wornArmor->HasKeywordString("zad_PermitAnal")) {
							keys.insert("zad_DeviousPlugAnal");
						}
						if (!wornArmor->HasKeywordString("zad_PermitVaginal")) {
							keys.insert("zad_DeviousPiercingsVaginal");
							keys.insert("zad_DeviousPlugVaginal");
						}
					}
					if (kwname == "zad_DeviousBra") {
						keys.insert("zad_DeviousPiercingsNipple");
					}
				}
			}
		}
		return keys;
	}

	RE::TESObjectARMO* GetWornInventoryDeviceByKeyword(RE::Actor* actor, std::string keyword) {
		if (!actor) return nullptr;

		auto inventory = actor->GetInventory();
		for (auto const& [k, v] : inventory) {
			if (v.second.get()->IsWorn()) {
				RE::TESObjectARMO* wornArmor = k->As<RE::TESObjectARMO>();
				if (!wornArmor) {
					continue;
				}
				RE::TESObjectARMO* rend = DeviousDevicesAPI::g_API->GetDeviceRender(wornArmor);
				if (!rend) {
					continue;
				}
				for (std::string kw : GetDeviceKeywords(rend, false)) {
					//log::trace("kw: {}", kw);
					if (kw == keyword) {
						return wornArmor;
					}
				}
			}
		}
		return nullptr;
	}

	std::set<std::string> GetKeywordsCantEquip(RE::Actor* actor) {
		std::set<std::string> keys;
		if (!actor) return keys;

		auto inventory = actor->GetInventory();
		for (auto const& [k, v] : inventory) {
			if (v.second.get()->IsWorn()) {
				RE::TESObjectARMO* wornArmor = k->As<RE::TESObjectARMO>();
				if (!wornArmor) {
					continue;
				}
				for (std::string kw : GetDeviceKeywords(wornArmor, true)) { keys.insert(kw); }
			}
		}
		return keys;
	}

	std::set<std::string> GetWornDeviceKeywords(RE::Actor* actor) {
		std::set<std::string> keys;
		if (!actor) return keys;

		auto inventory = actor->GetInventory();
		for (auto const& [k, v] : inventory) {
			if (v.second.get()->IsWorn()) {
				RE::TESObjectARMO* wornArmor = k->As<RE::TESObjectARMO>();
				if (!wornArmor) {
					continue;
				}
				for (std::string kw : GetDeviceKeywords(wornArmor, false)) { keys.insert(kw); }
			}
		}
		return keys;
	}

	int GetVisibleDeviceCount(RE::Actor* actor) {
		if (!actor) return 0;

		bool plugVHidden = true;
		bool plugAHidden = true;
		bool piercingVHidden = true;
		bool piercingNHidden = true;

		if (CheckAND()) {
			RE::TESFaction* AND_ToplessFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x832, "Advanced Nudity Detection.esp");
			RE::TESFaction* AND_BottomlessFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x833, "Advanced Nudity Detection.esp");
			RE::TESFaction* AND_ShowingAssFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x82E, "Advanced Nudity Detection.esp");
			RE::TESFaction* AND_ShowingChestFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x82F, "Advanced Nudity Detection.esp");
			RE::TESFaction* AND_ShowingGenitalFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x830, "Advanced Nudity Detection.esp");

			bool is_player = actor == RE::PlayerCharacter::GetSingleton();

			if (actor->GetFactionRank(AND_ToplessFaction, is_player) > 0) {
				piercingNHidden = false;
			}
			if (actor->GetFactionRank(AND_BottomlessFaction, is_player) > 0) {
				plugAHidden = false;
				piercingVHidden = false;
				plugVHidden = false;
			}
			if (actor->GetFactionRank(AND_ShowingAssFaction, is_player) > 0) {
				plugAHidden = false;
			}
			if (actor->GetFactionRank(AND_ShowingChestFaction, is_player) > 0) {
				piercingNHidden = false;
			}
			if (actor->GetFactionRank(AND_ShowingGenitalFaction, is_player) > 0) {
				piercingVHidden = false;
				plugVHidden = false;
			}
		}

		else {
			auto chestArmor = actor->GetWornArmor((RE::BIPED_MODEL::BipedObjectSlot::kBody));
			if (!chestArmor) {
				plugAHidden = false;
				piercingVHidden = false;
				plugVHidden = true;
				piercingNHidden = false;
			}
			else {
				if (chestArmor->HasKeywordString("zad_PermitAnal")) {
					plugAHidden = false;
				}
				if (chestArmor->HasKeywordString("zad_PermitVaginal")) {
					piercingVHidden = false;
					plugVHidden = false;
				}
				if (chestArmor->HasKeywordString("zad_ExposedBreasts")) {
					piercingNHidden = false;
				}
			}
		}

		auto inventory = actor->GetInventory();
		int count = 0;
		for (auto const& [k, v] : inventory) {
			if (v.second.get()->IsWorn()) {
				RE::TESObjectARMO* inventoryDevice = k->As<RE::TESObjectARMO>();
				if (!inventoryDevice) {
					continue;
				}
				RE::TESObjectARMO* renderedDevice = DeviousDevicesAPI::g_API->GetDeviceRender(inventoryDevice);
				if (!renderedDevice) {
					continue;
				}

				bool shouldCount = false;

				for (auto* aa : renderedDevice->armorAddons) {
					actor->VisitArmorAddon(renderedDevice, aa, [&shouldCount](bool, RE::NiAVObject&) {
						shouldCount = true;
					});
				}

				if (renderedDevice->HasKeywordString("zad_DeviousPlugVaginal") && plugVHidden) {
					shouldCount = false;
				}
				if (renderedDevice->HasKeywordString("zad_DeviousPlugAnal") && plugAHidden) {
					shouldCount = false;
				}
				if (renderedDevice->HasKeywordString("zad_DeviousPiercingsNipple") && piercingNHidden) {
					shouldCount = false;
				}
				if (renderedDevice->HasKeywordString("zad_DeviousPiercingsVaginal") && piercingVHidden) {
					shouldCount = false;
				}

				//log::trace("Device {} is {}", inventoryDevice->GetName(), shouldCount ? "COUNTED" : "NOT COUNTED");

				if (shouldCount) {
					count++;
				}
			}
		}
		return count;
	}

	DeviceList GetRandomWeightedList(RE::Actor* actor, std::set<std::string> skipList, std::string theme) {
		if (!actor) return DeviceList();

		auto devices = Devices::GetSingleton();
		auto settings = Settings::GetSingleton();

		auto sex = SexLab::GetSex(actor);

		static const std::vector<std::string> allDeviceKeywords = { "zad_DeviousBelt", "zad_DeviousBra", "zad_DeviousPlugVaginal", "zad_DeviousPlugAnal", "zad_DeviousCollar", "zad_DeviousLegCuffs",
																	"zad_DeviousArmCuffs", "zad_DeviousPiercingsNipple", "zad_DeviousPiercingsVaginal", "zad_DeviousBlindfold", "zad_DeviousHarness",
																	"zad_DeviousGag", "zad_DeviousBoots", "zad_DeviousGloves", "zad_DeviousHood", "zad_DeviousSuit", "zad_DeviousHeavyBondage" };
		std::vector<std::pair<DeviceList*, double>> lists;
		for (auto const& keyword : allDeviceKeywords) {
			if (std::find(skipList.begin(), skipList.end(), keyword) == skipList.end()) {// Can equip this keyword
				if (keyword == "zad_DeviousBelt") {
					if (devices->beltsCages.list.size() > 0) {
						if (sex == 2 || sex == 0) {
							lists.push_back(std::pair(&devices->beltsCages, settings->beltWeight));
						}
						else {
							lists.push_back(std::pair(&devices->belts, settings->beltWeight));
							lists.push_back(std::pair(&devices->beltsPiercings, settings->chastityPiercingWeight));
						}
					}
					else {
						lists.push_back(std::pair(&devices->beltsPiercings, settings->chastityPiercingWeight));
						lists.push_back(std::pair(&devices->belts, settings->beltWeight));
					}
				}
				if (keyword == "zad_DeviousBra") {
					lists.push_back(std::pair(&devices->bras, settings->braWeight));
				}
				if (keyword == "zad_DeviousPlugVaginal" && (!settings->useGenderedPlugs || sex == 1)) {
					lists.push_back(std::pair(&devices->plugsVLock, settings->lockingPlugsWeight));
					lists.push_back(std::pair(&devices->plugsVBasic, settings->plugsWeight));
					lists.push_back(std::pair(&devices->plugsVInf, settings->inflatablePlugsWeight));
				}
				if (keyword == "zad_DeviousPlugAnal") {
					lists.push_back(std::pair(&devices->plugsALock, settings->lockingPlugsWeight));
					lists.push_back(std::pair(&devices->plugsABasic, settings->plugsWeight));
					lists.push_back(std::pair(&devices->plugsAInf, settings->inflatablePlugsWeight));
				}
				if (keyword == "zad_DeviousCollar") {
					lists.push_back(std::pair(&devices->collars, settings->collarWeight));
				}
				if (keyword == "zad_DeviousLegCuffs") {
					if (settings->allowLegShackles) {
						lists.push_back(std::pair(&devices->legCuffs, settings->legCuffsWeight));
					}
					else {
						lists.push_back(std::pair(&devices->legCuffsStandard, settings->legCuffsWeight));
					}
				}
				if (keyword == "zad_DeviousArmCuffs") {
					lists.push_back(std::pair(&devices->armCuffs, settings->armCuffsWeight));
				}
				if (keyword == "zad_DeviousPiercingsNipple") {
					lists.push_back(std::pair(&devices->piercingsN, settings->nipplePiercingsWeight));
				}
				if (keyword == "zad_DeviousPiercingsVaginal") {
					lists.push_back(std::pair(&devices->piercingsV, settings->vaginalPiercingsWeight));
				}
				if (keyword == "zad_DeviousBlindfold") {
					lists.push_back(std::pair(&devices->blindfolds, settings->blindfoldWeight));
				}
				if (keyword == "zad_DeviousHarness") {
					lists.push_back(std::pair(&devices->harnessesOpen, settings->slaveHarnessWeight));
					lists.push_back(std::pair(&devices->corsetsNoBelt, settings->corsetWeight));
					if (std::find(skipList.begin(), skipList.end(), "zad_DeviousBelt") != skipList.end()) { // No Belt
						lists.push_back(std::pair(&devices->harnesses, settings->chastityHarnessWeight));
						lists.push_back(std::pair(&devices->corsetsBelt, settings->corsetWeight));
					}
				}
				if (keyword == "zad_DeviousGag") {
					lists.push_back(std::pair(&devices->gagsStandard, settings->gagWeight));
					lists.push_back(std::pair(&devices->gagsLarge, settings->largeGagWeight));
					lists.push_back(std::pair(&devices->gagsOpen, settings->ringGagWeight));
					lists.push_back(std::pair(&devices->gagsOpenLarge, settings->largeRingGagWeight));
				}
				if (keyword == "zad_DeviousBoots") {
					lists.push_back(std::pair(&devices->boots, settings->bootsWeight));
				}
				if (keyword == "zad_DeviousGloves") {
					lists.push_back(std::pair(&devices->glovesNoMittens, settings->glovesWeight));
					lists.push_back(std::pair(&devices->glovesMittens, settings->mittensWeight));
				}
				if (keyword == "zad_DeviousHood") {
					bool canBlindfold = std::find(skipList.begin(), skipList.end(), "zad_DeviousBlindfold") == skipList.end();// && !settings->hoodNoBlind;
					bool canGag = std::find(skipList.begin(), skipList.end(), "zad_DeviousGag") == skipList.end();// && !settings->hoodNoGag;
					lists.push_back(std::pair(&devices->hoodsNoBlock, settings->hoodNoneWeight));
					if (canBlindfold) {
						lists.push_back(std::pair(&devices->hoodsBlockEye, settings->hoodBlindWeight));
					}
					if (canGag) {
						lists.push_back(std::pair(&devices->hoodsBlockGag, settings->hoodGagWeight));
					}
					if (canGag && canBlindfold) {
						lists.push_back(std::pair(&devices->hoodsBlockAll, settings->hoodBothWeight));
					}
				}
				if (keyword == "zad_DeviousSuit") {
					lists.push_back(std::pair(&devices->suitsSimple, settings->catsuitWeight));
					double w1 = (100.0 - settings->hobbleSkirtDifficulty) / 100.0;
					double w2 = settings->hobbleSkirtDifficulty / 100.0;
					lists.push_back(std::pair(&devices->hobbleSkirtsRelaxed, settings->hobbleSkirtWeight * w1));
					lists.push_back(std::pair(&devices->hobbleSkirtsForcedWalk, settings->hobbleSkirtWeight * w2));
				}
				if (keyword == "zad_DeviousHeavyBondage") {
					lists.push_back(std::pair(&devices->armbinders, settings->armbinderWeight));
					lists.push_back(std::pair(&devices->elbowbinders, settings->elbowbinderWeight));
					lists.push_back(std::pair(&devices->yokes, settings->yokeWeight));
					lists.push_back(std::pair(&devices->armShackles, settings->shacklesWeight));
					if (std::find(skipList.begin(), skipList.end(), "zad_DeviousSuit") == skipList.end()) {
						lists.push_back(std::pair(&devices->straitJacketsAllowRun, settings->straitjacketWeight));
						lists.push_back(std::pair(&devices->straitJacketsLegbinder, settings->straitjacketLegbinderWeight));
						lists.push_back(std::pair(&devices->petSuits, settings->petSuitWeight));
					}
				}
			}
		}

		std::vector<std::pair<DeviceList, double>> adjustedLists;

		for (auto list : lists) {
			auto adj = GetAdjustedDeviceList(list.first, skipList, theme);
			if (adj.list.size() > 0) {
				adjustedLists.push_back(std::make_pair(adj, list.second));
			}
		}

		auto list = Util::VectorSelectWeighted(adjustedLists);

		if (list.has_value()) {
			return list.value().first;
		}
		else {
			return DeviceList();
		}
	}

	std::optional<DeviceData> GetRandomEquipableDevice(RE::Actor* actor, std::set<std::string> skipList, std::string theme) {
		if (!actor) return std::nullopt;


		DeviceList randomList = GetRandomWeightedList(actor, skipList, theme);
		if (randomList.list.size() == 0) {
			if (!randomList.name.empty()) log::trace("Random list {} has no items.", randomList.name);
			return std::nullopt;
		}
		auto dev = GetRandomDevice(&randomList);
		if (!dev) {
			//log::trace("Failed to get device from list {} - Length {}", randomList.second, randomList.list.size());
			return std::nullopt;
		}
		else {
			log::trace("Got device {} from list {} - Length {}", dev.value().inv->GetName(), randomList.name, randomList.list.size());
		}
		return dev;
	}

	int GetWornDeviceCount(RE::Actor* actor, std::string theme) {
		if (!actor) return 0;

		int count = 0;
		auto inventory = actor->GetInventory();
		for (auto const& [k, v] : inventory) {
			if (v.second.get()->IsWorn()) {
				RE::TESObjectARMO* wornArmor = k->As<RE::TESObjectARMO>();
				if (!wornArmor) {
					continue;
				}
				if (!theme.empty() && !Util::testFormComp(theme, wornArmor)) {
					continue;
				}
				RE::TESObjectARMO* inv = DeviousDevicesAPI::g_API->GetDeviceInventory(wornArmor);
				if (inv && inv->HasKeywordString("zad_InventoryDevice")) {
					count++;
				}
			}
		}
		return count;
	}

	uint32_t GetItemCount(RE::TESObjectREFR* object, RE::TESForm* item) {
		auto inventory = object->GetInventory();
		for (auto const& [k, v] : inventory) {
			if (k->formID == item->formID) {
				return v.first;
			}
		}
		return 0;
	}

	bool ActorIsWearingDevice(RE::Actor* actor, RE::TESObjectARMO* device) {
		if (!actor) return false;
		auto inventory = actor->GetInventory();
		for (auto const& [k, v] : inventory) {
			RE::TESObjectARMO* armor = k->As<RE::TESObjectARMO>();
			if (armor && armor == device && v.second.get()->IsWorn()) {
				return true;
			}
		}
		return false;
	}

	bool PlayerIsLucky() {
		auto player = RE::PlayerCharacter::GetSingleton();
		RE::TESObjectARMO* lucky_piercings = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LUCKY_PIERCINGS, "Devious Curses.esp");
		RE::TESObjectARMO* lucky_piercings_r = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectARMO>(LUCKY_PIERCINGS, "Devious Curses.esp");
		auto inventory = player->GetInventory();
		for (auto const& [k, v] : inventory) {
			RE::TESObjectARMO* armor = k->As<RE::TESObjectARMO>();
			if (armor && (armor == lucky_piercings || armor == lucky_piercings_r) && v.second.get()->IsWorn()) {
				return true;
			}
		}
		return false;
	}

	std::vector<RE::TESKey*> GenerateKeys(RE::TESObjectREFR* activatedObject, bool skipRand, bool onlyOne) {
		auto player = RE::PlayerCharacter::GetSingleton();
		auto settings = Settings::GetSingleton();
		auto counters = Serialized::GetCounters();

		RE::TESKey* restraintsKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(std::stoi("1775f", 0, 16), "Devious Devices - Integration.esm");
		RE::TESKey* chastityKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(std::stoi("8a4f", 0, 16), "Devious Devices - Integration.esm");
		RE::TESKey* piercingKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(std::stoi("409a4", 0, 16), "Devious Devices - Integration.esm");

		int total_keys = GetItemCount(player, restraintsKey) + GetItemCount(player, chastityKey) + GetItemCount(player, piercingKey);

		if (total_keys >= settings->maxHeldKeys && settings->maxHeldKeys > 0) {
			return std::vector<RE::TESKey*>();
		}

		if (!(activatedObject && activatedObject->HasContainer())) {
			return std::vector<RE::TESKey*>();
		}

		double restraintsWeight = settings->restraintsKeyWeight;
		double chastityWeight = settings->chastityKeyWeight;
		double piercingWeight = settings->piercingToolWeight;

		int restraintsTotal = 0;
		int chastityTotal = 0;
		int piercingTotal = 0;

		bool isLucky = PlayerIsLucky();

		if (settings->preferRelevantKeys) {
			auto api = DeviousDevicesAPI::g_API;
			auto inventory = player->GetInventory();
			for (auto const& [k, v] : inventory) {
				if (v.second.get()->IsWorn()) {
					RE::TESObjectARMO* wornArmor = k->As<RE::TESObjectARMO>();
					if (!wornArmor) {
						continue;
					}
					RE::TESForm* deviceKey = api->GetPropertyForm(wornArmor, "deviceKey", nullptr, 0);
					if (!deviceKey) {
						continue;
					}
					if (deviceKey == restraintsKey) {
						restraintsTotal += 1;
					}
					if (deviceKey == chastityKey) {
						chastityTotal += 1;
					}
					if (deviceKey == piercingKey) {
						piercingTotal += 1;
					}
				}
			}
		}

		if (restraintsTotal + chastityTotal + piercingTotal > 0) {
			if (restraintsTotal == 0) {
				restraintsWeight = 0;
			}
			if (chastityTotal == 0) {
				chastityWeight = 0;
			}
			if (piercingTotal == 0) {
				piercingWeight = 0;
			}
		}

		double baseChance = settings->keyChance;
		double chance = baseChance;
		int deviceCount = GetWornDeviceCount(player);
		if (settings->keyBonus > 0) {
			chance += deviceCount * settings->keyBonus;
		}
		double keyForgiveness = (4.0f * (counters->SinceLastKey + 5.0f)) / (counters->SinceLastKey + 20.0f);
		if (settings->keyForgiveness) {
			chance *= keyForgiveness;
		}
		RE::Actor* actor = activatedObject->As<RE::Actor>();
		if (actor && !actor->IsDead() && !actor->IsChild() && player->IsSneaking() && actor->CanPickpocket()) {
			//log::trace("Pickpocket: {}", settings->keyPickpocketBonus);
			chance *= settings->keyPickpocketBonus;
		}
		if (isLucky && settings->keyLuckyBonus > 1.0) {
			chance *= settings->keyLuckyBonus;
		}

		double r = Util::random();
		log::trace("key chance {:.2f}%{} ({:.2f})", chance, isLucky ? " [Lucky]" : "", r);

		int count = onlyOne ? 1 : Util::random(settings->minKeysLooted, settings->maxKeysLooted);

		std::vector<RE::TESKey*> keys;

		if (r < chance || skipRand) {
			for (int i = 0; i < count; i++) {
				double weightSum = restraintsWeight + chastityWeight + piercingWeight;

				double roll = Util::random(weightSum);
				if (roll < piercingWeight) {
					activatedObject->AddObjectToContainer(skyrim_cast<RE::TESBoundObject*>(piercingKey), nullptr, 1, nullptr);
					counters->SinceLastKey = 0;
					keys.push_back(piercingKey);
				}
				else if (roll - piercingWeight < chastityWeight) {
					activatedObject->AddObjectToContainer(skyrim_cast<RE::TESBoundObject*>(chastityKey), nullptr, 1, nullptr);
					counters->SinceLastKey = 0;
					keys.push_back(chastityKey);
				}
				else {
					activatedObject->AddObjectToContainer(skyrim_cast<RE::TESBoundObject*>(restraintsKey), nullptr, 1, nullptr);
					counters->SinceLastKey = 0;
					keys.push_back(restraintsKey);
				}
			}
		}

		counters->SinceLastKey++;
		return keys;
	}

	void RemoveKeys(RE::TESObjectREFR* activatedObject) {
		RE::TESKey* restraintsKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(std::stoi("1775f", 0, 16), "Devious Devices - Integration.esm");
		RE::TESKey* chastityKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(std::stoi("8a4f", 0, 16), "Devious Devices - Integration.esm");
		RE::TESKey* piercingKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(std::stoi("409a4", 0, 16), "Devious Devices - Integration.esm");

		RE::TESObjectMISC* volatileGem = StaticDataHolder::GetSingleton()->LookupForm<RE::TESObjectMISC>(VOLATILE_GEM, "Devious Curses.esp");


		if (!(activatedObject && activatedObject->HasContainer())) {
			return;
		}

		auto isWearingLatex = IsWearingOppLatex(UINT32_MAX);

		auto inventory = activatedObject->GetInventory();
		for (auto const& [k, v] : inventory) {

			if (k == restraintsKey) {
				activatedObject->RemoveItem(skyrim_cast<RE::TESBoundObject*>(restraintsKey), v.first, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
			}
			if (k == chastityKey) {
				activatedObject->RemoveItem(skyrim_cast<RE::TESBoundObject*>(chastityKey), v.first, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
			}
			if (k == piercingKey) {
				activatedObject->RemoveItem(skyrim_cast<RE::TESBoundObject*>(piercingKey), v.first, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
			}

			if (!(isWearingLatex && Serialized::GetOppDeviceCounters()->livingLatexCounter == 2) && k == volatileGem) {
				activatedObject->RemoveItem(skyrim_cast<RE::TESBoundObject*>(volatileGem), v.first, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
			}
		}

	}

	void RemoveAllRestraints(RE::Actor* actor, bool destroyAll) {
		if (!actor) return;
		log::trace("Attempting to remove all restraints from {}", actor->GetName());
		std::vector<std::pair<RE::TESObjectARMO*, RE::TESObjectARMO*>> removes;

		auto inventory = actor->GetInventory();
		for (auto const& [k, v] : inventory) {
			RE::TESObjectARMO* render = k->As<RE::TESObjectARMO>();
			if (render && DeviceRenderedIsGeneric(render) && v.second.get() && v.second.get()->IsWorn()) {
				auto armor = DeviousDevicesAPI::g_API->GetDeviceInventory(render);
				if (armor) {
					removes.push_back(std::make_pair(armor, render));
				}
			}
		}

		auto scriptManager = ScriptingManager();
		for (auto& [dev, rend] : removes) {
			//log::trace("Removing device {}", dev->GetName());
			scriptManager.UnlockDevice(actor, dev, rend, nullptr, destroyAll, true);
		}
	}

	bool UndressActor(RE::Actor* akActor, bool removeCombatStuff) {
		if (!akActor) return false;

		auto settings = Settings::GetSingleton();

		std::vector<RE::TESForm*> removes = std::vector<RE::TESForm*>();

		if (settings->enableSlowStrip) {
			ScriptingManager().SlowStrip(akActor);
			return false;
		}

		for (uint32_t i = 1; i < (1 << 31); i = i << 1) {
			typedef RE::BGSBipedObjectForm::BipedObjectSlot BOS;
			RE::TESObjectARMO* equipped = akActor->GetWornArmor((BOS)i);
			if (equipped == nullptr) { continue; }

			if (settings->stripOnlyKeywords && (!equipped->HasKeywordString("ArmorHeavy") && !equipped->HasKeywordString("ArmorLight") && !equipped->HasKeywordString("ArmorClothing"))) {
				continue;
			}

			BOS slotMask = equipped->GetSlotMask();

			if ((equipped->GetArmorRating() <= 0.1 && (slotMask == BOS::kAmulet || slotMask == BOS::kRing || slotMask == BOS::kCirclet))) {
				continue;
			}
			if ((i == (uint32_t)BOS::kShield) && !removeCombatStuff) {
				continue;
			}
			if (equipped->HasKeywordString("SexLabNoStrip")) {
				continue;
			}
			//*didAnything = true;
			//UnequipItem(akActor, equipped);
			removes.push_back(equipped);
		}

		if (removeCombatStuff) {
			auto inventory = akActor->GetInventory();
			for (auto const& [k, v] : inventory) {
				if (v.second.get()->IsWorn()) {
					RE::TESAmmo* ammo = k->As<RE::TESAmmo>();
					if (!ammo) {
						continue;
					}
					//UnequipItem(akActor, ammo);
					removes.push_back(ammo);
				}
			}
		}

		if (removes.size() > 0) {
			log::trace("Undress removed {} items", removes.size());
			auto scriptManager = ScriptingManager();
			for (auto equipped : removes) {
				scriptManager.UnequipItem(akActor, equipped);
			}
			return true;
		}

		return false;
	}

	void UnequipItems(RE::Actor* akActor) {
		if (!akActor) return;

		auto scriptManager = ScriptingManager();

		auto shieldSlot = RE::BGSBipedObjectForm::BipedObjectSlot::kShield;
		RE::TESObjectARMO* shield = akActor->GetWornArmor(shieldSlot);
		if (shield) {
			scriptManager.UnequipItem(akActor, shield);
		}

		auto rightHand = akActor->GetEquippedObject(false);
		if (rightHand) {
			auto rightHandSpell = rightHand->As<RE::SpellItem>();
			if (rightHandSpell) {
				scriptManager.UnequipSpell(akActor, rightHandSpell, 1);
			}
			else {
				scriptManager.UnequipItem(akActor, rightHand);
			}
		}

		auto leftHand = akActor->GetEquippedObject(false);
		if (leftHand) {
			auto leftHandSpell = leftHand->As<RE::SpellItem>();
			if (leftHandSpell) {
				scriptManager.UnequipSpell(akActor, leftHandSpell, 0);
			}
			else {
				scriptManager.UnequipItem(akActor, leftHand);
			}
		}
		if (leftHand || rightHand || shield) {
			Util::ExecuteWithDelay(50ms, [akActor] {
				akActor->DrawWeaponMagicHands(false);
			});
		}
	}

	bool UndressAndUnequipActor(RE::Actor* akActor) {
		UnequipItems(akActor);

		return UndressActor(akActor, true);
	}
}