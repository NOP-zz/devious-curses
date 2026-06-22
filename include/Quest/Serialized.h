#pragma once

namespace DCURSES::Quest {

	inline const auto QuestDataRecord = _byteswap_ulong('QDAT');
	class QuestData {
	private:
		QuestData() {}
	public:
		QuestData(QuestData const&) = delete;
		void operator=(QuestData const&) = delete;
		static QuestData* GetSingleton();
		void revert();

		uint32_t radLFTemplateFormInvRef = 0;
		int32_t dummyDoNotUsePad = 0;
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
		int64_t dummyDoNotUse11 = 0;
		int64_t dummyDoNotUse12 = 0;
		int64_t dummyDoNotUse13 = 0;
		int64_t dummyDoNotUse14 = 0;
		int64_t dummyDoNotUse15 = 0;
		int64_t dummyDoNotUse16 = 0;
		int64_t dummyDoNotUse17 = 0;
		int64_t dummyDoNotUse18 = 0;
		int64_t dummyDoNotUse19 = 0;
	};

	static_assert(sizeof(QuestData) == 0x8 * 20); //Set version 0.9.0

	void SerdeOnGameSaved(SKSE::SerializationInterface* serde);

	void SerdeOnRecordLoaded(SKSE::SerializationInterface* serde, std::uint32_t type, std::uint32_t size, std::uint32_t version);

	void SerdeOnRevert(SKSE::SerializationInterface* serde);
}