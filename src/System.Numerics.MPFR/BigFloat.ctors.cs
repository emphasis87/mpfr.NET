using static System.Numerics.MPFR.MPFRLibrary;

namespace System.Numerics.MPFR
{
	public partial class BigFloat
	{
		/// <summary>
		/// Create a new <see cref="BigFloat"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// The <paramref name="value"/> string is expected to be in a specified <paramref name="vbase"/>.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="vbase">The expected base of the give value</param>
		/// <param name="precision">The underlying precision in bits</param>
		public BigFloat(string value, int vbase = 10, ulong? precision = null)
		{
			Initialize(precision);
			mpfr_set_str(_value, value, vbase, defaultRounding);
		}
		/*
		value, int base, UInt64 precision)
		{ SetPrecision(precision); Set(value); }

		/// <summary>
		/// Create a new <see cref="BigFloat"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		private BigFloat(Int64 value, UInt64 precision, IntPtr value1)
		{
			_value = value1;
			SetPrecision(precision); Set(value); }

		/// <summary>
		/// Create a new <see cref="BigFloat"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		private BigFloat(UInt64 value, UInt64 precision, IntPtr value1)
		{
			_value = value1;
			SetPrecision(precision); Set(value); }

		/// <summary>
		/// Create a new <see cref="BigFloat"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		private BigFloat(Single value, UInt64 precision, IntPtr value1)
		{
			_value = value1;
			SetPrecision(precision); Set(value); }

		/// <summary>
		/// Create a new <see cref="BigFloat"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		private BigFloat(Double value, UInt64 precision, IntPtr value1)
		{
			_value = value1;
			SetPrecision(precision); Set(value); }

		/// <summary>
		/// Create a new <see cref="BigFloat"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		private BigFloat(Decimal value, UInt64 precision, IntPtr value1)
		{
			_value = value1;
			SetPrecision(precision); Set(value); }
			*/
	}
}