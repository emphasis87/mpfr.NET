#pragma once

#include "mpfr.h"

namespace System::ArbitraryPrecision {

	public enum class Rounding {
		ToNearestTiesToEven = (int)MPFR_RNDN,
		TowardsZero = (int)MPFR_RNDZ,
		TowardsPlusInfinity = (int)MPFR_RNDU,
		TowardsMinusInfinity = (int)MPFR_RNDD,
		AwayFromZero = (int)MPFR_RNDA,
		Faithful = (int)MPFR_RNDF,
		ToNearestTiesAwayFromZero = (int)MPFR_RNDNA,
	};
}