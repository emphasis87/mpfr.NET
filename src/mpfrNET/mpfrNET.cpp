// This is the main DLL file.

#include "stdafx.h"
#include <stdio.h>

#include "mpfrNET.h"

void System::ArbitraryPrecision::Mpfr::Print()
{
	mpfr_t x;
	int value = 2;
	int bit_precision = 200;
	int base = 10;
	size_t digits = 0;
	mp_exp_t exp = 0;

	mpfr_init2(x, bit_precision);
	mpfr_set_d(x, value, MPFR_RNDN);
	mpfr_log(x, x, MPFR_RNDN);
	char * str = mpfr_get_str(NULL, &exp, base, digits, x, MPFR_RNDN);
	String^ result = gcnew String(str);
	mpfr_free_str(str);
	mpfr_clear(x);

	Console::WriteLine("cli: val: " + result);
	Console::WriteLine("cli: exp: " + exp);
}