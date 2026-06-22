#pragma once

constexpr auto EXCLUSIONS_FILE = "Data/SKSE/Plugins/DeviousCursesExclusions.json";
constexpr auto MOD_EXCLUSIONS_FILE = "Data/SKSE/Plugins/DeviousCursesModExclusions.json";

using namespace SKSE;

namespace DCURSES {

	inline const std::set<std::string> AllDeviceKeywords = {
		"zad_DeviousBelt",
		"zad_DeviousBra",
		"zad_DeviousPlugVaginal",
		"zad_DeviousPlugAnal",
		"zad_DeviousCollar",
		"zad_DeviousLegCuffs",
		"zad_DeviousArmCuffs",
		"zad_DeviousPiercingsNipple",
		"zad_DeviousPiercingsVaginal",
		"zad_DeviousBlindfold",
		"zad_DeviousHarness",
		"zad_DeviousHood",
		"zad_DeviousGag",
		"zad_DeviousBoots",
		"zad_DeviousGloves",
		"zad_DeviousSuit",
		"zad_DeviousYoke",
		"zad_DeviousArmbinder",
		"zad_DeviousCorset",
	};

	struct DeviceData {
	public:
		RE::TESObjectARMO* inv;
		RE::TESObjectARMO* rend;
		int keyCount;
		bool isLockless;
		bool isCockCage;
	};

	class DeviceList {
	public:
		std::vector<DeviceData> list;
		std::string name;
		size_t reserve;

		DeviceList(size_t reserve) {
			this->list.reserve(reserve);
			this->reserve = reserve;
		}

		DeviceList() {
			this->list.reserve(100);
			this->reserve = 100;
		}

		void push_back(const DeviceData& data) {
			if (this->list.size() == this->list.capacity()) {
				this->list.reserve(this->reserve * 2);
			}
			this->list.push_back(data);
		}

		size_t get_memory_size() {
			size_t size = this->list.size();
			size_t reserved = this->list.capacity();
			SKSE::log::trace("List {}: {} ({})", this->name, size, reserved);
			return reserved * (sizeof(DeviceData)) + this->name.capacity();
		}
	};

	class Devices {
	private:
		Devices() {}
	public:
		Devices(Devices const&) = delete;
		void operator=(Devices const&) = delete;

		static Devices* GetSingleton() {
			static Devices instance;
			return &instance;
		};

		DeviceList anything = DeviceList(3000);
		DeviceList belts;
		DeviceList beltsPiercings;
		DeviceList beltsCages;
		DeviceList bras;
		DeviceList plugsV;
		DeviceList plugsVBasic;
		DeviceList plugsVLock;
		DeviceList plugsVInf;
		DeviceList plugsA;
		DeviceList plugsABasic;
		DeviceList plugsALock;
		DeviceList plugsAInf;
		DeviceList collars = DeviceList(200);
		DeviceList legCuffs;
		DeviceList legCuffsStandard;
		DeviceList legCuffsShackles;
		DeviceList armCuffs;
		DeviceList piercingsN;
		DeviceList piercingsV;
		DeviceList blindfolds;
		DeviceList harnesses;
		DeviceList harnessesOpen;
		DeviceList gags = DeviceList(300);
		DeviceList gagsStandard = DeviceList(200);
		DeviceList gagsLarge;
		DeviceList gagsOpen;
		DeviceList gagsOpenLarge;
		DeviceList corsetsNoBelt;
		DeviceList corsetsBelt;
		DeviceList boots = DeviceList(200);
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
		//DeviceList suits = DeviceList(300);
		DeviceList suitsSimple;
		DeviceList straitJackets;
		DeviceList straitJacketsAllowRun;
		DeviceList straitJacketsLegbinder;
		DeviceList hobbleSkirts;
		DeviceList hobbleSkirtsRelaxed;
		DeviceList hobbleSkirtsForcedWalk;

		void ClearLists();
	};

	static std::optional<std::filesystem::file_time_type> lastExclusionsEditTime = std::nullopt;
	static std::optional<std::filesystem::file_time_type> lastModExclusionsEditTime = std::nullopt;

	bool NeedUpdateForExclusions();

	DeviceList GetAdjustedDeviceList(DeviceList* list, std::set<std::string> skipList, std::string theme = "");

	std::optional<DeviceData> GetRandomDevice(DeviceList* list, std::set<std::string> skipList = {}, std::string theme = "");

	void CreateExclusionsFileIfNeeded();

	void CreateModExclusionsFileIfNeeded();

	std::vector<std::string> GetDeviceExclusions();

	std::vector<std::string> GetModExclusions();

	bool ProcessDevice(DeviceData dev, std::vector<std::string> exclusions, std::vector<RE::TESFile*> mod_exclusions);

	RE::TESKey* GetDeviceKey(RE::TESObjectARMO* device);

	bool IsGenericKey(RE::TESKey* key);

	bool DeviceHasGenericKey(RE::TESObjectARMO* device);

	bool DeviceInventoryIsGeneric(RE::TESObjectARMO* inv);

	bool DeviceRenderedIsGeneric(RE::TESObjectARMO* rend);

	void createDevices();

	void RecalculateDeviceLists();

	std::set<std::string> GetDeviceKeywords(RE::TESObjectARMO* wornArmor, bool includeBlocking);

	RE::TESObjectARMO* GetWornInventoryDeviceByKeyword(RE::Actor* actor, std::string keyword);

	std::set<std::string> GetKeywordsCantEquip(RE::Actor* actor);

	std::set<std::string> GetWornDeviceKeywords(RE::Actor* actor);

	int GetVisibleDeviceCount(RE::Actor* actor);
	int GetWornDeviceCount(RE::Actor* actor, std::string theme = "");

	DeviceList GetRandomWeightedList(RE::Actor* actor, std::set<std::string> skipList, std::string theme = "");

	std::optional<DeviceData> GetRandomEquipableDevice(RE::Actor* actor, std::set<std::string> skipList, std::string theme = "");

	uint32_t GetItemCount(RE::TESObjectREFR* object, RE::TESForm* item);

	bool ActorIsWearingDevice(RE::Actor* actor, RE::TESObjectARMO* device);

	bool PlayerIsLucky();

	std::vector<RE::TESKey*> GenerateKeys(RE::TESObjectREFR* activatedObject, bool skipRand = false, bool onlyOne = false);

	void RemoveKeys(RE::TESObjectREFR* activatedObject);

	void RemoveAllRestraints(RE::Actor* actor, bool destroyAll = false);

	bool UndressActor(RE::Actor* akActor, bool removeCombatStuff);

	void UnequipItems(RE::Actor* akActor);

	bool UndressAndUnequipActor(RE::Actor* akActor);
}