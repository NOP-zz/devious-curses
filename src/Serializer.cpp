#include "Serializer.h"

#include "SKSE/Interfaces.h"

#include "Quest/Serialized.h"

using namespace SKSE;

namespace DCURSES {
    void Counters::tick() {
        clock_SexTimeout += 1;
        clock_lastSex += 1;
        clock_GlobalTicker += 1;
    }
    void Counters::clear() {
        clock_SexTimeout = 0;
        clock_lastSex = 0;
        clock_GlobalTicker = 0;
        SinceLastKey = 0;
        SinceLastEvent = 0;
        SinceLastSex = 0;
        dummyDoNotUse01 = 0;
        dummyDoNotUse02 = 0;
        dummyDoNotUse03 = 0;
        dummyDoNotUse04 = 0;
        dummyDoNotUse05 = 0;
        dummyDoNotUse06 = 0;
        dummyDoNotUse07 = 0;
        dummyDoNotUse08 = 0;
        dummyDoNotUse09 = 0;
        dummyDoNotUse10 = 0;
    }
    void OppDeviceCounters::clear() {
        summonCollarCounter = INT64_MIN;
        livingLatexCounter = INT64_MIN;
        dwarvenCuirassCounter = INT64_MIN;
        madnessPlugCounter = INT64_MIN;
        nocturnalPiercingCounter = INT64_MIN;
        summonCollarTarget = 0;
        dummyDoNotUse03 = INT32_MIN;
        dummyDoNotUse04 = INT64_MIN;
        dummyDoNotUse05 = INT64_MIN;
        dummyDoNotUse06 = INT64_MIN;
        dummyDoNotUse07 = INT64_MIN;
        dummyDoNotUse08 = INT64_MIN;
        dummyDoNotUse09 = INT64_MIN;
    }
    void LewdMarkCounters::clear() {
        currentMark = 0;
        heatCounter = INT32_MIN;
        allureCounter = INT32_MIN;
        bondageCounter = INT32_MIN;
        healslutCounter = INT32_MIN;
        nudityCounter = INT32_MIN;
        painslutCounter = INT32_MIN;
        painslutSexTarget = 0;
        dummyDoNotUse02 = INT32_MIN;
        dummyDoNotUse03 = INT32_MIN;
        dummyDoNotUse04 = INT32_MIN;
        dummyDoNotUse05 = INT32_MIN;
        dummyDoNotUse06 = INT32_MIN;
        dummyDoNotUse07 = INT32_MIN;
        dummyDoNotUse08 = INT32_MIN;
        dummyDoNotUse09 = INT32_MIN;
    }
    void RefLists::clear() {
        for (int i = 0; i < REF_COUNT; i++) { populatedList[i] = 0; }
        for (int i = 0; i < REF_COUNT; i++) { eventList[i] = 0; }
        for (int i = 0; i < PICK_COUNT; i++) { pickpocketList[i] = 0; }
        for (int i = 0; i < CONS_COUNT; i++) { consequenceList[i] = 0; }
        eventIndex = 0;
        populatedIndex = 0;
        pickpocketIndex = 0;
        consequenceIndex = 0;
        lastActivatedObjectREFR = 0;
    }
    Counters* Serialized::GetCounters() {
        static Counters instance;
        return &instance;
    }
    OppDeviceCounters* Serialized::GetOppDeviceCounters() {
        static OppDeviceCounters instance;
        return &instance;
    }
    LewdMarkCounters* Serialized::GetLewdMarkCounters() {
        static LewdMarkCounters instance;
        return &instance;
    }
    RefLists* Serialized::GetRefLists() {
        static RefLists instance;
        return &instance;
    }
    void Serialized::ClearAll() {
        GetCounters()->clear();
        GetOppDeviceCounters()->clear();
        GetLewdMarkCounters()->clear();
        GetRefLists()->clear();
    }
    bool IsObjectRefKnown(uint32_t refId) {
        for (int i = 0; i < REF_COUNT; i++) {
            if (Serialized::GetRefLists()->eventList[i] == refId) {
                return true;
            }
        }
        return false;
    }
    bool IsObjectPopulated(uint32_t refId) {
        for (int i = 0; i < REF_COUNT; i++) {
            if (Serialized::GetRefLists()->populatedList[i] == refId) {
                return true;
            }
        }
        return false;
    }
    bool IsPickpocketTargetKnown(uint32_t refId) {
        for (int i = 0; i < PICK_COUNT; i++) {
            if (Serialized::GetRefLists()->pickpocketList[i] == refId) {
                return true;
            }
        }
        return false;
    }
    bool IsConsequenceTargetKnown(uint32_t refId) {
        for (int i = 0; i < CONS_COUNT; i++) {
            if (Serialized::GetRefLists()->consequenceList[i] == refId) {
                return true;
            }
        }
        return false;
    }
    void SetObjectRefKnown(uint32_t refId) {
        auto refLists = Serialized::GetRefLists();
        refLists->eventList[refLists->eventIndex] = refId;
        //log::trace("assigning form {} to index {}", refId, knownRefsIndex);
        refLists->eventIndex = (refLists->eventIndex + 1) % REF_COUNT;
    }
    void SetObjectPopulated(uint32_t refId) {
        auto refLists = Serialized::GetRefLists();
        refLists->populatedList[refLists->populatedIndex] = refId;
        //log::trace("assigning form {} to index {}", refId, knownRefsIndex);
        refLists->populatedIndex = (refLists->populatedIndex + 1) % REF_COUNT;
    }
    void SetPickpocketTargetKnown(uint32_t refId) {
        auto refLists = Serialized::GetRefLists();
        refLists->pickpocketList[refLists->pickpocketIndex] = refId;
        //log::trace("assigning form {} to index {}", refId, knownRefsIndex);
        refLists->pickpocketIndex = (refLists->pickpocketIndex + 1) % PICK_COUNT;
    }
    void SetConsequenceTargetKnown(uint32_t refId) {
        auto refLists = Serialized::GetRefLists();
        refLists->consequenceList[refLists->consequenceIndex] = refId;
        //log::trace("assigning form {} to index {}", refId, knownRefsIndex);
        refLists->consequenceIndex = (refLists->consequenceIndex + 1) % CONS_COUNT;
    }

