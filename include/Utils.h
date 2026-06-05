 #pragma once

#include <random>
#include <string>
#include <ranges>
#include <cctype>
#include <numeric>

using namespace SKSE;

namespace DCURSES::Util {
	template<class T>
	using uniform_distribution =
	typename std::conditional<
		std::is_floating_point<T>::value,
		std::uniform_real_distribution<T>,
		typename std::conditional<
			std::is_integral<T>::value,
			std::uniform_int_distribution<T>,
			void
		>::type
	>::type;

	template<class T>
	T random(T min, T max) {
		if (min >= max) {
			return min;
		}
		std::random_device rd;
		std::mt19937 e2(rd());

		uniform_distribution<T> dist(min, max);

		return dist(e2);
	}

	template<class T>
	T random(T max) {
		if constexpr (std::is_integral_v<T>) {
			return random<T>(0, max - 1);
		}
		else if constexpr (std::is_floating_point_v<T>) {
			return random<T>(0, max);
		}
	}

	template<class T>
	T random() {
		return random<T>(100);
	}

	double random();

	template<class T>
	bool vectorContains(std::vector<T> vec, T elem) {
		return std::find(vec.begin(), vec.end(), elem) != vec.end();
	}

	template<class T>
	void ShuffleVector(std::vector<T>& vector) {
		auto seed1 = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 e2(seed1);
		std::shuffle(vector.begin(), vector.end(), e2);
	}

	template<class T, class V>
	std::vector<T> VectorSortBySecond(std::vector<std::pair<T, V>> vector) {
		std::sort(vector.begin(), vector.end(), [](auto& left, auto& right) {
			return left.second < right.second;
		});

		std::vector<T> result;

		for (auto& [t, v] : vector) {
			result.push_back(t);
		}

		return result;
	}

	template<class T>
	double VectorGetWeightsSum(std::vector<std::pair<T, double>> vector) {
		return std::accumulate(vector.begin(), vector.end(), 0.0, [](double acc, std::pair<T, double> x) {return acc + x.second; });
	}

	template<class T>
	std::optional<std::pair<T, double>> VectorSelectWeighted(std::vector<std::pair<T, double>> vector) {
		if (VectorGetWeightsSum(vector) == 0) {
			return {};
		}
		std::vector<double> weights;
		weights.reserve(vector.size());

		for (auto [a, b] : vector) {
			if (b < 0) {
				log::error("Negative value in weighted vector, assigning 0");
				weights.push_back(0);
			}
			else {
				weights.push_back(b);
			}
		}

		std::random_device rd;
		std::mt19937 e2(rd());
		std::discrete_distribution<size_t> d(weights.begin(), weights.end());
		return vector[d(e2)];
	}

	int ColorScale(int color, double mult);

	inline std::string GetFormEditorId(const RE::TESForm* a_form);

	bool FormEditorIdContains(RE::TESForm* a_form, std::string substring);

	std::string tolower(std::string string);

	std::string toupper(std::string string);

	std::string trim(const std::string in);

	std::vector<std::string> split(const std::string& s, const std::string& delimiter);

	std::string join(std::vector<std::string> list, std::string token, std::string if_empty = "");

	size_t findMatchingParen(const std::string& str, size_t index);

	bool testFormComp(const std::string& theme, RE::TESForm* form, bool showTrace = false);

	RE::TESObjectREFR* GetClosestRefr(RE::Actor* actor);

	bool ActorIsCreature(RE::Actor* actor);

	template<class T>
	T* GetCrosshairRefAs() {
		auto pickData = RE::CrosshairPickData::GetSingleton();
		if (pickData) {
			for (int i = 0; i < 3; i++) {
				auto ref = pickData->target[i];
				if (ref && ref.get()) {
					T* result = ref.get()->As<T>();
					if (result) {
						return result;
					}
				}
			}
		}
		return nullptr;
	}


	// MUST NOT BORROW ANYTHING!
	void ExecuteWithDelay(std::chrono::milliseconds time, std::function<void()> func);

	std::vector<RE::Actor*> GetFollowers();

	std::vector<RE::Actor*> GetWatchingActors(RE::Actor* target, bool excludeFollowers = true, int radius = -1, bool allowCreatures = false);

	void StopPlayerCombat();

	void ProfileExecutionTime(std::string name, std::function<void()> func);
}