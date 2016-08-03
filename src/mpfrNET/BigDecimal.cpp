#include "stdafx.h"
#include "BigDecimal.h"

using namespace System;
using namespace System::Globalization;
using namespace System::Runtime::InteropServices;

namespace System::ArbitraryPrecision {

#pragma region Precision

	int BigDecimal::PrecisionBits::get() {
		return _precisionBits;
	}
	void BigDecimal::PrecisionBits::set(int precisionBits) {
		_precisionBits = precisionBits;
		mpfr_set_prec(value, precisionBits);
	}
#pragma endregion

#pragma region Public Constructors

	BigDecimal::BigDecimal(Byte value, int precisionBits) : BigDecimal(precisionBits) {
		mpfr_set_ui(this->value, value, MPFR_RNDN);
	}
	BigDecimal::BigDecimal(SByte value, int precisionBits) : BigDecimal(precisionBits) {
		mpfr_set_si(this->value, value, MPFR_RNDN);
	}
	BigDecimal::BigDecimal(Int64 value, int precisionBits) : BigDecimal(precisionBits) {
		mpfr_set_si(this->value, value, MPFR_RNDN);
	}
	BigDecimal::BigDecimal(UInt64 value, int precisionBits) : BigDecimal(precisionBits) {
		mpfr_set_ui(this->value, value, MPFR_RNDN);
	}
	BigDecimal::BigDecimal(Single value, int precisionBits) : BigDecimal(precisionBits) {
		mpfr_set_flt(this->value, value, MPFR_RNDN);
	}
	BigDecimal::BigDecimal(Double value, int precisionBits) : BigDecimal(precisionBits) {
		mpfr_set_d(this->value, value, MPFR_RNDN);
	}
	BigDecimal::BigDecimal(String^ value, int base, int precisionBits) : BigDecimal(precisionBits) {
		char* cstr = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(value).ToPointer();
		mpfr_set_str(this->value, cstr, base, MPFR_RNDN);
		Marshal::FreeHGlobal((IntPtr)cstr);
	}
#pragma endregion
#pragma region NonPublic Constructors

	BigDecimal::BigDecimal()
	{
		value = new mpfr_t;
		mpfr_init(value);
	}

	BigDecimal::BigDecimal(int precisionBits) : BigDecimal()
	{
		value = new mpfr_t;
		mpfr_init2(value, precisionBits);
		_precisionBits = precisionBits;
	}
#pragma endregion
#pragma region Destructor & Finalizer

	BigDecimal::~BigDecimal()
	{
		if (isDisposed)
			return;

		this->!BigDecimal();
		isDisposed = true;
	}

	BigDecimal::!BigDecimal()
	{
		if (value != nullptr) {
			mpfr_clear(value);
			delete value;
		}
	}
#pragma endregion
#pragma region Static instances

	BigDecimal^ BigDecimal::NaN::get() {
		BigDecimal^ result = gcnew BigDecimal();
		mpfr_set_nan(result->value);
		return result;
	}

	BigDecimal^ BigDecimal::PositiveInfinity::get() {
		BigDecimal^ result = gcnew BigDecimal();
		mpfr_set_inf(result->value, +1);
		return result;
	}

	BigDecimal^ BigDecimal::NegativeInfinity::get() {
		BigDecimal^ result = gcnew BigDecimal();
		mpfr_set_inf(result->value, -1);
		return result;
	}

	BigDecimal^ BigDecimal::PositiveZero::get() {
		BigDecimal^ result = gcnew BigDecimal();
		mpfr_set_zero(result->value, +1);
		return result;
	}

	BigDecimal^ BigDecimal::NegativeZero::get() {
		BigDecimal^ result = gcnew BigDecimal();
		mpfr_set_zero(result->value, -1);
		return result;
	}

#pragma endregion

	BigDecimal^ BigDecimal::Combine(BigDecimal^ x, BigDecimal^ y) {
		int precision = Math::Max(x->PrecisionBits, y->PrecisionBits);
		return gcnew BigDecimal(precision);
	}

	BigDecimal^ BigDecimal::operator+(BigDecimal^ x, BigDecimal^ y) {
		BigDecimal^ result = Combine(x, y);
		mpfr_add(result->value, x->value, y->value, MPFR_RNDN);
		return result;
	}

#pragma region Logarithms

	BigDecimal^ BigDecimal::Log2() {
		mpfr_log2(value, value, MPFR_RNDN);
		return this;
	}

	BigDecimal^ BigDecimal::Log10() {
		mpfr_log10(value, value, MPFR_RNDN);
		return this;
	}

	BigDecimal^ BigDecimal::Ln() {
		mpfr_log(value, value, MPFR_RNDN);
		return this;
	}

#pragma endregion
#pragma region ToString
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
#pragma endregion
}
