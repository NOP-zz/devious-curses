#pragma once

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
        int64_t SinceLastSex = 0;
        int64_t dummyDoNotUse01 = 0;
        int64_t dummyDoNotUse02 = 0;
        int64_t dummyDoNotUse03 = 0;
        int64_t dummyDoNotUse04 = 0;
        int64_t dummyDoNotUse05 = 0;
        int64_t dummyDoNotUse06 = 0;
        int64_t dummyDoNotUse07 = 0;
        int64_t dummyDoNotUse08 = 0;
        int64_t dummyDoNotUse09 = 0;
        int64_t dummyDoNotUse10 = 0;

        void tick();

        void clear();
    };

    static_assert(sizeof(Counters) == 0x8 * 16); //Set version 0.5.1

    class OppDeviceCounters {
    public:
        int64_t summonCollarCounter = INT64_MIN;
        int64_t livingLatexCounter = INT64_MIN;
        int64_t dwarvenCuirassCounter = INT64_MIN;
        int64_t madnessPlugCounter = INT64_MIN;
        int64_t nocturnalPiercingCounter = INT64_MIN;
        uint32_t summonCollarTarget = 0;
        int32_t dummyDoNotUse03 = INT32_MIN;
        int64_t dummyDoNotUse04 = INT64_MIN;
        int64_t dummyDoNotUse05 = INT64_MIN;
        int64_t dummyDoNotUse06 = INT64_MIN;
        int64_t dummyDoNotUse07 = INT64_MIN;
        int64_t dummyDoNotUse08 = INT64_MIN;
        int64_t dummyDoNotUse09 = INT64_MIN;

        void clear();
    };

    static_assert(sizeof(OppDeviceCounters) == 0x8 * 12); //Set version 0.5.1

    class LewdMarkCounters {
    public:
        int32_t currentMark = 0;
        int32_t heatCounter = INT32_MIN;
        int32_t allureCounter = INT32_MIN;
        int32_t bondageCounter = INT32_MIN;
        int32_t healslutCounter = INT32_MIN;
        int32_t nudityCounter = INT32_MIN;
        int32_t painslutCounter = INT32_MIN;
        uint32_t painslutSexTarget = 0;
        int32_t dummyDoNotUse02 = INT32_MIN;
        int32_t dummyDoNotUse03 = INT32_MIN;
        int32_t dummyDoNotUse04 = INT32_MIN;
        int32_t dummyDoNotUse05 = INT32_MIN;
        int32_t dummyDoNotUse06 = INT32_MIN;
        int32_t dummyDoNotUse07 = INT32_MIN;
        int32_t dummyDoNotUse08 = INT32_MIN;
        int32_t dummyDoNotUse09 = INT32_MIN;

        void clear();
    };

    static_assert(sizeof(LewdMarkCounters) == 0x4 * 16); //Set version 0.8.3

    class RefLists {
    public:
        uint32_t eventList[REF_COUNT] = {};
        size_t eventIndex = 0;
        uint32_t populatedList[REF_COUNT] = {};
        size_t populatedIndex = 0;
        uint32_t pickpocketList[PICK_COUNT] = {};
        size_t pickpocketIndex = 0;
        uint32_t consequenceList[CONS_COUNT] = {};
        size_t consequenceIndex = 0;

        uint32_t lastActivatedObjectREFR = 0;

        void clear();
    };

    class Serialized {
    public:
        static Counters* GetCounters();

        static OppDeviceCounters* GetOppDeviceCounters();

        static LewdMarkCounters* GetLewdMarkCounters();

        static RefLists* GetRefLists();

        static void ClearAll();
    };


    inline const auto RefListsRecord = _byteswap_ulong('REFL');
    inline const auto OppDeviceCounterRecord = _byteswap_ulong('ODCR');
    inline const auto LewdMarkCounterRecord = _byteswap_ulong('LMCR');
    inline const auto ClocksRecord = _byteswap_ulong('CLKS');

    bool IsObjectRefKnown(uint32_t refId);

    bool IsObjectPopulated(uint32_t refId);

    bool IsPickpocketTargetKnown(uint32_t refId);

    bool IsConsequenceTargetKnown(uint32_t refId);

    void SetObjectRefKnown(uint32_t refId);
    void SetObjectPopulated(uint32_t refId);

    void SetPickpocketTargetKnown(uint32_t refId);

    void SetConsequenceTargetKnown(uint32_t refId);
    
    void OnGameSaved(SKSE::SerializationInterface* serde);

    void OnGameLoaded(SKSE::SerializationInterface* serde);

    void OnRevert(SKSE::SerializationInterface*);


    void InitializeSerialization();
}