#pragma once

#include "apis/quicklootAPI_4.h"
#include "apis/quicklootAPI_3.h"

#include "Settings.h"
#include "Events.h"

namespace DCURSES {
	void QLIEAttemptInit() {
		if (GetModuleHandle(L"QuickLootIE") == nullptr) {
			return;
		}


		if (!QuickLoot::API4::QuickLootAPI::Init("DeviousCurses")) {
			QuickLoot::API3::QuickLootAPI::Init();
		}
	}

	void QLIETakeItemCallback_3(QuickLoot::API3::TakingItemEvent* e) {
		if (e) {
			CalculateEventChance(e->container);
		}
	}
	void QLIETakeItemCallback_4(QuickLoot::API4::TakingItemEvent* e) {
		if (e) {
			CalculateEventChance(e->container.get().get());
		}
	}

	void QLIEOpenContainerCallback_3(QuickLoot::API3::OpeningLootMenuEvent* e) {
		if (e) {
			auto data = GetContainerData(e->container);
			PopulateContainer(e->container, data);
		}
	}
	void QLIEOpenContainerCallback_4(QuickLoot::API4::OpeningLootMenuEvent* e) {
		if (e) {
			auto container = e->container.get().get();
			auto data = GetContainerData(container);
			if (data.isDeadActor || data.isLeveled || data.isPickpocket) {
				PopulateContainer(container, data);
			}
		}
	}

	bool QLIEAttemptRegisterEvent() {
		if (GetModuleHandle(L"QuickLootIE") == nullptr) {
			return false;
		}
		if (QuickLoot::API4::QuickLootAPI::IsReady()) {
			QuickLoot::API4::QuickLootAPI::RegisterTakeItemHandler((QuickLoot::API4::TakeItemHandler)QLIETakeItemCallback_4);
			QuickLoot::API4::QuickLootAPI::RegisterOpeningLootMenuHandler((QuickLoot::API4::OpeningLootMenuHandler)QLIEOpenContainerCallback_4);
			log::info("Loaded Quick Loot API 4.0");
			return true;
		}
		else if (QuickLoot::API3::QuickLootAPI::IsReady()) {
			QuickLoot::API3::QuickLootAPI::RegisterTakeItemHandler((QuickLoot::API3::TakeItemHandler)QLIETakeItemCallback_3);
			QuickLoot::API3::QuickLootAPI::RegisterOpeningLootMenuHandler((QuickLoot::API3::OpeningLootMenuHandler)QLIEOpenContainerCallback_3);
			log::info("Loaded Quick Loot API 3.x");
			return true;
		}

		//using TakingItemHandler = EventHandler<TakingItemEvent>;

		return false;
	}
}