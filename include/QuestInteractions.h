#pragma once

namespace DCURSES {
	

	//void QIMeridiaInteraction();

	//void QISanguineInteraction1();

	//void QISanguineInteractionEnd();

	//void QIBlackStarTouch();

	//void QIMindOfMadness();

	//void QIPotemaInteraction(); // Add a curse during the potema questline. Sugestion was to have a curse that periodically summons devices. Gets stronger when fighting potema??

	//void QIMainDiplomaticImmunity();

	//void QIMGInteraction1();

	//void QIMGBrelyna1();

	//void QIMGBrelyna2();

	//void QIDwemerMuseum();

	//void QITrinityRestored();

	//void QICompanionsProvingHonor();

	//void QICompanionsCollarJoke();

	//void QILaidToRest();

	//void QICriedWolf();

	//void QIRingmaker();

	void QICheckQuestStage(RE::FormID quest_id, uint16_t stage);

	void QICheckObjectActivation(RE::TESObjectREFR* object);

	void QIOnSpellCast(const RE::TESSpellCastEvent* spellEvent);
}