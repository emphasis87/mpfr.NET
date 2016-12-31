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

			new BigFloat("5").ToString("b2d5").Should().Be("0.101E+3");

			new BigFloat("5.123").ToString("d3").Should().Be("0.512E+1");
			new BigFloat("5").ToString("d5u").Should().Be("0.50000E+1");

			new BigFloat("5").ToString("p2").Should().Be("05");
			new BigFloat("5.1").ToString("p2").Should().Be("05");
			new BigFloat("5").ToString("p2.2").Should().Be("05.00");
			new BigFloat("5.67").ToString("p2.1").Should().Be("05.6");
			new BigFloat("5.67").ToString("p.1").Should().Be("5.6");
			new BigFloat("5.67").ToString("p.0").Should().Be("5");
			new BigFloat("5.6789").ToString("p.").Should().Be("5.678");
			new BigFloat("5.678").ToString("p.1#2").Should().Be("5.67");
			new BigFloat("5.6").ToString("p.1#2").Should().Be("5.6");
			new BigFloat("5.6").ToString("p.#2").Should().Be("5.600");
			new BigFloat("5").ToString("p.#2").Should().Be("5.000");
			new BigFloat("5.456789").ToString("p.#4").Should().Be("5.4567");
			new BigFloat("5.456789").ToString("p#2").Should().Be("5.45");
			new BigFloat("5.456789").ToString("p#").Should().Be("5.456789");
			new BigFloat("5.4567").ToString("p4#2").Should().Be("0005.45");
			new BigFloat("5.4567").ToString("p4#").Should().Be("0005.4567");
			new BigFloat("5.4567").ToString("p4#0").Should().Be("0005");
			new BigFloat("5.4567").ToString("p4.0#0").Should().Be("0005");
			new BigFloat("5.4567").ToString("p4.#").Should().Be("0005.4567");
			new BigFloat("5.45").ToString("p4.#").Should().Be("0005.450");
		}
	}
}