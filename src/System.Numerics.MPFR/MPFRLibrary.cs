namespace System.Numerics.MPFR
{
	public partial class MPFRLibrary
	{
		public const int DefaultPrecision = 53;
		public const Rounding DefaultRounding = Rounding.NearestTiesToEven;

		public static string Version { get; set; }
	}
}