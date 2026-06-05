#pragma once

namespace DCURSES {
    void GenerateRandomDevices(RE::TESObjectREFR* activatedObject);

    bool DoStandardEvent(RE::Actor* actor, bool isBoss, std::string contName, std::string theme = "", int countOverride = -1, int minDevices = 1, std::vector<std::string> skipKeywords = {});

    bool DoSimpleSlaveryEvent(std::string contName);

    bool DoTattooEvent(RE::Actor* actor, std::string containerName, int num_tattoos = -1, bool skipMax = false);

    bool DoContraptionEvent(std::string containerName, RE::Actor* target = nullptr, std::string theme = "");

    bool DoLewdMarkEvent(std::string containerName, double multiplier = 1.0);

    void DoWickedEvent(std::string containerName);

    bool DoAbadonEvent(std::string containerName);

    enum class AbadonEventType : uint32_t {
        Warrior = 1,
        Scout = 2,
        Witch = 3
    };

    bool DoAbadonSetEvent(std::string containerName, RE::Actor* actor, AbadonEventType type);

    std::vector<RE::Actor*> GetFollowersForEvent();

    bool DoEvent(bool isBoss, std::string contName);

    void PlayWardEffect();

    struct ContainerData {
        bool isDeadActor = false;
        bool isPickpocket = false;
        bool isTalking = false;
        bool isBoss = false;
        bool isLeveled = false; // also isContainer
        bool isDoor = false;
        bool isLocked = false;
        bool isDragon = false;
        bool isMage = false;
        int lockLevel = 0;
        int goldValue = 0;
    };

    ContainerData GetContainerData(RE::TESObjectREFR* activatedObject);

    void PopulateContainer(RE::TESObjectREFR* activatedObject, ContainerData data);

    void CalculateEventChance(RE::TESObjectREFR* activatedObject);

    void EventsCheckModIntergations();
}