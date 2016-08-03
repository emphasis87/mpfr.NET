#pragma once

#include "mpfr.h"
#include "gmp.h"

using namespace System;

namespace System::ArbitraryPrecision
{
	public ref class BigDecimal : IFormattable
	{
	public:
		BigDecimal(Byte value, int precisionBits);
		BigDecimal(SByte value, int precisionBits);
		BigDecimal(Int16 value, int precisionBits) : BigDecimal((Int64)value, precisionBits) {};
		BigDecimal(Int32 value, int precisionBits) : BigDecimal((Int64)value, precisionBits) {};
		BigDecimal(Int64 value, int precisionBits);
		BigDecimal(UInt16 value, int precisionBits) : BigDecimal((UInt64)value, precisionBits) {};
		BigDecimal(UInt32 value, int precisionBits) : BigDecimal((UInt64)value, precisionBits) {};
		BigDecimal(UInt64 value, int precisionBits);
		BigDecimal(Single value, int precisionBits);
		BigDecimal(Double value, int precisionBits);
		BigDecimal(Decimal value, int precisionBits) : BigDecimal(value.ToString(), precisionBits) {};
		BigDecimal(String^ value, int precisionBits) : BigDecimal(value, 10, precisionBits) {};
		BigDecimal(String^ value, int base, int precisionBits);

		virtual ~BigDecimal();
		!BigDecimal();

		static property BigDecimal^ NaN { BigDecimal^ get(); }
		static property BigDecimal^ PositiveInfinity { BigDecimal^ get(); }
		static property BigDecimal^ NegativeInfinity { BigDecimal^ get(); }
		static property BigDecimal^ PositiveZero { BigDecimal^ get(); }
		static property BigDecimal^ NegativeZero { BigDecimal^ get(); }

		/// <summary>
		/// The precision of the underlying number in bits. 
		/// </summary>
		property int PrecisionBits { int get(); void set(int); }

		//BigDecimal^ operator -(BigDecimal^ y);
		static BigDecimal^ operator +(BigDecimal^ x, BigDecimal^ y);
		/*BigDecimal^ operator *(BigDecimal^ y);
		BigDecimal^ operator /(BigDecimal^ y);
		BigDecimal^ operator ++(int i);
		BigDecimal^ operator --(int i);

		BigDecimal Decrease(BigDecimal y);
		BigDecimal Increase(BigDecimal y);
		BigDecimal Multiply(BigDecimal y);
		BigDecimal Divide(BigDecimal y);*/

		BigDecimal^ Log2();
		BigDecimal^ Log10();
		BigDecimal^ Ln();

		virtual String^ ToString() override { return ToString(10, nullptr, nullptr); }
		virtual String^ ToString(String^ format) { return ToString(10, format, nullptr); }
		virtual String^ ToString(IFormatProvider^ provider) { return ToString(10, nullptr, provider); }
		virtual String^ ToString(String^ format, IFormatProvider^ provider) { return ToString(10, format, provider); }
		virtual String^ ToString(int base) { return ToString(base, nullptr, nullptr); }
		virtual String^ ToString(int base, String^ format) { return ToString(base, format, nullptr); }
		virtual String^ ToString(int base, IFormatProvider^ provider) { return ToString(base, nullptr, provider); }
		virtual String^ ToString(int base, String^ format, IFormatProvider^ provider);
	protected:
		/// <summary>
		/// A number with an arbitrary precision.
		/// </summary>
		BigDecimal();

		/// <summary>
		/// A number with an arbitrary precision.
		/// </summary>
		/// <param name="precisionBits">The precision of the underlying number in bits.</param>
		BigDecimal(int precisionBits);

		static BigDecimal^ Combine(BigDecimal^ x, BigDecimal^ y);

		bool isDisposed = false;
		mpfr_ptr value;
	private:
		int _precisionBits;
		bool _hasValue = false;
	};
}
