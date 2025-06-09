#pragma once

#include "../include/quicklootAPI.h"
#include "../include/quicklootAPI_OLD.h"

namespace DCURSES {
	void QLIEAttemptInit() {
		if (GetModuleHandle(L"QuickLootIE") == nullptr) {
			return;
		}

		if (!QuickLoot::API::QuickLootAPI::Init("DeviousCurses")) {
			QuickLoot::QuickLootAPI::Init();
		}
	}

	void QLIETakeItemCallback(QuickLoot::API::TakingItemEvent* e) {
		Util::ProfileExecutionTime("Calculate Event Chance", [e] {
			CalculateEventChance(e->container);
		});
	}

	void QLIEOpenContainerCallback(QuickLoot::API::OpeningLootMenuEvent* e) {
		auto data = GetContainerData(e->container);
		PopulateContainer(e->container, data);
	}

	bool QLIEAttemptRegisterEvent() {
		if (GetModuleHandle(L"QuickLootIE") == nullptr) {
			return false;
		}
		if (QuickLoot::API::QuickLootAPI::IsReady()) {
			QuickLoot::API::QuickLootAPI::RegisterTakeItemHandler((QuickLoot::API::TakeItemHandler)QLIETakeItemCallback);
			QuickLoot::API::QuickLootAPI::RegisterOpeningLootMenuHandler((QuickLoot::API::OpeningLootMenuHandler)QLIEOpenContainerCallback);
			return true;
		}
		else if (QuickLoot::QuickLootAPI::IsReady()) {
			QuickLoot::QuickLootAPI::RegisterTakeItemHandler((QuickLoot::TakeItemHandler)QLIETakeItemCallback);
			QuickLoot::QuickLootAPI::RegisterOpeningLootMenuHandler((QuickLoot::OpeningLootMenuHandler)QLIEOpenContainerCallback);
			return true;
		}

		//using TakingItemHandler = EventHandler<TakingItemEvent>;

		return false;
	}
}