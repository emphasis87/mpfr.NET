#pragma once

#include "mpfr.h"
#include "gmp.h"

#include "Rounding.h"

using namespace System;
using namespace System::Globalization;
using namespace System::Runtime::InteropServices;

namespace System::ArbitraryPrecision
{
	public ref class BigDecimal : IFormattable
	{
	public:

#pragma region Constructors

		BigDecimal(SByte value, UInt64 precision) : BigDecimal((Int64)value, precision) {};
		BigDecimal(Int16 value, UInt64 precision) : BigDecimal((Int64)value, precision) {};
		BigDecimal(Int32 value, UInt64 precision) : BigDecimal((Int64)value, precision) {};
		BigDecimal(Int64 value, UInt64 precision) { SetPrecision(precision); Set(value); }
		BigDecimal(Byte value, UInt64 precision) : BigDecimal((UInt64)value, precision) {};
		BigDecimal(UInt16 value, UInt64 precision) : BigDecimal((UInt64)value, precision) {};
		BigDecimal(UInt32 value, UInt64 precision) : BigDecimal((UInt64)value, precision) {};
		BigDecimal(UInt64 value, UInt64 precision) { SetPrecision(precision); Set(value); }
		BigDecimal(Single value, UInt64 precision) { SetPrecision(precision); Set(value); }
		BigDecimal(Double value, UInt64 precision) { SetPrecision(precision); Set(value); }
		BigDecimal(Decimal value, UInt64 precision) { SetPrecision(precision); Set(value); }
		BigDecimal(String^ value, UInt64 precision) : BigDecimal(value, 10, precision) {};
		BigDecimal(String^ value, int base, UInt64 precision) { SetPrecision(precision); Set(value); }

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

		static BigDecimal^ Create() { return gcnew BigDecimal(); }
		static BigDecimal^ Create(UInt64 precision) { return Create()->SetPrecision(precision); }

		virtual ~BigDecimal();
		!BigDecimal();

#pragma region Static Instances
		static property BigDecimal^ NaN { BigDecimal^ get() { return Create()->SetNaN(); }}
		static property BigDecimal^ PositiveInfinity { BigDecimal^ get() { return Create()->SetNaN(); }}
		static property BigDecimal^ NegativeInfinity { BigDecimal^ get() { return Create()->SetNaN(); }}
		static property BigDecimal^ PositiveZero { BigDecimal^ get() { return Create()->SetNaN(); }}
		static property BigDecimal^ NegativeZero { BigDecimal^ get() { return Create()->SetZeroNegative(); }}

		static property BigDecimal^ LnOf2 { BigDecimal^ get() { return Create()->SetLn2(); }}
		static property BigDecimal^ Pi { BigDecimal^ get() { return Create()->SetPi(); }}
		static property BigDecimal^ Euler { BigDecimal^ get() { return Create()->SetEuler(); }}
		static property BigDecimal^ Catalan { BigDecimal^ get() { return Create()->SetCatalan(); }}
#pragma endregion

		static property UInt64 DefaultPrecision { UInt64 get(); void set(UInt64); }
		static property Rounding DefaultRounding { Rounding get(); void set(Rounding);}

		/// <summary>
		/// The precision of the underlying number in bits. 
		/// </summary>
		property UInt64 Precision { UInt64 get(); void set(UInt64); }
		BigDecimal^ SetPrecision(UInt64 precision) { Precision = precision; return this; }
		BigDecimal^ SetPrecision(BigDecimal^ y) { Precision = y->Precision; return this; }

		static BigDecimal^ operator +(BigDecimal^ x, BigDecimal^ y) { return LValue(x, y)->Add(y); }
		static BigDecimal^ operator -(BigDecimal^ x, BigDecimal^ y) { return LValue(x, y)->Sub(y); }
		static BigDecimal^ operator *(BigDecimal^ x, BigDecimal^ y) { return LValue(x, y)->Mul(y); }
		static BigDecimal^ operator /(BigDecimal^ x, BigDecimal^ y) { return LValue(x, y)->Div(y); }
		static BigDecimal^ operator ++(BigDecimal^ x) { return LValue(x)->Add(1); }
		static BigDecimal^ operator --(BigDecimal^ x) { return LValue(x)->Sub(1); }

#pragma region Value Setters
#pragma region Value Setters from Value Types
		BigDecimal^ Set(SByte value) { return Set((Int64)value); }
		BigDecimal^ Set(Int16 value) { return Set((Int64)value); }
		BigDecimal^ Set(Int32 value) { return Set((Int64)value); }
		BigDecimal^ Set(Int64 value) { mpfr_set_si(this->value, value, MPFR_RNDN); return this; }
		BigDecimal^ Set(Byte value) { return Set((UInt64)value); }
		BigDecimal^ Set(UInt16 value) { return Set((UInt64)value); }
		BigDecimal^ Set(UInt32 value) { return Set((UInt64)value); }
		BigDecimal^ Set(UInt64 value) { mpfr_set_ui(this->value, value, MPFR_RNDN); return this; }
		BigDecimal^ Set(Single value) { mpfr_set_flt(this->value, value, MPFR_RNDN); return this; }
		BigDecimal^ Set(Double value) { mpfr_set_d(this->value, value, MPFR_RNDN);return this; }
		BigDecimal^ Set(Decimal value) { return Set(value.ToString()); }
		BigDecimal^ Set(String^ value) { return Set(value, 10); }
		BigDecimal^ Set(String^ value, int base) {
			char* cstr = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(value).ToPointer();
			mpfr_set_str(this->value, cstr, base, MPFR_RNDN);
			Marshal::FreeHGlobal((IntPtr)cstr);
			return this;
		}
#pragma endregion
#pragma region Value Setters of Constants

		/// <summary>
		/// Set the value to the not a number constant.
		/// </summary>
		BigDecimal^ SetNaN() { mpfr_set_nan(value); return this; }

		/// <summary>
		/// Set the value to the positive infinity constant.
		/// </summary>
		BigDecimal^ SetInf() { return SetInfPositive(); }

		/// <summary>
		/// Set the value to the positive or negative infinity constant based on the sign of <paramref name="sign"/>.
		/// </summary>
		/// <param name="sign">The value to determine the sign of the resulting infinity constant. Zero counts towards plus values.</param>
		BigDecimal^ SetInf(int sign) { mpfr_set_inf(value, sign); return this; }
		
		/// <summary>
		/// Set the value to the positive infinity constant.
		/// </summary>
		BigDecimal^ SetInfPositive() { return SetInf(+1); }

		/// <summary>
		/// Set the value to the negative infinity constant.
		/// </summary>
		BigDecimal^ SetInfNegative() { return SetInf(-1); }

		/// <summary>
		/// Set the value to the positive zero constant.
		/// </summary>
		BigDecimal^ SetZero() { return SetZeroPositive(); }

		/// <summary>
		/// Set the value to the positive or negative zero constant based on the sign of <paramref name="sign"/>.
		/// </summary>
		/// <param name="sign>The value to determine the sign of the resulting zero constant. Zero counts towards plus values.</param>
		BigDecimal^ SetZero(int sign) { mpfr_set_zero(value, sign); return this; }
		
		/// <summary>
		/// Set the value to the positive zero constant.
		/// </summary>
		BigDecimal^ SetZeroPositive() { return SetZero(+1); }

		/// <summary>
		/// Set the value to the negative zero constant.
		/// </summary>
		BigDecimal^ SetZeroNegative() { return SetZero(-1); }

		/// <summary>
		/// Set the value to the natural logarithm of 2 constant.
		/// </summary>
		BigDecimal^ SetLn2() { return SetLn2(DefaultRounding); }

		/// <summary>
		/// Set the value to the natural logarithm of 2 constant.
		/// </summary>
		BigDecimal^ SetLn2(Rounding rounding) { mpfr_const_log2(value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the Pi constant.
		/// </summary>
		BigDecimal^ SetPi() { return SetPi(DefaultRounding); }

		/// <summary>
		/// Set the value to the Pi constant.
		/// </summary>
		BigDecimal^ SetPi(Rounding rounding) { mpfr_const_pi(value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the Euler's constant.
		/// </summary>
		BigDecimal^ SetEuler() { return SetEuler(DefaultRounding); }

		/// <summary>
		/// Set the value to the Euler's constant.
		/// </summary>
		BigDecimal^ SetEuler(Rounding rounding) { mpfr_const_euler(value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the Catalan's constant.
		/// </summary>
		BigDecimal^ SetCatalan() { return SetCatalan(DefaultRounding); }

		/// <summary>
		/// Set the value to the Catalan's constant.
		/// </summary>
		BigDecimal^ SetCatalan(Rounding rounding) { mpfr_const_catalan(value, (mpfr_rnd_t)rounding); return this; }
#pragma endregion

		/// <summary>
		/// Set the value to that of <paramref name="y"/>.
		/// </summary>
		/// <param name="y">The value to set</param>
		BigDecimal^ Set(BigDecimal^ y) { return Set(y, DefaultRounding); }

		/// <summary>
		/// Set the value to that of <paramref name="y"/>.
		/// </summary>
		/// <param name="y">The value to set</param>
		BigDecimal^ Set(BigDecimal^ y, Rounding rounding) { mpfr_set(value, y->value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Swap the current instance and <paramref name="y"/> inplace.
		/// </summary>
		/// <param name="y">The value to swap with</param>
		BigDecimal^ Swap(BigDecimal^ y)
		{
			mpfr_swap(value, y->value);
			UInt64 precision = Precision;
			SetPrecision(y);
			y->SetPrecision(precision);
			return this;
		}
#pragma endregion
#pragma region Arithmetic Functions

		/// <summary>
		/// Set the value to the current value added by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to add</param>
		BigDecimal^ Add(BigDecimal^ y) { return Add(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value added by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to add</param>
		BigDecimal^ Add(BigDecimal^ y, Rounding rounding) { mpfr_add(value, value, y->value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the current value subtracted by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to subtract</param>
		BigDecimal^ Sub(BigDecimal^ y) { return Sub(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value subtracted by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to subtract</param>
		BigDecimal^ Sub(BigDecimal^ y, Rounding rounding) { mpfr_sub(value, value, y->value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the current value multiplied by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to multiply by</param>
		BigDecimal^ Mul(BigDecimal^ y) { return Mul(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value multiplied by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to multiply by</param>
		BigDecimal^ Mul(BigDecimal^ y, Rounding rounding) { mpfr_mul(value, value, y->value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the current value divided by <paramref name="y"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		BigDecimal^ Div(BigDecimal^ y) { return Div(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value divided by <paramref name="y"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		BigDecimal^ Div(BigDecimal^ y, Rounding rounding) { mpfr_div(value, value, y->value, (mpfr_rnd_t)rounding); return this; }
#pragma endregion
#pragma region Comparison Functions
		/// <summary>
		/// Compare this instance to <paramref name="y"/>.
		/// </summary>
		/// <param name="y">The value to campare to</param>
		/// <returns>A positive value if <paramref name="y"/> is lesser and so on. If either number is NaN returns 0.</returns>
		int Compare(BigDecimal^ y) { return mpfr_cmp(value, y->value); }

		/// <summary>
		/// Compare this instance to <paramref name="y"/> in absolute values.
		/// </summary>
		/// <param name="y">The value to campare with</param>
		/// <returns>A positive value if <paramref name="y"/> is lesser and so on. If either number is NaN returns 0.</returns>
		int CompareAbs(BigDecimal^ y) { return mpfr_cmpabs(value, y->value); }

		/// <summary>
		/// Get the value representing the sign of the current value.
		/// </summary>
		/// <returns>A negative value if the current value is negative and so on. Returns 0 for zero or NaN.</returns>
		int Sign() { return mpfr_sgn(value); }

		/// <summary>
		/// Check whether the current value is positive.
		/// </summary>
		/// <returns>True if the current value is positive</returns>
		bool IsPositive() { return Sign() > 0; }

		/// <summary>
		/// Check whether the current value is negative.
		/// </summary>
		/// <returns>True if the current value is negative</returns>
		bool IsNegative() { return Sign() < 0; }

		/// <summary>
		/// Check whether the current value is greater than <paramref name="y"/>.
		/// </summary>
		/// <param name="y">The value to compare to</param>
		/// <returns>True if the current value is greater than <paramref name="y"/></returns>
		bool IsGreater(BigDecimal^ y) { return mpfr_greater_p(value, y->value) != 0; }

		/// <summary>
		/// Check whether the current value is greater than <paramref name="y"/> or equal.
		/// </summary>
		/// <param name="y">The value to compare to</param>
		/// <returns>True if the current value is greater than <paramref name="y"/> or equal</returns>
		bool IsGreaterOrEqual(BigDecimal^ y) { return mpfr_greaterequal_p(value, y->value) != 0; }

		/// <summary>
		/// Check whether the current value is less than <paramref name="y"/>.
		/// </summary>
		/// <param name="y">The value to compare to</param>
		/// <returns>True if the current value is less than <paramref name="y"/></returns>
		bool IsLess(BigDecimal^ y) { return mpfr_less_p(value, y->value) != 0; }

		/// <summary>
		/// Check whether the current value is less than <paramref name="y"/> or equal.
		/// </summary>
		/// <param name="y">The value to compare to</param>
		/// <returns>True if the current value is less than <paramref name="y"/> or equal</returns>
		bool IsLessOrEqual(BigDecimal^ y) { return mpfr_lessequal_p(value, y->value) != 0; }

		/// <summary>
		/// Check whether the current value is equal to <paramref name="y"/>.
		/// </summary>
		/// <param name="y">The value to compare to</param>
		/// <returns>True if the current value is equal to <paramref name="y"/></returns>
		bool IsEqual(BigDecimal^ y) { return mpfr_equal_p(value, y->value) != 0; }

		/// <summary>
		/// Check whether the current value is not equal to <paramref name="y"/>.
		/// </summary>
		/// <param name="y">The value to compare to</param>
		/// <returns>True if the current value is not equal to <paramref name="y"/></returns>
		bool IsNotEqual(BigDecimal^ y) { return mpfr_lessgreater_p(value, y->value) != 0; }

		/// <summary>
		/// Check whether either the current value or <paramref name="y"/> is not a number.
		/// </summary>
		/// <param name="y">The value to compare to</param>
		/// <returns>True if the current value is not equal to <paramref name="y"/></returns>
		bool IsNotComparable(BigDecimal^ y) { return mpfr_unordered_p(value, y->value) != 0; }

		/// <summary>
		/// Check whether the current value is not a number.
		/// </summary>
		/// <returns>True if the current value is NaN</returns>
		bool IsNaN() { return mpfr_nan_p(value) != 0; }

		/// <summary>
		/// Check whether the current value is an infinity.
		/// </summary>
		/// <returns>True if the current value is an infinity</returns>
		bool IsInfinity() { return mpfr_inf_p(value) != 0; }

		/// <summary>
		/// Check whether the current value is an ordinary number.
		/// </summary>
		/// <returns>True if the current value is an ordinary number</returns>
		bool IsNumber() { return mpfr_number_p(value) != 0; }

		/// <summary>
		/// Check whether the current value is zero.
		/// </summary>
		/// <returns>True if the current value is zero</returns>
		bool IsZero() { return mpfr_zero_p(value) != 0; }

		/// <summary>
		/// Check whether the current value is a regular number (an ordinary number except zero).
		/// </summary>
		/// <returns>True if the current value is a regular number</returns>
		bool IsRegular() { return mpfr_regular_p(value) != 0; }

		/// <summary>
		/// Check whether the current value is an integer.
		/// </summary>
		/// <returns>True if the current value is an integer</returns>
		bool IsInteger() { return mpfr_integer_p(value) != 0; }
#pragma endregion
#pragma region Special Functions

		/// <summary>
		/// Set the value to the natural logarithm of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Natural_logarithm">Natural_logarithm</a> on wiki.
		/// </summary>
		BigDecimal^ Ln() { return Ln(DefaultRounding); }

		/// <summary>
		/// Set the value to the natural logarithm of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Natural_logarithm">Natural_logarithm</a> on wiki.
		/// </summary>
		BigDecimal^ Ln(Rounding rounding) { mpfr_log(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the binary logarithm of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Binary_logarithm">Binary_logarithm</a> on wiki.
		/// </summary>
		BigDecimal^ Log2() { return Log2(DefaultRounding); }

		/// <summary>
		/// Set the value to the binary logarithm of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Binary_logarithm">Binary_logarithm</a> on wiki.
		/// </summary>
		BigDecimal^ Log2(Rounding rounding) { mpfr_log2(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the decadic logarithm of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Common_logarithm">Common_logarithm</a> on wiki.
		/// </summary>
		BigDecimal^ Log10() { return Log10(DefaultRounding); }

		/// <summary>
		/// Set the value to the decadic logarithm of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Common_logarithm">Common_logarithm</a> on wiki.
		/// </summary>
		BigDecimal^ Log10(Rounding rounding) { mpfr_log10(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to exponential of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Exponential_function">Exponential_function</a> on wiki.
		/// </summary>
		BigDecimal^ Exp() { return Exp(DefaultRounding); }

		/// <summary>
		/// Set the value to exponential of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Exponential_function">Exponential_function</a> on wiki.
		/// </summary>
		BigDecimal^ Exp(Rounding rounding) { mpfr_exp(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the 2 power of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Power_function">Power_function</a> on wiki.
		/// </summary>
		BigDecimal^ Exp2() { return Exp2(DefaultRounding); }
		
		/// <summary>
		/// Set the value to the 2 power of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Power_function">Power_function</a> on wiki.
		/// </summary>
		BigDecimal^ Exp2(Rounding rounding) { mpfr_exp2(value, value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the 10 power of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Power_function">Power_function</a> on wiki.
		/// </summary>
		BigDecimal^ Exp10() { return Exp10(DefaultRounding); }

		/// <summary>
		/// Set the value to the 10 power of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Power_function">Power_function</a> on wiki.
		/// </summary>
		BigDecimal^ Exp10(Rounding rounding) { mpfr_exp10(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the sine of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Sine">Sine</a> on wiki.
		/// </summary>
		BigDecimal^ Sin() { return Sin(DefaultRounding); }

		/// <summary>
		/// Set the value to the sine of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Sine">Sine</a> on wiki.
		/// </summary>
		BigDecimal^ Sin(Rounding rounding) { mpfr_sin(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the cosine of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Cosine">Cosine</a> on wiki.
		/// </summary>
		BigDecimal^ Cos() { return Cos(DefaultRounding); }

		/// <summary>
		/// Set the value to the cosine of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Cosine">Cosine</a> on wiki.
		/// </summary>
		BigDecimal^ Cos(Rounding rounding) { mpfr_cos(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the tangent of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Tangent_function">Tangent_function</a> on wiki.
		/// </summary>
		BigDecimal^ Tan() { return Tan(DefaultRounding); }

		/// <summary>
		/// Set the value to the tangent of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Tangent_function">Tangent_function</a> on wiki.
		/// </summary>
		BigDecimal^ Tan(Rounding rounding) { mpfr_tan(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the secant of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Secant_function">Secant_function</a> on wiki.
		/// </summary>
		BigDecimal^ Sec() { return Sec(DefaultRounding); }

		/// <summary>
		/// Set the value to the secant of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Secant_function">Secant_function</a> on wiki.
		/// </summary>
		BigDecimal^ Sec(Rounding rounding) { mpfr_sec(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the cosecant of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Cosecant">Cosecant</a> on wiki.
		/// </summary>
		BigDecimal^ Csc() { return Csc(DefaultRounding); }

		/// <summary>
		/// Set the value to the cosecant of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Cosecant">Cosecant</a> on wiki.
		/// </summary>
		BigDecimal^ Csc(Rounding rounding) { mpfr_csc(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the cotangent of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Ctg">Ctg</a> on wiki.
		/// </summary>
		BigDecimal^ Cot() { return Cot(DefaultRounding); }

		/// <summary>
		/// Set the value to the cotangent of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Ctg">Ctg</a> on wiki.
		/// </summary>
		BigDecimal^ Cot(Rounding rounding) { mpfr_cot(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the arc-cosine of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Arccosine">Arccosine</a> on wiki.
		/// </summary>
		BigDecimal^ Acos() { return Acos(DefaultRounding); }

		/// <summary>
		/// Set the value to the arc-cosine of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Arccosine">Arccosine</a> on wiki.
		/// </summary>
		BigDecimal^ Acos(Rounding rounding) { mpfr_acos(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the arc-sine of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Arcsine">Arcsine</a> on wiki.
		/// </summary>
		BigDecimal^ Asin() { return Asin(DefaultRounding); }

		/// <summary>
		/// Set the value to the arc-sine of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Arcsine">Arcsine</a> on wiki.
		/// </summary>
		BigDecimal^ Asin(Rounding rounding) { mpfr_asin(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the arc-tangent of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Arctangent">Arctangent</a> on wiki.
		/// </summary>
		BigDecimal^ Atan() { return Atan(DefaultRounding); }

		/// <summary>
		/// Set the value to the arc-tangent of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Arctangent">Arctangent</a> on wiki.
		/// </summary>
		BigDecimal^ Atan(Rounding rounding) { mpfr_atan(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the arc-tangent2 of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Atan2">Atan2</a> on wiki.
		/// </summary>
		BigDecimal^ Atan2(BigDecimal^ y) { return Atan2(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the arc-tangent2 of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Atan2">Atan2</a> on wiki.
		/// </summary>
		BigDecimal^ Atan2(BigDecimal^ y, Rounding rounding) { mpfr_atan2(value, value, y->value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the hyperbolic cosine of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Hyperbolic_function#Cosh">Hyperbolic_function#Cosh</a> on wiki.
		/// </summary>
		BigDecimal^ Cosh() { return Cosh(DefaultRounding); }

		/// <summary>
		/// Set the value to the hyperbolic cosine of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Hyperbolic_function#Cosh">Hyperbolic_function#Cosh</a> on wiki.
		/// </summary>
		BigDecimal^ Cosh(Rounding rounding) { mpfr_cosh(value, value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the hyperbolic sine of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Sinh">Sinh</a> on wiki.
		/// </summary>
		BigDecimal^ Sinh() { return Sinh(DefaultRounding); }

		/// <summary>
		/// Set the value to the hyperbolic sine of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Sinh">Sinh</a> on wiki.
		/// </summary>
		BigDecimal^ Sinh(Rounding rounding) { mpfr_sinh(value, value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the hyperbolic tangent of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Tanh">Tanh</a> on wiki.
		/// </summary>
		BigDecimal^ Tanh() { return Tanh(DefaultRounding); }

		/// <summary>
		/// Set the value to the hyperbolic tangent of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Tanh">Tanh</a> on wiki.
		/// </summary>
		BigDecimal^ Tanh(Rounding rounding) { mpfr_tanh(value, value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the hyperbolic secant of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Sech">Sech</a> on wiki.
		/// </summary>
		BigDecimal^ Sech() { return Sech(DefaultRounding); }

		/// <summary>
		/// Set the value to the hyperbolic secant of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Sech">Sech</a> on wiki.
		/// </summary>
		BigDecimal^ Sech(Rounding rounding) { mpfr_sech(value, value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the hyperbolic cosecant of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Csch">Csch</a> on wiki.
		/// </summary>
		BigDecimal^ Csch() { return Csch(DefaultRounding); }

		/// <summary>
		/// Set the value to the hyperbolic cosecant of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Csch">Csch</a> on wiki.
		/// </summary>
		BigDecimal^ Csch(Rounding rounding) { mpfr_csch(value, value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the hyperbolic cotangent of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Coth">Coth</a> on wiki.
		/// </summary>
		BigDecimal^ Coth() { return Coth(DefaultRounding); }

		/// <summary>
		/// Set the value to the hyperbolic cotangent of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Coth">Coth</a> on wiki.
		/// </summary>
		BigDecimal^ Coth(Rounding rounding) { mpfr_coth(value, value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the inverse hyperbolic cosine of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Acosh">Acosh</a> on wiki.
		/// </summary>
		BigDecimal^ Acosh() { return Acosh(DefaultRounding); }

		/// <summary>
		/// Set the value to the inverse hyperbolic cosine of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Acosh">Acosh</a> on wiki.
		/// </summary>
		BigDecimal^ Acosh(Rounding rounding) { mpfr_acosh(value, value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the inverse hyperbolic sine of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Asinh">Asinh</a> on wiki.
		/// </summary>
		BigDecimal^ Asinh() { return Asinh(DefaultRounding); }

		/// <summary>
		/// Set the value to the inverse hyperbolic sine of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Asinh">Asinh</a> on wiki.
		/// </summary>
		BigDecimal^ Asinh(Rounding rounding) { mpfr_asinh(value, value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the inverse hyperbolic tangent of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Atanh">Atanh</a> on wiki.
		/// </summary>
		BigDecimal^ Atanh() { return Atanh(DefaultRounding); }

		/// <summary>
		/// Set the value to the inverse hyperbolic tangent of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Atanh">Atanh</a> on wiki.
		/// </summary>
		BigDecimal^ Atanh(Rounding rounding) { mpfr_atanh(value, value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the factorial of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Factorial">Factorial</a> on wiki.
		/// </summary>
		/// <param name="value">The input argument to the factorial function.</param>
		BigDecimal^ Fact(UInt64 value) { return Fact(value, DefaultRounding); }

		/// <summary>
		/// Set the value to the factorial of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Factorial">Factorial</a> on wiki.
		/// </summary>
		/// <param name="value">The input argument to the factorial function.</param>
		BigDecimal^ Fact(UInt64 value, Rounding rounding) { mpfr_fac_ui(this->value, value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Set the value to the logarithm of one plus the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Log1p">Log1p</a> on wiki.
		/// </summary>
		BigDecimal^ Log1p() { return Log1p(DefaultRounding); }

		/// <summary>
		/// Set the value to the logarithm of one plus the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Log1p">Log1p</a> on wiki.
		/// </summary>
		BigDecimal^ Log1p(Rounding rounding) { mpfr_log1p(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the exponential of the current value followed by a subtraction by one using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Expm1">Expm1</a> on wiki.
		/// </summary>
		BigDecimal^ Expm1() { return Expm1(DefaultRounding); }

		/// <summary>
		/// Set the value to the exponential of the current value followed by a subtraction by one using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Expm1">Expm1</a> on wiki.
		/// </summary>
		BigDecimal^ Expm1(Rounding rounding) { mpfr_expm1(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the exponential integral of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Exponential_integral">Exponential_integral</a> on wiki.
		/// </summary>
		BigDecimal^ Eint() { return Eint(DefaultRounding); }

		/// <summary>
		/// Set the value to the exponential integral of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Exponential_integral">Exponential_integral</a> on wiki.
		/// </summary>
		BigDecimal^ Eint(Rounding rounding) { mpfr_eint(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the real part of the dilogarithm of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Li2">Li2</a> on wiki.
		/// </summary>
		BigDecimal^ Li2() { return Li2(DefaultRounding); }

		/// <summary>
		/// Set the value to the real part of the dilogarithm of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Li2">Li2</a> on wiki.
		/// </summary>
		BigDecimal^ Li2(Rounding rounding) { mpfr_li2(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the value of the Gamma function on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Gamma_function">Gamma_function</a> on wiki.
		/// </summary>
		BigDecimal^ Gamma() { return Gamma(DefaultRounding); }

		/// <summary>
		/// Set the value to the value of the Gamma function on the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Gamma_function">Gamma_function</a> on wiki.
		/// </summary>
		BigDecimal^ Gamma(Rounding rounding) { mpfr_gamma(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the value of the logarithm of the Gamma function on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Gamma_function">Power_function</a> on wiki.
		/// </summary>
		BigDecimal^ LnGamma() { return LnGamma(DefaultRounding); }

		/// <summary>
		/// Set the value to the value of the logarithm of the Gamma function on the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Gamma_function">Power_function</a> on wiki.
		/// </summary>
		BigDecimal^ LnGamma(Rounding rounding) { mpfr_lngamma(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the value of the logarithm of the absolute value of the Gamma function on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Gamma_function">Gamma_function</a> on wiki.
		/// </summary>
		/// <param name="sign">The sign of a value of the Gamma function on the current value</param> 
		BigDecimal^ LGamma([Out] int% sign) { return LGamma(sign, DefaultRounding); }

		/// <summary>
		/// Set the value to the value of the logarithm of the absolute value of the Gamma function on the current value  using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Gamma_function">Gamma_function</a> on wiki.
		/// </summary>
		/// <param name="sign">The sign of a value of the Gamma function on the current value</param> 
		BigDecimal^ LGamma([Out] int% sign, Rounding rounding) {
			int sgn = 0;
			mpfr_lgamma(value, &sgn, value, (mpfr_rnd_t)rounding); 
			sign = sgn;
			return this; 
		}

		/// <summary>
		/// Set the value to the value of the Digamma function on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Digamma_function">Digamma_function</a> on wiki.
		/// </summary>
		BigDecimal^ Digamma() { return Digamma(DefaultRounding); }

		/// <summary>
		/// Set the value to the value of the Digamma function on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Digamma_function">Digamma_function</a> on wiki.
		/// </summary>
		BigDecimal^ Digamma(Rounding rounding) { mpfr_digamma(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the value of Riemann Zeta function on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Riemann_zeta_function">Riemann_zeta_function</a> on wiki.
		/// </summary>
		BigDecimal^ Zeta() { return Zeta(DefaultRounding); }

		/// <summary>
		/// Set the value to the value of Riemann Zeta function on the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Riemann_zeta_function">Riemann_zeta_function</a> on wiki.
		/// </summary>
		BigDecimal^ Zeta(Rounding rounding) { mpfr_zeta(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the value of Riemann Zeta function on <paramref name="value"/> using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Riemann_zeta_function">Riemann_zeta_function</a> on wiki.
		/// </summary>
		BigDecimal^ Zeta(UInt64 value) { return Zeta(value, DefaultRounding); }

		/// <summary>
		/// Set the value to the value of Riemann Zeta function on <paramref name="value"/> using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Riemann_zeta_function">Riemann_zeta_function</a> on wiki.
		/// </summary>
		BigDecimal^ Zeta(UInt64 value, Rounding rounding) { mpfr_zeta_ui(this->value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the error function on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Error_function">Error_function</a> on wiki.
		/// </summary>
		BigDecimal^ Erf() { return Erf(DefaultRounding); }

		/// <summary>
		/// Set the value to the error function on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Error_function">Error_function</a> on wiki.
		/// </summary>
		BigDecimal^ Erf(Rounding rounding) { mpfr_erf(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the complementary errof function on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Error_function">Error_function</a> on wiki.
		/// </summary>
		BigDecimal^ Erfc() { return Erfc(DefaultRounding); }

		/// <summary>
		/// Set the value to the complementary errof function on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Error_function">Error_function</a> on wiki.
		/// </summary>
		BigDecimal^ Erfc(Rounding rounding) { mpfr_erfc(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the first kind Bessel function of order 0 on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		BigDecimal^ J0() { return J0(DefaultRounding); }

		/// <summary>
		/// Set the value to the first kind Bessel function of order 0 on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		BigDecimal^ J0(Rounding rounding) { mpfr_j0(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the first kind Bessel function of order 1 on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		BigDecimal^ J1() { return J1(DefaultRounding); }

		/// <summary>
		/// Set the value to the first kind Bessel function of order 1 on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		BigDecimal^ J1(Rounding rounding) { mpfr_j1(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the first kind Bessel function of order <paramref name="n"/> on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		/// <param name="n">The order of the first kind Bessel function to compute</param>
		BigDecimal^ Jn(Int64 n) { return Jn(n, DefaultRounding); }

		/// <summary>
		/// Set the value to the first kind Bessel function of order <paramref name="n"/> on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		/// <param name="n">The order of the first kind Bessel function to compute</param>
		BigDecimal^ Jn(Int64 n, Rounding rounding) { mpfr_jn(value, n, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the second kind Bessel function of order 0 on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		BigDecimal^ Y0() { return Y0(DefaultRounding); }

		/// <summary>
		/// Set the value to the second kind Bessel function of order 0 on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		BigDecimal^ Y0(Rounding rounding) { mpfr_y0(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the second kind Bessel function of order 1 on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		BigDecimal^ Y1() { return Y1(DefaultRounding); }

		/// <summary>
		/// Set the value to the second kind Bessel function of order 1 on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		BigDecimal^ Y1(Rounding rounding) { mpfr_y1(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the second kind Bessel function of order <paramref name="n"/> on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		/// <param name="n">The order of the second kind Bessel function to compute</param>
		BigDecimal^ Yn(Int64 n) { return Yn(n, DefaultRounding); }

		/// <summary>
		/// Set the value to the second kind Bessel function of order <paramref name="n"/> on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		/// <param name="n">The order of the second kind Bessel function to compute</param>
		BigDecimal^ Yn(Int64 n, Rounding rounding) { mpfr_yn(value, n, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the arithmetic-geometric mean of the current value and <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Arithmetic–geometric_mean">Arithmetic–geometric_mean</a> on wiki.
		/// </summary>
		BigDecimal^ Agm(BigDecimal^ y) { return Agm(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the arithmetic-geometric mean of the current value and <paramref name="y"/> using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Arithmetic–geometric_mean">Arithmetic–geometric_mean</a> on wiki.
		/// </summary>
		BigDecimal^ Agm(BigDecimal^ y, Rounding rounding) { mpfr_agm(value, value, y->value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the Euclidean norm of the current value and <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Euclidean_norm">Euclidean_norm</a> on wiki.
		/// </summary>
		BigDecimal^ Hypot(BigDecimal^ y) { return Hypot(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the Euclidean norm of the current value and <paramref name="y"/> using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Euclidean_norm">Euclidean_norm</a> on wiki.
		/// </summary>
		BigDecimal^ Hypot(BigDecimal^ y, Rounding rounding) { mpfr_hypot(value, value, y->value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Set the value to the Airy function Ai on the current value using the <see cref="DefaultRounding"/> using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Airy_function">Airy_function</a> on wiki.
		/// </summary>
		BigDecimal^ Ai() { return Ai(DefaultRounding); }

		/// <summary>
		/// Set the value to the Airy function Ai on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Airy_function">Airy_function</a> on wiki.
		/// </summary>
		BigDecimal^ Ai(Rounding rounding) { mpfr_ai(value, value, (mpfr_rnd_t)rounding); return this; }
#pragma endregion
#pragma region Integer and Remainder Related Functions

		/// <summary>
		/// Round the current value using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		BigDecimal^ Round() { return Round(DefaultRounding); }

		/// <summary>
		/// Round the current value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		BigDecimal^ Round(Rounding rounding) { mpfr_rint(value, value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Round to the nearest representable value using away from zero rounding.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		BigDecimal^ RoundAfz() { mpfr_round(value, value); return this; }

		/// <summary>
		/// Round to the next higher or equal representable value using using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		BigDecimal^ Ceil() { return Ceil(DefaultRounding); }

		/// <summary>
		/// Round to the next higher or equal representable value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		BigDecimal^ Ceil(Rounding rounding) { mpfr_rint_ceil(value, value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Round to the next higher or equal representable value using away from zero rounding.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		BigDecimal^ CeilAfz() { mpfr_ceil(value, value); return this; }

		/// <summary>
		/// Round to the next lower or equal representable value using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		BigDecimal^ Floor() { return Floor(DefaultRounding); }

		/// <summary>
		/// Round to the next lower or equal representable value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		BigDecimal^ Floor(Rounding rounding) { mpfr_rint_floor(value, value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Round to the next lower or equal representable value using away from zero rounding.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		BigDecimal^ FloorAfz() { mpfr_floor(value, value); return this; }

		/// <summary>
		/// Round the next higher or equal representable value using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		BigDecimal^ Trunc() { return Trunc(DefaultRounding); }

		/// <summary>
		/// Round the next higher or equal representable value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		BigDecimal^ Trunc(Rounding rounding) { mpfr_rint_trunc(value, value, (mpfr_rnd_t)rounding); return this; }
		
		/// <summary>
		/// Round the next higher or equal representable value using away from zero rounding.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		BigDecimal^ TruncAfz() { mpfr_ceil(value, value); return this; }

		/// <summary>
		/// Set the value to the fractional part of the current value using the <see cref="DefaultRounding"/>.
		/// </summary>
		BigDecimal^ Frac() { return Frac(DefaultRounding); }

		/// <summary>
		/// Set the value to the fractional part of the current value using <paramref name="rounding"/>.
		/// </summary>
		BigDecimal^ Frac(Rounding rounding) { mpfr_frac(value, value, (mpfr_rnd_t)rounding); return this; }

		/// <summary>
		/// Fill simultaneously <paramref name="fraction"/> with the fractional part and
		/// <paramref name="integral"/> with the integral part of the current value
		/// using the <see cref="DefaultRounding"/>.
		/// </summary>
		BigDecimal^ Modf([Out] BigDecimal^% fraction, [Out] BigDecimal^% integral) { return Modf(fraction, integral, DefaultRounding); }

		/// <summary>
		/// Fill simultaneously <paramref name="fraction"/> with the fractional part and
		/// <paramref name="integral"/> with the integral part of the current value
		/// using <paramref name="rounding"/>.
		/// </summary>
		BigDecimal^ Modf([Out] BigDecimal^% fraction, [Out] BigDecimal^% integral, Rounding rounding) { 
			fraction = Create(Precision);
			integral = Create(Precision);
			mpfr_modf(fraction->value, integral->value, value, (mpfr_rnd_t)rounding);
			return this;
		}
#pragma endregion

		/// <summary>
		/// Clear the cache of the library. This should be called before on each thread.
		/// </summary>
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

		virtual BigDecimal^ CombinePrecision(BigDecimal^ y) { return SetPrecision(Math::Max(Precision, y->Precision)); }
		static BigDecimal^ LValue(BigDecimal^ x) { return Create()->SetPrecision(x)->Set(x); }
		static BigDecimal^ LValue(BigDecimal^ x, BigDecimal^ y) { return Create()->CombinePrecision(y)->Set(y); }

		bool isDisposed = false;
		property mpfr_ptr value { mpfr_ptr get(); }
	private:
		static Rounding _defaultRounding = Rounding::ToNearestTiesAwayFromZero;
		static int _defaultPrecision = 53;

		int _precision = DefaultPrecision;
		mpfr_ptr _value;
	};
}
