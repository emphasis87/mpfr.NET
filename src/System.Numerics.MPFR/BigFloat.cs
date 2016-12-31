using System.Collections.Generic;
using System.Globalization;
using System.Linq;
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
		public BigFloat(int value, ulong? precision = null, Rounding? rounding = null)
			: this((long)value, precision, rounding) { }

		/// <summary>
		/// Create a new <see cref="BigFloat"/> instance with a given <paramref name="value"/> and a <paramref name="precision"/> in bits.
		/// </summary>
		/// <param name="value">The underlying value</param>
		/// <param name="precision">The underlying precision in bits</param>
		/// <param name="rounding">The rounding used during <paramref name="value"/> initialization</param>
		public BigFloat(long value, ulong? precision = null, Rounding? rounding = null)
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
		public BigFloat(ulong value, ulong? precision = null, Rounding? rounding = null)
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
		public BigFloat(float value, ulong? precision = null, Rounding? rounding = null)
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
		public BigFloat(double value, ulong? precision = null, Rounding? rounding = null)
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

		#region Functions

		public static bool IsPositive(BigFloat op) => op?.IsPositive() ?? false;
		public static bool IsNegative(BigFloat op) => op?.IsNegative() ?? false;

		public bool IsPositive() => !IsNegative();
		public bool IsNegative() => SignBit() != 0 && !IsNan();

		#endregion

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

		#region ToString
		private static readonly Regex notDigitPattern = new Regex("^([^0-9]*)", RegexOptions.Compiled);
		private static readonly Regex lastZerosPattern = new Regex("0*$", RegexOptions.Compiled);
		private static readonly Regex formatPattern = new Regex(@"
			(?<sign>^[^][!;_][!;_][!;_+-]) |
			(?<base>b[0-9]+) |
			(?<digits>d[0-9]+) |
			(?<positional>p
				(?<p_fixedPrefix>[0-9]*)?
				([.]
					(?<p_fixedSuffix>[0-9]*)?
					([#](?<p_optionalSuffix>[0-9]*)?)?
				)?
				(
					(?<p_comparison>[<>]?[=]?[+-]?[0-9]+) |
					(?<p_interval>[(][+-]?[0-9]+;[+-]?[0-9]+[)])
				)*
			) |
			(?<exponent>[eE]
				([^](?<e_sign>[!;][!;][!;_+-])?
				(?<e_fixedLength>[0-9]*)?
				(
					(?<e_comparison>[<>]?[=]?[+-]?[0-9]+) |
					([(](?<e_interval>[+-]?[0-9]+;[+-]?[0-9]+)[)])
				)*
			) |
			(?<unchanged>u) ",
			RegexOptions.Compiled | RegexOptions.IgnorePatternWhitespace);

		public string ToString(string format, IFormatProvider formatProvider = null)
		{
			format = format.Collapse();
			formatProvider = formatProvider ?? CultureInfo.CurrentUICulture;

			SignOptions sign = null;
			var sbase = 10;
			uint digits = 0;
			PositionalDecimalOptions positionalDecimal = null;
			ExponentialDecimalOptions exponentialDecimal = null;
			var unchanged = false;

			if (!format.IsVoid())
			{
				var options = new HashSet<char>();
				var m = formatPattern.Match(format);
				var pos = 0;
				while (m.Success)
				{
					var capture = m.Captures[0].Value;
					var optval = capture.Substring(1);
					var opt = capture[0];
					switch (opt)
					{
						case '^':
							sign = new SignOptions(optval);
							break;

						case 'b':
							if (!int.TryParse(optval, out sbase) || sbase < 2 || sbase > 62)
								throw new FormatException($"A format with the base '{sbase}' is not supported. Use a number between 2 and 62.");
							break;

						case 'd':
							if (!uint.TryParse(optval, out digits) || (digits < 2 && digits != 0))
								throw new FormatException(
									$"A format with the number of digits '{sbase}' is not supported. Use a number greater than 2 or 0.");
							break;

						case 'p':
							positionalDecimal = new PositionalDecimalOptions(m);
							break;

						case '@':
						case 'E':
						case 'e':
							opt = 'e';
							exponentialDecimal = new ExponentialDecimalOptions(m);
							break;

						case 'u':
							unchanged = true;
							break;
					}

					if (!options.Add(opt))
						throw new FormatException($"There are duplicate format options specified for the group '{opt}'.");

					pos = m.Index + m.Length;
					m = m.NextMatch();
				}

				if (pos < format.Length)
					throw new FormatException($"An unsupported format: '{format}' at position {pos}.");
			}

			var nfi = NumberFormatInfo.GetInstance(formatProvider);
			if (IsNan())
				return sbase > 16 ? $"@{nfi.NaNSymbol}@" : nfi.NaNSymbol;

			if (IsInf())
			{
				var isNegative = IsNegative();

				var infinity = isNegative ? nfi.NegativeInfinitySymbol : nfi.PositiveInfinitySymbol;
				var prefix = isNegative ? nfi.NegativeSign : nfi.PositiveSign;

				if (sign != null)
				{
					switch (sign.WhenPositive)
					{
						case ValueSignOption.Always:
							return infinity.PrependOnce(prefix);

						case ValueSignOption.None:
							return infinity.SkipOnce(prefix);
					}
				}

				if (sbase > 16)
				{
					if (infinity.StartsWith(prefix))
						return $"{infinity.Insert(prefix.Length, "@")}@";
					return $"@{infinity}@";
				}
				return infinity;
			}

			long exp;
			var str = ToString(sbase, digits, out exp);

			int offset;
			str = ApplySign(str, out offset, sign, nfi.PositiveSign, nfi.NegativeSign);

			if (!unchanged && exp < str.Length)
				str = Normalize(str, exp, sbase);

			var useExponential = ShouldUseExponent(exponentialDecimal, positionalDecimal, exp);
			if (useExponential)
			{
				str = str.Insert(offset, $"0{nfi.NumberDecimalSeparator}");
				str = ApplyExponent(str, exp, sbase, exponentialDecimal, nfi.PositiveSign, nfi.NegativeSign);
				return str;
			}

			str = ApplyPositional(str, exp, offset, positionalDecimal, nfi.NumberDecimalSeparator);
			return str;
		}

		public string ToString(int sbase, uint digits, out long exponent)
		{
			var capacity = digits == 0
				? (int)Math.Ceiling((decimal)Precision / (sbase - 1)) + 8
				: (int)Math.Max(digits + 2, 7);

			var sb = new StringBuilder(capacity);
			exponent = 0;
			mpfr_get_str(sb, ref exponent, sbase, digits, _value, GetRounding());
			var str = sb.ToString();

			return str;
		}

		public override string ToString() => ToString(null);

		private string ApplySign(string str, out int offset, SignOptions sign, string plus, string minus)
		{
			offset = 0;
			var dm = notDigitPattern.Match(str);
			if (dm.Success)
				offset = dm.Groups[0].Value.Length;

			if (sign == null)
				return str;

			if (IsZero())
			{
				switch (sign.WhenZero)
				{
					case ZeroSignOption.Always:
						return ReplaceSign(str, ref offset, IsNegative() ? minus : plus);

					case ZeroSignOption.Plus:
						return ReplaceSign(str, ref offset, plus);

					case ZeroSignOption.Minus:
						return ReplaceSign(str, ref offset, minus);

					case ZeroSignOption.None:
						return ReplaceSign(str, ref offset);
				}
			}
			else
			{
				var prefix = IsNegative() ? minus : plus;
				switch (sign.WhenPositive)
				{
					case ValueSignOption.Always:
						return ReplaceSign(str, ref offset, prefix);

					case ValueSignOption.None:
						return ReplaceSign(str, ref offset);
				}
			}

			return str;
		}

		private static string ReplaceSign(string str, ref int offset, string mark = "")
		{
			if (offset != 0)
			{
				str = mark + str.Substring(offset);
				offset = 0;
			}
			else if (mark.Length != 0)
			{
				str = mark + str;
				offset = mark.Length;
			}
			return str;
		}

		private static bool ShouldUseExponent(ExponentialDecimalOptions e, PositionalDecimalOptions p, long exp)
		{
			var isExponential = e != null;
			var isPositional = p != null;

			var useExponential = true;
			if (isExponential && isPositional)
			{
				if (p.Contains(exp) && !e.Contains(exp))
					useExponential = false;
			}
			else if (isPositional)
				useExponential = p.Contains(exp);
			else if (isExponential)
				useExponential = !e.Contains(exp);
			return useExponential;
		}

		private string ApplyExponent(string str, long exp, int sbase, ExponentialDecimalOptions e, string plus, string minus)
		{
			var mark = sbase > 16 ? "@" : e?.Mark ?? "E";
			var sign = e?.SignOptions ?? new SignOptions("!!+");

			var sigexp = "";
			switch (Math.Sign(exp))
			{
				case 0:
					switch (sign.WhenZero)
					{
						case ZeroSignOption.Always:
						case ZeroSignOption.Plus:
						case ZeroSignOption.Default:
							sigexp = plus;
							break;

						case ZeroSignOption.Minus:
							sigexp = minus;
							break;
					}
					break;

				case 1:
					switch (sign.WhenPositive)
					{
						case ValueSignOption.Always:
						case ValueSignOption.Default:
							sigexp = plus;
							break;
					}
					break;

				case -1:
					switch (sign.WhenNegative)
					{
						case ValueSignOption.Always:
						case ValueSignOption.Default:
							sigexp = minus;
							break;
					}
					break;
			}

			return $"{str}{mark}{sigexp}{Math.Abs(exp)}";
		}

		private string ApplyPositional(string str, long exp, int offset, PositionalDecimalOptions p, string separator)
		{
			var fixedPrefix = Math.Max(p?.FixedPrefix ?? 1, 1);
			var fixedSuffix = p?.FixedSuffix ?? 0;
			var optionalSuffix = p?.OptionalSuffix ?? 0;

			string sign, digits;
			str.SplitParts(offset, out sign, out digits);

			string ldigits, rdigits;
			str.SplitParts(exp, out ldigits, out rdigits);

			rdigits = rdigits.TrimEnd('0');

			if (ldigits.Length < fixedPrefix)
				ldigits = ldigits.PadLeft(fixedPrefix, '0');
			if (rdigits.Length < fixedSuffix)
				rdigits = rdigits.PadRight(fixedSuffix, '0');

			if (optionalSuffix > fixedSuffix)
			{
				string fs, os;
				rdigits.SplitParts(optionalSuffix - fixedSuffix, out fs, out os);

				if (os.Length > 0)
				{
					os = lastZerosPattern.Replace(os, "");
					rdigits = fs + os;
				}
			}

			return rdigits.Length > 0 ? $"{sign}{ldigits}{separator}{rdigits}" : $"{sign}{ldigits}";
		}

		private string Normalize(string str, long exp, int sbase)
		{
			if (str.IsVoid())
				return str;

			var last = _digits[sbase];
			if (str.LastChar() != last)
				return str;

			var alt = str.TrimEnd(last);
			if (alt.Length == 0)
				alt = "1";
			else
			{
				last = _digits[(_position[alt.LastChar()] + 1) % sbase];
				alt = $"{(alt.Length > 1 ? alt.Substring(0, alt.Length - 1) : "")}{last}";
			}

			var check = new BigFloat($"0.{alt}@{(exp >= 0 ? "+" : "-")}{exp}", sbase, Precision);
			if (check.IsEqual(this))
				return alt;

			return str;
		}

		#region SignOptions

		private class SignOptions
		{
			public ValueSignOption WhenPositive { get; }
			public ValueSignOption WhenNegative { get; }
			public ZeroSignOption WhenZero { get; }

			public SignOptions()
			{
			}

			public SignOptions(string sign)
			{
				if (sign == null)
					return;

				if (sign.Length > 2)
					WhenZero = ParseZeroSignOption(sign[2]);
				if (sign.Length > 1)
					WhenNegative = ParseValueSignOption(sign[1]);
				if (sign.Length > 0)
					WhenPositive = ParseValueSignOption(sign[0]);
			}

			private static ValueSignOption ParseValueSignOption(char option)
			{
				switch (option)
				{
					case '!': return ValueSignOption.Always;
					case ';': return ValueSignOption.Default;
					case '_': return ValueSignOption.None;
					default:
						throw new FormatException($"'{option}' is not recognized as an option for a sign-filling behavior for a positive or negative value.");
				}
			}

			private static ZeroSignOption ParseZeroSignOption(char option)
			{
				switch (option)
				{
					case '!': return ZeroSignOption.Always;
					case ';': return ZeroSignOption.Default;
					case '_': return ZeroSignOption.None;
					case '+': return ZeroSignOption.Plus;
					case '-': return ZeroSignOption.Minus;
					default:
						throw new FormatException($"'{option}' is not recognized as an option for a sign-filling behavior for zero.");
				}
			}
		}

		private enum ValueSignOption
		{
			Default,
			Always,
			None,
		}

		private enum ZeroSignOption
		{
			Always,
			Default,
			None,
			Plus,
			Minus,
		}

		#endregion
		#region DecimalOptions

		private interface IInterval
		{
			bool Contains(long value);
		}

		private class DecimalOptions : IInterval
		{
			private IInterval[] Comparisons { get; }
			private IInterval[] Intervals { get; }

			protected DecimalOptions(Match match)
			{
				var comparisons = new[] { match.Groups["e_comparison"], match.Groups["p_comparison"] }
					.Where(x => x.Success)
					.Select(x => x.Captures.ToEnumerable().Cast<Capture>().Select(c => new Comparison(c.Value)).ToArray())
					.FirstOrDefault() ?? new Comparison[0];
				Comparisons = comparisons.OfType<IInterval>().ToArray();

				var intervals = new[] { match.Groups["e_interval"], match.Groups["p_interval"] }
					.Where(x => x.Success)
					.Select(x => x.Captures.ToEnumerable().Cast<Capture>().Select(c => new Interval(c.Value)).ToArray())
					.FirstOrDefault() ?? new Interval[0];
				Intervals = intervals.OfType<IInterval>().ToArray();
			}

			public bool Contains(long exponent) => Comparisons.Concat(Intervals).Any(x => x.Contains(exponent));
		}

		private class PositionalDecimalOptions : DecimalOptions
		{
			public int FixedPrefix { get; }
			public int FixedSuffix { get; }
			public int OptionalSuffix { get; }

			public PositionalDecimalOptions(Match match) : base(match)
			{
				var fpGroup = match.Groups["p_fixedPrefix"];
				if (fpGroup.Success && !fpGroup.Value.IsVoid())
					FixedPrefix = int.Parse(fpGroup.Value);

				var fsGroup = match.Groups["p_fixedSuffix"];
				if (fsGroup.Success && !fsGroup.Value.IsVoid())
					FixedSuffix = int.Parse(fsGroup.Value);

				var osGroup = match.Groups["p_optionalSuffix"];
				if (osGroup.Success && !osGroup.Value.IsVoid())
					OptionalSuffix = int.Parse(osGroup.Value);
			}
		}

		private class ExponentialDecimalOptions : DecimalOptions
		{
			public SignOptions SignOptions { get; }
			public string Mark { get; }

			public ExponentialDecimalOptions(Match match) : base(match)
			{
				Mark = match.Groups["exponent"].Value.Substring(0, 1);

				var signGroup = match.Groups["e_sign"];
				if (!signGroup.Success)
					return;

				var sign = signGroup.Value;
				SignOptions = new SignOptions(sign);
			}
		}

		#region Comparison

		private class Comparison : IInterval
		{
			public ComparisonOperator Operator { get; }
			public int Value { get; }

			public Comparison(string comparison)
			{
				var c1 = comparison[0];
				var c2 = comparison[1];
				switch (c1)
				{
					case '=':
						Operator = ComparisonOperator.Equal;
						break;

					case '<':
						Operator = c2 == '=' ? ComparisonOperator.LessOrEqual : ComparisonOperator.Less;
						break;

					case '>':
						Operator = c2 == '=' ? ComparisonOperator.GreaterOrEqual : ComparisonOperator.Greater;
						break;
				}
				var value = comparison.Substring(1 + (c2 == '=' ? 1 : 0));
				Value = int.Parse(value);
			}

			public bool Contains(long exponent)
			{
				switch (Operator)
				{
					case ComparisonOperator.Equal:
						return exponent == Value;

					case ComparisonOperator.GreaterOrEqual:
						return exponent >= Value;

					case ComparisonOperator.Greater:
						return exponent > Value;

					case ComparisonOperator.LessOrEqual:
						return exponent <= Value;

					case ComparisonOperator.Less:
						return exponent < Value;

					default:
						return false;
				}
			}
		}

		private enum ComparisonOperator
		{
			Equal,
			GreaterOrEqual,
			Greater,
			LessOrEqual,
			Less,
		}

		#endregion

		#region Interval

		private class Interval : IInterval
		{
			public int First { get; }
			public int Second { get; }

			public Interval(string interval)
			{
				var values = interval.Split(';').Select(int.Parse).OrderBy(x => x).ToArray();
				First = values[0];
				Second = values[1];
			}

			public bool Contains(long exponent) => exponent >= First && exponent <= Second;
		}

		#endregion

		#endregion

		private const string _digits = "_0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		private static readonly Dictionary<char, int> _position = new Dictionary<char, int>
		{
			['0'] = 1,
			['1'] = 2,
			['2'] = 3,
			['3'] = 4,
			['4'] = 5,
			['5'] = 6,
			['6'] = 7,
			['7'] = 8,
			['8'] = 9,
			['9'] = 10,
			['A'] = 11,
			['B'] = 12,
			['C'] = 13,
			['D'] = 14,
			['E'] = 15,
			['F'] = 16,
			['G'] = 17,
			['H'] = 18,
			['I'] = 19,
			['J'] = 20,
			['K'] = 21,
			['L'] = 22,
			['M'] = 23,
			['N'] = 24,
			['O'] = 25,
			['P'] = 26,
			['Q'] = 27,
			['R'] = 28,
			['S'] = 29,
			['T'] = 30,
			['U'] = 31,
			['V'] = 32,
			['W'] = 33,
			['X'] = 34,
			['Y'] = 35,
			['Z'] = 36,
			['a'] = 37,
			['b'] = 38,
			['c'] = 39,
			['d'] = 40,
			['e'] = 41,
			['f'] = 42,
			['g'] = 43,
			['h'] = 44,
			['i'] = 45,
			['j'] = 46,
			['k'] = 47,
			['l'] = 48,
			['m'] = 49,
			['n'] = 50,
			['o'] = 51,
			['p'] = 52,
			['q'] = 53,
			['r'] = 54,
			['s'] = 55,
			['t'] = 56,
			['u'] = 57,
			['v'] = 58,
			['w'] = 59,
			['x'] = 60,
			['y'] = 61,
			['z'] = 62,
		};

		#endregion
	}
}