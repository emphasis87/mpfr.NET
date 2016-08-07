#pragma once

#include <stdarg.h>
#include <varargs.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "mpfr.h"

#include "Rounding.h"

using namespace System;
using namespace System::Globalization;
using namespace System::Runtime::InteropServices;

namespace System::ArbitraryPrecision
{
	/// <summary>
	/// The class represents a floating point number with arbitrary precision significand (matissa) and limited precision exponent.
	/// Most methods are constructed to allow fluent interface.
	/// For standard numeric types there are conversion operators provided, as well as for <see cref="String"/> type.
	/// Standard mathematical operators are also provided.
	/// If not specified the <see cref="DefaultPrecision"/> is used for creating new instances of <see cref="BigDecimal"/>.
	/// Also, if not specified whereever there is an overload allowing for providing custom <see cref="Rounding"/> the <see cref="DefaultRounding"/> is used.
	/// The implementation uses internally calls to an unamanged library MPFR.
	/// Unamanged resources are automatically freed in a finalizer, but can be also collected deterministically using the <see cref="Dispose"/> destructor.
	/// </summary>
	public ref class BigDecimal :
		IConvertible,
		IComparable, IComparable<BigDecimal^>,
		IEquatable<BigDecimal^>,
		IFormattable
	{
	public:
		static BigDecimal() {
			mpfr_set_default_rounding_mode(_defaultRounding);
			mpfr_set_default_prec(_defaultPrecision);
		}

#pragma region Constructors & Destructors
#pragma region Constructors

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and the <see cref="DefaultPrecision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		BigDecimal(SByte value) : BigDecimal((Int64)value, DefaultPrecision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		BigDecimal(SByte value, UInt64 precision) : BigDecimal((Int64)value, precision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and the <see cref="DefaultPrecision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		BigDecimal(Int16 value) : BigDecimal((Int64)value, DefaultPrecision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		BigDecimal(Int16 value, UInt64 precision) : BigDecimal((Int64)value, precision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and the <see cref="DefaultPrecision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		BigDecimal(Int32 value) : BigDecimal((Int64)value, DefaultPrecision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		BigDecimal(Int32 value, UInt64 precision) : BigDecimal((Int64)value, precision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and the <see cref="DefaultPrecision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		BigDecimal(Int64 value) : BigDecimal(value, DefaultPrecision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		BigDecimal(Int64 value, UInt64 precision) { SetPrecision(precision); Set(value); }

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and the <see cref="DefaultPrecision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		BigDecimal(Byte value) : BigDecimal((UInt64)value, DefaultPrecision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		BigDecimal(Byte value, UInt64 precision) : BigDecimal((UInt64)value, precision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and the <see cref="DefaultPrecision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		BigDecimal(UInt16 value) : BigDecimal((UInt64)value, DefaultPrecision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		BigDecimal(UInt16 value, UInt64 precision) : BigDecimal((UInt64)value, precision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and the <see cref="DefaultPrecision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		BigDecimal(UInt32 value) : BigDecimal((UInt64)value, DefaultPrecision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		BigDecimal(UInt32 value, UInt64 precision) : BigDecimal((UInt64)value, precision) {};
		
		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and the <see cref="DefaultPrecision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		BigDecimal(UInt64 value) : BigDecimal((UInt64)value, DefaultPrecision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		BigDecimal(UInt64 value, UInt64 precision) { SetPrecision(precision); Set(value); }

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and the <see cref="DefaultPrecision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		BigDecimal(Single value) : BigDecimal(value, DefaultPrecision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		BigDecimal(Single value, UInt64 precision) { SetPrecision(precision); Set(value); }

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and the <see cref="DefaultPrecision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		BigDecimal(Double value) : BigDecimal(value, DefaultPrecision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		BigDecimal(Double value, UInt64 precision) { SetPrecision(precision); Set(value); }

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and the <see cref="DefaultPrecision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		BigDecimal(Decimal value) : BigDecimal(value, DefaultPrecision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		BigDecimal(Decimal value, UInt64 precision) { SetPrecision(precision); Set(value); }

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and the <see cref="DefaultPrecision"/> in bits.
		/// The <paramref name="value"/> string is expected to be in a base of 10.
		/// </summary>
		/// <param name="value">The underlying value</param>
		BigDecimal(String^ value) : BigDecimal(value, 10) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// The <paramref name="value"/> string is expected to be in a base of 10.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		BigDecimal(String^ value, UInt64 precision) : BigDecimal(value, 10, precision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and the <see cref="DefaultPrecision"/> in bits.
		/// The <paramref name="value"/> string is expected to be in a specified <paramref name="base"/>.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="value">The expected base of the give value</param>
		BigDecimal(String^ value, int base) : BigDecimal(value, base, DefaultPrecision) {};

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// The <paramref name="value"/> string is expected to be in a specified <paramref name="base"/>.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="value">The expected base of the give value</param>
		/// <param name="precision">The underlying precision in bits</param>
		BigDecimal(String^ value, int base, UInt64 precision) { SetPrecision(precision); Set(value); }
#pragma endregion

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with the <see cref="DefaultPrec/> in bits.
		/// </summary>
		static BigDecimal^ Create() { return gcnew BigDecimal(); }

		/// <summary>
		/// Create a new <see cref="BigDecimal"/> instance with a given <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="precision">The underlying precision in bits</param>
		static BigDecimal^ Create(UInt64 precision) { return Create()->SetPrecision(precision); }

		virtual ~BigDecimal() {
			if (!_isDisposed) {
				this->!BigDecimal();
				_isDisposed = true;
			}
		}

		!BigDecimal() {
			if (_value != nullptr) {
				mpfr_clear(_value);
				delete _value;
			}
		}

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
#pragma region Explicit Cast Operators
		static explicit operator SByte(BigDecimal^ x) { return x->ToSByte(); }
		static explicit operator Int16(BigDecimal^ x) { return x->ToInt16(); }
		static explicit operator Int32(BigDecimal^ x) { return x->ToInt32(); }
		static explicit operator Int64(BigDecimal^ x) { return x->ToInt64(); }
		static explicit operator Byte(BigDecimal^ x) { return x->ToByte(); }
		static explicit operator UInt16(BigDecimal^ x) { return x->ToUInt16(); }
		static explicit operator UInt32(BigDecimal^ x) { return x->ToInt32(); }
		static explicit operator UInt64(BigDecimal^ x) { return x->ToUInt64(); }
		static explicit operator Single(BigDecimal^ x) { return x->ToSingle(); }
		static explicit operator Double(BigDecimal^ x) { return x->ToDouble(); }
		static explicit operator Decimal(BigDecimal^ x) { return x->ToDecimal(); }
#pragma endregion

#pragma region DefaultRounding
		/// <summary>
		/// The default halfway rounding method used if not otherwise specified.
		/// </summary>
		static property Rounding^ DefaultRounding {
			Rounding^ get() { return _defaultRounding; }
			void set(Rounding^ rounding) {
				_defaultRounding = rounding;
				mpfr_set_default_rounding_mode(rounding);
			}
		}
#pragma endregion
#pragma region DefaultPrecision
		/// <summary>
		/// The default precision in bits used to initialize a new <see cref="BigDecimal"/> if otherwise not specified.
		/// </summary>
		static property UInt64 DefaultPrecision {
			UInt64 get() { return _defaultPrecision; }
			void set(UInt64 precision) {
				_defaultPrecision = precision;
				mpfr_set_default_prec(precision);
			}
		}
#pragma endregion
#pragma region Precision
		/// <summary>
		/// The precision of the underlying number in bits.
		/// Note that setting this will erase the current value of this instance.
		/// </summary>
		property UInt64 Precision {
			UInt64 get() { return _precision; }
			void set(UInt64 precision) {
				if (_precision != precision) {
					_precision = precision;
					if (_value != nullptr)
						mpfr_set_prec(value, precision);
				}
			}
		}

		/// <summary>
		/// Set the precision of the underlying number in bits to <paramref name="precision"/>, same as <see cref="Precision"/>.
		/// Note that setting this will erase the current value of this instance.
		/// </summary>
		/// <param name="precision">The new precision in bits</param>
		/// <returns>This instance with the new precision</returns>
		BigDecimal^ SetPrecision(UInt64 precision) { Precision = precision; return this; }

		/// <summary>
		/// Set the precision of the underlying number in bits to that of <paramref name="y"/>.
		/// Note that setting this will erase the current value of this instance.
		/// </summary>
		/// <param name="y">The source of a new precision in bits</param>
		/// <returns>This instance with the new precision</returns>
		BigDecimal^ SetPrecision(BigDecimal^ y) { return SetPrecision(y->Precision); }

		/// <summary>
		/// Round the value to the new <paramref name="precision"/> using <see cref="RoundToPrecision"/> and the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="precision">The new precision in bits</param>
		/// <returns>This instance with the value changed to the new precision</returns>
		BigDecimal^ SetPrecisionSafely(UInt64 precision) { return SetPrecisionSafely(precision, DefaultRounding); }

		/// <summary>
		/// Round the value to the new <paramref name="precision"/> using <see cref="RoundToPrecision"/> and the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="precision">The new precision in bits</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the value changed to the new precision</returns>
		BigDecimal^ SetPrecisionSafely(UInt64 precision, Rounding^ rounding)
		{
			RoundToPrecision(precision, rounding);
			_precision = precision;
			return this;
		}

		/// <summary>
		/// Round the value to a precision of <paramref name="y"/> using <see cref="RoundToPrecision"/> and the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The source of a new precision in bits</param>
		/// <returns>This instance with the value changed to the new precision</returns>
		BigDecimal^ SetPrecisionSafely(BigDecimal^ y) { return SetPrecisionSafely(y->Precision, DefaultRounding); }

		/// <summary>
		/// Round the value to a precision of <paramref name="y"/> using <see cref="RoundToPrecision"/> and the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The source of a new precision in bits</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the value changed to the new precision</returns>
		BigDecimal^ SetPrecisionSafely(BigDecimal^ y, Rounding^ rounding) { return SetPrecisionSafely(y->Precision, rounding); }
#pragma endregion

#pragma region Static Instances

		/// <summary>
		/// Creates a new <see cref="BigDecimal"/> instance with a value set to not a number constant.
		/// </summary>
		static property BigDecimal^ NaN { BigDecimal^ get() { return Create()->SetNaN(); }}

		/// <summary>
		/// Creates a new <see cref="BigDecimal"/> instance with a value set to the positive infinity constant.
		/// </summary>
		static property BigDecimal^ Infinity { BigDecimal^ get() { return Create()->SetInf(); }}

		/// <summary>
		/// Creates a new <see cref="BigDecimal"/> instance with a value set to the positive infinity constant.
		/// </summary>
		static property BigDecimal^ PositiveInfinity { BigDecimal^ get() { return Create()->SetInfPositive(); }}

		/// <summary>
		/// Creates a new <see cref="BigDecimal"/> instance with a value set to the negative infinity constant.
		/// </summary>
		static property BigDecimal^ NegativeInfinity { BigDecimal^ get() { return Create()->SetInfNegative(); }}

		/// <summary>
		/// Creates a new <see cref="BigDecimal"/> instance with a value set to the positive zero constant.
		/// </summary>
		static property BigDecimal^ Zero { BigDecimal^ get() { return Create()->SetZero(); }}

		/// <summary>
		/// Creates a new <see cref="BigDecimal"/> instance with a value set to the positive zero constant.
		/// </summary>
		static property BigDecimal^ PositiveZero { BigDecimal^ get() { return Create()->SetZeroPositive(); }}

		/// <summary>
		/// Creates a new <see cref="BigDecimal"/> instance with a value set to the negative zero constant.
		/// </summary>
		static property BigDecimal^ NegativeZero { BigDecimal^ get() { return Create()->SetZeroNegative(); }}

		/// <summary>
		/// Creates a new <see cref="BigDecimal"/> instance with a value set to the natural logarithm of 2 constant.
		/// </summary>
		static property BigDecimal^ Ln2 { BigDecimal^ get() { return Create()->SetLn2(); }}

		/// <summary>
		/// Creates a new <see cref="BigDecimal"/> instance with a value set to the Pi constant.
		/// </summary>
		static property BigDecimal^ Pi { BigDecimal^ get() { return Create()->SetPi(); }}

		/// <summary>
		/// Creates a new <see cref="BigDecimal"/> instance with a value set to the positive Euler's constant.
		/// </summary>
		static property BigDecimal^ Euler { BigDecimal^ get() { return Create()->SetEuler(); }}

		/// <summary>
		/// Creates a new <see cref="BigDecimal"/> instance with a value set to the Catalan's constant.
		/// </summary>
		static property BigDecimal^ Catalan { BigDecimal^ get() { return Create()->SetCatalan(); }}
#pragma endregion

#pragma region Arithmetic Operators
		static BigDecimal^ operator +(BigDecimal^ x) { return LValue(x); }
		static BigDecimal^ operator -(BigDecimal^ x) { return LValue(x)->Neg(); }

		static BigDecimal^ operator +(BigDecimal^ x, BigDecimal^ y) { return LValue(x, y)->Add(y); }
		static BigDecimal^ operator +(BigDecimal^ x, Int64 y) { return LValue(x, y)->Add(y); }
		static BigDecimal^ operator +(BigDecimal^ x, UInt64 y) { return LValue(x, y)->Add(y); }
		static BigDecimal^ operator +(BigDecimal^ x, Double y) { return LValue(x, y)->Add(y); }

		static BigDecimal^ operator -(BigDecimal^ x, BigDecimal^ y) { return LValue(x, y)->Sub(y); }
		static BigDecimal^ operator -(BigDecimal^ x, Int64 y) { return LValue(x, y)->Sub(y); }
		static BigDecimal^ operator -(BigDecimal^ x, UInt64 y) { return LValue(x, y)->Sub(y); }
		static BigDecimal^ operator -(BigDecimal^ x, Double y) { return LValue(x, y)->Sub(y); }

		static BigDecimal^ operator *(BigDecimal^ x, BigDecimal^ y) { return LValue(x, y)->Mul(y); }
		static BigDecimal^ operator *(BigDecimal^ x, Int64 y) { return LValue(x, y)->Mul(y); }
		static BigDecimal^ operator *(BigDecimal^ x, UInt64 y) { return LValue(x, y)->Mul(y); }
		static BigDecimal^ operator *(BigDecimal^ x, Double y) { return LValue(x, y)->Mul(y); }

		static BigDecimal^ operator /(BigDecimal^ x, BigDecimal^ y) { return LValue(x, y)->Div(y); }
		static BigDecimal^ operator /(BigDecimal^ x, Int64 y) { return LValue(x, y)->Div(y); }
		static BigDecimal^ operator /(BigDecimal^ x, UInt64 y) { return LValue(x, y)->Div(y); }
		static BigDecimal^ operator /(BigDecimal^ x, Double y) { return LValue(x, y)->Div(y); }

		static BigDecimal^ operator %(BigDecimal^ x, BigDecimal^ y) { return LValue(x, y)->Fmod(y); }
		static BigDecimal^ operator %(BigDecimal^ x, Int64 y) { return LValue(x, y)->Fmod(y); }
		static BigDecimal^ operator %(BigDecimal^ x, UInt64 y) { return LValue(x, y)->Fmod(y); }
		static BigDecimal^ operator %(BigDecimal^ x, Double y) { return LValue(x, y)->Fmod(y); }

		static BigDecimal^ operator ^(BigDecimal^ x, BigDecimal^ y) { return LValue(x, y)->Pow(y); }
		static BigDecimal^ operator ^(BigDecimal^ x, Int64 y) { return LValue(x, y)->Pow(y); }
		static BigDecimal^ operator ^(BigDecimal^ x, UInt64 y) { return LValue(x, y)->Pow(y); }

		static BigDecimal^ operator ++(BigDecimal^ x) { return LValue(x)->Add((UInt64)1); }
		static BigDecimal^ operator --(BigDecimal^ x) { return LValue(x)->Sub((UInt64)1); }
#pragma endregion
#pragma region Comparison Operators

#pragma endregion

#pragma region Value Setters
#pragma region Value Setters from Value Types
		/// <summary>
		/// Set the value to <paramref name="value"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(SByte value) { return Set(value, DefaultRounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(SByte value, Rounding^ rounding) { return Set((Int64)value, rounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(Int16 value) { return Set(value, DefaultRounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(Int16 value, Rounding^ rounding) { return Set((Int64)value, rounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(Int32 value) { return Set(value, DefaultRounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(Int32 value, Rounding^ rounding) { return Set((Int64)value, rounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(Int64 value) { return Set(value, DefaultRounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(Int64 value, Rounding^ rounding) { mpfr_set_si(this->value, value, rounding); return this; }

		/// <summary>
		/// Set the value to <paramref name="value"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(Byte value) { return Set(value, DefaultRounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(Byte value, Rounding^ rounding) { return Set((UInt64)value, rounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(UInt16 value) { return Set(value, DefaultRounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(UInt16 value, Rounding^ rounding) { return Set((UInt64)value, rounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(UInt32 value) { return Set(value, DefaultRounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(UInt32 value, Rounding^ rounding) { return Set((UInt64)value, rounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(UInt64 value) { return Set(value, DefaultRounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(UInt64 value, Rounding^ rounding) { mpfr_set_ui(this->value, value, rounding); return this; }

		/// <summary>
		/// Set the value to <paramref name="value"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(Single value) { return Set(value, DefaultRounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(Single value, Rounding^ rounding) { mpfr_set_flt(this->value, value, rounding); return this; }

		/// <summary>
		/// Set the value to <paramref name="value"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(Double value) { return Set(value, DefaultRounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(Double value, Rounding^ rounding) { mpfr_set_d(this->value, value, rounding); return this; }

		/// <summary>
		/// Set the value to <paramref name="value"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(Decimal value) { return Set(value, DefaultRounding); }

		/// <summary>
		/// Set the value to <paramref name="value"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(Decimal value, Rounding^ rounding) { return Set(value.ToString(CultureInfo::InvariantCulture), rounding); }

		/// <summary>
		/// Parse a new value from <paramref name="value"/> using the <see cref="DefaultRounding"/>.
		/// The base of <paramref name="value"/> is inferred from significand prefixes 0b or 0B to be 2, for 0x or 0X to be 16, and 10 otherwise.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(String^ value) { return Set(value, 0, DefaultRounding); }

		/// <summary>
		/// Parse a new value from <paramref name="value"/> using <paramref name="rounding"/>.
		/// The base of <paramref name="value"/> is inferred from significand prefixes 0b or 0B to be 2, for 0x or 0X to be 16, and 10 otherwise.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(String^ value, Rounding^ rounding) { return Set(value, 0, rounding); }

		/// <summary>
		/// Parse a new value from <paramref name="value"/> using the <see cref="DefaultRounding"/>.
		/// The base of the <paramref name="value"/> is expected to be between 2 and 62 or 0.
		/// If <paramref name="base"/> is 0 then the base is inferred from significand prefixes 0b or 0B to be 2, for 0x or 0X to be 16, and 10 otherwise.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <param name="base">The base of the <paramref name="value"/></param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(String^ value, int base) { return Set(value, base, DefaultRounding); }

		/// <summary>
		/// Parse a new value from <paramref name="value"/> using <paramref name="rounding"/>.
		/// The base of the <paramref name="value"/> is expected to be between 2 and 62 or 0.
		/// If <paramref name="base"/> is 0 then the base is inferred from significand prefixes 0b or 0B to be 2, for 0x or 0X to be 16, and 10 otherwise.
		/// </summary>
		/// <param name="value">The new value to assume</param>
		/// <param name="base">The base of the <paramref name="value"/></param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(String^ value, int base, Rounding^ rounding) {
			char* cstr = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(value).ToPointer();
			mpfr_set_str(this->value, cstr, base, rounding);
			Marshal::FreeHGlobal((IntPtr)cstr);
			return this;
		}
#pragma endregion
#pragma region Value Setters of Constants

		/// <summary>
		/// Set the value to the not a number constant.
		/// </summary>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetNaN() { mpfr_set_nan(value); return this; }

		/// <summary>
		/// Set the value to the positive infinity constant.
		/// </summary>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetInf() { return SetInfPositive(); }

		/// <summary>
		/// Set the value to the positive or negative infinity constant based on the sign of <paramref name="sign"/>.
		/// </summary>
		/// <param name="sign">The value to determine the sign of the resulting infinity constant. Zero counts towards plus values.</param>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetInf(int sign) { mpfr_set_inf(value, sign); return this; }

		/// <summary>
		/// Set the value to the positive infinity constant.
		/// </summary>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetInfPositive() { return SetInf(+1); }

		/// <summary>
		/// Set the value to the negative infinity constant.
		/// </summary>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetInfNegative() { return SetInf(-1); }

		/// <summary>
		/// Set the value to the positive zero constant.
		/// </summary>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetZero() { return SetZeroPositive(); }

		/// <summary>
		/// Set the value to the positive or negative zero constant based on the sign of <paramref name="sign"/>.
		/// </summary>
		/// <param name="sign>The value to determine the sign of the resulting zero constant. Zero counts towards plus values.</param>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetZero(int sign) { mpfr_set_zero(value, sign); return this; }

		/// <summary>
		/// Set the value to the positive zero constant.
		/// </summary>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetZeroPositive() { return SetZero(+1); }

		/// <summary>
		/// Set the value to the negative zero constant.
		/// </summary>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetZeroNegative() { return SetZero(-1); }

		/// <summary>
		/// Set the value to the natural logarithm of 2 constant.
		/// </summary>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetLn2() { return SetLn2(DefaultRounding); }

		/// <summary>
		/// Set the value to the natural logarithm of 2 constant.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetLn2(Rounding^ rounding) { mpfr_const_log2(value, rounding); return this; }

		/// <summary>
		/// Set the value to the Pi constant.
		/// </summary>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetPi() { return SetPi(DefaultRounding); }

		/// <summary>
		/// Set the value to the Pi constant.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetPi(Rounding^ rounding) { mpfr_const_pi(value, rounding); return this; }

		/// <summary>
		/// Set the value to the Euler's constant.
		/// </summary>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetEuler() { return SetEuler(DefaultRounding); }

		/// <summary>
		/// Set the value to the Euler's constant.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetEuler(Rounding^ rounding) { mpfr_const_euler(value, rounding); return this; }

		/// <summary>
		/// Set the value to the Catalan's constant.
		/// </summary>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetCatalan() { return SetCatalan(DefaultRounding); }

		/// <summary>
		/// Set the value to the Catalan's constant.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance set to the constant</returns>
		BigDecimal^ SetCatalan(Rounding^ rounding) { mpfr_const_catalan(value, rounding); return this; }
#pragma endregion

		/// <summary>
		/// Set the value to that of <paramref name="y"/>.
		/// </summary>
		/// <param name="y">The value to set</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Set(BigDecimal^ y) { return Set(y, DefaultRounding); }

		/// <summary>
		/// Set the value to that of <paramref name="y"/>.
		/// </summary>
		/// <param name="y">The value to set</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the new value</returns>
		BigDecimal^ Set(BigDecimal^ y, Rounding^ rounding) { mpfr_set(value, y->value, rounding); return this; }

		/// <summary>
		/// Swap the current instance and <paramref name="y"/> inplace.
		/// </summary>
		/// <param name="y">The value to swap with</param>
		/// <returns>This instance with the content swapped</returns>
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
		/// Negate the current value using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Neg() { return Neg(DefaultRounding); }

		/// <summary>
		/// Negate the current value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Neg(Rounding^ rounding) { mpfr_neg(value, value, rounding); return this; }

		/// <summary>
		/// Change the current value to its absolute using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Abs() { return Abs(DefaultRounding); }

		/// <summary>
		/// Change the current value to its absolute using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Abs(Rounding^ rounding) { mpfr_abs(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the current value added by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to add</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Add(BigDecimal^ y) { return Add(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value added by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to add</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Add(BigDecimal^ y, Rounding^ rounding) { mpfr_add(value, value, y->value, rounding); return this; }

		/// <summary>
		/// Set the value to the current value added by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to add</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Add(Int64 y) { return Add(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value added by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to add</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Add(Int64 y, Rounding^ rounding) { mpfr_add_si(value, value, y, rounding); return this; }

		/// <summary>
		/// Set the value to the current value added by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to add</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Add(UInt64 y) { return Add(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value added by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to add</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Add(UInt64 y, Rounding^ rounding) { mpfr_add_ui(value, value, y, rounding); return this; }

		/// <summary>
		/// Set the value to the current value added by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to add</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Add(Double y) { return Add(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value added by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to add</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Add(Double y, Rounding^ rounding) { mpfr_add_ui(value, value, y, rounding); return this; }

		/// <summary>
		/// Set the value to the current value subtracted by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to subtract</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sub(BigDecimal^ y) { return Sub(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value subtracted by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to subtract</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sub(BigDecimal^ y, Rounding^ rounding) { mpfr_sub(value, value, y->value, rounding); return this; }

		/// <summary>
		/// Set the value to the current value subtracted by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to subtract</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sub(Int64 y) { return Sub(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value subtracted by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to subtract</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sub(Int64 y, Rounding^ rounding) { mpfr_sub_si(value, value, y, rounding); return this; }

		/// <summary>
		/// Set the value to the current value subtracted by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to subtract</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sub(UInt64 y) { return Sub(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value subtracted by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to subtract</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sub(UInt64 y, Rounding^ rounding) { mpfr_sub_ui(value, value, y, rounding); return this; }

		/// <summary>
		/// Set the value to the current value subtracted by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to subtract</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sub(Double y) { return Sub(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value subtracted by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to subtract</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sub(Double y, Rounding^ rounding) { mpfr_sub_d(value, value, y, rounding); return this; }

		/// <summary>
		/// Set the value to the current value multiplied by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to multiply by</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Mul(BigDecimal^ y) { return Mul(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value multiplied by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to multiply by</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Mul(BigDecimal^ y, Rounding^ rounding) { mpfr_mul(value, value, y->value, rounding); return this; }

		/// <summary>
		/// Set the value to the current value multiplied by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to multiply by</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Mul(Int64 y) { return Mul(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value multiplied by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to multiply by</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Mul(Int64 y, Rounding^ rounding) { mpfr_mul_si(value, value, y, rounding); return this; }

		/// <summary>
		/// Set the value to the current value multiplied by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to multiply by</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Mul(UInt64 y) { return Mul(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value multiplied by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to multiply by</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Mul(UInt64 y, Rounding^ rounding) { mpfr_mul_ui(value, value, y, rounding); return this; }

		/// <summary>
		/// Set the value to the current value multiplied by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to multiply by</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Mul(Double y) { return Mul(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value multiplied by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to multiply by</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Mul(Double y, Rounding^ rounding) { mpfr_mul_d(value, value, y, rounding); return this; }

		/// <summary>
		/// Set the value to the current value divided by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Div(BigDecimal^ y) { return Div(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value divided by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Div(BigDecimal^ y, Rounding^ rounding) { mpfr_div(value, value, y->value, rounding); return this; }

		/// <summary>
		/// Set the value to the current value divided by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Div(Int64 y) { return Div(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value divided by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Div(Int64 y, Rounding^ rounding) { mpfr_div_si(value, value, y, rounding); return this; }

		/// <summary>
		/// Set the value to the current value divided by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Div(UInt64 y) { return Div(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value divided by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Div(UInt64 y, Rounding^ rounding) { mpfr_div_ui(value, value, y, rounding); return this; }

		/// <summary>
		/// Set the value to the current value divided by <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Div(Double y) { return Div(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the current value divided by <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to divide by</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Div(Double y, Rounding^ rounding) { mpfr_div_si(value, value, y, rounding); return this; }

		/// <summary>
		/// Raise the current value to <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to raise by</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Pow(BigDecimal^ y) { return Pow(y, DefaultRounding); }

		/// <summary>
		/// Raise the current value to <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to raise by</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Pow(BigDecimal^ y, Rounding^ rounding) { mpfr_pow(value, value, y->value, rounding); return this; }

		/// <summary>
		/// Raise the current value to <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to raise by</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Pow(Int64 y) { return Pow(y, DefaultRounding); }

		/// <summary>
		/// Raise the current value to <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to raise by</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Pow(Int64 y, Rounding^ rounding) { mpfr_pow_si(value, value, y, rounding); return this; }

		/// <summary>
		/// Raise the current value to <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to raise by</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Pow(UInt64 y) { return Pow(y, DefaultRounding); }

		/// <summary>
		/// Raise the current value to <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value to raise by</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Pow(UInt64 y, Rounding^ rounding) { mpfr_pow_ui(value, value, y, rounding); return this; }

		/// <summary>
		/// Set the value to its square root using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sqrt() { return Sqrt(DefaultRounding); }

		/// <summary>
		/// Set the value to its square root using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sqrt(Rounding^ rounding) { mpfr_sqrt(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the squeare root of <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The operand of the square root function</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sqrt(UInt64 y) { return Sqrt(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the squeare root of <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The operand of the square root function</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sqrt(UInt64 y, Rounding^ rounding) { mpfr_pow_si(value, value, y, rounding); return this; }

		/// <summary>
		/// Set the value to its reciprocal square root using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value to raise by</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ RecSqrt() { return RecSqrt(DefaultRounding); }

		/// <summary>
		/// Set the value to its reciprocal square root using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ RecSqrt(Rounding^ rounding) { mpfr_rec_sqrt(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to its cubic root using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Cbrt() { return Cbrt(DefaultRounding); }

		/// <summary>
		/// Set the value to its cubic root using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Cbrt(Rounding^ rounding) { mpfr_cbrt(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the <paramref name="n"/>th root of <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The nth root</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Root(UInt64 n) { return Root(n, DefaultRounding); }

		/// <summary>
		/// Set the value to the <paramref name="n"/>th root of <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="n">The nth root</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Root(UInt64 n, Rounding^ rounding) { mpfr_root(value, value, n, rounding); return this; }

		/// <summary>
		/// Set the value to a positive difference from <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value from which to compute the positive difference from</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Dim(BigDecimal^ y) { return Dim(y, DefaultRounding); }

		/// <summary>
		/// Set the value to a positive difference from <paramref name="y"/> using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value from which to compute the positive difference from</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Dim(BigDecimal^ y, Rounding^ rounding) { mpfr_dim(value, value, y->value, rounding); return this; }
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
		bool IsPositive() { return !IsNegative(); }

		/// <summary>
		/// Check whether the current value is negative.
		/// </summary>
		/// <returns>True if the current value is negative</returns>
		bool IsNegative() { return mpfr_signbit(value) != 0; }

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
		/// <returns>This instance with the result</returns>
		BigDecimal^ Ln() { return Ln(DefaultRounding); }

		/// <summary>
		/// Set the value to the natural logarithm of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Natural_logarithm">Natural_logarithm</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Ln(Rounding^ rounding) { mpfr_log(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the binary logarithm of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Binary_logarithm">Binary_logarithm</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Log2() { return Log2(DefaultRounding); }

		/// <summary>
		/// Set the value to the binary logarithm of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Binary_logarithm">Binary_logarithm</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Log2(Rounding^ rounding) { mpfr_log2(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the decadic logarithm of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Common_logarithm">Common_logarithm</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Log10() { return Log10(DefaultRounding); }

		/// <summary>
		/// Set the value to the decadic logarithm of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Common_logarithm">Common_logarithm</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Log10(Rounding^ rounding) { mpfr_log10(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to exponential of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Exponential_function">Exponential_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Exp() { return Exp(DefaultRounding); }

		/// <summary>
		/// Set the value to exponential of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Exponential_function">Exponential_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Exp(Rounding^ rounding) { mpfr_exp(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the 2 power of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Power_function">Power_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Exp2() { return Exp2(DefaultRounding); }

		/// <summary>
		/// Set the value to the 2 power of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Power_function">Power_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Exp2(Rounding^ rounding) { mpfr_exp2(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the 10 power of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Power_function">Power_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Exp10() { return Exp10(DefaultRounding); }

		/// <summary>
		/// Set the value to the 10 power of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Power_function">Power_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Exp10(Rounding^ rounding) { mpfr_exp10(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the sine of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Sine">Sine</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sin() { return Sin(DefaultRounding); }

		/// <summary>
		/// Set the value to the sine of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Sine">Sine</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sin(Rounding^ rounding) { mpfr_sin(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the cosine of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Cosine">Cosine</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Cos() { return Cos(DefaultRounding); }

		/// <summary>
		/// Set the value to the cosine of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Cosine">Cosine</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Cos(Rounding^ rounding) { mpfr_cos(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the tangent of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Tangent_function">Tangent_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Tan() { return Tan(DefaultRounding); }

		/// <summary>
		/// Set the value to the tangent of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Tangent_function">Tangent_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Tan(Rounding^ rounding) { mpfr_tan(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the secant of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Secant_function">Secant_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sec() { return Sec(DefaultRounding); }

		/// <summary>
		/// Set the value to the secant of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Secant_function">Secant_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sec(Rounding^ rounding) { mpfr_sec(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the cosecant of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Cosecant">Cosecant</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Csc() { return Csc(DefaultRounding); }

		/// <summary>
		/// Set the value to the cosecant of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Cosecant">Cosecant</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Csc(Rounding^ rounding) { mpfr_csc(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the cotangent of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Ctg">Ctg</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Cot() { return Cot(DefaultRounding); }

		/// <summary>
		/// Set the value to the cotangent of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Ctg">Ctg</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Cot(Rounding^ rounding) { mpfr_cot(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the arc-cosine of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Arccosine">Arccosine</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Acos() { return Acos(DefaultRounding); }

		/// <summary>
		/// Set the value to the arc-cosine of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Arccosine">Arccosine</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Acos(Rounding^ rounding) { mpfr_acos(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the arc-sine of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Arcsine">Arcsine</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Asin() { return Asin(DefaultRounding); }

		/// <summary>
		/// Set the value to the arc-sine of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Arcsine">Arcsine</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Asin(Rounding^ rounding) { mpfr_asin(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the arc-tangent of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Arctangent">Arctangent</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Atan() { return Atan(DefaultRounding); }

		/// <summary>
		/// Set the value to the arc-tangent of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Arctangent">Arctangent</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Atan(Rounding^ rounding) { mpfr_atan(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the arc-tangent2 of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Atan2">Atan2</a> on wiki.
		/// </summary>
		/// <param name="y">The second operand of the arc-tangent2 function</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Atan2(BigDecimal^ y) { return Atan2(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the arc-tangent2 of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Atan2">Atan2</a> on wiki.
		/// </summary>
		/// <param name="y">The second operand of the arc-tangent2 function</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Atan2(BigDecimal^ y, Rounding^ rounding) { mpfr_atan2(value, value, y->value, rounding); return this; }

		/// <summary>
		/// Set the value to the hyperbolic cosine of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Hyperbolic_function#Cosh">Hyperbolic_function#Cosh</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Cosh() { return Cosh(DefaultRounding); }

		/// <summary>
		/// Set the value to the hyperbolic cosine of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Hyperbolic_function#Cosh">Hyperbolic_function#Cosh</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Cosh(Rounding^ rounding) { mpfr_cosh(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the hyperbolic sine of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Sinh">Sinh</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sinh() { return Sinh(DefaultRounding); }

		/// <summary>
		/// Set the value to the hyperbolic sine of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Sinh">Sinh</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sinh(Rounding^ rounding) { mpfr_sinh(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the hyperbolic tangent of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Tanh">Tanh</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Tanh() { return Tanh(DefaultRounding); }

		/// <summary>
		/// Set the value to the hyperbolic tangent of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Tanh">Tanh</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Tanh(Rounding^ rounding) { mpfr_tanh(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the hyperbolic secant of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Sech">Sech</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sech() { return Sech(DefaultRounding); }

		/// <summary>
		/// Set the value to the hyperbolic secant of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Sech">Sech</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Sech(Rounding^ rounding) { mpfr_sech(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the hyperbolic cosecant of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Csch">Csch</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Csch() { return Csch(DefaultRounding); }

		/// <summary>
		/// Set the value to the hyperbolic cosecant of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Csch">Csch</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Csch(Rounding^ rounding) { mpfr_csch(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the hyperbolic cotangent of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Coth">Coth</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Coth() { return Coth(DefaultRounding); }

		/// <summary>
		/// Set the value to the hyperbolic cotangent of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Coth">Coth</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Coth(Rounding^ rounding) { mpfr_coth(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the inverse hyperbolic cosine of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Acosh">Acosh</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Acosh() { return Acosh(DefaultRounding); }

		/// <summary>
		/// Set the value to the inverse hyperbolic cosine of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Acosh">Acosh</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Acosh(Rounding^ rounding) { mpfr_acosh(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the inverse hyperbolic sine of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Asinh">Asinh</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Asinh() { return Asinh(DefaultRounding); }

		/// <summary>
		/// Set the value to the inverse hyperbolic sine of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Asinh">Asinh</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Asinh(Rounding^ rounding) { mpfr_asinh(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the inverse hyperbolic tangent of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Atanh">Atanh</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Atanh() { return Atanh(DefaultRounding); }

		/// <summary>
		/// Set the value to the inverse hyperbolic tangent of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Atanh">Atanh</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Atanh(Rounding^ rounding) { mpfr_atanh(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the factorial of <paramref name="value"/> using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Factorial">Factorial</a> on wiki.
		/// </summary>
		/// <param name="value">The argument to the factorial function.</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Fact(UInt64 value) { return Fact(value, DefaultRounding); }

		/// <summary>
		/// Set the value to the factorial of <paramref name="value"/> using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Factorial">Factorial</a> on wiki.
		/// </summary>
		/// <param name="value">The argument to the factorial function.</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Fact(UInt64 value, Rounding^ rounding) { mpfr_fac_ui(this->value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the logarithm of one plus the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Log1p">Log1p</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Log1p() { return Log1p(DefaultRounding); }

		/// <summary>
		/// Set the value to the logarithm of one plus the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Log1p">Log1p</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Log1p(Rounding^ rounding) { mpfr_log1p(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the exponential of the current value followed by a subtraction by one using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Expm1">Expm1</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Expm1() { return Expm1(DefaultRounding); }

		/// <summary>
		/// Set the value to the exponential of the current value followed by a subtraction by one using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Expm1">Expm1</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Expm1(Rounding^ rounding) { mpfr_expm1(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the exponential integral of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Exponential_integral">Exponential_integral</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Eint() { return Eint(DefaultRounding); }

		/// <summary>
		/// Set the value to the exponential integral of the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Exponential_integral">Exponential_integral</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Eint(Rounding^ rounding) { mpfr_eint(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the real part of the dilogarithm of the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Li2">Li2</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Li2() { return Li2(DefaultRounding); }

		/// <summary>
		/// Set the value to the real part of the dilogarithm of the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Li2">Li2</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Li2(Rounding^ rounding) { mpfr_li2(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the value of the Gamma function on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Gamma_function">Gamma_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Gamma() { return Gamma(DefaultRounding); }

		/// <summary>
		/// Set the value to the value of the Gamma function on the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Gamma_function">Gamma_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Gamma(Rounding^ rounding) { mpfr_gamma(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the value of the logarithm of the Gamma function on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Gamma_function">Power_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ LnGamma() { return LnGamma(DefaultRounding); }

		/// <summary>
		/// Set the value to the value of the logarithm of the Gamma function on the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Gamma_function">Power_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ LnGamma(Rounding^ rounding) { mpfr_lngamma(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the value of the logarithm of the absolute value of the Gamma function on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Gamma_function">Gamma_function</a> on wiki.
		/// </summary>
		/// <param name="sign">The sign of a value of the Gamma function on the current value</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ LGamma([Out] int% sign) { return LGamma(sign, DefaultRounding); }

		/// <summary>
		/// Set the value to the value of the logarithm of the absolute value of the Gamma function on the current value  using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Gamma_function">Gamma_function</a> on wiki.
		/// </summary>
		/// <param name="sign">The sign of a value of the Gamma function on the current value</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ LGamma([Out] int% sign, Rounding^ rounding) {
			int sgn = 0;
			mpfr_lgamma(value, &sgn, value, rounding);
			sign = sgn;
			return this;
		}

		/// <summary>
		/// Set the value to the value of the Digamma function on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Digamma_function">Digamma_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Digamma() { return Digamma(DefaultRounding); }

		/// <summary>
		/// Set the value to the value of the Digamma function on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Digamma_function">Digamma_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Digamma(Rounding^ rounding) { mpfr_digamma(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the value of Riemann Zeta function on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Riemann_zeta_function">Riemann_zeta_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Zeta() { return Zeta(DefaultRounding); }

		/// <summary>
		/// Set the value to the value of Riemann Zeta function on the current value using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Riemann_zeta_function">Riemann_zeta_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Zeta(Rounding^ rounding) { mpfr_zeta(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the value of Riemann Zeta function on <paramref name="value"/> using the <see cref="DefaultRounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Riemann_zeta_function">Riemann_zeta_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Zeta(UInt64 value) { return Zeta(value, DefaultRounding); }

		/// <summary>
		/// Set the value to the value of Riemann Zeta function on <paramref name="value"/> using <paramref name="rounding"/>.
		/// See also <a href="http://en.wikipedia.org/wiki/Riemann_zeta_function">Riemann_zeta_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Zeta(UInt64 value, Rounding^ rounding) { mpfr_zeta_ui(this->value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the error function on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Error_function">Error_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Erf() { return Erf(DefaultRounding); }

		/// <summary>
		/// Set the value to the error function on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Error_function">Error_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Erf(Rounding^ rounding) { mpfr_erf(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the complementary errof function on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Error_function">Error_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Erfc() { return Erfc(DefaultRounding); }

		/// <summary>
		/// Set the value to the complementary errof function on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Error_function">Error_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Erfc(Rounding^ rounding) { mpfr_erfc(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the first kind Bessel function of order 0 on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ J0() { return J0(DefaultRounding); }

		/// <summary>
		/// Set the value to the first kind Bessel function of order 0 on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ J0(Rounding^ rounding) { mpfr_j0(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the first kind Bessel function of order 1 on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ J1() { return J1(DefaultRounding); }

		/// <summary>
		/// Set the value to the first kind Bessel function of order 1 on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ J1(Rounding^ rounding) { mpfr_j1(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the first kind Bessel function of order <paramref name="n"/> on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		/// <param name="n">The order of the first kind Bessel function to compute</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Jn(Int64 n) { return Jn(n, DefaultRounding); }

		/// <summary>
		/// Set the value to the first kind Bessel function of order <paramref name="n"/> on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		/// <param name="n">The order of the first kind Bessel function to compute</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Jn(Int64 n, Rounding^ rounding) { mpfr_jn(value, n, value, rounding); return this; }

		/// <summary>
		/// Set the value to the second kind Bessel function of order 0 on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Y0() { return Y0(DefaultRounding); }

		/// <summary>
		/// Set the value to the second kind Bessel function of order 0 on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Y0(Rounding^ rounding) { mpfr_y0(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the second kind Bessel function of order 1 on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Y1() { return Y1(DefaultRounding); }

		/// <summary>
		/// Set the value to the second kind Bessel function of order 1 on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Y1(Rounding^ rounding) { mpfr_y1(value, value, rounding); return this; }

		/// <summary>
		/// Set the value to the second kind Bessel function of order <paramref name="n"/> on the current value using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		/// <param name="n">The order of the second kind Bessel function to compute</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Yn(Int64 n) { return Yn(n, DefaultRounding); }

		/// <summary>
		/// Set the value to the second kind Bessel function of order <paramref name="n"/> on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Bessel_function">Bessel_function</a> on wiki.
		/// </summary>
		/// <param name="n">The order of the second kind Bessel function to compute</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Yn(Int64 n, Rounding^ rounding) { mpfr_yn(value, n, value, rounding); return this; }

		/// <summary>
		/// Set the value to the arithmetic-geometric mean of the current value and <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Arithmetic–geometric_mean">Arithmetic–geometric_mean</a> on wiki.
		/// </summary>
		/// <param name="y">The second operand of arithmetic-geometric mean</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Agm(BigDecimal^ y) { return Agm(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the arithmetic-geometric mean of the current value and <paramref name="y"/> using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Arithmetic–geometric_mean">Arithmetic–geometric_mean</a> on wiki.
		/// </summary>
		/// <param name="y">The second operand of arithmetic-geometric mean</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Agm(BigDecimal^ y, Rounding^ rounding) { mpfr_agm(value, value, y->value, rounding); return this; }

		/// <summary>
		/// Set the value to the Euclidean norm of the current value and <paramref name="y"/> using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Euclidean_norm">Euclidean_norm</a> on wiki.
		/// </summary>
		/// <param name="y">The second operand of the Euclidian norm</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Hypot(BigDecimal^ y) { return Hypot(y, DefaultRounding); }

		/// <summary>
		/// Set the value to the Euclidean norm of the current value and <paramref name="y"/> using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Euclidean_norm">Euclidean_norm</a> on wiki.
		/// </summary>
		/// <param name="y">The second operand of the Euclidian norm</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Hypot(BigDecimal^ y, Rounding^ rounding) { mpfr_hypot(value, value, y->value, rounding); return this; }

		/// <summary>
		/// Set the value to the Airy function Ai on the current value using the <see cref="DefaultRounding"/> using the <see cref="DefaultRounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Airy_function">Airy_function</a> on wiki.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Ai() { return Ai(DefaultRounding); }

		/// <summary>
		/// Set the value to the Airy function Ai on the current value using <paramref name="rounding"/>.
		/// See also <a href="https://en.wikipedia.org/wiki/Airy_function">Airy_function</a> on wiki.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Ai(Rounding^ rounding) { mpfr_ai(value, value, rounding); return this; }
#pragma endregion
#pragma region Integer and Remainder Related Functions

		/// <summary>
		/// Round the current value using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Round() { return Round(DefaultRounding); }

		/// <summary>
		/// Round the current value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Round(Rounding^ rounding) { mpfr_rint(value, value, rounding); return this; }

		/// <summary>
		/// Round to the nearest representable value using away from zero rounding.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ RoundAfz() { mpfr_round(value, value); return this; }

		/// <summary>
		/// Round the current value to <paramref name="precision"/> in bits using the <paramref name="DefaultRounding"/>.
		/// </summary>
		/// <param name="precision">The new precision in bits</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ RoundToPrecision(UInt64 precision) { return RoundToPrecision(precision, DefaultRounding); }

		/// <summary>
		/// Round the current value to <paramref name="precision"/> in bits using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="precision">The new precision in bits</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ RoundToPrecision(UInt64 precision, Rounding^ rounding) { mpfr_prec_round(value, precision, rounding); return this; }

		/// <summary>
		/// Round to the next higher or equal representable value using using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Ceil() { return Ceil(DefaultRounding); }

		/// <summary>
		/// Round to the next higher or equal representable value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Ceil(Rounding^ rounding) { mpfr_rint_ceil(value, value, rounding); return this; }

		/// <summary>
		/// Round to the next higher or equal representable value using away from zero rounding.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ CeilAfz() { mpfr_ceil(value, value); return this; }

		/// <summary>
		/// Round to the next lower or equal representable value using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Floor() { return Floor(DefaultRounding); }

		/// <summary>
		/// Round to the next lower or equal representable value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Floor(Rounding^ rounding) { mpfr_rint_floor(value, value, rounding); return this; }

		/// <summary>
		/// Round to the next lower or equal representable value using away from zero rounding.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ FloorAfz() { mpfr_floor(value, value); return this; }

		/// <summary>
		/// Round to the next higher or equal representable value using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Trunc() { return Trunc(DefaultRounding); }

		/// <summary>
		/// Round to the next higher or equal representable value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Trunc(Rounding^ rounding) { mpfr_rint_trunc(value, value, rounding); return this; }

		/// <summary>
		/// Round to the next higher or equal representable value using away from zero rounding.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ TruncAfz() { mpfr_trunc(value, value); return this; }

		/// <summary>
		/// Set the value to the fractional part of the current value using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Frac() { return Frac(DefaultRounding); }

		/// <summary>
		/// Set the value to the fractional part of the current value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Frac(Rounding^ rounding) { mpfr_frac(value, value, rounding); return this; }

		/// <summary>
		/// Fill simultaneously <paramref name="fraction"/> with the fractional part and <paramref name="integral"/>
		/// with the integral part of the current value using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="fraction">A new instance containing only the fractional part</param>
		/// <param name="integral">A new instance containing only the integral part</param>
		/// <returns>This instance</returns>
		BigDecimal^ Modf([Out] BigDecimal^% fraction, [Out] BigDecimal^% integral) { return Modf(fraction, integral, DefaultRounding); }

		/// <summary>
		/// Fill simultaneously <paramref name="fraction"/> with the fractional par and <paramref name="integral"/>
		/// with the integral part of the current value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="fraction">A new instance containing only the fractional part</param>
		/// <param name="integral">A new instance containing only the integral part</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance</returns>
		BigDecimal^ Modf([Out] BigDecimal^% fraction, [Out] BigDecimal^% integral, Rounding^ rounding) {
			fraction = Create(Precision);
			integral = Create(Precision);
			mpfr_modf(fraction->value, integral->value, value, rounding);
			return this;
		}

		/// <summary>
		/// Set the value to <code>x % y</code> or more precisely to <code>x - n * y</code> where <code>n</code>
		/// is the integer quotient of <code>x / y</code> rounded towards zero and then rounded using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value for which to compute modulo for</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Fmod(BigDecimal^ y) { return Fmod(y, DefaultRounding); }

		/// <summary>
		/// Set the value to <code>x % y</code> or more precisely to <code>x - n * y</code> where <code>n</code>
		/// is the integer quotient of <code>x / y</code> rounded towards zero and then rounded using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value for which to compute modulo for</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Fmod(BigDecimal^ y, Rounding^ rounding) { mpfr_fmod(value, value, y->value, rounding); return this; }

		/// <summary>
		/// Set the value to <code>x % y</code> or more precisely to <code>x - n * y</code> where <code>n</code>
		/// is the integer quotient of <code>x / y</code> rounded to the nearest integer with ties to even and then rounded using the <see cref="DefaultRounding"/>.
		/// </summary>
		/// <param name="y">The value for which to compute modulo for</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Remainder(BigDecimal^ y) { return Remainder(y, DefaultRounding); }

		/// <summary>
		/// Set the value to <code>x % y</code> or more precisely to <code>x - n * y</code> where <code>n</code>
		/// is the integer quotient of <code>x / y</code> rounded to the nearest integer with ties to even and then rounded using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="y">The value for which to compute modulo for</param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Remainder(BigDecimal^ y, Rounding^ rounding) { mpfr_remainder(value, value, y->value, rounding); return this; }

		/// <summary>
		/// Set the value to <code>x % y</code> or more precisely to <code>x - n * y</code> where <code>n</code>
		/// is the integer quotient of <code>x / y</code> rounded to the nearest integer with ties to even and then rounded using the <see cref="DefaultRounding"/>.
		/// Also the low significant bits from the quotient <code>n</code> are stored in <paramref name="quotient"/>.
		/// </summary>
		/// <param name="y">The value for which to compute modulo for</param>
		/// <param name="quotient">The low significant bits of the quotient <code>n</code></param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Remquo(BigDecimal^ y, [Out] Int64 quotient) { return Remquo(y, DefaultRounding); }

		/// <summary>
		/// Set the value to <code>x % y</code> or more precisely to <code>x - n * y</code> where <code>n</code>
		/// is the integer quotient of <code>x / y</code> rounded to the nearest integer with ties to even and then rounded using <paramref name="rounding"/>.
		/// Also the low significant bits from the quotient <code>n</code> are stored in <paramref name="quotient"/>.
		/// </summary>
		/// <param name="y">The value for which to compute modulo for</param>
		/// <param name="quotient">The low significant bits of the quotient <code>n</code></param>
		/// <param name="rounding">The rounding to use</param>
		/// <returns>This instance with the result</returns>
		BigDecimal^ Remquo(BigDecimal^ y, [Out] Int64 quotient, Rounding^ rounding)
		{
			long q;
			mpfr_remquo(value, &q, value, y->value, rounding);
			quotient = q;
			return this;
		}
#pragma endregion

#pragma region Output Conversion Functions

		/// <summary>
		/// Convert this instance to a <see cref="SByte"/> value using the <see cref="DefaultRounding"/>.
		/// </summary>
		SByte ToSByte() { return ToInt64(DefaultRounding); }

		/// <summary>
		/// Convert this instance to a <see cref="SByte"/> value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		SByte ToSByte(Rounding^ rounding) { return ToInt64(rounding); }

		/// <summary>
		/// Convert this instance to a <see cref="Int16"/> value using the <see cref="DefaultRounding"/>.
		/// </summary>
		Int16 ToInt16() { return ToInt64(DefaultRounding); }

		/// <summary>
		/// Convert this instance to a <see cref="Int16"/> value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		Int16 ToInt16(Rounding^ rounding) { return ToInt64(rounding); }

		/// <summary>
		/// Convert this instance to a <see cref="Int32"/> value using the <see cref="DefaultRounding"/>.
		/// </summary>
		Int32 ToInt32() { return ToInt64(DefaultRounding); }

		/// <summary>
		/// Convert this instance to a <see cref="Int32"/> value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		Int32 ToInt32(Rounding^ rounding) { return ToInt64(rounding); }

		/// <summary>
		/// Convert this instance to a <see cref="Int64"/> value using the <see cref="DefaultRounding"/>.
		/// </summary>
		Int64 ToInt64() { return ToInt64(DefaultRounding); }

		/// <summary>
		/// Convert this instance to a <see cref="Int64"/> value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		Int64 ToInt64(Rounding^ rounding) { return mpfr_get_si(value, rounding); }

		/// <summary>
		/// Convert this instance to a <see cref="Byte"/> value using the <see cref="DefaultRounding"/>.
		/// </summary>
		UInt32 ToByte() { return ToUInt64(DefaultRounding); }

		/// <summary>
		/// Convert this instance to a <see cref="Byte"/> value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		UInt32 ToByte(Rounding^ rounding) { return ToUInt64(rounding); }

		/// <summary>
		/// Convert this instance to a <see cref="UInt16"/> value using the <see cref="DefaultRounding"/>.
		/// </summary>
		UInt32 ToUInt16() { return ToUInt64(DefaultRounding); }

		/// <summary>
		/// Convert this instance to a <see cref="UInt16"/> value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		UInt32 ToUInt16(Rounding^ rounding) { return ToUInt64(rounding); }

		/// <summary>
		/// Convert this instance to a <see cref="UInt32"/> value using the <see cref="DefaultRounding"/>.
		/// </summary>
		UInt32 ToUInt32() { return ToUInt64(DefaultRounding); }

		/// <summary>
		/// Convert this instance to a <see cref="UInt32"/> value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		UInt32 ToUInt32(Rounding^ rounding) { return ToUInt64(rounding); }

		/// <summary>
		/// Convert this instance to a <see cref="UInt64"/> value using the <see cref="DefaultRounding"/>.
		/// </summary>
		UInt64 ToUInt64() { return ToUInt64(DefaultRounding); }

		/// <summary>
		/// Convert this instance to a <see cref="UInt64"/> value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		UInt64 ToUInt64(Rounding^ rounding) { return mpfr_get_ui(value, rounding); }

		/// <summary>
		/// Convert this instance to a <see cref="Single"/> value using the <see cref="DefaultRounding"/>.
		/// </summary>
		Single ToSingle() { return ToSingle(DefaultRounding); }

		/// <summary>
		/// Convert this instance to a <see cref="Single"/> value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		Single ToSingle(Rounding^ rounding) { return mpfr_get_flt(value, rounding); }

		/// <summary>
		/// Convert this instance to a <see cref="Double"/> value using the <see cref="DefaultRounding"/>.
		/// </summary>
		Double ToDouble() { return ToDouble(DefaultRounding); }

		/// <summary>
		/// Convert this instance to a <see cref="Double"/> value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		Double ToDouble(Rounding^ rounding) { return mpfr_get_d(value, rounding); }

		/// <summary>
		/// Convert this instance to a <see cref="Decimal"/> value using the <see cref="DefaultRounding"/>.
		/// </summary>
		Decimal ToDecimal() { return ToDecimal(DefaultRounding); }

		/// <summary>
		/// Convert this instance to a <see cref="Decimal"/> value using <paramref name="rounding"/>.
		/// </summary>
		/// <param name="rounding">The rounding to use</param>
		Decimal ToDecimal(Rounding^ rounding) {
			throw gcnew NotImplementedException();
			// TODO: possible aproaches:
			// 1) get a binary representation from value and use new Decimal(...)
			// 2) get a string representation and use Decimal.Parse(...)
		}
#pragma endregion

#pragma region IConvertible
		virtual TypeCode GetTypeCode() sealed { return TypeCode::Object; }

		virtual Boolean ToBoolean(IFormatProvider^ provider) sealed { throw gcnew InvalidCastException(); }
		virtual Char ToChar(IFormatProvider^ provider) sealed { throw gcnew InvalidCastException(); }
		virtual DateTime ToDateTime(IFormatProvider^ provider) sealed { throw gcnew InvalidCastException(); }

		virtual SByte ToSByte(IFormatProvider^ provider) sealed { return ToInt64(); }
		virtual Int16 ToInt16(IFormatProvider^ provider) sealed { return ToInt64(); }
		virtual Int32 ToInt32(IFormatProvider^ provider) sealed { return ToInt64(); }
		virtual Int64 ToInt64(IFormatProvider^ provider) sealed { return ToInt64(); }
		virtual Byte ToByte(IFormatProvider^ provider) sealed { return ToUInt64(); }
		virtual UInt16 ToUInt16(IFormatProvider^ provider) sealed { return ToUInt64(); }
		virtual UInt32 ToUInt32(IFormatProvider^ provider) sealed { return ToUInt64(); }
		virtual UInt64 ToUInt64(IFormatProvider^ provider) sealed { return ToUInt64(); }
		virtual Single ToSingle(IFormatProvider^ provider) sealed { return ToSingle(); }
		virtual Double ToDouble(IFormatProvider^ provider) sealed { return ToDouble(); }
		virtual Decimal ToDecimal(IFormatProvider^ provider) sealed { return ToDecimal(); }
		virtual String^ ToString(IFormatProvider^ provider) sealed { return ToString(nullptr, provider); }

		virtual Object^ ToType(Type^ type, IFormatProvider^ provider) sealed {
			if (type == BigDecimal::typeid) return this;
			if (type == Boolean::typeid) return ToBoolean(provider);
			if (type == Char::typeid) return ToChar(provider);
			if (type == DateTime::typeid) return ToDateTime(provider);
			if (type == SByte::typeid) return ToSByte(provider);
			if (type == Int16::typeid) return ToInt16(provider);
			if (type == Int32::typeid) return ToInt32(provider);
			if (type == Int64::typeid) return ToInt64(provider);
			if (type == Byte::typeid) return ToByte(provider);
			if (type == UInt16::typeid) return ToUInt16(provider);
			if (type == UInt32::typeid) return ToUInt32(provider);
			if (type == UInt64::typeid) return ToUInt64(provider);
			if (type == Single::typeid) return ToSingle(provider);
			if (type == Double::typeid) return ToDouble(provider);
			if (type == Decimal::typeid) return ToDecimal(provider);
			if (type == String::typeid) return ToString(provider);

			throw gcnew InvalidCastException(String::Format("Unable to cast to the given type: {0}.", type));
		}
#pragma endregion
#pragma region IComparable
		virtual int CompareTo(Object^ other) {
			if (ReferenceEquals(other, nullptr)) return 1;
			if (ReferenceEquals(this, other)) return 0;

			BigDecimal^ y = dynamic_cast<BigDecimal^>(other);
			if (y != nullptr)
				return Compare(y);

			try {
				y = (BigDecimal^)Convert::ChangeType(y, BigDecimal::typeid);
				if (!ReferenceEquals(y, nullptr))
					return Compare(y);
			}
			catch (Exception^ ex) {
				throw ex;
			}

			throw gcnew ArgumentException(String::Format("The given value is not comparable: {0}.", other), "other");
		}

		virtual int CompareTo(BigDecimal^ other) {
			if (ReferenceEquals(other, nullptr)) return 1;
			if (ReferenceEquals(this, other)) return 0;

			return Compare(other);
		}
#pragma endregion
#pragma region IEquatable
		virtual bool Equals(BigDecimal^ other) {
			if (ReferenceEquals(other, nullptr)) return false;
			if (ReferenceEquals(this, other)) return true;

			return CompareTo(other) == 0;
		}
#pragma endregion

		/// <summary>
		/// A function to provide a custom operator for combining precisions.
		/// </summary>
		static property Func<BigDecimal^, BigDecimal^, UInt64>^ CombinePrecisionOperator;

		/// <summary>
		/// Clear the cache of the library. This should be called before a thread exit.
		/// </summary>
		static void ClearCache() { mpfr_free_cache(); }

#pragma region ToString
		virtual String^ ToString() override sealed { return ToString(10, nullptr, nullptr); }
		String^ ToString(String^ format) { return ToString(10, format, nullptr); }
		virtual String^ ToString(String^ format, IFormatProvider^ provider) sealed { return ToString(10, format, provider); }
		String^ ToString(int base) { return ToString(base, nullptr, nullptr); }
		String^ ToString(int base, String^ format) { return ToString(base, format, nullptr); }
		String^ ToString(int base, IFormatProvider^ provider) { return ToString(base, nullptr, provider); }
		virtual String^ ToString(int base, String^ format, IFormatProvider^ provider);
#pragma endregion
	protected:
		BigDecimal() {};

		/// <summary>
		/// Create a new instance of <see cref="BigDecimal"/> based on <paramref name="x"/>.
		/// </summary>
		/// <param name="x">The instance which provides a value and a precision</param>
		/// <returns>A new instance</returns>
		static BigDecimal^ LValue(BigDecimal^ x) { return Create(x->Precision)->Set(x); }

		/// <summary>
		/// Create a new instance of <see cref="BigDecimal"/> based on <paramref name="x"/>.
		/// The value is copied from the left operand <paramref name="x"/> and the precision is set
		/// to a combination of <paramref name="x"/> and <paramref name="y"/> using <see cref="LPrecision"/>.
		/// </summary>
		/// <param name="x">The instance which provides a value and a precision</param>
		/// <param name="x">The instance which provides a precision</param>
		/// <returns>A new instance</returns>
		static BigDecimal^ LValue(BigDecimal^ x, BigDecimal^ y) { return Create(x->Precision)->LPrecision(y)->Set(x); }

		/// <summary>
		/// Combine the current precision with that of <paramref name="y"/>.
		/// By default the highest precision is selected.
		/// You can override this behavior by setting a custom operator into <see cref="CombinePrecisionOperator"/>.
		/// </summary>
		BigDecimal^ LPrecision(BigDecimal^ y) {
			Func<BigDecimal^, BigDecimal^, UInt64>^ op = CombinePrecisionOperator;
			UInt64 precision = op != nullptr ? op(this, y) : Math::Max(Precision, y->Precision);
			return SetPrecision(precision);
		}

		/// <summary>
		/// Get the current underlying value.
		/// The value is initialized before its first use to the current <see cref="Precision"/>.
		/// </summary>
		property mpfr_ptr value {
			mpfr_ptr get() {
				if (_value == nullptr) {
					_value = new mpfr_t;
					mpfr_init2(_value, Precision);
				}
				return _value;
			}
		}

		/// <summary>
		/// The value indicating whether the current instance has been disposed.
		/// </summary>
		property bool isDisposed { bool get() { return isDisposed; }}
	private:
		static Rounding^ _defaultRounding = Rounding::NearestTiesToEven;
		static int _defaultPrecision = 53;

		int _precision = DefaultPrecision;
		mpfr_ptr _value;
		bool _isDisposed = false;
	};
}
