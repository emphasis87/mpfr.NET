namespace System.Numerics.MPFR
{
	public enum NativeLoadingPreferences
	{
		/// <summary>
		/// Prefer a library found by the default library search mechanism.
		/// https://msdn.microsoft.com/en-us/library/7d83bc18.aspx
		/// </summary>
		PreferDefault,

		/// <summary>
		/// Prefer the library shipped internally or any other specified in settings.
		/// </summary>
		PreferCustom,

		/// <summary>
		/// Prefer a library with the highest version.
		/// </summary>
		PreferLatest,

		/// <summary>
		/// Ignore any library found that does not provide its version information.
		/// </summary>
		IgnoreUnversioned,

		/// <summary>
		/// Disables any strategies to distribute and load native libraries and uses the default PInvoke mechanism.
		/// </summary>
		Disable,
	}
}