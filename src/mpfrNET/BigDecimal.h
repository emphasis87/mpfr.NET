#pragma once

#include "mpfr.h"
#include "gmp.h"

using namespace System;

namespace System::ArbitraryPrecision
{
	public ref class BigDecimal : IFormattable
	{
	public:

#pragma region Constructors

		BigDecimal(SByte value, UInt64 precision) : BigDecimal((Int64)value, precision) {};
		BigDecimal(Int16 value, UInt64 precision) : BigDecimal((Int64)value, precision) {};
		BigDecimal(Int32 value, UInt64 precision) : BigDecimal((Int64)value, precision) {};
		BigDecimal(Int64 value, UInt64 precision);
		BigDecimal(Byte value, UInt64 precision) : BigDecimal((UInt64)value, precision) {};
		BigDecimal(UInt16 value, UInt64 precision) : BigDecimal((UInt64)value, precision) {};
		BigDecimal(UInt32 value, UInt64 precision) : BigDecimal((UInt64)value, precision) {};
		BigDecimal(UInt64 value, UInt64 precision);
		BigDecimal(Single value, UInt64 precision);
		BigDecimal(Double value, UInt64 precision);
		BigDecimal(Decimal value, UInt64 precision) : BigDecimal(value.ToString(), precision) {};
		BigDecimal(String^ value, UInt64 precision) : BigDecimal(value, 10, precision) {};
		BigDecimal(String^ value, int base, UInt64 precision);

		BigDecimal(SByte value) : BigDecimal((Int64)value, DefaultPrecision) {};
		BigDecimal(Int16 value) : BigDecimal((Int64)value, DefaultPrecision) {};
		BigDecimal(Int32 value) : BigDecimal((Int64)value, DefaultPrecision) {};
		BigDecimal(Int64 value) : BigDecimal(value, DefaultPrecision) {};
		BigDecimal(Byte value) : BigDecimal((UInt64)value, DefaultPrecision) {};
		BigDecimal(UInt16 value) : BigDecimal((UInt64)value, DefaultPrecision) {};
		BigDecimal(UInt32 value) : BigDecimal((UInt64)value, DefaultPrecision) {};
		BigDecimal(UInt64 value) : BigDecimal((UInt64)value, DefaultPrecision) {};
		BigDecimal(Single value) : BigDecimal(value, DefaultPrecision) {};
		BigDecimal(Double value) : BigDecimal(value, DefaultPrecision) {};
		BigDecimal(Decimal value) : BigDecimal(value, DefaultPrecision) {};
		BigDecimal(String^ value) : BigDecimal(value, DefaultPrecision) {};
		BigDecimal(String^ value, int base) : BigDecimal(value, base, DefaultPrecision) {};
#pragma endregion
#pragma region Implicit Cast Operators

		static operator BigDecimal ^ (Byte x) { return gcnew BigDecimal(x); }
		static operator BigDecimal ^ (SByte x) { return gcnew BigDecimal(x); }
		static operator BigDecimal ^ (Int16 x) { return gcnew BigDecimal(x); }
		static operator BigDecimal ^ (Int32 x) { return gcnew BigDecimal(x); }
		static operator BigDecimal ^ (Int64 x) { return gcnew BigDecimal(x); }
		static operator BigDecimal ^ (UInt16 x) { return gcnew BigDecimal(x); }
		static operator BigDecimal ^ (UInt32 x) { return gcnew BigDecimal(x); }
		static operator BigDecimal ^ (UInt64 x) { return gcnew BigDecimal(x); }
		static operator BigDecimal ^ (Single x) { return gcnew BigDecimal(x); }
		static operator BigDecimal ^ (Double x) { return gcnew BigDecimal(x); }
		static operator BigDecimal ^ (Decimal x) { return gcnew BigDecimal(x); }
#pragma endregion

		static property BigDecimal^ Instance { BigDecimal^ get() { return gcnew BigDecimal(); }}

		virtual ~BigDecimal();
		!BigDecimal();

#pragma region Static Instances

		static property BigDecimal^ NaN { BigDecimal^ get() { return Instance->SetNaN(); }}
		static property BigDecimal^ PositiveInfinity { BigDecimal^ get() { return Instance->SetNaN(); }}
		static property BigDecimal^ NegativeInfinity { BigDecimal^ get() { return Instance->SetNaN(); }}
		static property BigDecimal^ PositiveZero { BigDecimal^ get() { return Instance->SetNaN(); }}
		static property BigDecimal^ NegativeZero { BigDecimal^ get() { return Instance->SetZeroNegative(); }}

		static property BigDecimal^ LogOf2 { BigDecimal^ get() { return Instance->SetLogOf2(); }}
		static property BigDecimal^ Pi { BigDecimal^ get() { return Instance->SetPi(); }}
		static property BigDecimal^ Euler { BigDecimal^ get() { return Instance->SetEuler(); }}
		static property BigDecimal^ Catalan { BigDecimal^ get() { return Instance->SetCatalan(); }}
#pragma endregion

		static property UInt64 DefaultPrecision { UInt64 get(); void set(UInt64); }

		/// <summary>
		/// The precision of the underlying number in . 
		/// </summary>
		property UInt64 Precision { UInt64 get(); void set(UInt64); }

		static BigDecimal^ operator +(BigDecimal^ x, BigDecimal^ y);
		static BigDecimal^ operator -(BigDecimal^ x, BigDecimal^ y);
		static BigDecimal^ operator *(BigDecimal^ x, BigDecimal^ y);
		static BigDecimal^ operator /(BigDecimal^ x, BigDecimal^ y);
		static BigDecimal^ operator ++(BigDecimal^ x);
		static BigDecimal^ operator --(BigDecimal^ x);

#pragma region Set Constants

		BigDecimal^ SetNaN() { mpfr_set_nan(value); return this; }
		BigDecimal^ SetInf() { return SetInfPositive(); }
		BigDecimal^ SetInf(int sign) { mpfr_set_inf(value, sign); return this; }
		BigDecimal^ SetInfPositive() { return SetInf(+1); }
		BigDecimal^ SetInfNegative() { return SetInf(-1); }
		BigDecimal^ SetZero() { return SetZeroPositive(); }
		BigDecimal^ SetZero(int sign) { mpfr_set_zero(value, sign); return this; }
		BigDecimal^ SetZeroPositive() { return SetZero(+1); }
		BigDecimal^ SetZeroNegative() { return SetZero(-1); }

		BigDecimal^ SetLogOf2() { mpfr_const_log2(value, MPFR_RNDN); return this; }
		BigDecimal^ SetPi() { mpfr_const_pi(value, MPFR_RNDN); return this; }
		BigDecimal^ SetEuler() { mpfr_const_euler(value, MPFR_RNDN); return this; }
		BigDecimal^ SetCatalan() { mpfr_const_catalan(value, MPFR_RNDN); return this; }

#pragma endregion

		BigDecimal^ Add(BigDecimal^ y) { mpfr_add(value, value, y->value, MPFR_RNDN); return this; }
		BigDecimal^ Sub(BigDecimal^ y) { mpfr_sub(value, value, y->value, MPFR_RNDN); return this; }
		BigDecimal^ Mul(BigDecimal^ y) { mpfr_mul(value, value, y->value, MPFR_RNDN); return this; }
		BigDecimal^ Div(BigDecimal^ y) { mpfr_div(value, value, y->value, MPFR_RNDN); return this; }

#pragma region Special Functions

		BigDecimal^ Ln() { mpfr_log(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Log2() { mpfr_log2(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Log10() { mpfr_log10(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Exp() { mpfr_exp(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Exp2() { mpfr_exp2(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Exp10() { mpfr_exp10(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Sin() { mpfr_sin(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Cos() { mpfr_cos(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Tan() { mpfr_tan(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Sec() { mpfr_sec(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Csc() { mpfr_csc(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Cot() { mpfr_cot(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Acos() { mpfr_acos(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Asin() { mpfr_asin(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Atan() { mpfr_atan(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Atan2(BigDecimal^ y) { mpfr_atan2(value, value, y->value, MPFR_RNDN); return this; }
		BigDecimal^ Cosh() { mpfr_cosh(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Sinh() { mpfr_sinh(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Tanh() { mpfr_tanh(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Sech() { mpfr_sech(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Csch() { mpfr_csch(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Coth() { mpfr_coth(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Acosh() { mpfr_acosh(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Asinh() { mpfr_asinh(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Atanh() { mpfr_atanh(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Fact(UInt64 value) { mpfr_fac_ui(this->value, value, MPFR_RNDN); return this; }
		BigDecimal^ Log1p() { mpfr_log1p(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Expm1() { mpfr_expm1(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Eint() { mpfr_eint(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Li2() { mpfr_li2(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Gamma() { mpfr_gamma(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Lngamma() { mpfr_lngamma(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Digamma() { mpfr_digamma(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Zeta() { mpfr_zeta(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Zeta(UInt64 value) { mpfr_zeta_ui(this->value, value, MPFR_RNDN); return this; }
		BigDecimal^ Erf() { mpfr_erf(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Erfc() { mpfr_erfc(value, value, MPFR_RNDN); return this; }
		BigDecimal^ J0() { mpfr_j0(value, value, MPFR_RNDN); return this; }
		BigDecimal^ J1() { mpfr_j1(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Jn(long n) { mpfr_jn(value, n, value, MPFR_RNDN); return this; }
		BigDecimal^ Y0() { mpfr_y0(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Y1() { mpfr_y1(value, value, MPFR_RNDN); return this; }
		BigDecimal^ Yn(long n) { mpfr_yn(value, n, value, MPFR_RNDN); return this; }
		BigDecimal^ Agm(BigDecimal^ y) { mpfr_agm(value, value, y->value, MPFR_RNDN); return this; }
		BigDecimal^ Hypot(BigDecimal^ y) { mpfr_hypot(value, value, y->value, MPFR_RNDN); return this; }
		BigDecimal^ Ai() { mpfr_ai(value, value, MPFR_RNDN); return this; }
#pragma endregion

		static void ClearCache() { mpfr_free_cache(); }

#pragma region ToString

		virtual String^ ToString() override { return ToString(10, nullptr, nullptr); }
		virtual String^ ToString(String^ format) { return ToString(10, format, nullptr); }
		virtual String^ ToString(IFormatProvider^ provider) { return ToString(10, nullptr, provider); }
		virtual String^ ToString(String^ format, IFormatProvider^ provider) { return ToString(10, format, provider); }
		virtual String^ ToString(int base) { return ToString(base, nullptr, nullptr); }
		virtual String^ ToString(int base, String^ format) { return ToString(base, format, nullptr); }
		virtual String^ ToString(int base, IFormatProvider^ provider) { return ToString(base, nullptr, provider); }
		virtual String^ ToString(int base, String^ format, IFormatProvider^ provider);
#pragma endregion
	protected:
		BigDecimal() {};

		static BigDecimal^ Combine(BigDecimal^ x, BigDecimal^ y);

		bool isDisposed = false;
		property mpfr_ptr value { mpfr_ptr get(); }
	private:
		static int _defaultPrecision = 53;

		int _precision = DefaultPrecision;
		mpfr_ptr _value;
	};
}
