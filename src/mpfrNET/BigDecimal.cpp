#include "stdafx.h"
#include "BigDecimal.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace System::ArbitraryPrecision {

	int BigDecimal::PrecisionBits::get() {
		return _precisionBits;
	}
	void BigDecimal::PrecisionBits::set(int precisionBits) {
		_precisionBits = precisionBits;
		mpfr_set_prec(value, precisionBits);
	}

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

	BigDecimal::BigDecimal(int precisionBits)
	{
		value = (mpfr_ptr)malloc(sizeof(__mpfr_struct));
		value->_mpfr_d = new mp_limb_t;
		mpfr_init2(value, precisionBits);
		_precisionBits = precisionBits;
	}

	BigDecimal::~BigDecimal()
	{
		if (isDisposed)
			return;

		this->!BigDecimal();
		isDisposed = true;
	}

	BigDecimal::!BigDecimal()
	{
		if (value != nullptr)
			mpfr_clear(value);
	}

	BigDecimal^ BigDecimal::Combine(BigDecimal^ x, BigDecimal^ y) {
		int precision = Math::Max(x->PrecisionBits, y->PrecisionBits);
		return gcnew BigDecimal(precision);
	}

	BigDecimal^ BigDecimal::operator+(BigDecimal^ x, BigDecimal^ y) {
		BigDecimal^ result = Combine(x, y);
		mpfr_add(result->value, x->value, y->value, MPFR_RNDN);
		return result;
	}

	String^ BigDecimal::ToString() {
		mp_exp_t exp = 0;
		int base = 10;
		size_t digits = 0;
		char * str = mpfr_get_str(NULL, &exp, base, digits, value, MPFR_RNDN);
		String^ result = gcnew String(str);
		mpfr_free_str(str);
		return result;
	}
}
