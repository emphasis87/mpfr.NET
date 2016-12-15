namespace System.Numerics.MPFR
{
	public enum Rounding
	{
		NearestTiesToEven = 0,
		TowardsZero = 1,
		TowardsPlusInfinity = 2,
		TowardsMinusInfinity = 3,
		AwayFromZero = 4,
		Faithful = 5,
		NearestTiesAwayFromZero = -1,
	}
}