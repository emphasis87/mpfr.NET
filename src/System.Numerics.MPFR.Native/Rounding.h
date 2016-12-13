#pragma once

#include "mpfr.h"

namespace System::ArbitraryPrecision {

	public ref class Rounding {
	public:
		static property Rounding^ NearestTiesToEven { Rounding^ get() { return _nearestTiesToEven; }}
		static property Rounding^ TowardsZero { Rounding^ get() { return _towardsZero; }}
		static property Rounding^ TowardsPlusInfinity { Rounding^ get() { return _towardsPlusInfinity; }}
		static property Rounding^ TowardsMinusInfinity { Rounding^ get() { return _towardsMinusInfinity; }}
		static property Rounding^ AwayFromZero { Rounding^ get() { return _awayFromZero; }}
		static property Rounding^ Faithful { Rounding^ get() { return _faithful; }}
		static property Rounding^ NearestTiesAwayFromZero { Rounding^ get() { return _nearestTiesAwayFromZero; }}

		static operator mpfr_rnd_t(Rounding^ rounding) { return (mpfr_rnd_t)rounding->_value; }
	protected:
		Rounding(int value) { _value = value; }
	private:
		static initonly Rounding^ _nearestTiesToEven = gcnew Rounding(MPFR_RNDN);
		static initonly Rounding^ _towardsZero = gcnew Rounding(MPFR_RNDZ);
		static initonly Rounding^ _towardsPlusInfinity = gcnew Rounding(MPFR_RNDU);
		static initonly Rounding^ _towardsMinusInfinity = gcnew Rounding(MPFR_RNDN);
		static initonly Rounding^ _awayFromZero = gcnew Rounding(MPFR_RNDD);
		static initonly Rounding^ _faithful = gcnew Rounding(MPFR_RNDF);
		static initonly Rounding^ _nearestTiesAwayFromZero = gcnew Rounding(MPFR_RNDNA);

		int _value;
	};
}