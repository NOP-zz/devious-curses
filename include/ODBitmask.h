#pragma once

namespace DCURSES {
	class ODBitmask {
	private:
		uint32_t mask_internal;


	public:
		enum OppressiveDevice : uint32_t {
			SummonerCollar = 1 << 0,
			LivingLatex = 1 << 1,
			DwarvenCuirass = 1 << 2,
			MadnessPlug = 1 << 3,
			NocturnalPiercing = 1 << 4,
		};

		ODBitmask() {
			mask_internal = 0;
		}

		ODBitmask(uint32_t mask) {
			mask_internal = mask;
		}

		operator uint32_t() const {
			return this->mask_internal;
		}

		ODBitmask operator&(uint32_t other) {
			return ODBitmask(this->mask_internal & other);
		}

		ODBitmask operator&=(uint32_t other) {
			this->mask_internal &= other;
			return *this;
		}

		ODBitmask operator|(uint32_t other) {
			return ODBitmask(this->mask_internal | other);
		}

		ODBitmask operator|=(uint32_t other) {
			this->mask_internal |= other;
			return *this;
		}

		bool hasDevice(OppressiveDevice od) {
			return *this | od;
		}
	};
}