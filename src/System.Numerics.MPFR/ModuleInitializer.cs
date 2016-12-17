using System;
using System.Text;
using System.Runtime.InteropServices;
using System.Numerics.MPFR;

/// <summary>
/// Used by the ModuleInit. All code inside the Initialize method is ran as soon as the assembly is loaded.
/// </summary>
public static class ModuleInitializer
{
	/// <summary>
	/// Initializes the module.
	/// </summary>
	public static void Initialize()
	{
		LoadDefaultLibrary();
	}

	private static void LoadDefaultLibrary()
	{
		var shouldFreeMpfr = false;
		IntPtr mpfr = IntPtr.Zero;
		try
		{
			mpfr = LoadLibrary("libmpfr-4");
			if (mpfr == IntPtr.Zero)
			{
				Console.WriteLine("Unable to find libmpfr-4 in the default search path.");
				return;
			}
			shouldFreeMpfr = true;

			var module = GetModuleHandle("libmpfr-4");
			if (module != IntPtr.Zero)
			{
				Console.WriteLine("ModuleName:");
				var fileName = new StringBuilder(255);
				GetModuleFileName(module, fileName, fileName.Capacity);
				Console.WriteLine(fileName.ToString());
			}

			var gv = GetProcAddress(mpfr, "mpfr_get_version");
			if (gv == IntPtr.Zero)
			{
				Console.WriteLine("Unable to find mpfr_get_version in libmpfr-4 from the default search path.");
				return;
			}

			var getVersion = (mpfr_get_version)Marshal.GetDelegateForFunctionPointer(gv, typeof(mpfr_get_version));
			MPFRLibrary.Version = getVersion();
		}
		finally
		{
			if (shouldFreeMpfr && mpfr != IntPtr.Zero)
				FreeLibrary(mpfr);
		}
	}

	[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
	[return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CharPtrMarshaler))]
	private delegate string mpfr_get_version();

	[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
	private static extern IntPtr LoadLibrary(string lpFileName);

	[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
	private static extern bool FreeLibrary(IntPtr hModule);

	[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
	public static extern IntPtr GetProcAddress(IntPtr hModule, string procedureName);

	[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
	public static extern IntPtr GetModuleHandle(string lpModuleName);

	[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
	public static extern uint GetModuleFileName(IntPtr hModule, StringBuilder lpFilename, [MarshalAs(UnmanagedType.U4)]int nSize);
}