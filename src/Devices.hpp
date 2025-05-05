#pragma once

#include "Settings.hpp"
#include "Utils.hpp"
#include "Scripting.hpp"
#include "Serializer.hpp"

#include "../include/DDNG_API.h"

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
#include <fstream>

constexpr auto EXCLUSIONS_FILE = "Data/SKSE/Plugins/DeviousCursesExclusions.json";

using namespace SKSE;

namespace DCURSES {
	
	struct DeviceData {
		RE::TESObjectARMO* inv;
		RE::TESObjectARMO* rend;
		bool isLockless;
		int keyCount;
	};

	typedef std::pair<std::vector<DeviceData>, std::string> DeviceList;

	DeviceList GetAdjustedDeviceList(DeviceList* list, std::vector<std::string> skipList, std::string theme = "") {
		DeviceList result;
		result.second = list->second;
		for (auto x : list->first) {
			if (Util::testFormComp(theme, x.inv)) {
				bool canUse = true;
				for (auto key : skipList) {
					if (x.rend->HasKeywordString(key)) {
						canUse = false;
						continue;
					}
				}
				if (canUse) {
					result.first.push_back(x);
				}
			}
		}
		return result;
	}

	std::optional<DeviceData> GetRandomDevice(DeviceList* list, std::vector<std::string> skipList = std::vector<std::string>(), std::string theme = "") {
		if (list == nullptr) { return std::nullopt; }
		//if (theme == "") {
		if (list->first.size() == 0) { return std::nullopt; }
		int r = Util::randomInt(static_cast<int>(list->first.size()));
		return (list->first)[r];
		//}

		//auto adj = GetAdjustedDeviceList(list, skipList, theme);
		//if (adj.first.size() == 0) { return std::nullopt; }
		//int r = Util::randomInt(static_cast<int>(adj.first.size()));
		//return (adj.first)[r];
	}

	struct Devices {
		DeviceList anything;
		DeviceList belts;
		DeviceList beltsNoPiercings;
		DeviceList bras;
		DeviceList plugs;
		DeviceList plugsV;
		DeviceList plugsVBasic;
		DeviceList plugsVLock;
		DeviceList plugsVInf;
		DeviceList plugsA;
		DeviceList plugsABasic;
		DeviceList plugsALock;
		DeviceList plugsAInf;
		DeviceList collars;
		DeviceList legCuffs;
		DeviceList legCuffsStandard;
		DeviceList legCuffsShackles;
		DeviceList armCuffs;
		DeviceList piercingsN;
		DeviceList piercingsV;
		DeviceList blindfolds;
		DeviceList harnesses;
		DeviceList harnessesOpen;
		DeviceList gags;
		DeviceList gagsStandard;
		DeviceList gagsLarge;
		DeviceList gagsOpen;
		DeviceList gagsOpenLarge;
		DeviceList corsetsNoBelt;
		DeviceList corsetsBelt;
		DeviceList boots;
		DeviceList glovesMittens;
		DeviceList glovesNoMittens;
		DeviceList hoodsBlockAll;
		DeviceList hoodsBlockGag;
		DeviceList hoodsBlockEye;
		DeviceList hoodsNoBlock;
		DeviceList armbindersPlus;
		DeviceList armbinders;
		DeviceList elbowbinders;
		DeviceList yokes;
		DeviceList armShackles;
		DeviceList petSuits;
		DeviceList suits;
		DeviceList suitsSimple;
		DeviceList straitJackets;
		DeviceList straitJacketsAllowRun;
		DeviceList straitJacketsLegbinder;
		DeviceList hobbleSkirts;
		DeviceList hobbleSkirtsRelaxed;
		DeviceList hobbleSkirtsStandard;
		DeviceList hobbleSkirtsForcedWalk;
		DeviceList heavyBondageAll;
		DeviceList heavyBondageNoSuit;
	};

	// GLOBAL
	struct Devices devices = Devices();

