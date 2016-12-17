using System;
using System.Diagnostics;
using System.IO;
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

			string path = null;
			var module = GetModuleHandle("libmpfr-4");
			if (module != IntPtr.Zero)
			{
				Console.WriteLine("ModuleName:");
				var fileName = new StringBuilder(255);
				GetModuleFileName(module, fileName, fileName.Capacity);

				path = fileName.ToString();
				Console.WriteLine(path);

				if (File.Exists(path))
				{
					var version = FileVersionInfo.GetVersionInfo(path);
					if (version != null && !string.IsNullOrWhiteSpace(version.FileVersion))
						Console.WriteLine(version.FileVersion);
				}
			}

			var gv = GetProcAddress(mpfr, "mpfr_get_version");
			if (gv == IntPtr.Zero)
			{
				Console.WriteLine($"Unable to find mpfr_get_version in { path ?? "libmpfr-4 from the default search path"}.");
				return;
			}

			var getVersion = (mpfr_get_version)Marshal.GetDelegateForFunctionPointer(gv, typeof(mpfr_get_version));
			MPFRLibrary.Version = getVersion();
		}
		finally
		{
			if (shouldFreeMpfr && mpfr != IntPtr.Zero) ;
			//FreeLibrary(mpfr);
		}
	}

	[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
	[return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CStringMarshaler))]
	private delegate string mpfr_get_version();

	[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
	private static extern IntPtr LoadLibrary(string lpFileName);

	[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
	private static extern IntPtr LoadLibraryEx(string lpFileName, IntPtr hReservedNull, LoadLibraryFlags dwFlags);

	[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
	private static extern bool FreeLibrary(IntPtr hModule);

	[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
	public static extern IntPtr GetProcAddress(IntPtr hModule, string procedureName);

	[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
	public static extern IntPtr GetModuleHandle(string lpModuleName);

	[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
	public static extern uint GetModuleFileName(IntPtr hModule, StringBuilder lpFilename, [MarshalAs(UnmanagedType.U4)]int nSize);

	[Flags]
	public enum LoadLibraryFlags : uint
	{
		DONT_RESOLVE_DLL_REFERENCES = 0x00000001,
		LOAD_IGNORE_CODE_AUTHZ_LEVEL = 0x00000010,
		LOAD_LIBRARY_AS_DATAFILE = 0x00000002,
		LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE = 0x00000040,
		LOAD_LIBRARY_AS_IMAGE_RESOURCE = 0x00000020,
		LOAD_WITH_ALTERED_SEARCH_PATH = 0x00000008,
		LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR = 0x00000100,
		LOAD_LIBRARY_SEARCH_SYSTEM32 = 0x00000800,
		LOAD_LIBRARY_SEARCH_DEFAULT_DIRS = 0x00001000
	}
}