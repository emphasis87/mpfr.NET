namespace System.Numerics.MPFR
{
	public static class BigFloatExtensions
	{
		public static T WithPrecision<T>(this T flt, ulong precision)
			where T : BigFloat
		{
			flt.Precision = precision;
			return flt;
		}
	}
}