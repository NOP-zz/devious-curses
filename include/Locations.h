#pragma once

namespace DCURSES {
	enum class LocationType {
		Wilderness,
		PlayerHome,
		City,
		Town,
		Draugr,
		Falmer,
		Dwarven,
		Forsworn,
		Vampire,
		Warlock,
		DragonLair,
		Apocrypha,
		Bandit,
        SoulCairn,
        Unknown,
	};

    LocationType GetLocationType(RE::BGSLocation* location);

    LocationType GetPlayerLocationType();

    std::string GetLocationTypeString(LocationType type);

	float GetLocationTypeEventModifier(LocationType type);
}