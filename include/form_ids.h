#pragma once

using namespace SKSE;

namespace DCURSES {
// DCURSES
constexpr auto MAGIC_KEY = 0x806;
constexpr auto TATTOO_CHARM = 0x809;
constexpr auto DCURSES_MCM = 0x800;

constexpr auto SAARTHAL_COLLAR = 0x810;
constexpr auto SAARTHAL_MCOLLAR = 0x811;
constexpr auto SAARTHAL_KEY = 0x807;
constexpr auto SAARTHAL_SUMMON_SPELL = 0x801;

constexpr auto NOCTURNAL_PLUG1 = 0x812;
constexpr auto NOCTURNAL_PLUG2 = 0x813;

constexpr auto MARK_CONTROLLER = 0x818;
constexpr auto MARK_SPELL = 0x817;
constexpr auto MARK_EFFECT = 0x816;
// DDX
constexpr auto DDX_RUSTY_PEAR_ANAL_SIGN = 0x1FC45;
constexpr auto DDX_RUSTY_PEAR_VAGINAL = 0x1FC4F;
constexpr auto DDX_STEEL_YOKE = 0x3D2E1;
constexpr auto DDX_RED_ARMBINDER = 0x110F2;
constexpr auto DDX_RED_CATSUIT = 0x3D8fC;

	class StaticDataHolder {
	private: 
		std::map<std::pair<uint32_t, std::string>, RE::TESForm*> _internalData;
		StaticDataHolder() {}
	public:
		StaticDataHolder(StaticDataHolder const&) = delete;
		void operator=(StaticDataHolder const&) = delete;

		static StaticDataHolder* GetSingleton() {
			static StaticDataHolder instance;
			return &instance;
		}

		template<class T>
		T* LookupForm(uint32_t formid, std::string modname) {
			auto pair = std::make_pair(formid, modname);
			if (_internalData.count(pair)) {
				//log::trace("StaticDataHolder Returning stored data {:X} from {}", formid, modname);
				auto form = _internalData.at(pair)->As<T>();
				return form->Is(T::FORMTYPE) ? static_cast<T*>(form) : 0;
			}
			else {
				//log::trace("StaticDataHolder grabbing {:X} from {}", formid, modname);
				RE::TESForm* form = RE::TESDataHandler::GetSingleton()->LookupForm(formid, modname);
				_internalData.insert({ pair, form });
				return form->Is(T::FORMTYPE) ? static_cast<T*>(form) : 0;
			}
		}
	};
}