namespace System.Numerics.MPFR
{
	public partial class MPFRLibrary
	{
		public const string FileName = "libmpfr-4";

		public const int DefaultPrecision = 53;
		public const Rounding DefaultRounding = Rounding.NearestTiesToEven;

		public string Version { get; internal set; }
	}
}