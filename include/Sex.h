#pragma once

namespace DCURSES {

	bool getIsPlayerCommandedActor(RE::Actor* actor);

	int GetDeviceMask(RE::Actor* actor);

	bool SexActorFilter(RE::Actor* actor, bool allowInCombat);

	bool sexCheckPlayerRequirements();

	bool sexCheckActorRequirements(RE::Actor* actor);

	bool sexCheckCreatureRequirements(RE::Actor* actor);

	std::vector<std::pair<RE::Actor*, std::string>> getAllAvailableActors();

	std::vector<RE::Actor*> getPlayerCommandedActors();

	std::string P_GetAnimationFilterTags(RE::StaticFunctionTag*, RE::Actor* akActor);

	std::string P_GetAnimationFilterTagsP(RE::StaticFunctionTag*, RE::Actor* akActor);

	void StartMasturbationImpl();

	void SexUpdate();

	void P_SexStarted(RE::StaticFunctionTag*, RE::BSTArray<RE::Actor*> actors);

	void P_SexEnded(RE::StaticFunctionTag*, RE::BSTArray<RE::Actor*> actors);

	void P_DDPlayerOrgasm(RE::StaticFunctionTag*);

	bool PapyrusFunctionsSex(RE::BSScript::IVirtualMachine* ivm);
}