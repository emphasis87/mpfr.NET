namespace System.Numerics.MPFR
{
	public partial class MPFRLibrary
	{
		public const string FileName = "libmpfr-4";

		public const int DefaultPrecision = 53;
		public const Rounding DefaultRounding = Rounding.NearestTiesToEven;

		public static string Version { get; internal set; }
		public static string Location { get; internal set; }
	}
}