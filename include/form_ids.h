#pragma once

#include "../src/Utils.hpp"

using namespace SKSE;

namespace DCURSES {
// DCURSES
constexpr auto TATTOO_CHARM = 0x809;
constexpr auto VOLATILE_GEM = 0x839;
constexpr auto AROUSAL_POTION = 0x83B;
constexpr auto DCURSES_MCM = 0x800;

// DEVICES
constexpr auto SUMMONER_COLLAR = 0x810;
constexpr auto SUMMONER_COLLAR_R = 0x80A;
constexpr auto LIVING_LATEX = 0x812;
constexpr auto LIVING_LATEX_R = 0x813;
constexpr auto LIVING_LATEX_OPEN = 0x819;
constexpr auto LIVING_LATEX_OPEN_R = 0x81A;
constexpr auto DWARVEN_CURIAS = 0x828;
constexpr auto DWARVEN_CURIAS_R = 0x81B;
constexpr auto DWARVEN_CURIAS_HEAVY = 0x82E;
constexpr auto DWARVEN_CURIAS_HEAVY_R = 0x82D;
constexpr auto MADNESS_PLUG = 0x82F;
constexpr auto MADNESS_PLUG_R = 0x82A;
constexpr auto MADNESS_PIERCINGS = 0x834;


// KEYS
constexpr auto MAGIC_KEY = 0x806;
constexpr auto SUMMONER_COLLAR_KEY = 0x807;

// SPELLS
constexpr auto MGEF_SPELL = 0x817;
constexpr auto SUMMONER_SUMMON_SPELL = 0x801;
constexpr auto HEALSLUT_RESTORATION_SPELL = 0x83A;

// EFFECTS
constexpr auto ALLURE_EFFECT = 0x80B;
constexpr auto HEAT_EFFECT = 0x805;
constexpr auto NUDITY_EFFECT = 0x80F;
constexpr auto BONDAGE_EFFECT = 0x811;
constexpr auto BRANDING_EFFECT = 0x808;
constexpr auto HEALSLUT_EFFECT = 0x835;
constexpr auto SUMMONER_COLLAR_EFFECT = 0x803;
constexpr auto LIVING_LATEX_EFFECT = 0x816;
constexpr auto DWARVEN_CUIRASS_EFFECT = 0x82B;
constexpr auto MADNESS_PLUG_EFFECT = 0x833;
constexpr auto AROUSAL_POTION_EFFECT = 0x83C;

// PERKS
constexpr auto MGEF_CONTROLLER = 0x818;
constexpr auto HEALSLUT_PERK = 0x837;

// DDX
constexpr auto DDX_RUSTY_PEAR_ANAL_SIGN = 0x1FC45;
constexpr auto DDX_RUSTY_PEAR_VAGINAL = 0x1FC4F;
constexpr auto DDX_STEEL_YOKE = 0x3D2E1;
constexpr auto DDX_RED_ARMBINDER = 0x110F2;
constexpr auto DDX_RED_CATSUIT = 0x3D8fC;
constexpr auto DDX_PUPPY_COLLAR = 0x4F916;

	class StaticDataHolder {
	private: 
		std::mutex mutex = std::mutex();
		std::map<std::pair<uint32_t, std::string>, RE::TESForm*> _internalData;
		StaticDataHolder() {}
	public:
		StaticDataHolder(StaticDataHolder const&) = delete;
		void operator=(StaticDataHolder const&) = delete;

		static StaticDataHolder* GetSingleton() {
			static StaticDataHolder instance;
			return &instance;
		}

		RE::TESForm* LookupFormNoCache(uint32_t a_localFormID, std::string modname) {
			return RE::TESDataHandler::GetSingleton()->LookupForm(a_localFormID, modname);
		}

		template<class T>
		T* LookupFormNoCache(uint32_t a_localFormID, std::string modname) {
			RE::TESForm* form = LookupFormNoCache(a_localFormID, modname);
			return (form && form->Is(T::FORMTYPE)) ? static_cast<T*>(form) : nullptr;
		}

		RE::TESForm* LookupForm(uint32_t formid, std::string modname) {
			auto pair = std::make_pair(formid, modname);
			if (_internalData.count(pair)) {
				//log::trace("StaticDataHolder Returning stored data {:X} from {}", formid, modname);
				return _internalData.at(pair);
			}
			else {
				//log::trace("StaticDataHolder grabbing {:X} from {}", formid, modname);
				RE::TESForm* form = LookupFormNoCache(formid, modname);
				if (form) {
					mutex.lock();
					_internalData.insert({ pair, form });
					mutex.unlock();
				}
				return form;
			}
		}

		template<class T>
		T* LookupForm(uint32_t formid, std::string modname) {
			RE::TESForm* form = LookupForm(formid, modname);
			return (form && form->Is(T::FORMTYPE)) ? static_cast<T*>(form) : nullptr;
		}

		void InvalidateCache() {
			mutex.lock();
			_internalData = std::map<std::pair<uint32_t, std::string>, RE::TESForm*>();
			mutex.unlock();
		}
	};
}