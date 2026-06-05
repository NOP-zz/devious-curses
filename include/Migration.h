#pragma once

namespace DCURSES {
	bool needsMigrationFor(const std::string& current, const std::string& target);

	void VersionMigrate();
}