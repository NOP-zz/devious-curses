#pragma once

#include "../include/quicklootAPI.h"

namespace DCURSES {
	void QLIEAttemptInit() {
		if (GetModuleHandle(L"QuickLootIE") == nullptr) {
			return;
		}
		QuickLoot::QuickLootAPI::Init();
	}

	void QLIETakeItemCallback(QuickLoot::TakingItemEvent* e) {
		log::trace("QILE Trigger");
		CalculateEventChance(e->container);
	}

	void QLIEOpenContainerCallback(QuickLoot::OpeningLootMenuEvent* e) {
		log::trace("QILE Trigger");
		auto data = GetContainerData(e->container);
		PopulateContainer(e->container, data);
	}

	bool QLIEAttemptRegisterEvent() {
		if (GetModuleHandle(L"QuickLootIE") == nullptr) {
			return false;
		}
		if (!QuickLoot::QuickLootAPI::IsReady()) {
			return false;
		}

		//using TakingItemHandler = EventHandler<TakingItemEvent>;

		QuickLoot::QuickLootAPI::RegisterTakeItemHandler((QuickLoot::TakeItemHandler)QLIETakeItemCallback);
		QuickLoot::QuickLootAPI::RegisterOpeningLootMenuHandler((QuickLoot::OpeningLootMenuHandler)QLIEOpenContainerCallback);
		return true;
	}
}