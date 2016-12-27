# MPFR for .NET

A .NET wrapper for the GNU MPFR library

1. **Install**

    There is a nuget package available:
    
    `PM> Install-Package System.Numerics.MPFR`

    This package comes with a distribution of **libmpfr-4.dll** and its dependency **libgmp-10.dll**, both built with MSYS2/mingw64 compiler. The library **System.Numerics.MPFR.dll** which is included tries to preload those packages. Since they have to be first decompressed you will notice a few seconds pause on the first run.
    
    If you wish to compile and distribute your own libmpfr-4.dll, see [libmpfr-msys2-mingw64](https://github.com/emphasis87/libmpfr-msys2-mingw64) on github for a tutorial.

2. **Configure**

    Native dll pre-loading behavior can be configured in `System.Numerics.MPFR.Settings` configuration section in your `app.config` or `web.config`. See an example [app.config](https://github.com/emphasis87/mpfr.NET/blob/master/src/System.Numerics.MPFR/app.config).

  * [NativeLoadingPreferences](https://github.com/emphasis87/mpfr.NET/blob/master/src/System.Numerics.MPFR/NativeLoadingPreferences.cs):

    | Option            | Meaning |
    | ----------------- | ------- |
    | PreferDefault     | Prefer a library found by the default library search mechanism |
    | PreferCustom      | Prefer the library shipped internally or any other specified in settings |
    | PreferLatest      | Prefer a library with the highest version |
    | IgnoreUnversioned | Ignore any library found that does not provide its version information |
    | Disable           | Disables any strategies to distribute and load native libraries and uses the default PInvoke mechanism |

    Multiple options are comma-separated.
    <br>If both `PreferDefault` and `PreferCustom` are specified, only `PreferDefault` is used.
    <br>The default configuration is `PreferCustom,PreferLatest,IgnoreUnversioned`.
