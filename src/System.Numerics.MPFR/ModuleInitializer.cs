using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Numerics.MPFR;
using System.Numerics.MPFR.Helpers;
using System.Numerics.MPFR.Resources;

/// <summary>
/// Used by the ModuleInit. All code inside the Initialize method is run as soon as the assembly is loaded.
/// </summary>
public static class ModuleInitializer
{
	/// <summary>
	/// Initializes the module.
	/// </summary>
	public static void Initialize()
	{
		var initializer = new PreloadingInitializer();
		initializer.Initialize();
	}

	internal class PreloadingInitializer
	{
		private string AssemblyLocation { get; set; }

		private ICollection<string> Modules { get; } = new List<string>();
		private IDictionary<string, string> Versions { get; } = new Dictionary<string, string>();

		private HashSet<NativeLoadingPreferences> LoadingPreferences { get; } = new HashSet<NativeLoadingPreferences>();
		private bool PreferDefault => LoadingPreferences.Contains(NativeLoadingPreferences.PreferDefault);
		private bool PreferCustom => LoadingPreferences.Contains(NativeLoadingPreferences.PreferCustom);
		private bool PreferLatest => LoadingPreferences.Contains(NativeLoadingPreferences.PreferLatest);
		private bool IgnoreUnversioned => LoadingPreferences.Contains(NativeLoadingPreferences.IgnoreUnversioned);
		private bool DisablePreloading => LoadingPreferences.Contains(NativeLoadingPreferences.Disable);

		public void Initialize()
		{
			AssemblyLocation = Path.GetDirectoryName(typeof(ModuleInitializer).Assembly.Location);

			SetupLoadingPreferences();
			if (DisablePreloading)
			{
				//TODO Log preference
				return;
			}

			var library = FindLibrary();
			if (library != null)
			{
				var path = Path.Combine(Path.GetDirectoryName(library), Path.GetFileNameWithoutExtension(library));
				var mpfr = LoadLibraryEx(path, IntPtr.Zero, LoadLibraryFlags.LOAD_WITH_ALTERED_SEARCH_PATH);
				if (mpfr == IntPtr.Zero)
				{
					//Console.WriteLine($"Unable to load: '{path}'");
				}

				MPFRLibrary.Version = Versions[library];
				MPFRLibrary.Location = path;
			}
		}

		private string FindLibrary()
		{
			IntPtr mpfr = GetModuleHandle(MPFRLibrary.FileName);
			if (mpfr != IntPtr.Zero)
			{
				//TODO log "nothing can be done, since it is not safe to unload"
				return null;
			}

			InstallInternalLibrary();

			var path = Environment.Is64BitProcess
				? (Settings.Default.x64_NativePath + ";mpfr_gmp/bin/x64")
				: (Settings.Default.x32_NativePath + ";mpfr_gmp/bin/x32");
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
			var module = Modules
				.OrderByDescending(x => Version.Parse(Versions[x]))
				.FirstOrDefault();

			return module;
		}

		private string PreloadLibrary(string dir)
		{
			//Console.WriteLine($"Preloading: {dir}");
			var mpfr = IntPtr.Zero;
			try
			{
				if (dir == null)
					mpfr = LoadLibrary(MPFRLibrary.FileName);
				else
					mpfr = LoadLibraryEx(Path.Combine(dir, MPFRLibrary.FileName), IntPtr.Zero, LoadLibraryFlags.LOAD_WITH_ALTERED_SEARCH_PATH);

				if (mpfr == IntPtr.Zero)
				{
					//Console.WriteLine(new Win32Exception(Marshal.GetLastWin32Error()).Message);
					// TODO log
					return null;
				}

				var path = GetLocation(mpfr);
				Modules.Add(path);

				var version = GetVersion(mpfr);
				//Console.WriteLine($" {version}");
				if (IgnoreUnversioned && version == null)
				{
					//Console.WriteLine(new Win32Exception(Marshal.GetLastWin32Error()).Message);
					return null;
				}

				Versions[path] = version;
				return path;
			}
			catch
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

		private void InstallInternalLibrary()
		{
			var dir = Path.Combine(AssemblyLocation, "mpfr_gmp/bin", Environment.Is64BitProcess ? "x64" : "x32");
			if (!Directory.Exists(dir))
				Directory.CreateDirectory(dir);

			var libs = new[] { "libgmp-10.dll", "libmpfr-4.dll" };
			var copy = libs.Any(x => !File.Exists(Path.Combine(dir, x)));
			if (!copy)
				return;

			var dec = Path.Combine(AssemblyLocation, "7zdec.exe");
			var file = Path.Combine(AssemblyLocation, "mpfr_gmp.7z");

			File.WriteAllBytes(dec, Resources._7zdec);
			File.WriteAllBytes(file, Resources.mpfr_gmp);

			var info = new ProcessStartInfo("7zdec.exe")
			{
				WorkingDirectory = AssemblyLocation,
				Arguments = "x mpfr_gmp.7z",
				WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden,
				UseShellExecute = true, 
			};
			var proc = Process.Start(info);
			proc.WaitForExit();

			File.Delete(dec);
			File.Delete(file);
		}

		private string GetVersion(IntPtr mpfr)
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

		private string GetLocation(IntPtr mpfr)
		{
			var sb = new StringBuilder(1024);
			var result = GetModuleFileName(mpfr, sb, sb.Capacity);
			return sb.ToString();
		}

		private void SetupLoadingPreferences()
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
