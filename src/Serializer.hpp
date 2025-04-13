#pragma once

using namespace SKSE;

namespace DCURSES {
    inline const size_t REF_COUNT = 512;
    inline const size_t PICK_COUNT = 32;
    inline const size_t CONS_COUNT = 32;

    class Counters {
    public:
        int64_t clock_lastSex = 0;
        int64_t clock_LMEventTimer = 0;
        int64_t clock_QIMeridia = 0;
        int64_t clock_QINocturnal = 0;
        void tick() {
            clock_lastSex += 1;
            clock_LMEventTimer += 1;
            clock_QIMeridia += 1;
            clock_QINocturnal += 1;
        }
        int64_t SinceLastKey = 0;
        int64_t SinceLastEvent = 0;

        int64_t LMDevicesEquipped = 0;
        int64_t LMContainersOpened = 0;
        int64_t LMPeopleTalked = 0;
        int64_t LMSexCounter = 0;
    } counters;

    class RefLists {
    public:
        uint32_t eventList[REF_COUNT];
        size_t eventIndex = 0;
        uint32_t pickpocketList[PICK_COUNT];
        size_t pickpocketIndex = 0;
        uint32_t consequenceList[CONS_COUNT];
        size_t consequenceIndex = 0;

        RefLists() {
            for (int i = 0; i < REF_COUNT; i++) { eventList[i] = 0; }
            for (int i = 0; i < PICK_COUNT; i++) { pickpocketList[i] = 0; }
            for (int i = 0; i < CONS_COUNT; i++) { consequenceList[i] = 0; }
        }
    } refLists;


    inline const auto RefListsRecord = _byteswap_ulong('REFL');

    inline const auto ClocksRecord = _byteswap_ulong('CLKS');

    bool IsObjectRefKnown(uint32_t refId) {
        for (int i = 0; i < REF_COUNT; i++) {
            if (refLists.eventList[i] == refId) {
                return true;
            }
        }
        return false;
    }

    bool IsPickpocketTargetKnown(uint32_t refId) {
        for (int i = 0; i < PICK_COUNT; i++) {
            if (refLists.pickpocketList[i] == refId) {
                return true;
            }
        }
        return false;
    }

    bool IsConsequenceTargetKnown(uint32_t refId) {
        for (int i = 0; i < CONS_COUNT; i++) {
            if (refLists.consequenceList[i] == refId) {
                return true;
            }
        }
        return false;
    }

    void SetObjectRefKnown(uint32_t refId) {
        refLists.eventList[refLists.eventIndex] = refId;
        //log::trace("assigning form {} to index {}", refId, knownRefsIndex);
        refLists.eventIndex = (refLists.eventIndex + 1) % REF_COUNT;
    }

    void SetPickpocketTargetKnown(uint32_t refId) {
        refLists.pickpocketList[refLists.pickpocketIndex] = refId;
        //log::trace("assigning form {} to index {}", refId, knownRefsIndex);
        refLists.pickpocketIndex = (refLists.pickpocketIndex + 1) % PICK_COUNT;
    }

    void SetConsequenceTargetKnown(uint32_t refId) {
        refLists.consequenceList[refLists.consequenceIndex] = refId;
        //log::trace("assigning form {} to index {}", refId, knownRefsIndex);
        refLists.consequenceIndex = (refLists.consequenceIndex + 1) % CONS_COUNT;
    }
    
    void OnGameSaved(SerializationInterface* serde) {
        if (!serde->OpenRecord(RefListsRecord, 0)) {
            log::error("Unable to open record to write cosave data.");
            return;
        }
        serde->WriteRecordData(&refLists, sizeof(RefLists));

        if (!serde->OpenRecord(ClocksRecord, 0)) {
            log::error("Unable to open record to write cosave data.");
            return;
        }
        serde->WriteRecordData(&counters, sizeof(Counters));
    }

    void OnGameLoaded(SerializationInterface* serde) {
        std::uint32_t type;
        std::uint32_t size;
        std::uint32_t version;
        
        while (serde->GetNextRecordInfo(type, version, size)) {
            if (type == RefListsRecord) {
                if (sizeof(RefLists) == size) {
                    serde->ReadRecordData(&refLists, sizeof(RefLists));
                }
                else {
                    log::warn("Error reading ref lists info.");
                }
            }
            if (type == ClocksRecord) {
                if (sizeof(Counters) == size) {
                    serde->ReadRecordData(&counters, sizeof(Counters));
                }
                else {
                    log::warn("Error reading clocks info, all timers reset.");
                }
            }
        }
    }

    void OnRevert(SerializationInterface*) {
        refLists = RefLists();
        counters = Counters();
    }


    void InitializeSerialization() {
        log::trace("Initializing cosave serialization...");
        auto* serde = GetSerializationInterface();
        serde->SetUniqueID(_byteswap_ulong('DCRS'));
        serde->SetSaveCallback(OnGameSaved);
        serde->SetRevertCallback(OnRevert);
        serde->SetLoadCallback(OnGameLoaded);
        log::trace("Cosave serialization initialized.");
    }
}