    void OnGameSaved(SKSE::SerializationInterface* serde) {
        if (!serde->OpenRecord(RefListsRecord, 0)) {
            log::error("Unable to open record to write cosave data.");
            return;
        }
        serde->WriteRecordData(Serialized::GetRefLists(), sizeof(RefLists));

        if (!serde->OpenRecord(ClocksRecord, 0)) {
            log::error("Unable to open record to write cosave data.");
            return;
        }
        serde->WriteRecordData(Serialized::GetCounters(), sizeof(Counters));

        if (!serde->OpenRecord(OppDeviceCounterRecord, 0)) {
            log::error("Unable to open record to write cosave data.");
            return;
        }
        serde->WriteRecordData(Serialized::GetOppDeviceCounters(), sizeof(OppDeviceCounters));

        if (!serde->OpenRecord(LewdMarkCounterRecord, 0)) {
            log::error("Unable to open record to write cosave data.");
            return;
        }
        serde->WriteRecordData(Serialized::GetLewdMarkCounters(), sizeof(LewdMarkCounters));

        Quest::SerdeOnGameSaved(serde);
    }

    void OnGameLoaded(SKSE::SerializationInterface* serde) {
        std::uint32_t type;
        std::uint32_t size;
        std::uint32_t version;

        while (serde->GetNextRecordInfo(type, version, size)) {
            if (type == RefListsRecord) {
                if (sizeof(RefLists) == size) {
                    serde->ReadRecordData(Serialized::GetRefLists(), sizeof(RefLists));
                }
                else {
                    log::warn("Error reading ref lists info.");
                }
            }
            if (type == ClocksRecord) {
                if (sizeof(Counters) == size) {
                    serde->ReadRecordData(Serialized::GetCounters(), sizeof(Counters));
                }
                else {
                    log::warn("Error reading clocks info, all timers reset.");
                }
            }
            if (type == OppDeviceCounterRecord) {
                if (sizeof(OppDeviceCounters) == size) {
                    serde->ReadRecordData(Serialized::GetOppDeviceCounters(), sizeof(OppDeviceCounters));
                }
                else {
                    log::warn("Error reading odevice info, all timers reset.");
                }
            }
            if (type == LewdMarkCounterRecord) {
                if (sizeof(LewdMarkCounters) == size) {
                    serde->ReadRecordData(Serialized::GetLewdMarkCounters(), sizeof(LewdMarkCounters));
                }
                else {
                    log::warn("Error reading lewd mark info, all timers reset.");
                }
            }

            Quest::SerdeOnRecordLoaded(serde, type, size, version);
        }
    }
    void OnRevert(SKSE::SerializationInterface* serde) {
        Serialized::ClearAll();

        Quest::SerdeOnRevert(serde);
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