#pragma once

#include "mpfr.h"
#include "gmp.h"

namespace System::ArbitraryPrecision
{
	public ref class BigDecimal
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

		virtual String^ ToString() override;
	protected:
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
