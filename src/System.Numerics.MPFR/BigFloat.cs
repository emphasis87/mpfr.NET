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
			Precision = precision ?? DefaultPrecision;
			mpfr_init2(v, Precision);
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
		private static readonly Regex notDigitPattern = new Regex("^([^0-9a-zA-Z@]*)", RegexOptions.Compiled);
		private static readonly Regex formatPattern = new Regex(@"
			^(?<sign>\^[!;_]([!;_]([!;_+-])?)?) | # !always ;default _none +positive -negative
			(?<base>b[0-9]+) |
			(?<digits>d[0-9]+) |
			(?<positional>p
				(?<p_fixedPrefix>[0-9]*)? # before .
				(?<p_fixedSuffix>\.[0-9]*)? # at least after ., '.' means default
				(?<p_optionalSuffix>\#[0-9]*)? # optional after ., '#' means unrestricted
				(
					(?<p_comparison>([<>]=|=|[<>])[+-]?[0-9]+) |
					(\((?<p_interval>[+-]?[0-9]+[,;][+-]?[0-9]+)\))
				)*
			) |
			(?<exponent>[eE@]
				(?<e_fixedLength>[0-9]+)?
				(\^(?<e_sign>[!;_]([!;_]([!;_+-])?)?))?
				(
					(?<e_comparison>([<>]=|=|[<>])[+-]?[0-9]+) |
					(\((?<e_interval>[+-]?[0-9]+[,;][+-]?[0-9]+)\))
				)*
			) |
			(?<unchanged>u((?:[=#])(?!.*\1))?) # rounding or length",
			RegexOptions.Compiled | RegexOptions.IgnorePatternWhitespace);

		public string ToString(string format, IFormatProvider formatProvider = null)
		{
			format = format.Collapse();
			formatProvider = formatProvider ?? CultureInfo.CurrentCulture;

			var fmt = new StringFormatOptions(this, NumberFormatInfo.GetInstance(formatProvider));
			fmt.Parse(format);
			return fmt.Format();
		}

		private static readonly Dictionary<int, double> _lns = new Dictionary<int, double>();
		private static double GetLn(int n)
		{
			if (_lns.ContainsKey(n))
				return _lns[n];

			var ln = Math.Log(n);
			_lns[n] = ln;
			return ln;
		}

		private static readonly Dictionary<int, double> _ratios = new Dictionary<int, double>();
		private static double GetRatio(int n)
		{
			if (_ratios.ContainsKey(n))
				return _ratios[n];

			var ratio = GetLn(n)/GetLn(2);
			_ratios[n] = ratio;
			return ratio;
		}

		public string ToString(int sbase, uint digits, out long exponent)
		{
			var capacity = 7 + (digits == 0
				? (int) Math.Ceiling(Precision/GetRatio(sbase))
				: (int) digits + 2);

			var sb = new StringBuilder(capacity);
			exponent = 0;
			mpfr_get_str(sb, ref exponent, sbase, digits, _value, GetRounding());
			if (exponent > int.MaxValue && CmpAbs(new BigFloat(1)) < 0)
				exponent = -((1L << 32) - exponent);
			var str = sb.ToString();

			return str;
		}

		public override string ToString() => ToString(null);

		private class StringFormatOptions
		{
			private BigFloat Number { get; }

			#region IsNaN
			private bool? _isNaN;
			private bool IsNaN
			{
				get
				{
					if (_isNaN == null)
						_isNaN = Number.IsNan();
					return _isNaN.Value;
				}
			}
			#endregion
			#region IsInf
			private bool? _isInf;
			private bool IsInf
			{
				get
				{
					if (_isInf == null)
						_isInf = Number.IsInf();
					return _isInf.Value;
				}
			}
			#endregion
			#region IsNegative
			private bool? _isNegative;
			private bool IsNegative
			{
				get
				{
					if (_isNegative == null)
						_isNegative = Number.IsNegative();
					return _isNegative.Value;
				}
			}
			#endregion
			private bool IsPositive => !IsNegative;
			#region IsZero
			private bool? _isZero;
			private bool IsZero
			{
				get
				{
					if (_isZero == null)
						_isZero = Number.IsZero();
					return _isZero.Value;
				}
			}
			#endregion

			private NumberFormatInfo NuberFormatInfo { get; }

			private string NaN => NuberFormatInfo.NaNSymbol;
			private string PositiveInf => NuberFormatInfo.PositiveInfinitySymbol;
			private string NegativeInf => NuberFormatInfo.NegativeInfinitySymbol;
			private string PositiveSign => NuberFormatInfo.PositiveSign;
			private string NegativeSign => NuberFormatInfo.NegativeSign;
			private string Separator => NuberFormatInfo.NumberDecimalSeparator;

			public StringFormatOptions(BigFloat number, NumberFormatInfo nfi)
			{
				Number = number;
				NuberFormatInfo = nfi;
			}

			private SignOptions Sign;
			private int Base = 10;
			private uint SignigicantDigits;
			private PositionalDecimalOptions Positional;
			private ExponentialDecimalOptions Exponential;
			private bool UnchangedRounding;
			private bool UnchangedLength;

			private string Value;
			private long Exponent;
			private int SignOffset;
			private string SignPart;
			private string DigitsPart;
			private string LDigitsPart;
			private string RDigitsPart;

			public void Parse(string format)
			{
				if (format.IsVoid())
					return;

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
							Sign = new SignOptions(optval);
							break;

						case 'b':
							int sbase;
							if (!int.TryParse(optval, out sbase) || sbase < 2 || sbase > 62)
								throw new FormatException($"A format with the base '{sbase}' is not supported. Use a number between 2 and 62.");
							Base = sbase;
							break;

						case 'd':
							uint digits;
							if (!uint.TryParse(optval, out digits) || (digits < 2 && digits != 0))
								throw new FormatException($"A format with the number of digits '{digits}' is not supported. Use a number greater than 2 or 0.");
							SignigicantDigits = digits;
							break;

						case 'p':
							Positional = new PositionalDecimalOptions(m);
							break;

						case '@':
						case 'E':
						case 'e':
							opt = 'e';
							Exponential = new ExponentialDecimalOptions(m);
							break;

						case 'u':
							if (optval.Length == 0)
							{
								UnchangedRounding = true;
								UnchangedLength = true;
							}
							else
							{
								UnchangedRounding = optval.Contains('=');
								UnchangedLength = optval.Contains('#');
							}
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

			public string Format()
			{
				if (IsNaN)
					return Base > 16 ? $"@{NaN}@" : NaN;

				if (IsInf)
				{
					var infinity = IsNegative ? NegativeInf : PositiveInf;
					var prefix = IsNegative ? NegativeSign : PositiveSign;

					if (Sign != null)
					{
						switch (Sign.WhenPositive)
						{
							case ValueSignOption.Always:
								return infinity.PrependOnce(prefix);

							case ValueSignOption.None:
								return infinity.SkipOnce(prefix);
						}
					}

					if (Base > 16)
					{
						if (infinity.StartsWith(prefix))
							return $"{infinity.Insert(prefix.Length, "@")}@";
						return $"@{infinity}@";
					}
					return infinity;
				}

				Value = Number.ToString(Base, SignigicantDigits, out Exponent);

				ApplySign();

				Value.SplitParts(SignOffset, out SignPart, out DigitsPart);

				Normalize();

				var useExponential = ShouldUseExponential();
				if (useExponential)
					ApplyExponential();
				else
					ApplyPositional();

				return Value;
			}

			private void ApplySign()
			{
				var dm = notDigitPattern.Match(Value);
				if (dm.Success)
					SignOffset = dm.Groups[0].Value.Length;

				if (Sign == null)
					return;

				if (IsZero)
				{
					switch (Sign.WhenZero)
					{
						case ZeroSignOption.Always:
							ReplaceSign(IsNegative ? NegativeSign : PositiveSign);
							break;

						case ZeroSignOption.Plus:
							ReplaceSign(PositiveSign);
							break;

						case ZeroSignOption.Minus:
							ReplaceSign(NegativeSign);
							break;

						case ZeroSignOption.None:
							ReplaceSign();
							break;
					}
				}
				else
				{
					var prefix = IsNegative ? NegativeSign : PositiveSign;
					switch (Sign.WhenPositive)
					{
						case ValueSignOption.Always:
							ReplaceSign(prefix);
							break;

						case ValueSignOption.None:
							ReplaceSign();
							break;
					}
				}
			}

			private void ReplaceSign(string mark = "")
			{
				if (SignOffset != 0)
				{
					Value = mark + Value.Substring(SignOffset);
					SignOffset = 0;
				}
				else if (mark.Length != 0)
				{
					Value = mark + Value;
					SignOffset = mark.Length;
				}
			}

			private void Normalize()
			{
				if (DigitsPart.IsVoid())
					return;

				if (UnchangedRounding || Exponent > DigitsPart.Length)
					return;

				var max = _digits[Base];
				var last = DigitsPart.TakeLast(2);

				if (last.Length < 2)
					return;

				var exp = Exponent;
				string alt;
				if (last[1] != '0' && last[1] != max)
					last = last.TakeFirst();

				if (last[0] == '0')
					alt = DigitsPart.SkipLast().TrimEnd('0');
				else if (last[0] == max)
				{
					alt = DigitsPart.SkipLast().TrimEnd(max);
					if (alt.Length == 0)
					{
						alt = "1";
						exp = Exponent + 1;
					}
					else if (last[0] == max)
					{
						var c = alt.TakeLast()[0];
						max = _digits[_position[c] + 1];
						alt = $"{(alt.Length > 1 ? alt.Substring(0, alt.Length - 1) : "")}{max}";
					}
				}
				else
					alt = DigitsPart.SkipLast();

				var check = new BigFloat($"{SignPart}0.{alt}@{(exp >= 0 ? "+" : "-")}{Math.Abs(Exponent)}", Base, Number.Precision);
				if (!check.IsEqual(Number))
					return;

				if (UnchangedLength)
					alt = alt.PadRight(DigitsPart.Length, '0');

				Exponent = exp;
				DigitsPart = alt;
				Value = $"{SignPart}{DigitsPart}";
			}

			private bool ShouldUseExponential()
			{
				var e = Exponential != null;
				var ec = Exponential?.Contains(Exponent) ?? false;

				var p = Positional != null;
				var pc = Positional?.Contains(Exponent) ?? false;

				if (e && p)
					return ec || !pc;
				if (e)
					return ec;
				if (p)
					return !pc;

				return true;
			}

			private void ApplyExponential()
			{
				var expMark = Base > 10 ? "@" : Exponential?.Mark ?? "E";
				var signopt = Exponential?.SignOptions ?? new SignOptions("!!+");

				var expSign = "";
				switch (Math.Sign(Exponent))
				{
					case 0:
						switch (signopt.WhenZero)
						{
							case ZeroSignOption.Always:
							case ZeroSignOption.Plus:
							case ZeroSignOption.Default:
								expSign = PositiveSign;
								break;

							case ZeroSignOption.Minus:
								expSign = NegativeSign;
								break;
						}
						break;

					case 1:
						switch (signopt.WhenPositive)
						{
							case ValueSignOption.Always:
							case ValueSignOption.Default:
								expSign = PositiveSign;
								break;
						}
						break;

					case -1:
						switch (signopt.WhenNegative)
						{
							case ValueSignOption.Always:
							case ValueSignOption.Default:
								expSign = NegativeSign;
								break;
						}
						break;
				}

				if (DigitsPart.IsVoid())
					DigitsPart = "0";

				var exp = Math.Abs(Exponent).ToString("D" + (Exponential?.FixedLength ?? 1));
				Value = $"{SignPart}0{Separator}{DigitsPart}{expMark}{expSign}{exp}";
			}

			private void ApplyPositional()
			{
				DigitsPart.SplitParts(Exponent, out LDigitsPart, out RDigitsPart);
				if (Exponent < 0)
				{
					var pad = (int) Math.Abs(Exponent) - LDigitsPart.Length;
					if (pad > 0)
						RDigitsPart = new string('0', pad) + RDigitsPart;
				}
				else if (Exponent > 0)
				{
					var pad = (int)Math.Abs(Exponent) - LDigitsPart.Length;
					if (pad > 0)
						LDigitsPart += new string('0', pad);
				}

				var fp = Positional?.FixedPrefix;
				var fs = Positional?.FixedSuffix;
				var os = Positional?.OptionalSuffix;

				var fsPresent = fs != null;
				var osPresent = os != null;

				var fsMark = Positional?.HasFixedSuffix ?? false;
				var osMark = Positional?.HasOptionalSuffix ?? false;

				if (fsMark && !fsPresent)
					fs = Math.Max(NuberFormatInfo.NumberDecimalDigits, 0);

				int? trimLen = null, padLen = null;

				if (fsMark && osMark)
				{
					if (!osPresent)
						padLen = fs;
					else
					{
						trimLen = Math.Max(fs.Value, os.Value);
						padLen = fs.Value;
					}
				}
				else if (fsMark)
				{
					trimLen = fs.Value;
					padLen = fs.Value;
				}
				else if (osMark)
				{
					trimLen = os;
				}
				else if (fp != null)
				{
					trimLen = 0;
				}

				fp = Math.Max(fp ?? 1, 1);
				if (LDigitsPart.Length < fp)
					LDigitsPart = LDigitsPart.PadLeft(fp.Value, '0');

				if (RDigitsPart.Length > trimLen)
					RDigitsPart = RDigitsPart.Substring(0, trimLen.Value);

				if (RDigitsPart.Length < padLen)
					RDigitsPart = RDigitsPart.PadRight(padLen.Value, '0');

				Value = RDigitsPart.Length == 0 ? $"{SignPart}{LDigitsPart}" : $"{SignPart}{LDigitsPart}{Separator}{RDigitsPart}";
			}
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
			Default,
			Always,
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
			private IInterval[] Intervals { get; }

			protected DecimalOptions(Match match)
			{
				var comparisons = new[] { match.Groups["e_comparison"], match.Groups["p_comparison"] }
					.Where(x => x.Success)
					.Select(x => x.Captures.ToEnumerable().Cast<Capture>().Select(c => new Comparison(c.Value)).ToArray())
					.FirstOrDefault() ?? new Comparison[0];

				var intervals = new[] { match.Groups["e_interval"], match.Groups["p_interval"] }
					.Where(x => x.Success)
					.Select(x => x.Captures.ToEnumerable().Cast<Capture>().Select(c => new Interval(c.Value)).ToArray())
					.FirstOrDefault() ?? new Interval[0];

				Intervals = comparisons.OfType<IInterval>().Concat(intervals).ToArray();
			}

			public bool Contains(long exponent) => Intervals.IsEmpty() || Intervals.Any(x => x.Contains(exponent));
		}

		private class PositionalDecimalOptions : DecimalOptions
		{
			public int? FixedPrefix { get; }
			public bool HasFixedSuffix { get; }
			public int? FixedSuffix { get; }
			public bool HasOptionalSuffix { get; }
			public int? OptionalSuffix { get; }

			public PositionalDecimalOptions(Match match) : base(match)
			{
				var fpGroup = match.Groups["p_fixedPrefix"];
				if (fpGroup.Success && !fpGroup.Value.IsVoid())
					FixedPrefix = int.Parse(fpGroup.Value);

				var fsGroup = match.Groups["p_fixedSuffix"];
				if (fsGroup.Success && !fsGroup.Value.IsVoid())
				{
					HasFixedSuffix = true;
					var fs = fsGroup.Value.Substring(1);
					if (fs.Length > 0)
						FixedSuffix = int.Parse(fs);
				}

				var osGroup = match.Groups["p_optionalSuffix"];
				if (osGroup.Success && !osGroup.Value.IsVoid())
				{
					HasOptionalSuffix = true;
					var os = osGroup.Value.Substring(1);
					if (os.Length > 0)
						OptionalSuffix = int.Parse(os);
				}
			}
		}

		private class ExponentialDecimalOptions : DecimalOptions
		{
			public SignOptions SignOptions { get; }
			public string Mark { get; }
			public int? FixedLength { get; }

			public ExponentialDecimalOptions(Match match) : base(match)
			{
				Mark = match.Groups["exponent"].Value.Substring(0, 1);

				var signGroup = match.Groups["e_sign"];
				if (signGroup.Success)
				{
					var sign = signGroup.Value;
					SignOptions = new SignOptions(sign);
				}

				var flGroup = match.Groups["e_fixedLength"];
				if (flGroup.Success)
				{
					FixedLength = int.Parse(flGroup.Value);
				}
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
			private int First { get; }
			private int Second { get; }

			public Interval(string interval)
			{
				var values = interval.Split(';', ',').Select(int.Parse).OrderBy(x => x).ToArray();
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