	void CreateExclusionsFileIfNeeded() {
		nlohmann::json j = nlohmann::json::array();

		if (!std::filesystem::exists(EXCLUSIONS_FILE)) {
			log::warn("Unable to load exclusions file. Creating blank file.");
			std::ofstream o(EXCLUSIONS_FILE);
			o << j << std::endl;
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

	bool ProcessDevice(DeviceData dev, std::vector<std::string> exclusions) {
		RE::TESObjectARMO* rend = dev.rend;
		if (!rend) {
			log::warn("ProcessDevice called with bad device data");
			return false;
		}
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
		
		if (deviceTypeCount > 4) { // We don't want restraints that block too much.
			return false;
		}

		devices.anything.first.push_back(dev);

		// Skipped Keywords: zad_HasPumps, zad_DeviousClamps, zad_PermitXXX

		// DEVICES
		if (!rend->HasKeywordString("zad_DeviousHeavyBondage")) { // No standard devices should include heavy bondage
			if (rend->HasKeywordString("zad_DeviousBelt") && !rend->HasKeywordString("zad_DeviousSuit") && !rend->HasKeywordString("zad_DeviousCorset") && !rend->HasKeywordString("zad_DeviousHarness")) { // Belts
				devices.belts.first.push_back(dev);
				if (!rend->HasKeywordString("zad_DeviousPiercingsVaginal")) {
					devices.beltsNoPiercings.first.push_back(dev);
				}
			}
			if (rend->HasKeywordString("zad_DeviousBra") && !rend->HasKeywordString("zad_DeviousSuit") && !rend->HasKeywordString("zad_DeviousHarness")) { // Bras
				devices.bras.first.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousPlug") && deviceTypeCount == 1) { // All Plugs
				devices.plugs.first.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousPlugVaginal") && deviceTypeCount == 1) { // VPlugs
				devices.plugsV.first.push_back(dev);
				if (rend->HasKeywordString("zad_HasPumps")) {
					devices.plugsVInf.first.push_back(dev);
				}
				else if (!rend->HasKeywordString("zad_Lockable")) {
					devices.plugsVBasic.first.push_back(dev);
				}
				else {
					devices.plugsVLock.first.push_back(dev);
				}
			}
			if (rend->HasKeywordString("zad_DeviousPlugAnal") && deviceTypeCount == 1) { // APlugs
				devices.plugsA.first.push_back(dev);
				if (rend->HasKeywordString("zad_HasPumps")) {
					devices.plugsAInf.first.push_back(dev);
				}
				else if (!rend->HasKeywordString("zad_Lockable")) {
					devices.plugsABasic.first.push_back(dev);
				}
				else {
					devices.plugsALock.first.push_back(dev);
				}
			}
			if (rend->HasKeywordString("zad_DeviousCollar") && (deviceTypeCount == 1 || (rend->HasKeywordString("zad_DeviousPiercingsNipple") && deviceTypeCount == 2))) { // Collars
				devices.collars.first.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousLegCuffs") && deviceTypeCount == 1) { // All Leg Cuffs
				devices.legCuffs.first.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousLegCuffs") && !rend->HasKeywordString("zad_DeviousAnkleShackles") && !rend->HasKeywordString("zad_EffectForcedWalk") && deviceTypeCount == 1) { // Leg Cuffs without shackles
				devices.legCuffsStandard.first.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousLegCuffs") && (rend->HasKeywordString("zad_DeviousAnkleShackles") || rend->HasKeywordString("zad_EffectForcedWalk")) && deviceTypeCount == 1) { // Shackles
				devices.legCuffsShackles.first.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousArmCuffs") && deviceTypeCount == 1) { // Arm Cuffs
				devices.armCuffs.first.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousPiercingsNipple") && deviceTypeCount == 1) { // Nipple Piercings
				devices.piercingsN.first.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousPiercingsVaginal") && deviceTypeCount == 1) { // Vaginal piercings
				devices.piercingsV.first.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousBlindfold") && deviceTypeCount == 1) { // Blindfolds (doesn't include hoods)
				devices.blindfolds.first.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousHarness") && !rend->HasKeywordString("zad_DeviousCorset") && rend->HasKeywordString("zad_DeviousBelt")) { // Harnesses
				devices.harnesses.first.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousHarness") && !rend->HasKeywordString("zad_DeviousCorset") && !rend->HasKeywordString("zad_DeviousBelt")) { // Harnesses without belts
				devices.harnessesOpen.first.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousGag") && deviceTypeCount == 1) { // All Gags (Not including hoods)
				devices.gags.first.push_back(dev);
				if (!rend->HasKeywordString("zad_DeviousGagLarge") && !rend->HasKeywordString("zad_PermitOral")) { // Gags not open or large
					devices.gagsStandard.first.push_back(dev);
				}
				if (rend->HasKeywordString("zad_DeviousGagLarge")) { // Gags large (can be open)
					if (rend->HasKeywordString("zad_PermitOral")) {
						devices.gagsOpenLarge.first.push_back(dev);
					}
					else {
						devices.gagsLarge.first.push_back(dev);
					}
				}
				if (rend->HasKeywordString("zad_PermitOral") && !rend->HasKeywordString("zad_DeviousGagLarge")) { // Gags open
					devices.gagsOpen.first.push_back(dev);
				}
			}
			if (rend->HasKeywordString("zad_DeviousCorset") && !rend->HasKeywordString("zad_DeviousBelt")) { // Corsets without belts
				devices.corsetsNoBelt.first.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousCorset") && rend->HasKeywordString("zad_DeviousBelt")) { // Corsets with belts
				devices.corsetsBelt.first.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousBoots") && deviceTypeCount == 1) { // Boots
				devices.boots.first.push_back(dev);
			}
			if (rend->HasKeywordString("zad_DeviousGloves") && deviceTypeCount == 1) { // All Gloves
				if (!rend->HasKeywordString("zad_DeviousBondageMittens")) { // Gloves without mittens
					devices.glovesNoMittens.first.push_back(dev);
				}
				if (rend->HasKeywordString("zad_DeviousBondageMittens")) { // Mittens
					devices.glovesMittens.first.push_back(dev);
				}
			}
			if (rend->HasKeywordString("zad_DeviousHood")) { // Hoods
				if (rend->HasKeywordString("zad_DeviousGag") && rend->HasKeywordString("zad_DeviousBlindfold")) {
					devices.hoodsBlockAll.first.push_back(dev);
				}
				else if (rend->HasKeywordString("zad_DeviousGag")) {
					devices.hoodsBlockGag.first.push_back(dev);
				}
				else if (rend->HasKeywordString("zad_DeviousBlindfold")) {
					devices.hoodsBlockEye.first.push_back(dev);
				}
				else {
					devices.hoodsNoBlock.first.push_back(dev);
				}
			}
		}



		if (rend->HasKeywordString("zad_DeviousArmbinder") || rend->HasKeywordString("zad_DeviousArmbinderElbow")) { // Armbinders and Elbowbinders
			devices.armbindersPlus.first.push_back(dev);
		}
		if (rend->HasKeywordString("zad_DeviousArmbinderElbow")) { // Elbowbinders
			devices.elbowbinders.first.push_back(dev);
		}
		if (rend->HasKeywordString("zad_DeviousArmbinder")) { // Armbinders
			devices.armbinders.first.push_back(dev);
		}
		if (rend->HasKeywordString("zad_DeviousYoke") || rend->HasKeywordString("zad_DeviousYokeBB")) { // Yokes (includes BB yoke)
			devices.yokes.first.push_back(dev);
		}
		if (rend->HasKeywordString("zad_DeviousCuffsFront") || rend->HasKeywordString("zad_DeviousElbowTie")) { // Heavy cuffs and other shackles
			devices.armShackles.first.push_back(dev);
		}
		if (rend->HasKeywordString("zad_DeviousPetSuit")) { // Pet Suits
			devices.petSuits.first.push_back(dev);
		}


		if (rend->HasKeywordString("zad_DeviousSuit")) { // Suits (all suits, includes heavy bondage and hobble skirts)
			devices.suits.first.push_back(dev);
		}
		if (rend->HasKeywordString("zad_DeviousSuit") && !rend->HasKeywordString("zad_DeviousHeavyBondage") && !rend->HasKeywordString("zad_DeviousHobbleSkirt")) { // Suits without heavy bondage or skirts
			devices.suitsSimple.first.push_back(dev);
		}
		if (rend->HasKeywordString("zad_DeviousStraitJacket")) { // All StraitJackets
			devices.straitJackets.first.push_back(dev);
			if (!rend->HasKeywordString("zad_EffectForcedWalk")) { // Allow running
				devices.straitJacketsAllowRun.first.push_back(dev);
			}
			else {
				devices.straitJacketsLegbinder.first.push_back(dev);
			}
		}
		else {														 // All hobble skirt lists won't contain strait jackets
			if (rend->HasKeywordString("zad_DeviousHobbleSkirt")) { // All Hobble Skirt
				devices.hobbleSkirts.first.push_back(dev);
				if (rend->HasKeywordString("zad_DeviousHobbleSkirtRelaxed")) { // Relaxed
					devices.hobbleSkirtsRelaxed.first.push_back(dev);
				}
				if (!rend->HasKeywordString("zad_DeviousHobbleSkirtRelaxed") && !rend->HasKeywordString("zad_EffectForcedWalk")) { // Standard
					devices.hobbleSkirtsStandard.first.push_back(dev);
				}
				if (rend->HasKeywordString("zad_EffectForcedWalk")) { // Forced Walk
					devices.hobbleSkirtsForcedWalk.first.push_back(dev);
				}
			}
		}

		devices.heavyBondageAll.first.insert(devices.heavyBondageAll.first.end(), devices.straitJackets.first.begin(), devices.straitJackets.first.end());
		devices.heavyBondageAll.first.insert(devices.heavyBondageAll.first.end(), devices.armbindersPlus.first.begin(), devices.armbindersPlus.first.end());
		devices.heavyBondageAll.first.insert(devices.heavyBondageAll.first.end(), devices.yokes.first.begin(), devices.yokes.first.end());
		devices.heavyBondageAll.first.insert(devices.heavyBondageAll.first.end(), devices.petSuits.first.begin(), devices.petSuits.first.end());

		devices.heavyBondageNoSuit.first.insert(devices.heavyBondageNoSuit.first.end(), devices.heavyBondageAll.first.begin(), devices.heavyBondageAll.first.end());
		//std::copy_if(devices.heavyBondageAll.begin(), devices.heavyBondageAll.end(), std::back_inserter(devices.heavyBondageNoSuit), [](DevicePair i) {return !i.second->HasKeywordString("zad_DeviousSuit"); });
		//auto x = devices.heavyBondageNoSuit | std::ranges::views::filter([](DevicePair i) {return !i.second->HasKeywordString("zad_DeviousSuit"); });
		return true;
	}

	bool vectorContains(std::vector<std::string> vec, std::string elem) {
		return std::find(vec.begin(), vec.end(), elem) != vec.end();
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
		return false;
	}

	void createDevices() {
		auto API = DeviousDevicesAPI::g_API;
		if (!API) {
			log::error("Devious Devices API not loaded");
			return;
		}

		int counter = 0;

		if (RE::TESDataHandler::GetSingleton()->LookupLoadedModByName("UnforgivingDevices.esp") == nullptr) {
			settings.onlyUseUnforgivingDevices = false;
			SetMCMBool("onlyUseUnforgivingDevices", false);
		}

		if (settings.onlyUseUnforgivingDevices) {
			log::info("Building device lists for Unforgiving Devices.");
		}

		auto exclusions = GetDeviceExclusions();

		log::info("Total devices from api: {}", API->GetDatabase().size());
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
			
			if (!deviceKey && API->GetPropertyFloat(device, "LockAccessDifficulty", 0.0, 0) == 0) {
				continue;
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

			if (settings.onlyUseUnforgivingDevices && !(deviceRendered->HasKeywordString("UD_UnforgivingDevice") && deviceInventory->HasKeywordString("UD_InventoryDevice"))) {
				continue;
			}

			auto keyCount = API->GetPropertyInt(device, "NumberOfKeysNeeded", 1, 0);

			if (keyCount > settings.maxHeldKeys && settings.maxHeldKeys > 0) {
				continue;
			}

			bool isLockless = false;
			if (!deviceKey && API->GetPropertyFloat(device, "LockAccessDifficulty", 0.0, 0) > 0) {
				isLockless = true;
			}

			DeviceData dat{
				deviceInventory,
				deviceRendered,
				isLockless,
				keyCount
			};

			if (ProcessDevice(dat, exclusions)) {
				counter++;
			}
		}
		log::info("Total accepted devices: {}", counter);

		//CODEGEN_START_DEVICES_NAMES
		devices.belts.second = "belts";
		devices.beltsNoPiercings.second = "beltsNoPiercings";
		devices.bras.second = "bras";
		devices.plugs.second = "plugs";
		devices.plugsV.second = "plugsV";
		devices.plugsVBasic.second = "plugsVBasic";
		devices.plugsVLock.second = "plugsVLock";
		devices.plugsVInf.second = "plugsVInf";
		devices.plugsA.second = "plugsA";
		devices.plugsABasic.second = "plugsABasic";
		devices.plugsALock.second = "plugsALock";
		devices.plugsAInf.second = "plugsAInf";
		devices.collars.second = "collars";
		devices.legCuffs.second = "legCuffs";
		devices.legCuffsStandard.second = "legCuffsStandard";
		devices.legCuffsShackles.second = "legCuffsShackles";
		devices.armCuffs.second = "armCuffs";
		devices.piercingsN.second = "piercingsN";
		devices.piercingsV.second = "piercingsV";
		devices.blindfolds.second = "blindfolds";
		devices.harnesses.second = "harnesses";
		devices.harnessesOpen.second = "harnessesOpen";
		devices.gags.second = "gags";
		devices.gagsStandard.second = "gagsStandard";
		devices.gagsLarge.second = "gagsLarge";
		devices.gagsOpen.second = "gagsOpen";
		devices.gagsOpenLarge.second = "gagsOpenLarge";
		devices.corsetsNoBelt.second = "corsetsNoBelt";
		devices.corsetsBelt.second = "corsetsBelt";
		devices.boots.second = "boots";
		devices.glovesMittens.second = "glovesMittens";
		devices.glovesNoMittens.second = "glovesNoMittens";
		devices.hoodsBlockAll.second = "hoodsBlockAll";
		devices.hoodsBlockGag.second = "hoodsBlockGag";
		devices.hoodsBlockEye.second = "hoodsBlockEye";
		devices.hoodsNoBlock.second = "hoodsNoBlock";
		devices.armbindersPlus.second = "armbindersPlus";
		devices.armbinders.second = "armbinders";
		devices.elbowbinders.second = "elbowbinders";
		devices.yokes.second = "yokes";
		devices.armShackles.second = "armShackles";
		devices.petSuits.second = "petSuits";
		devices.suits.second = "suits";
		devices.suitsSimple.second = "suitsSimple";
		devices.straitJackets.second = "straitJackets";
		devices.straitJacketsAllowRun.second = "straitJacketsAllowRun";
		devices.straitJacketsLegbinder.second = "straitJacketsLegbinder";
		devices.hobbleSkirts.second = "hobbleSkirts";
		devices.hobbleSkirtsRelaxed.second = "hobbleSkirtsRelaxed";
		devices.hobbleSkirtsStandard.second = "hobbleSkirtsStandard";
		devices.hobbleSkirtsForcedWalk.second = "hobbleSkirtsForcedWalk";
		devices.heavyBondageAll.second = "heavyBondageAll";
		devices.heavyBondageNoSuit.second = "heavyBondageNoSuit";
		//CODEGEN_END_DEVICES_NAMES
	}

	void RecalculateDeviceLists() {
		devices = Devices();
		createDevices();
	}

	std::vector<std::string> GetDeviceKeywords(RE::TESObjectARMO* wornArmor, bool includeBlocking) {
		std::vector<std::string> keys;
		if (!wornArmor) return keys;

		for (uint32_t i = 0; i < wornArmor->numKeywords; i++) {
			auto keywd = wornArmor->keywords[i];
			auto kwname = Util::GetFormEditorId(keywd);
			if (kwname.starts_with("zad_Devious") && kwname != "zad_DeviousPlug") {
				keys.push_back(kwname);
				if (includeBlocking) {
					if (kwname == "zad_DeviousHarness") {
						keys.push_back("zad_DeviousCorset");
					}
					if (kwname == "zad_DeviousCorset") {
						keys.push_back("zad_DeviousHarness");
					}
					if (
						kwname == "zad_DeviousBelt")
					{
						if (!wornArmor->HasKeywordString("zad_PermitAnal")) {
							keys.push_back("zad_DeviousPlugAnal");
						}
						if (!wornArmor->HasKeywordString("zad_PermitVaginal")) {
							keys.push_back("zad_DeviousPiercingsVaginal");
							keys.push_back("zad_DeviousPlugVaginal");
						}
					}
					if (kwname == "zad_DeviousBra") {
						keys.push_back("zad_DeviousPiercingsNipple");
					}
				}
			}
		}
		return keys;
	}

	RE::TESObjectARMO* GetWornDeviceByKeyword(RE::Actor* actor, std::string keyword) {
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

	std::vector<std::string> GetKeywordsCantEquip(RE::Actor* actor) {
		std::vector<std::string> keys;
		if (!actor) return keys;

		auto inventory = actor->GetInventory();
		for (auto const& [k, v] : inventory) {
			if (v.second.get()->IsWorn()) {
				RE::TESObjectARMO* wornArmor = k->As<RE::TESObjectARMO>();
				if (!wornArmor) {
					continue;
				}
				for (std::string kw : GetDeviceKeywords(wornArmor, true)) { keys.push_back(kw); }
			}
		}
		return keys;
	}

	std::vector<std::string> GetWornDeviceKeywords(RE::Actor* actor) {
		std::vector<std::string> keys;
		if (!actor) return keys;

		auto inventory = actor->GetInventory();
		for (auto const& [k, v] : inventory) {
			if (v.second.get()->IsWorn()) {
				RE::TESObjectARMO* wornArmor = k->As<RE::TESObjectARMO>();
				if (!wornArmor) {
					continue;
				}
				for (std::string kw : GetDeviceKeywords(wornArmor, false)) { keys.push_back(kw); }
			}
		}
		return keys;
	}

	int numDevicesVisible(RE::Actor* actor) {
		if (!actor) return 0;

		auto inventory = actor->GetInventory();
		bool hasChestArmor = actor->GetWornArmor((RE::BIPED_MODEL::BipedObjectSlot::kBody)) != nullptr;
		std::set<std::string> checked = std::set<std::string>();
		int count = 0;
		for (auto const& [k, v] : inventory) {
			if (v.second.get()->IsWorn()) {
				RE::TESObjectARMO* wornArmor = k->As<RE::TESObjectARMO>();
				if (!wornArmor) {
					continue;
				}
				for (std::string kw : GetDeviceKeywords(wornArmor, false)) {
					if (checked.find(kw) != checked.end()) { continue; }
					checked.insert(kw);
					if (kw == "zad_DeviousHeavyBondage" || kw == "zad_DeviousCollar" || kw == "zad_DeviousBoots" || kw == "zad_DeviousSuit" || kw == "zad_DeviousGloves" || kw == "zad_DeviousHood" || kw == "zad_DeviousGag" || kw == "zad_DeviousBlindfold") {
						count++;
					}
					else if (!hasChestArmor) {
						if (kw == "zad_DeviousCorset" || kw == "zad_DeviousHarness" || kw == "zad_DeviousArmCuffs" || kw == "zad_DeviousLegCuffs" || kw == "zad_DeviousBelt" || kw == "zad_DeviousBra" || kw == "zad_DeviousPiercingsNipple" || kw == "zad_DeviousPiercingsVaginal") {
							count++;
						}
					}
				}
			}
		}
		return count;
	}

	DeviceList GetRandomWeightedList(RE::Actor* actor, std::vector<std::string> skipList, std::string theme = "") {
		if (!actor) return DeviceList();

		static const std::vector<std::string> allDeviceKeywords = { "zad_DeviousBelt", "zad_DeviousBra", "zad_DeviousPlugVaginal", "zad_DeviousPlugAnal", "zad_DeviousCollar", "zad_DeviousLegCuffs",
																	"zad_DeviousArmCuffs", "zad_DeviousPiercingsNipple", "zad_DeviousPiercingsVaginal", "zad_DeviousBlindfold", "zad_DeviousHarness",
																	"zad_DeviousGag", "zad_DeviousBoots", "zad_DeviousGloves", "zad_DeviousHood", "zad_DeviousSuit", "zad_DeviousHeavyBondage" };
		std::vector<std::pair<DeviceList*, double>> lists;
		for (auto const& keyword : allDeviceKeywords) {
			if (std::find(skipList.begin(), skipList.end(), keyword) == skipList.end()) {// Can equip this keyword
				if (keyword == "zad_DeviousBelt") {
					if (settings.noBeltPiercing || std::find(skipList.begin(), skipList.end(), "zad_DeviousPiercingsVaginal") != skipList.end()) {
						lists.push_back(std::pair(&devices.beltsNoPiercings, settings.beltWeight));
					}
					else {
						lists.push_back(std::pair(&devices.belts, settings.beltWeight));
					}
				}
				if (keyword == "zad_DeviousBra") {
					lists.push_back(std::pair(&devices.bras, settings.braWeight));
				}
				if (keyword == "zad_DeviousPlugVaginal") {
					lists.push_back(std::pair(&devices.plugsVLock, settings.lockingPlugsWeight));
					lists.push_back(std::pair(&devices.plugsVBasic, settings.plugsWeight));
					lists.push_back(std::pair(&devices.plugsVInf, settings.inflatablePlugsWeight));
				}
				if (keyword == "zad_DeviousPlugAnal") {
					lists.push_back(std::pair(&devices.plugsALock, settings.lockingPlugsWeight));
					lists.push_back(std::pair(&devices.plugsABasic, settings.plugsWeight));
					lists.push_back(std::pair(&devices.plugsAInf, settings.inflatablePlugsWeight));
				}
				if (keyword == "zad_DeviousCollar") {
					lists.push_back(std::pair(&devices.collars, settings.collarWeight));
				}
				if (keyword == "zad_DeviousLegCuffs") {
					if (settings.allowLegShackles) {
						lists.push_back(std::pair(&devices.legCuffs, settings.legCuffsWeight));
					}
					else {
						lists.push_back(std::pair(&devices.legCuffsStandard, settings.legCuffsWeight));
					}
				}
				if (keyword == "zad_DeviousArmCuffs") {
					lists.push_back(std::pair(&devices.armCuffs, settings.armCuffsWeight));
				}
				if (keyword == "zad_DeviousPiercingsNipple") {
					lists.push_back(std::pair(&devices.piercingsN, settings.nipplePiercingsWeight));
				}
				if (keyword == "zad_DeviousPiercingsVaginal") {
					lists.push_back(std::pair(&devices.piercingsV, settings.vaginalPiercingsWeight));
				}
				if (keyword == "zad_DeviousBlindfold") {
					lists.push_back(std::pair(&devices.blindfolds, settings.blindfoldWeight));
				}
				if (keyword == "zad_DeviousHarness") {
					lists.push_back(std::pair(&devices.harnessesOpen, settings.slaveHarnessWeight));
					lists.push_back(std::pair(&devices.corsetsNoBelt, settings.corsetWeight));
					if (std::find(skipList.begin(), skipList.end(), "zad_DeviousBelt") != skipList.end()) { // No Belt
						lists.push_back(std::pair(&devices.harnesses, settings.chastityHarnessWeight));
						lists.push_back(std::pair(&devices.corsetsBelt, settings.corsetWeight));
					}
				}
				if (keyword == "zad_DeviousGag") {
					lists.push_back(std::pair(&devices.gagsStandard, settings.gagWeight));
					lists.push_back(std::pair(&devices.gagsLarge, settings.largeGagWeight));
					lists.push_back(std::pair(&devices.gagsOpen, settings.ringGagWeight));
					lists.push_back(std::pair(&devices.gagsOpenLarge, settings.largeRingGagWeight));
				}
				if (keyword == "zad_DeviousBoots") {
					lists.push_back(std::pair(&devices.boots, settings.bootsWeight));
				}
				if (keyword == "zad_DeviousGloves") {
					lists.push_back(std::pair(&devices.glovesNoMittens, settings.glovesWeight));
					lists.push_back(std::pair(&devices.glovesMittens, settings.mittensWeight));
				}
				if (keyword == "zad_DeviousHood") {
					bool canBlindfold = std::find(skipList.begin(), skipList.end(), "zad_DeviousBlindfold") == skipList.end();// && !settings.hoodNoBlind;
					bool canGag = std::find(skipList.begin(), skipList.end(), "zad_DeviousGag") == skipList.end();// && !settings.hoodNoGag;
					lists.push_back(std::pair(&devices.hoodsNoBlock, settings.hoodNoneWeight));
					if (canBlindfold) {
						lists.push_back(std::pair(&devices.hoodsBlockEye, settings.hoodBlindWeight));
					}
					if (canGag) {
						lists.push_back(std::pair(&devices.hoodsBlockGag, settings.hoodGagWeight));
					}
					if (canGag && canBlindfold) {
						lists.push_back(std::pair(&devices.hoodsBlockAll, settings.hoodBothWeight));
					}
				}
				if (keyword == "zad_DeviousSuit") {
					lists.push_back(std::pair(&devices.suitsSimple, settings.catsuitWeight));
					double w1 = std::max(100 - 1.5 * settings.hobbleSkirtDifficulty, 0.0) / 125.0;
					double w2 = std::min(100 - 1.5 * std::abs(50 - settings.hobbleSkirtDifficulty), 75.0) / 125.0;
					double w3 = std::max(-50 + 1.5 * settings.hobbleSkirtDifficulty, 0.0) / 125.0;
					lists.push_back(std::pair(&devices.hobbleSkirtsRelaxed, settings.hobbleSkirtWeight * w1));
					lists.push_back(std::pair(&devices.hobbleSkirtsStandard, settings.hobbleSkirtWeight * w2));
					lists.push_back(std::pair(&devices.hobbleSkirtsForcedWalk, settings.hobbleSkirtWeight * w3));
				}
				if (keyword == "zad_DeviousHeavyBondage") {
					lists.push_back(std::pair(&devices.armbinders, settings.armbinderWeight));
					lists.push_back(std::pair(&devices.elbowbinders, settings.elbowbinderWeight));
					lists.push_back(std::pair(&devices.yokes, settings.yokeWeight));
					lists.push_back(std::pair(&devices.armShackles, settings.shacklesWeight));
					if (std::find(skipList.begin(), skipList.end(), "zad_DeviousSuit") == skipList.end()) {
						lists.push_back(std::pair(&devices.straitJacketsAllowRun, settings.straitjacketWeight));
						lists.push_back(std::pair(&devices.straitJacketsLegbinder, settings.straitjacketLegbinderWeight));
						lists.push_back(std::pair(&devices.petSuits, settings.petSuitWeight));
					}
				}
			}
		}

		std::vector<std::pair<DeviceList, double>> adjustedLists;

		for (auto list : lists) {
			auto adj = GetAdjustedDeviceList(list.first, skipList, theme);
			adjustedLists.push_back(std::make_pair(adj, list.second));
		}

		double weightMax = 0;
		for (auto const& list : adjustedLists) {
			if (list.first.first.size() > 0) {
				weightMax += list.second;
			}
		}

		double roll = Util::randomDouble(weightMax);
		for (auto const& list : adjustedLists) {
			if (roll < list.second && list.second != 0.0 && list.first.first.size() > 0) {
				log::trace("Selected list {} ({:.2f}%)", list.first.second, 100.0 * list.second / weightMax);
				return list.first;
			}
			if (list.first.first.size() > 0) {
				roll -= list.second;
			}
		}

		return DeviceList();
	}

	std::optional<DeviceData> GetRandomEquipableDevice(RE::Actor* actor, std::vector<std::string> skipList, std::string theme = "") {
		if (!actor) return std::nullopt;


		DeviceList randomList = GetRandomWeightedList(actor, skipList, theme);
		if (randomList.first.size() == 0) {
			if (!randomList.second.empty()) log::trace("Random list {} has no items.", randomList.second);
			return std::nullopt;
		}
		auto dev = GetRandomDevice(&randomList);
		if (!dev) {
			log::trace("Failed to get device from list {} - Length {}", randomList.second, randomList.first.size());
			return std::nullopt;
		}
		else {
			//log::info("Got device {} from list {} - Length {}", dev.value().inv->GetName(), randomList.second, randomList.first.size());
		}
		return dev;
	}

	int GetWornDeviceCount(RE::Actor* actor) {
		if (!actor) return 0;

		int count = 0;
		auto inventory = actor->GetInventory();
		for (auto const& [k, v] : inventory) {
			if (v.second.get()->IsWorn()) {
				RE::TESObjectARMO* wornArmor = k->As<RE::TESObjectARMO>();
				if (!wornArmor) {
					continue;
				}
				for (uint32_t i = 0; i < wornArmor->numKeywords; i++) {
					auto keywd = wornArmor->keywords[i];
					auto kwname = Util::GetFormEditorId(keywd);
					if (kwname == "zad_Lockable") {
						count++;
						break;
					}
				}
			}
		}
		return count;
	}

	uint32_t GetItemCount(RE::Actor* actor, RE::TESForm* item) {
		auto inventory = actor->GetInventory();
		for (auto const& [k, v] : inventory) {
			if (k->formID == item->formID) {
				return v.first;
			}
		}
		return 0;
	}

	RE::TESKey* GenerateKeys(RE::TESObjectREFR* activatedObject, bool skipRand = false) {
		auto player = RE::PlayerCharacter::GetSingleton();

		RE::TESKey* restraintsKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(std::stoi("1775f", 0, 16), "Devious Devices - Integration.esm");
		RE::TESKey* chastityKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(std::stoi("8a4f", 0, 16), "Devious Devices - Integration.esm");
		RE::TESKey* piercingKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(std::stoi("409a4", 0, 16), "Devious Devices - Integration.esm");

		int total_keys = GetItemCount(player, restraintsKey) + GetItemCount(player, chastityKey) + GetItemCount(player, piercingKey);

		if (total_keys >= settings.maxHeldKeys && settings.maxHeldKeys > 0) {
			return nullptr;
		}

		if (!(activatedObject && activatedObject->HasContainer())) {
			return nullptr;
		}

		double restraintsWeight = settings.restraintsKeyWeight;
		double chastityWeight = settings.chastityKeyWeight;
		double piercingWeight = settings.piercingToolWeight;

		int restraintsTotal = 0;
		int chastityTotal = 0;
		int piercingTotal = 0;

		if (settings.preferRelevantKeys) {
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

		double baseChance = settings.keyChance;
		double chance = baseChance;
		int deviceCount = GetWornDeviceCount(player);
		if (settings.keyBonus > 0) {
			chance += deviceCount * settings.keyBonus;
		}
		double keyForgiveness = (4.0f * (counters.SinceLastKey + 5.0f)) / (counters.SinceLastKey + 20.0f);
		if (settings.keyForgiveness) {
			chance *= keyForgiveness;
		}
		RE::Actor* actor = activatedObject->As<RE::Actor>();
		if (actor && !actor->IsDead() && !actor->IsChild() && player->IsSneaking() && actor->CanPickpocket()) {
			//log::trace("Pickpocket: {}", settings.keyPickpocketBonus);
			chance *= settings.keyPickpocketBonus;
		}

		double r = Util::randomDouble();
		log::trace("key chance {:.2f}% ({:.2f})", chance, r);

		if (r < chance || skipRand) {

			double weightSum = restraintsWeight + chastityWeight + piercingWeight;

			double roll = Util::randomDouble(weightSum);
			if (roll < piercingWeight) {
				//SKSE::GetTaskInterface()->AddTask([activatedObject, piercingKey] {
					activatedObject->AddObjectToContainer((RE::TESBoundObject*)piercingKey, nullptr, 1, nullptr);
					counters.SinceLastKey = 0;
				//});
				return piercingKey;
			}
			else if (roll - piercingWeight < chastityWeight) {
				//SKSE::GetTaskInterface()->AddTask([activatedObject, chastityKey] {
					activatedObject->AddObjectToContainer((RE::TESBoundObject*)chastityKey, nullptr, 1, nullptr);
					counters.SinceLastKey = 0;
				//});
				return chastityKey;
			}
			else {
				//SKSE::GetTaskInterface()->AddTask([activatedObject, restraintsKey] {
					activatedObject->AddObjectToContainer((RE::TESBoundObject*)restraintsKey, nullptr, 1, nullptr);
					counters.SinceLastKey = 0;
				//});
				return restraintsKey;
			}
		}

		counters.SinceLastKey++;
		return nullptr;
	}

	void RemoveKeys(RE::TESObjectREFR* activatedObject) {
		RE::TESKey* restraintsKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(std::stoi("1775f", 0, 16), "Devious Devices - Integration.esm");
		RE::TESKey* chastityKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(std::stoi("8a4f", 0, 16), "Devious Devices - Integration.esm");
		RE::TESKey* piercingKey = StaticDataHolder::GetSingleton()->LookupForm<RE::TESKey>(std::stoi("409a4", 0, 16), "Devious Devices - Integration.esm");

		//RE::TESKey* chaosFragment = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESKey>(std::stoi("01F367", 0, 16), "Devious Curses.esp");

		if (!(activatedObject && activatedObject->HasContainer())) {
			return;
		}

		//SKSE::GetTaskInterface()->AddTask([activatedObject, restraintsKey, chastityKey, piercingKey] {
			auto inventory = activatedObject->GetInventory();
			for (auto const& [k, v] : inventory) {

				if (k == restraintsKey) {
					activatedObject->RemoveItem((RE::TESBoundObject*)restraintsKey, v.first, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
				}
				if (k == chastityKey) {
					activatedObject->RemoveItem((RE::TESBoundObject*)chastityKey, v.first, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
				}
				if (k == piercingKey) {
					activatedObject->RemoveItem((RE::TESBoundObject*)piercingKey, v.first, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
				}
			}
		//});


	}

	void RemoveAllRestraints(RE::Actor* actor, bool destroyAll = false) {
		if (!actor) return;
		log::trace("Attempting to remove all restraints");
		std::vector<std::pair<RE::TESObjectARMO*, RE::TESObjectARMO*>> removes;

		auto inventory = actor->GetInventory();
		for (auto const& [k, v] : inventory) {
			RE::TESObjectARMO* armor = k->As<RE::TESObjectARMO>();
			if (armor && armor->HasKeywordString("zad_InventoryDevice") && !armor->HasKeywordString("zad_BlockGeneric") && !armor->HasKeywordString("zad_QuestItem") && v.second.get() && v.second.get()->IsWorn()) {
				auto render = DeviousDevicesAPI::g_API->GetDeviceRender(armor);
				if (render) {
					removes.push_back(std::make_pair(armor, render));
				}
			}
		}

		SKSE::GetTaskInterface()->AddTask([removes, actor, destroyAll] {
			for (auto& [dev, rend] : removes) {
				UnlockDevice(actor, dev, rend, nullptr, destroyAll, true);
			}
		});
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

	bool TestTheme(std::string theme, std::vector<std::string> skipKeywords = {}) {
		RE::Actor* player = RE::PlayerCharacter::GetSingleton();

		std::list<RE::TESObjectARMO*> to_equip;

		std::string device_names = "";
		std::string device_ids = "";

		std::vector<std::string> usedKeys = GetKeywordsCantEquip(player);

		for (auto kw : skipKeywords) {
			usedKeys.push_back(kw);
		}

		for (int i = 0; i < 10; i++) {
			auto dev = GetRandomEquipableDevice(player, usedKeys, theme);
			if (dev) {
				return true;
			}
		}

		return false;
	}
}