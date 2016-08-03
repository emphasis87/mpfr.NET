#pragma once

#include "mpfr.h"
#include "gmp.h"

using namespace System;

namespace System::ArbitraryPrecision
{
	public ref class BigDecimal : IFormattable
	{
	public:

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

		virtual ~BigDecimal();
		!BigDecimal();

		static property BigDecimal^ NaN { BigDecimal^ get(); }
		static property BigDecimal^ PositiveInfinity { BigDecimal^ get(); }
		static property BigDecimal^ NegativeInfinity { BigDecimal^ get(); }
		static property BigDecimal^ PositiveZero { BigDecimal^ get(); }
		static property BigDecimal^ NegativeZero { BigDecimal^ get(); }

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

		BigDecimal^ DecreaseBy(BigDecimal^ y);
		BigDecimal^ IncreaseBy(BigDecimal^ y);
		BigDecimal^ MultiplyBy(BigDecimal^ y);
		BigDecimal^ DivideBy(BigDecimal^ y);

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
