#pragma once

using namespace SKSE;

namespace DCURSES {
    inline const size_t REF_COUNT = 512;
    inline const size_t PICK_COUNT = 32;
    inline const size_t CONS_COUNT = 32;

    class Counters {
    public:
        int64_t clock_SexTimeout = 0;
        int64_t clock_lastSex = 0;
        uint64_t clock_GlobalTicker = 0;
        int64_t SinceLastKey = 0;
        int64_t SinceLastEvent = 0;
        int64_t ActiveLewdMark = 0;
        int64_t dummyDoNotUse00 = 0;
        int64_t dummyDoNotUse01 = 0;
        int64_t dummyDoNotUse02 = 0;
        int64_t dummyDoNotUse03 = 0;
        int64_t dummyDoNotUse04 = 0;
        int64_t dummyDoNotUse05 = 0;
        int64_t dummyDoNotUse06 = 0;
        int64_t dummyDoNotUse07 = 0;
        int64_t dummyDoNotUse08 = 0;
        int64_t dummyDoNotUse09 = 0;

        void tick() {
            clock_SexTimeout += 1;
            clock_lastSex += 1;
            clock_GlobalTicker += 1;
        }
    } counters;

    static_assert(sizeof(Counters) == 0x8 * 16); //Set version 0.5.1

    class OppDeviceCounters {
    public:
        int64_t summonCollarCounter = INT64_MIN;
        int64_t livingLatexCounter = INT64_MIN;
        int64_t dwarvenCuirassCounter = INT64_MIN;
        int64_t madnessPlugCounter = INT64_MIN;
        int64_t dummyDoNotUse02 = INT64_MIN;
        int64_t dummyDoNotUse03 = INT64_MIN;
        int64_t dummyDoNotUse04 = INT64_MIN;
        int64_t dummyDoNotUse05 = INT64_MIN;
        int64_t dummyDoNotUse06 = INT64_MIN;
        int64_t dummyDoNotUse07 = INT64_MIN;
        int64_t dummyDoNotUse08 = INT64_MIN;
        int64_t dummyDoNotUse09 = INT64_MIN;
    } oppdCounters;

    static_assert(sizeof(OppDeviceCounters) == 0x8 * 12); //Set version 0.5.1

    class RefLists {
    public:
        uint32_t eventList[REF_COUNT];
        size_t eventIndex = 0;
        uint32_t populatedList[REF_COUNT];
        size_t populatedIndex = 0;
        uint32_t pickpocketList[PICK_COUNT];
        size_t pickpocketIndex = 0;
        uint32_t consequenceList[CONS_COUNT];
        size_t consequenceIndex = 0;

        RefLists() {
            for (int i = 0; i < REF_COUNT; i++) { populatedList[i] = 0; }
            for (int i = 0; i < REF_COUNT; i++) { eventList[i] = 0; }
            for (int i = 0; i < PICK_COUNT; i++) { pickpocketList[i] = 0; }
            for (int i = 0; i < CONS_COUNT; i++) { consequenceList[i] = 0; }
        }
    } refLists;


    inline const auto RefListsRecord = _byteswap_ulong('REFL');
    inline const auto OppDeviceCounterRecord = _byteswap_ulong('ODCR');
    inline const auto ClocksRecord = _byteswap_ulong('CLKS');

    bool IsObjectRefKnown(uint32_t refId) {
        for (int i = 0; i < REF_COUNT; i++) {
            if (refLists.eventList[i] == refId) {
                return true;
            }
        }
        return false;
    }

    bool IsObjectPopulated(uint32_t refId) {
        for (int i = 0; i < REF_COUNT; i++) {
            if (refLists.populatedList[i] == refId) {
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
    void SetObjectPopulated(uint32_t refId) {
        refLists.populatedList[refLists.populatedIndex] = refId;
        //log::trace("assigning form {} to index {}", refId, knownRefsIndex);
        refLists.populatedIndex = (refLists.populatedIndex + 1) % REF_COUNT;
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

        if (!serde->OpenRecord(OppDeviceCounterRecord, 0)) {
            log::error("Unable to open record to write cosave data.");
            return;
        }
        serde->WriteRecordData(&oppdCounters, sizeof(OppDeviceCounters));
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
            if (type == OppDeviceCounterRecord) {
                if (sizeof(OppDeviceCounters) == size) {
                    serde->ReadRecordData(&oppdCounters, sizeof(OppDeviceCounters));
                }
                else {
                    log::warn("Error reading odevice info, all timers reset.");
                }
            }
        }
    }

    void OnRevert(SerializationInterface*) {
        refLists = RefLists();
        counters = Counters();
        oppdCounters = OppDeviceCounters();
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