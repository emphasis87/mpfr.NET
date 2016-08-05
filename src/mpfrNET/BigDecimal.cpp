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
			provider = CultureInfo::InvariantCulture;

		NumberFormatInfo^ formatter = NumberFormatInfo::GetInstance(provider);

		if (mpfr_inf_p(value))
			return mpfr_sgn(value) > 0 ? formatter->PositiveInfinitySymbol : formatter->NegativeInfinitySymbol;

		if (mpfr_nan_p(value))
			return formatter->NaNSymbol;

		mp_exp_t exp = 0;
		size_t digits = 0;
		char * str = mpfr_get_str(NULL, &exp, base, digits, value, MPFR_RNDN);
		String^ result = gcnew String(str);
		mpfr_free_str(str);

		return result;
	}
}
