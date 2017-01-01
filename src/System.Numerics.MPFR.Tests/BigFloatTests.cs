using System.Globalization;
using System.Threading;
using FluentAssertions;
using MoreLinq;
using NUnit.Framework;

namespace System.Numerics.MPFR.Tests
{
	public class BigFloatTests
	{
		private readonly BigFloat _num = new BigFloat(0);

		[SetUp]
		public void Setup()
		{
			Thread.CurrentThread.CurrentCulture = CultureInfo.InvariantCulture;
			Thread.CurrentThread.CurrentUICulture = CultureInfo.InvariantCulture;
		}

		[Test]
		public void Can_parse_format()
		{
			var b = new[] { "b2", "b10", "b62" };
			var d = new[] { "d0", "d2", "d10", "d100" };
			var s = new[] { "p" };
			var e = new[] { "e" };
			var c = new[] { "c" };

			b.ForEach(FormatShouldNotThrow);
			d.ForEach(FormatShouldNotThrow);
			s.ForEach(FormatShouldNotThrow);
			e.ForEach(FormatShouldNotThrow);
			c.ForEach(FormatShouldNotThrow);

			new[] {null, ""}.ForEach(FormatShouldNotThrow);

			new[] {"b1", "b0", "b2b2", "d1", "d2d2", "pp", "ee", "cc", "a" }.ForEach(FormatShouldThrow);
		}

		private void FormatShouldNotThrow(string format)
		{
			Action action = () => _num.ToString(format);
			action.ShouldNotThrow();
		}

		private void FormatShouldThrow(string format)
		{
			Action action = () => _num.ToString(format);
			action.ShouldThrow<FormatException>();
		}

