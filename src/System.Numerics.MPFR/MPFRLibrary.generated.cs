using System.Text;
using System.Runtime.InteropServices;

namespace System.Numerics.MPFR
{
	public partial class MPFRLibrary
	{
		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_init2([In, Out] mpfr_struct x, ulong prec);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_inits2(ulong prec, [In, Out] mpfr_struct x, IntPtr args);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_clear([In, Out] mpfr_struct x);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_clears([In, Out] mpfr_struct x, IntPtr args);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_init([In, Out] mpfr_struct x);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_inits([In, Out] mpfr_struct x, IntPtr args);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_set_default_prec(ulong prec);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern ulong mpfr_get_default_prec();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_set_prec([In, Out] mpfr_struct x, ulong prec);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern ulong mpfr_get_prec([In, Out] mpfr_struct x);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_set([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_set_ui([In, Out] mpfr_struct rop, ulong op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_set_si([In, Out] mpfr_struct rop, long op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_set_flt([In, Out] mpfr_struct rop, float op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_set_d([In, Out] mpfr_struct rop, double op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_set_ui_2exp([In, Out] mpfr_struct rop, ulong op, long e, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_set_si_2exp([In, Out] mpfr_struct rop, long op, long e, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_set_str([In, Out] mpfr_struct rop, string s, int sbase, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_set_nan([In, Out] mpfr_struct x);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_set_inf([In, Out] mpfr_struct x, int sign);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_set_zero([In, Out] mpfr_struct x, int sign);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_swap([In, Out] mpfr_struct x, [In, Out] mpfr_struct y);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_init_set_str([In, Out] mpfr_struct x, string s, int sbase, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern float mpfr_get_flt([In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern double mpfr_get_d([In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern long mpfr_get_si([In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern ulong mpfr_get_ui([In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern double mpfr_get_d_2exp(ref long exp, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_frexp(ref long exp, [In, Out] mpfr_struct y, [In, Out] mpfr_struct x, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CStringMarshaler))]
		public static extern string mpfr_get_str(StringBuilder str, ref long expptr, int b, uint n, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_free_str(StringBuilder str);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_fits_ulong_p([In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_fits_slong_p([In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_fits_uint_p([In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_fits_sint_p([In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_fits_ushort_p([In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_fits_sshort_p([In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_fits_uintmax_p([In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_fits_intmax_p([In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_add([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_add_ui([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, ulong op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_add_si([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, long op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_add_d([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, double op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_sub([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_ui_sub([In, Out] mpfr_struct rop, ulong op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_sub_ui([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, ulong op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_si_sub([In, Out] mpfr_struct rop, long op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_sub_si([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, long op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_d_sub([In, Out] mpfr_struct rop, double op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_sub_d([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, double op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_mul([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_mul_ui([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, ulong op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_mul_si([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, long op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_mul_d([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, double op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_sqr([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_div([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_ui_div([In, Out] mpfr_struct rop, ulong op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_div_ui([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, ulong op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_si_div([In, Out] mpfr_struct rop, long op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_div_si([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, long op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_d_div([In, Out] mpfr_struct rop, double op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_div_d([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, double op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_sqrt([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_sqrt_ui([In, Out] mpfr_struct rop, ulong op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_rec_sqrt([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_cbrt([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_root([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, ulong k, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_pow([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_pow_ui([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, ulong op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_pow_si([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, long op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_ui_pow_ui([In, Out] mpfr_struct rop, ulong op1, ulong op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_ui_pow([In, Out] mpfr_struct rop, ulong op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_neg([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_abs([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_dim([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_mul_2ui([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, ulong op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_mul_2si([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, long op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_div_2ui([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, ulong op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_div_2si([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, long op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_cmp([In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_cmp_ui([In, Out] mpfr_struct op1, ulong op2);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_cmp_si([In, Out] mpfr_struct op1, long op2);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_cmp_d([In, Out] mpfr_struct op1, double op2);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_cmp_ui_2exp([In, Out] mpfr_struct op1, ulong op2, long e);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_cmp_si_2exp([In, Out] mpfr_struct op1, long op2, long e);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_cmpabs([In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_nan_p([In, Out] mpfr_struct op);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_inf_p([In, Out] mpfr_struct op);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_number_p([In, Out] mpfr_struct op);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_zero_p([In, Out] mpfr_struct op);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_regular_p([In, Out] mpfr_struct op);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_greater_p([In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_greaterequal_p([In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_less_p([In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_lessequal_p([In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_equal_p([In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_lessgreater_p([In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_unordered_p([In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_log([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_log2([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_log10([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_exp([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_exp2([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_exp10([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_cos([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_sin([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_tan([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_sin_cos([In, Out] mpfr_struct sop, [In, Out] mpfr_struct cop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_sec([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_csc([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_cot([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_acos([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_asin([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_atan([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_atan2([In, Out] mpfr_struct rop, [In, Out] mpfr_struct y, [In, Out] mpfr_struct x, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_cosh([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_sinh([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_tanh([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_sinh_cosh([In, Out] mpfr_struct sop, [In, Out] mpfr_struct cop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_sech([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_csch([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_coth([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_acosh([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_asinh([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_atanh([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_fac_ui([In, Out] mpfr_struct rop, ulong op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_log1p([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_expm1([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_eint([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_li2([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_gamma([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_lngamma([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_lgamma([In, Out] mpfr_struct rop, ref int signp, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_digamma([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_zeta([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_zeta_ui([In, Out] mpfr_struct rop, ulong op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_erf([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_erfc([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_j0([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_j1([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_jn([In, Out] mpfr_struct rop, long n, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_y0([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_y1([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_yn([In, Out] mpfr_struct rop, long n, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_fma([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2, [In, Out] mpfr_struct op3, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_fms([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2, [In, Out] mpfr_struct op3, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_agm([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_hypot([In, Out] mpfr_struct rop, [In, Out] mpfr_struct x, [In, Out] mpfr_struct y, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_ai([In, Out] mpfr_struct rop, [In, Out] mpfr_struct x, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_const_log2([In, Out] mpfr_struct rop, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_const_pi([In, Out] mpfr_struct rop, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_const_euler([In, Out] mpfr_struct rop, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_const_catalan([In, Out] mpfr_struct rop, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_free_cache();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_sum([In, Out] mpfr_struct rop, IntPtr[] tab, ulong n, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_printf(string template, IntPtr args);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_vprintf(string template, IntPtr ap);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_sprintf(StringBuilder buf, string template, IntPtr args);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_vsprintf(StringBuilder buf, string template, IntPtr ap);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_snprintf(StringBuilder buf, uint n, string template, IntPtr args);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_vsnprintf(StringBuilder buf, uint n, string template, IntPtr ap);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_rint([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_ceil([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_floor([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_round([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_trunc([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_rint_ceil([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_rint_floor([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_rint_round([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_rint_trunc([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_frac([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_modf([In, Out] mpfr_struct iop, [In, Out] mpfr_struct fop, [In, Out] mpfr_struct op, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_fmod([In, Out] mpfr_struct r, [In, Out] mpfr_struct x, [In, Out] mpfr_struct y, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_remainder([In, Out] mpfr_struct r, [In, Out] mpfr_struct x, [In, Out] mpfr_struct y, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_remquo([In, Out] mpfr_struct r, ref long q, [In, Out] mpfr_struct x, [In, Out] mpfr_struct y, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_integer_p([In, Out] mpfr_struct op);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_set_default_rounding_mode(int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_get_default_rounding_mode();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_prec_round([In, Out] mpfr_struct x, ulong prec, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_can_round([In, Out] mpfr_struct b, long err, int rnd1, int rnd2, ulong prec);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern ulong mpfr_min_prec([In, Out] mpfr_struct x);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CStringMarshaler))]
		public static extern string mpfr_print_rnd_mode(int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_nexttoward([In, Out] mpfr_struct x, [In, Out] mpfr_struct y);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_nextabove([In, Out] mpfr_struct x);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_nextbelow([In, Out] mpfr_struct x);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_min([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_max([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern long mpfr_get_exp([In, Out] mpfr_struct x);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_set_exp([In, Out] mpfr_struct x, long e);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_signbit([In, Out] mpfr_struct op);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_setsign([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op, int s, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_copysign([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CStringMarshaler))]
		public static extern string mpfr_get_version();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CStringMarshaler))]
		public static extern string mpfr_get_patches();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_buildopt_tls_p();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_buildopt_decimal_p();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CStringMarshaler))]
		public static extern string mpfr_buildopt_tune_case();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern long mpfr_get_emin();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern long mpfr_get_emax();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_set_emin(long exp);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_set_emax(long exp);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern long mpfr_get_emin_min();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern long mpfr_get_emin_max();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern long mpfr_get_emax_min();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern long mpfr_get_emax_max();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_check_range([In, Out] mpfr_struct x, int t, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_subnormalize([In, Out] mpfr_struct x, int t, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_clear_underflow();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_clear_overflow();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_clear_divby0();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_clear_nanflag();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_clear_inexflag();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_clear_erangeflag();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_set_underflow();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_set_overflow();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_set_divby0();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_set_nanflag();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_set_inexflag();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_set_erangeflag();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_clear_flags();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_underflow_p();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_overflow_p();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_divby0_p();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_nanflag_p();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_inexflag_p();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_erangeflag_p();

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_set_prec_raw([In, Out] mpfr_struct x, ulong prec);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_eq([In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2, ulong op3);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_reldiff([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, [In, Out] mpfr_struct op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_mul_2exp([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, ulong op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_div_2exp([In, Out] mpfr_struct rop, [In, Out] mpfr_struct op1, ulong op2, int rnd);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern uint mpfr_custom_get_size(ulong prec);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_custom_init(IntPtr significand, ulong prec);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_custom_init_set([In, Out] mpfr_struct x, int kind, long exp, ulong prec, IntPtr significand);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern int mpfr_custom_get_kind([In, Out] mpfr_struct x);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr mpfr_custom_get_significand([In, Out] mpfr_struct x);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern long mpfr_custom_get_exp([In, Out] mpfr_struct x);

		[DllImport(FileName, CallingConvention = CallingConvention.Cdecl)]
		public static extern void mpfr_custom_move([In, Out] mpfr_struct x, IntPtr new_position);

	}
}