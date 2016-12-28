using System.Globalization;
using System.Numerics.MPFR.Helpers;
using System.Text;
using System.Text.RegularExpressions;
using static System.Numerics.MPFR.MPFRLibrary;

// ReSharper disable InconsistentNaming

namespace System.Numerics.MPFR
{
	public partial class BigFloat : IDisposable, IFormattable
	{
		static BigFloat()
		{
			mpfr_set_default_rounding_mode(defaultRounding);
			mpfr_set_default_prec(defaultPrecision);
		}

		public static int GetRounding(Rounding? rounding = null) => rounding.HasValue ? (int)rounding.Value : defaultRounding;

		#region DefaultPrecision
		protected static ulong defaultPrecision = MPFRLibrary.DefaultPrecision;

		/// <summary>
		/// The default precision in bits used to initialize a new <see cref="BigFloat"/> if otherwise not specified.
		/// </summary>
		public static ulong DefaultPrecision
		{
			get { return defaultPrecision; }
			set
			{
				mpfr_set_default_prec(value);
				defaultPrecision = value;
			}
		}
		#endregion
		#region DefaultRounding
		protected static int defaultRounding = (int)MPFRLibrary.DefaultRounding;

		/// <summary>
		/// The default halfway rounding method used if not otherwise specified.
		/// </summary>
		public static Rounding DefaultRounding
		{
			get { return (Rounding)defaultRounding; }
			set
			{
				var rnd = (int)value;
				mpfr_set_default_rounding_mode(rnd);
				defaultRounding = rnd;
			}
		}
		#endregion

		private mpfr_struct _value;
		public mpfr_struct Value => _value;

		#region Precision
		private ulong _precision = DefaultPrecision;

		/// <summary>
		/// The precision of the underlying number in bits.
		/// Note that setting this will erase the current value of this instance.
		/// </summary>
		public ulong Precision
		{
			get { return _precision; }
			set
			{
				if (_precision != value)
				{
					_precision = value;
					if (_value != null)
						mpfr_set_prec(_value, value);
				}
			}
		}
		#endregion

		#region Constructors
		/// <summary>
		/// Create a new <see cref="BigFloat"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// The <paramref name="value"/> string is expected to be in a specified <paramref name="vbase"/>.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="vbase">The expected base of the give value</param>
		/// <param name="precision">The underlying precision in bits</param>
		/// <param name="rounding">The rounding used during <paramref name="value"/> initialization</param>
		public BigFloat(string value, int vbase = 10, ulong? precision = null, Rounding? rounding = null)
		{
			Initialize(precision);
			Set(this, value, vbase, rounding);
		}

		/// <summary>
		/// Create a new <see cref="BigFloat"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		/// <param name="rounding">The rounding used during <paramref name="value"/> initialization</param>
		public BigFloat(long value, ulong precision, Rounding? rounding = null)
		{
			Initialize(precision);
			Set(this, value, rounding);
		}

		/// <summary>
		/// Create a new <see cref="BigFloat"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		/// <param name="rounding">The rounding used during <paramref name="value"/> initialization</param>
		public BigFloat(ulong value, ulong precision, Rounding? rounding = null)
		{
			Initialize(precision);
			Set(this, value, rounding);
		}

		/// <summary>
		/// Create a new <see cref="BigFloat"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		/// <param name="rounding">The rounding used during <paramref name="value"/> initialization</param>
		public BigFloat(float value, ulong precision, Rounding? rounding = null)
		{
			Initialize(precision);
			Set(this, value, rounding);
		}

		/// <summary>
		/// Create a new <see cref="BigFloat"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		/// <param name="rounding">The rounding used during <paramref name="value"/> initialization</param>
		public BigFloat(double value, ulong precision, Rounding? rounding = null)
		{
			Initialize(precision);
			Set(this, value, rounding);
		}

		/// <summary>
		/// Create a new <see cref="BigFloat"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		/// <param name="rounding">The rounding used during <paramref name="value"/> initialization</param>
		public BigFloat(decimal value, ulong precision, Rounding? rounding = null)
		{
			Initialize(precision);
			Set(this, value.ToString(CultureInfo.InvariantCulture), 10, rounding);
		}
		#endregion

		protected void Initialize(ulong? precision = null)
		{
			var v = new mpfr_struct();
			mpfr_init2(v, precision ?? Precision);
			_value = v;
		}

		#region Dispose
		private bool _disposed;

		protected virtual void Dispose(bool disposing)
		{
			if (_disposed)
				return;

			if (_value != null)
				mpfr_clear(_value);

			_disposed = true;
		}

		public void Dispose()
		{
			Dispose(true);
			GC.SuppressFinalize(this);
		}

		~BigFloat()
		{
			Dispose(false);
		}
		#endregion

		internal static readonly Regex formatPattern = new Regex(
			@"(?:
				(?<base>b[1-9][0-9]*)() |
				(?<digits>d[1-9][0-9]*)() |
				(?<point>\\.)()
			){3}
			\1\2\3",
			RegexOptions.Compiled | RegexOptions.IgnorePatternWhitespace);

		public string ToString(string format, IFormatProvider formatProvider)
		{
			format = format.AtLeast("b10d");
			formatProvider = formatProvider ?? NumberFormatInfo.CurrentInfo;

			var m = formatPattern.Match(format);
			if (!m.Success)
				throw new FormatException($"The format '{format}' is not supported.");

			var sbase = m.Groups["base"].Success ? int.Parse(m.Groups["base"].Value.Substring(1)) : 10;
			if (sbase > 62)
				throw new FormatException($"The base of {sbase} is not a supported format.");

			var digits = m.Groups["digits"].Success ? uint.Parse(m.Groups["digits"].Value.Substring(1)) : 0;
			if (digits < 2)
				throw new FormatException($"The number of digits {sbase} is not a supported format.");

			var capacity = digits == 0
				? (int)(Precision / Math.Ceiling((double)2 / sbase) + 8)
				: (int)Math.Max(digits + 2, 7);

			var sb = new StringBuilder(capacity);
			long exp = 0;
			mpfr_get_str(sb, ref exp, sbase, digits, _value, GetRounding());
			return sb.ToString();
		}

		public override string ToString() => ToString(null, null);
	}
}