		[Test]
		public void Can_print_format()
		{
			var culture = new CultureInfo("en-US", false)
			{
				NumberFormat = {NumberDecimalDigits = 3}
			};
			Thread.CurrentThread.CurrentCulture = culture;
			Thread.CurrentThread.CurrentUICulture = culture;

			new BigFloat("NaN").ToString().Should().Be("NaN");
			new BigFloat("Inf").ToString().Should().Be("∞");
			new BigFloat("Inf").ToString("^!").Should().Be("+∞");
			new BigFloat("-Inf").ToString().Should().Be("-∞");

			new BigFloat("5").ToString("b2d5").Should().Be("0.101E+3");

			new BigFloat("0.001").ToString().Should().Be("0.1E-2");
			new BigFloat("-5.123").ToString("d3").Should().Be("-0.512E+1");
			new BigFloat("5").ToString("d5u").Should().Be("0.50000E+1");
			new BigFloat("0.001").ToString().Should().Be("0.1E-2");
			new BigFloat("-0.001").ToString().Should().Be("-0.1E-2");
			new BigFloat("-0.001").ToString("E2").Should().Be("-0.1E-02");
			new BigFloat("-0.001").ToString("E2").Should().Be("-0.1E-02");
			new BigFloat("-0.001").ToString("e3^__").Should().Be("-0.1e002");
			new BigFloat("-0.001").ToString("@3^_!").Should().Be("-0.1@-002");
			new BigFloat("-0.001").ToString("E3^_;").Should().Be("-0.1E-002");
			new BigFloat("-0.1").ToString("E^___").Should().Be("-0.1E0");
			new BigFloat("-0.1").ToString("E^__!").Should().Be("-0.1E+0");
			new BigFloat("-0.1").ToString("E^__;").Should().Be("-0.1E+0");
			new BigFloat("-0.1").ToString("E^__+").Should().Be("-0.1E+0");
			new BigFloat("-0.1").ToString("E^__-").Should().Be("-0.1E-0");
			new BigFloat("-1").ToString("E2^!").Should().Be("-0.1E+01");
			new BigFloat("-1").ToString("E1^;").Should().Be("-0.1E+1");
			new BigFloat("-1").ToString("E0^_").Should().Be("-0.1E1");
			new BigFloat("-1").ToString("E").Should().Be("-0.1E+1");

			new BigFloat("5").ToString("p2").Should().Be("05");
			new BigFloat("-5.1").ToString("p2").Should().Be("-05");
			new BigFloat("5").ToString("p2.2").Should().Be("05.00");
			new BigFloat("5.67").ToString("p2.1").Should().Be("05.6");
			new BigFloat("-5.67").ToString("p.1").Should().Be("-5.6");
			new BigFloat("5.67").ToString("p.0").Should().Be("5");
			new BigFloat("5.6789").ToString("p.").Should().Be("5.678");
			new BigFloat("5.678").ToString("p.1#2").Should().Be("5.67");
			new BigFloat("5.6").ToString("p.1#2").Should().Be("5.6");
			new BigFloat("-5.6").ToString("p.#2").Should().Be("-5.600");
			new BigFloat("5").ToString("p.#2").Should().Be("5.000");
			new BigFloat("5.456789").ToString("p.#4").Should().Be("5.4567");
			new BigFloat("5.456789").ToString("p#2").Should().Be("5.45");
			new BigFloat("-5.456789").ToString("p#").Should().Be("-5.456789");
			new BigFloat("500.4567").ToString("p4#2").Should().Be("0500.45");
			new BigFloat("5.4567").ToString("p4#").Should().Be("0005.4567");
			new BigFloat("512.4567").ToString("p4#0").Should().Be("0512");
			new BigFloat("51234.4567").ToString("p4.0#0").Should().Be("51234");
			new BigFloat("-5.4567").ToString("p4.#").Should().Be("-0005.4567");
			new BigFloat("5.45").ToString("p4.#").Should().Be("0005.450");
			new BigFloat("-1E-3").ToString("p").Should().Be("-0.001");

			new BigFloat("5.67").ToString("pu").Should().Be("5.6699999999999999");
			new BigFloat("5.67").ToString("pu#").Should().Be("5.6700000000000000");
			new BigFloat("5.67").ToString("pu=").Should().Be("5.6699999999999999");

			new BigFloat("5.67").ToString("eu").Should().Be("0.56699999999999999e+1");
			new BigFloat("5.67").ToString("eu#").Should().Be("0.56700000000000000e+1");
			new BigFloat("5.67").ToString("eu=").Should().Be("0.56699999999999999e+1");

			new BigFloat("-1").ToString("E=0p=1").Should().Be("-1");
			new BigFloat("-1").ToString("E=1p=1").Should().Be("-0.1E+1");
			new BigFloat("-1").ToString("E=1p=0").Should().Be("-0.1E+1");

			new BigFloat("100").ToString("E(-1,1)=3").Should().Be("0.1E+3");
			new BigFloat("10").ToString("E(-1,1)=3").Should().Be("10");
			new BigFloat("1").ToString("E(-1,1)=3").Should().Be("0.1E+1");
			new BigFloat("0.1").ToString("E(-1,1)=3").Should().Be("0.1E+0");
			new BigFloat("0.01").ToString("E(-1,1)=3").Should().Be("0.1E-1");
			new BigFloat("0.001").ToString("E(-1,1)=3").Should().Be("0.001");

			new BigFloat("100").ToString("p(-1,1)=3").Should().Be("100");
			new BigFloat("10").ToString("p(-1,1)=3").Should().Be("0.1E+2");
			new BigFloat("1").ToString("p=3(-1,1)").Should().Be("1");
			new BigFloat("0.1").ToString("p(-1,1)=3").Should().Be("0.1");
			new BigFloat("0.01").ToString("p(-1,1)=3").Should().Be("0.01");
			new BigFloat("0.001").ToString("p=3(-1,1)=3").Should().Be("0.1E-2");

			var flt = new BigFloat("10", precision: 100);
			flt.Log();
			flt.ToString("p").Should().Be("2.302585092994045684017991454683");
		}
	}
}