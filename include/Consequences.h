#pragma once

namespace DCURSES {

	bool getIsNude(RE::Actor* actor, bool isConsequence = false);

	enum class consequenceSource {
		kUnknown,
		kSeenNude,
		kTalkedNude,
		kSeenRestrained,
		kTalkedRestrained,
		kSeenWithHeavy,
		kTalkedWithHeavy,
		kSeenHavingSex,
		kTalkedTattoos,
		kSeenTattoos,
		kSeenTrespassing,
	};

	bool ConsRandomDevice(RE::Actor* actor, consequenceSource source);

	bool ConsSex(RE::Actor* actor, consequenceSource source);

	bool ConsFine(RE::Actor* actor, consequenceSource source);

	bool ConsTattoo(RE::Actor* actor, consequenceSource source);

	bool ConsMercy(RE::Actor* actor, consequenceSource source);

	bool DoConsequence(RE::Actor* actor, consequenceSource source);

	void CheckConsequenceDialogue(RE::Actor* actor);

	void ConsSexEnded(RE::Actor* actor);

	void ConsUpdate();
}