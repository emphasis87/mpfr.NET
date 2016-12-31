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
			new BigFloat("5").ToString("b2d5").Should().Be("0.10100E+3");

			new BigFloat("5").ToString("d5").Should().Be("0.50000E+1");

			new BigFloat("5").ToString("p2").Should().Be("05");
			new BigFloat("5").ToString("p2.2").Should().Be("05.00");
			new BigFloat("5.67").ToString("p2.1").Should().Be("05.6");
			new BigFloat("5.67").ToString("p.1").Should().Be("5.6");
			new BigFloat("5.678").ToString("p.1#2").Should().Be("5.67");
			new BigFloat("5.6").ToString("p.1#2").Should().Be("5.6");
			new BigFloat("5.6").ToString("p.#2").Should().Be("5.6");
			new BigFloat("5").ToString("p.#2").Should().Be("5");
			new BigFloat("5.678").ToString("p.#2").Should().Be("5.67");
		}
	}
}