#pragma once

#include "Utils.h"
#include "form_ids.h"
#include <algorithm>

namespace SexLab {
	//Copy of data from SchlongsOfSkyrim.yaml
	static inline const std::vector<std::pair<std::string, uint32_t>> SOS_ExcludeFactionData = {
		{"BDHoodieFemale.esp", 0x90C},
		{"SOS - Pubic Hair for Females Addon.esp", 3427},
		{"SOS - BakaFire Addon.esp", 3427},
		{"SOS - BakaV Addon.esp", 3427},
		{"SOS - BakaTree Addon.esp", 3427},
		{"SOS - BakaLStrip Addon.esp", 3427},
		{"SOS Female Schlongifier (No Schlong Addon by Erundil).esp", 0xD63},
		{"SOS - No Futanari Schlong - Addon.esp", 0xD63},
		{"SOS - No Futanari Schlong - Addon ESL.esp", 1},
		{"SOS - Female Pubics.esp", 0x802},
		{"SOS - Female Pubics.esp", 0x849},
		{"SOS - Female Pubics.esp", 0x890},
		{"SOS - Female Pubics.esp", 0x8D7},
		{"SOS - Female Pubics.esp", 0x91E},
		{"SOS - Female Pubics.esp", 0x965},
		{"SOS - Female Pubics.esp", 0x9AC},
		{"SOS - Female Pubics.esp", 0x9F3},
		{"SOS - Female Pubics.esp", 0xA3A},
		{"SOS - Female Pubics.esp", 0xA83},
		{"SOS - Female Pubics.esp", 0xB02},
		{"SOS - Female Pubics.esp", 0xD63},
	};

	inline std::vector<RE::FormID> GetExcludeFactions() {
		std::vector<RE::FormID> ret;
		auto handler = RE::TESDataHandler::GetSingleton();
		for (auto pair : SOS_ExcludeFactionData) {
			const auto fac = handler->LookupFormID(pair.second, pair.first);
			if (fac) {
				ret.push_back(fac);
			}
		}
		return ret;
	}

	inline bool IsFuta(RE::Actor* a_actor)
	{
		static const auto tngkeyword = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("TNG_SkinWithPenis");
		if (tngkeyword) {
			if (auto skin = a_actor->GetSkin(); skin && skin->HasKeyword(tngkeyword)) {
				return true;
			}
		}

		static const auto sosfaction = DCURSES::StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(0x805, "Schlongs of Skyrim.esp");
		if (sosfaction) {
			bool ret = false;
			a_actor->VisitFactions([&ret](RE::TESFaction* a_faction, int8_t a_rank) -> bool {
				if (!a_faction || a_rank < 0)
					return false;

				if (a_faction == sosfaction) {
					ret = true;
					return false;
				}
				else if (std::ranges::contains(GetExcludeFactions(), a_faction->formID)) {
					ret = false;
					return true;
				}
				else if (std::string name{ a_faction->GetFullName() }; !name.empty()) {
					DCURSES::Util::tolower(name);
					if (name.find("pubic") != std::string::npos) {
						ret = false;
						return true;
					}
				}
				return false;
				});
			return ret;
		}
		return false;

	}

	// DOES NOT HANDLE CREATURES
	inline int GetSex(RE::Actor* a_actor, bool a_skipfactions = false)
	{
		if (!a_skipfactions) {
			RE::TESFaction* SexlabGenderFaction = DCURSES::StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("043A43", 0, 16), "SexLab.esm");
			auto rank = a_actor->GetFactionRank(SexlabGenderFaction, a_actor == RE::PlayerCharacter::GetSingleton());
			if (rank >= 0 && rank <= 2) {
				return rank;
			}
		}

		const auto base = a_actor->GetActorBase();
		if (!base) {
			return -1;
		}
		switch (base->GetSex()) {
		default:
		case RE::SEXES::kMale:
			return 0;
		case RE::SEXES::kFemale:
			return IsFuta(a_actor) ? 2 : 1;
		}
	}
}