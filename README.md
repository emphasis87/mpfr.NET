# mpfr.NET

A .NET wrapper for the GNU MPFR library

1. **Install**

    A nuget pre-release package is planned soon.

    This assembly comes with prepackaged libmpfr-4.dll for x86 and x64 Windows OS along with all runtime dependencies based on msys2/mingw64 compiler.
    If you wish to compile and distribute your own libmpfr-4.dll, see [libmpfr-msys2-mingw64](https://github.com/emphasis87/libmpfr-msys2-mingw64) on github for a tutorial.

2. **Configure**

    Native dll pre-loading behavior can be configured in `configuration/applicationSettings/System.Numerics.MPFR.Settings` section in your `app.config` or `web.config`.
    Multiple options are comma-separated.

  * [NativeLoadingPreferences](https://github.com/emphasis87/mpfr.NET/blob/master/src/System.Numerics.MPFR/NativeLoadingPreferences.cs):

    | Option            | Meaning |
    | ----------------- | ------- |
    | PreferDefault     | Prefer a library found by the default library search mechanism |
    | PreferCustom      | Prefer the library shipped internally or any other specified in settings |
    | PreferLatest      | Prefer a library with the highest version |
    | IgnoreUnversioned | Ignore any library found that does not provide its version information |
    | Disable           | Disables any strategies to distribute and load native libraries and uses the default PInvoke mechanism |

    If both `PreferDefault` and `PreferCustom` are specified, only `PreferDefault` is used.
    <br>The default configuration is `PreferCustom,PreferLatest,IgnoreUnversioned`.
