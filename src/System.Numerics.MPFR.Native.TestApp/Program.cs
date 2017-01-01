using System;

//using System.ArbitraryPrecision;
using System.ComponentModel;
using System.IO;
using System.Numerics.MPFR;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;

namespace mpfrNET.TestApp
{
	internal class Program
	{
		[System.Flags]
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

		[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
		private static extern IntPtr LoadLibrary(string lpFileName);

		[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
		private static extern IntPtr LoadLibraryEx(string lpFileName, IntPtr hReservedNull, LoadLibraryFlags dwFlags);

		[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
		private static extern bool FreeLibrary(IntPtr hModule);

		[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
		private static extern int AddDllDirectory(string lpPathName);

		[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
		public static extern bool SetDllDirectory(string lpPathName);

		static Program()
		{
			//LoadLib();
		}

		private static void LoadLib()
		{
			var libs = @"C:\libs\";
			//var path = Environment.GetEnvironmentVariable("PATH") + $";{libs}";
			//Environment.SetEnvironmentVariable("PATH", path);
			//Console.WriteLine(path);
			//if (Directory.Exists(@"c:\libs"))
			//SetDllDirectory(libs);
			//AddDllDirectory(libs);
			var lib = "libmpfr-4.dll";
			var location = Assembly.GetExecutingAssembly().Location;
			var p1 = Path.Combine(location, lib);
			try
			{
				var result = LoadLibraryEx(lib, IntPtr.Zero, 0);
				if (result == IntPtr.Zero)
					throw new Win32Exception(Marshal.GetLastWin32Error());
			}
			catch (Win32Exception ex)
			{
				Console.Write(ex);
			}
			try
			{
				var result = LoadLibraryEx(libs + lib, IntPtr.Zero, LoadLibraryFlags.LOAD_WITH_ALTERED_SEARCH_PATH);
				if (result == IntPtr.Zero)
					throw new Win32Exception(Marshal.GetLastWin32Error());
			}
			catch (Exception ex2)
			{
				Console.Write(ex2);
			}
			//Assembly.LoadFile(@"c:\libs\libmpfr-4.dll");
		}

		[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
		public static extern IntPtr GetModuleHandle(string lpModuleName);

		[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
		public static extern uint GetModuleFileName(IntPtr hModule, StringBuilder lpFilename, [MarshalAs(UnmanagedType.U4)]int nSize);

		[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Ansi)]
		public static extern IntPtr GetProcAddress(IntPtr hModule, string procedureName);

		private static void Main(string[] args)
		{
			Console.WriteLine("MAIN");

			Console.WriteLine($"{(Environment.Is64BitProcess ? "x64" : "x32")}");

			try
			{
				/*
				//BD();
				for (int i = 0; i < 5; i++)
				{
					var flt = new BigFloat("1.0");
					flt.Neg();
					Console.WriteLine(flt.ToString());
				}

				var value = new mpfr_struct();
				MPFRLibrary.mpfr_init(value);
				MPFRLibrary.mpfr_set_str(value, "10", 10, (int)Rounding.AwayFromZero);
				MPFRLibrary.mpfr_log(value, value, (int)Rounding.AwayFromZero);
				var sb = new StringBuilder(100);
				long expptr = 0;
				MPFRLibrary.mpfr_get_str(sb, ref expptr, 10, 0, value, (int)Rounding.AwayFromZero);
				Console.WriteLine(sb.ToString());

				var ve = MPFRLibrary.mpfr_get_version();
				Console.WriteLine(ve);
				*/

				var num = new BigFloat("10", precision: 100);
				num.Log();
				// Should print: 23025850929940456840179914546838
				Console.WriteLine(num.ToString("p"));
			}
			catch (DllNotFoundException ex)
			{
				Console.WriteLine(ex.Message);
			}

			/*
			var mpfr = GetModuleHandle("libmpfr-4");
			while (mpfr != IntPtr.Zero)
			{
				var fn = new StringBuilder(1024);
				GetModuleFileName(mpfr, fn, fn.Capacity);
				var path = fn.ToString();
				Console.WriteLine(path);
				FreeLibrary(mpfr);
				mpfr = GetModuleHandle("libmpfr-4");
			}
			*/
		}
		/*
		private static void BD()
		{
			try
			{
				var dec = new BigDecimal("2.1", 10, 300);
				//dec.Add(new BigDecimal("1.2", 10, 100));

				Console.WriteLine(dec);
			}
			catch (Exception ex)
			{
				Console.Write(ex);
			}
		}
		*/
	}
}