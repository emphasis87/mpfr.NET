#include "stdafx.h"
#include "BigDecimal.h"

using namespace System;
using namespace System::Globalization;
using namespace System::Runtime::InteropServices;

namespace System::ArbitraryPrecision {

	String^ BigDecimal::ToString(int base, String^ format, IFormatProvider^ provider) {
		if (base < 2 || base > 62)
			throw gcnew ArgumentOutOfRangeException("base", "Only a base between 2 and 62 is allowed.");

		if (provider == nullptr)
			provider = CultureInfo::CurrentCulture;

		NumberFormatInfo^ formatter = NumberFormatInfo::GetInstance(provider);

		if (IsInfinity())
			return IsPositive() ? formatter->PositiveInfinitySymbol : formatter->NegativeInfinitySymbol;

		if (IsNaN())
			return formatter->NaNSymbol;

		if (IsZero())
			return IsNegative() ? "-0" : "0";

		mp_exp_t exp = 0;
		size_t digits = 0;
		char * str = mpfr_get_str(NULL, &exp, base, digits, value, MPFR_RNDN);
		String^ result = gcnew String(str);
		mpfr_free_str(str);

		result = result->TrimEnd('0');
		
		int pos = exp;
		
		if (pos <= 0) {
			if (IsNegative())
				result = result->TrimStart('-');
			result = result->PadLeft(result->Length - pos + 1, '0');
			if (IsNegative())
				result = result->Insert(0, formatter->NegativeSign);
			pos = 1 + formatter->NegativeSign->Length;
		}
		else
			pos++;

		if (IsNegative())
			pos++;

		pos--;
		if (pos > 0)
			result = result->Insert(pos, formatter->CurrencyDecimalSeparator);

		return result;
	}
}
