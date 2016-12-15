using static System.Numerics.MPFR.MPFRLibrary;

namespace System.Numerics.MPFR
{
	public partial class BigFloat
	{
		public BigFloat Neg(Rounding? rounding = null)
		{
			mpfr_neg(_value, _value, GetRounding(rounding));
			return this;
		}
	}
}