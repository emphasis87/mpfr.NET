# MPFR for .NET

A .NET wrapper for the GNU MPFR library

## **Install**

There is a nuget package [MPFR for .NET](https://www.nuget.org/packages/System.Numerics.MPFR) available:
    
`PM> Install-Package System.Numerics.MPFR`

This package comes with a distribution of **libmpfr-4.dll** and its dependency **libgmp-10.dll**, both built with MSYS2/mingw64 compiler. The library **System.Numerics.MPFR.dll** which is included tries to preload those packages. Since they have to be first decompressed you will notice a few seconds pause on the first run.
    
If you wish to compile and distribute your own libmpfr-4.dll, see [libmpfr-msys2-mingw64](https://github.com/emphasis87/libmpfr-msys2-mingw64) on github for a tutorial.

## **How to use**

I wanted to have the package up and running as soon as possible, so there definitely will be some bugs. Please report them, as well as any other helpful suggestions.
    
The main classes of note are:

| Class       | Description |
| ----------- | ----------- |
| MPFRLibrary | Contains calls that are merely passed to the underlying C functions |
| BigFloat    | Provides an abstraction over MPFRLibrary with initialization and cleanup of resources |

An example using MPFRLibrary:

```csharp
var value = new mpfr_struct();
MPFRLibrary.mpfr_init(value);
MPFRLibrary.mpfr_set_str(value, "10", 10, (int)Rounding.AwayFromZero);
MPFRLibrary.mpfr_log(value, value, (int)Rounding.AwayFromZero);
var sb = new StringBuilder(100);
long expptr = 0;
MPFRLibrary.mpfr_get_str(sb, ref expptr, 10, 0, value, (int)Rounding.AwayFromZero);

// Should print: 23025850929940460
Console.WriteLine(sb.ToString());
```

An example using BigFloat:

```csharp
var num = new BigFloat("10", precision: 100);
num.Log();

// Should print: 2.302585092994045684017991454683
Console.WriteLine(num.ToString("p"));
```

  1. **ToString format**

    There are multiple options which can be combined in a sequence.
    
    * **Sign option**
        <br>**Format**: `^(\^[!;_]([!;_]([!;_+-])?)?)`
        <br>**Meaning**: The sign options for positive, negative and zero values. If present it must be placed at a start of a format string. The groups are in order for positive, negative and zero values where `!`, `;`, `_`, `+`, `-` denote always, default, none, positive sign and negative sign.
    
        ```csharp
        new BigFloat("1").ToString("^!") // +0.1E+1
        new BigFloat("-1").ToString("^;_") // 0.1E+1
        new BigFloat("0").ToString("^;;!") // +0.0E+0 or -0.0E+0 based on IsNegative()
        new BigFloat("0").ToString("^;;-") // -0.0E+0
        ```
  
    * **Base option**
        <br>**Format**: `b[0-9]+`
        <br>**Meaning**: The base of the result. Only values from 2 to 62 are allowed.

        ```csharp
        new BigFloat("7").ToString("b2") // 0.111E+3
        new BigFloat("-31").ToString("b16") // -0.1F@+2
        ```
    
    * **Digits option**
        <br>**Format**: `d[0-9]+`
        <br>**Meaning**: The number of significant digits of the result. The value 0 denotes a full precision.

        ```csharp
        new BigFloat("123").ToString("d2") // 0.12E+3
        ```
  
    * **Positional option**
        <br>**Format**: 
        ```
        p
        (?<fixedPrefix>[0-9]*)?
        (?<fixedSuffix>\.[0-9]*)?
        (?<optionalSuffix>\#[0-9]*)?
        (
            (?<comparison>([<>]=|=|[<>])[+-]?[0-9]+) |
            (\((?<interval>[+-]?[0-9]+[,;][+-]?[0-9]+)\))
        )*
        ```
        <br>**Meaning**: Prints the result in a positional formatting. Prefix and suffix groups determine a number of fixed or optional digits. A standalone `.` uses a number of digits from a given `IFormatProvider`, `#` ensures that significant digits are not trimmed. The comparison groups (eg. `=0`) and iterval groups (eg. `(-1;1)`) identify exponents to which this formatting applies.

        ```csharp
        new BigFloat("10.23").ToString("p") // 10.23
        new BigFloat("10.23").ToString("p3") // 010
        new BigFloat("10.2345").ToString("p.") // 10.23 based on the IFormatProvider
        new BigFloat("10.2345").ToString("p3#") // 010.2345
        new BigFloat("10.2").ToString("p.2#") // 10.20
        new BigFloat("10.2345").ToString("p.2#") // 10.2345
        new BigFloat("0.1").ToString("p=0") // 0.1 applies for the exponent 0
        new BigFloat("0.1").ToString("p=1") // 0.1E+0 does not apply
        new BigFloat("0.01").ToString("p=2<=0") // 0.01 applies for the exponent -1
        new BigFloat("0.1").ToString("p(-1;1") // 0.1 applies for the exponent 0
        ```
    
    * **Exponential option**
        <br>**Format**:
        ```
        [eE@]
        (?<fixedLength>[0-9]+)?
        (\^(?<sign>[!;_]([!;_]([!;_+-])?)?))?
        (
            (?<comparison>([<>]=|=|[<>])[+-]?[0-9]+) |
            (\((?<interval>[+-]?[0-9]+[,;][+-]?[0-9]+)\))
        )*
        ```
        <br>**Meaning**: Prints the result in a scientific formatting. The first character is used as an exponent mark up to the base 10, otherwise `@` is used. The fixedLength group determines a minimal length of the exponent part. The sign group has the same behavior as for the whole number. Identically as with positional option, the groups comparison and interval identify exponents to which this formatting applies.

        ```csharp
        new BigFloat("10.23").ToString("e2") // 0.1023e+02
        new BigFloat("1").ToString("b16e") // 0.1@+1
        new BigFloat("0.1").ToString("E^;;_") // 0.1E0
        new BigFloat("10.23").ToString("E=2") // 0.1023E+2 applies for the exponent 2
        new BigFloat("10.23").ToString("e>1") // 0.1023e+2 applies for the exponent 2
        new BigFloat("0.1").ToString("e>1") // 0.1 does not apply for the exponent 0
        new BigFloat("0.1").ToString("@(-1,1)") // 0.1@+0 applies for the exponent 0
        ```
    
## **Configure**

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
