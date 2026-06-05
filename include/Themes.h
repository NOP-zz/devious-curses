#pragma once

namespace DCURSES {
	void CreateThemesFileIfNeeded();

	std::string GetRandomTheme();

	bool TestTheme(std::string theme, std::vector<std::string> skipKeywords = {});
}