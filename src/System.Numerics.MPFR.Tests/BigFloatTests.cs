using FluentAssertions;
using MoreLinq;
using NUnit.Framework;

namespace System.Numerics.MPFR.Tests
{
	public class BigFloatTests
	{
		private readonly BigFloat _num = new BigFloat(0);

		[Test]
		public void Can_parse_format()
		{
			var b = new[] { "b2", "b10", "b62" };
			var d = new[] { "d0", "d2", "d10", "d100" };
			var s = new[] { "." };
			var e = new[] { "e" };

			b.ForEach(FormatShouldNotThrow);
			d.ForEach(FormatShouldNotThrow);
			s.ForEach(FormatShouldNotThrow);
			e.ForEach(FormatShouldNotThrow);

			new[] {null, ""}.ForEach(FormatShouldNotThrow);

			new[] {"b1", "b0", "b2b2", "d1", "d2d2", "..", "ee", ".e", "a"}.ForEach(FormatShouldThrow);
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
	}
}