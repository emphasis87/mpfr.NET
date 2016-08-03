#include "stdafx.h"
#include "BigDecimal.h"

using namespace System;
using namespace System::Globalization;
using namespace System::Runtime::InteropServices;

namespace System::ArbitraryPrecision {

#pragma region DefaultPrecision

	UInt64 BigDecimal::DefaultPrecision::get() {
		return _defaultPrecision;
	}
	void BigDecimal::DefaultPrecision::set(UInt64 precision) {
		_defaultPrecision = precision;
		mpfr_set_default_prec(precision);
	}
#pragma endregion
#pragma region Precision

	UInt64 BigDecimal::Precision::get() {
		return _precision;
	}
	void BigDecimal::Precision::set(UInt64 precision) {
		if (_precision != precision) {
			_precision = precision;
			if (_value != nullptr)
				mpfr_set_prec(value, precision);
		}
	}
#pragma endregion
#pragma region Value
	mpfr_ptr BigDecimal::value::get() {
		if (_value == nullptr) {
			_value = new mpfr_t;
			mpfr_init2(_value, Precision);
		}
		return _value;
	}
#pragma endregion

#pragma region Public Constructors

	BigDecimal::BigDecimal(Int64 value, UInt64 precision) {
		Precision = precision;
		mpfr_set_si(this->value, value, MPFR_RNDN);
	}
	BigDecimal::BigDecimal(UInt64 value, UInt64 precision) {
		Precision = precision;
		mpfr_set_ui(this->value, value, MPFR_RNDN);
	}
	BigDecimal::BigDecimal(Single value, UInt64 precision) {
		Precision = precision;
		mpfr_set_flt(this->value, value, MPFR_RNDN);
	}
	BigDecimal::BigDecimal(Double value, UInt64 precision) {
		Precision = precision;
		mpfr_set_d(this->value, value, MPFR_RNDN);
	}
	BigDecimal::BigDecimal(String^ value, int base, UInt64 precision) {
		Precision = precision;
		char* cstr = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(value).ToPointer();
		mpfr_set_str(this->value, cstr, base, MPFR_RNDN);
		Marshal::FreeHGlobal((IntPtr)cstr);
	}
#pragma endregion
#pragma region Destructor & Finalizer

	BigDecimal::~BigDecimal()
	{
		if (!isDisposed) {
			this->!BigDecimal();
			isDisposed = true;
		}
	}

	BigDecimal::!BigDecimal()
	{
		if (_value != nullptr) {
			mpfr_clear(_value);
			delete _value;
		}
	}
#pragma endregion

	BigDecimal^ BigDecimal::Combine(BigDecimal^ x, BigDecimal^ y) {
		int precision = Math::Max(x->Precision, y->Precision);
		BigDecimal^ result = gcnew BigDecimal();
		result->Precision = precision;
		return result;
	}
#pragma region Binary Operators

	BigDecimal^ BigDecimal::operator+(BigDecimal^ x, BigDecimal^ y) {
		BigDecimal^ result = Combine(x, y);
		mpfr_add(result->value, x->value, y->value, MPFR_RNDN);
		return result;
	}

	BigDecimal^ BigDecimal::operator-(BigDecimal^ x, BigDecimal^ y) {
		BigDecimal^ result = Combine(x, y);
		mpfr_sub(result->value, x->value, y->value, MPFR_RNDN);
		return result;
	}

	BigDecimal^ BigDecimal::operator*(BigDecimal^ x, BigDecimal^ y) {
		BigDecimal^ result = Combine(x, y);
		mpfr_mul(result->value, x->value, y->value, MPFR_RNDN);
		return result;
	}

	BigDecimal^ BigDecimal::operator/(BigDecimal^ x, BigDecimal^ y) {
		BigDecimal^ result = Combine(x, y);
		mpfr_div(result->value, x->value, y->value, MPFR_RNDN);
		return result;
	}
#pragma endregion
#pragma region Unary Operators

	BigDecimal^ BigDecimal::operator++(BigDecimal^ x) {
		mpfr_add_ui(x->value, x->value, +1, MPFR_RNDN);
		return x;
	}

	BigDecimal^ BigDecimal::operator--(BigDecimal^ x) {
		mpfr_add_si(x->value, x->value, -1, MPFR_RNDN);
		return x;
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
