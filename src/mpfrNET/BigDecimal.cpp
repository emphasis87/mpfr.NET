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

		mp_exp_t exp = 0;
		size_t digits = 0;
		char * str = mpfr_get_str(NULL, &exp, base, digits, value, MPFR_RNDN);
		String^ result = gcnew String(str);
		mpfr_free_str(str);

		int pos = exp + 1;
		if (pos > 0)
			result = result->Insert(exp, formatter->CurrencyDecimalSeparator);

		return result;
	}
}
