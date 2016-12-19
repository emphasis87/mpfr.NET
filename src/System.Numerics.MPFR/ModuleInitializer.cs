using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Numerics.MPFR;

/// <summary>
/// Used by the ModuleInit. All code inside the Initialize method is run as soon as the assembly is loaded.
/// </summary>
public static class ModuleInitializer
{
	private static string AssemblyLocation { get; set; }
	private static IDictionary<string, string> Libraries { get; } = new ConcurrentDictionary<string, string>();
	private static HashSet<NativeLoadingPreferences> LoadingPreferences { get; } = new HashSet<NativeLoadingPreferences>();
	private static bool PreferDefault => LoadingPreferences.Contains(NativeLoadingPreferences.PreferDefault);
	private static bool PreferCustom => LoadingPreferences.Contains(NativeLoadingPreferences.PreferCustom);
	private static bool PreferLatest => LoadingPreferences.Contains(NativeLoadingPreferences.PreferLatest);

	/// <summary>
	/// Initializes the module.
	/// </summary>
	public static void Initialize()
	{
		AssemblyLocation = Path.GetDirectoryName(typeof(ModuleInitializer).Assembly.Location);

		SetupLoadingPreferences();
		if (LoadingPreferences.Contains(NativeLoadingPreferences.Disable))
		{
			//TODO Log preference
			return;
		}

		var library = FindLibrary();
		if (library != null)
		{
			Console.WriteLine($"Using library: '{library}'");
			LoadLibraryEx(library, IntPtr.Zero, LoadLibraryFlags.LOAD_WITH_ALTERED_SEARCH_PATH);
		}
	}

	private static void SetupLoadingPreferences()
	{
		var nlp = new HashSet<string>(Enum.GetNames(typeof(NativeLoadingPreferences)));
		LoadingPreferences.UnionWith(
			Settings.Default.NativeLoadingPreferences.Split(',')
				.Select(x => x.Trim())
				.Where(x => nlp.Contains(x))
				.Select(x => (NativeLoadingPreferences)Enum.Parse(typeof(NativeLoadingPreferences), x)));

		if (LoadingPreferences.Count == 0)
			LoadingPreferences.UnionWith(new[]
			{
				NativeLoadingPreferences.PreferDefault,
				NativeLoadingPreferences.PreferLatest,
				NativeLoadingPreferences.IgnoreUnversioned
			});

		if (PreferDefault && PreferCustom)
		{
			// TODO log
			LoadingPreferences.Remove(NativeLoadingPreferences.PreferCustom);
		}

		if (!PreferDefault && !PreferCustom)
		{
			// TODO log
			LoadingPreferences.Add(NativeLoadingPreferences.PreferDefault);
		}
	}

	private static string FindLibrary()
	{
		IntPtr mpfr = GetModuleHandle(MPFRLibrary.FileName);
		if (mpfr != IntPtr.Zero)
		{
			//TODO log "nothing can be done, since it is not safe to unload"
			return null;
		}

		InstallInternalLibrary();

		var path = Environment.Is64BitProcess
			? (Settings.Default.x64_NativePath + ";x64")
			: (Settings.Default.x32_NativePath + ";x32");
		var paths = path.Split(';').Clean().Distinct()
			.Select(x => x.ResolvePath(AssemblyLocation)).ToList();

		if (PreferDefault)
			paths.Insert(0, null);
		else if (PreferCustom)
			paths.Add(null);

		if (!PreferLatest)
		{
			var first = paths.Select(PreloadLibrary).FirstOrDefault();
			return first;
		}

		var libs = paths.Select(PreloadLibrary).ToArray();
		var latest = libs.Clean()
			.OrderByDescending(x => Version.Parse(Libraries.Retrieve(x)))
			.FirstOrDefault();

		return latest;
	}

	private static string PreloadLibrary(string dir)
	{
		if (dir == null)
			return PreloadLibrary();

		var mpfr = IntPtr.Zero;
		try
		{
			var path = Path.Combine(dir, MPFRLibrary.FileName);
			mpfr = LoadLibraryEx(path, IntPtr.Zero, LoadLibraryFlags.LOAD_WITH_ALTERED_SEARCH_PATH);
			if (mpfr == IntPtr.Zero)
			{
				// TODO log
				return null;
			}

			var version = GetVersion(mpfr);
			if (LoadingPreferences.Contains(NativeLoadingPreferences.IgnoreUnversioned) && version == null)
			{
				// TODO log
				return null;
			}

			Libraries[path] = version;

			return path;
		}
		catch (Exception ex)
		{
			// TODO log
			return null;
		}
		finally
		{
			if (mpfr != IntPtr.Zero)
				FreeLibrary(mpfr);
		}
	}

	private static string PreloadLibrary()
	{
		var mpfr = IntPtr.Zero;
		try
		{
			mpfr = LoadLibrary(MPFRLibrary.FileName);
			if (mpfr == IntPtr.Zero)
			{
				// TODO log
				return null;
			}

			var version = GetVersion(mpfr);
			if (LoadingPreferences.Contains(NativeLoadingPreferences.IgnoreUnversioned) && version == null)
			{
				// TODO log
				return null;
			}

			var path = GetLocation(mpfr);
			Libraries[path] = version;

			return path;
		}
		catch (Exception ex)
		{
			// TODO log
			return null;
		}
		finally
		{
			if (mpfr != IntPtr.Zero)
				FreeLibrary(mpfr);
		}
	}

	private static string GetVersion(IntPtr mpfr)
	{
		var gvAddr = GetProcAddress(mpfr, "mpfr_get_version");
		if (gvAddr == IntPtr.Zero)
		{
			/* //TODO log
			var err = new Win32Exception(Marshal.GetLastWin32Error()).Message;
			*/
			return null;
		}

		var getVersion = (mpfr_get_version)Marshal.GetDelegateForFunctionPointer(gvAddr, typeof(mpfr_get_version));
		var version = getVersion();
		return version;
	}

	private static string GetLocation(IntPtr mpfr)
	{
		var sb = new StringBuilder(1024);
		var result = GetModuleFileName(mpfr, sb, sb.Capacity);
		return sb.ToString();
	}

	private static void InstallInternalLibrary()
	{
		var dir = Path.Combine(AssemblyLocation, Environment.Is64BitProcess ? "x64" : "x32");
		if (!Directory.Exists(dir))
			Directory.CreateDirectory(dir);

		var bytes = Environment.Is64BitProcess ? Resources.x64_libmpfr_4 : Resources.x32_libmpfr_4;
		var path = Path.Combine(dir, MPFRLibrary.FileName + ".dll");
		if (File.Exists(path))
		{
			if (new FileInfo(path).Length == bytes.Length)
				return;

			//TODO log overwrite warning
		}

		File.WriteAllBytes(path, bytes);
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

	[DllImport("kernel32.dll", ExactSpelling = true, CharSet = CharSet.Ansi, SetLastError = true)]
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