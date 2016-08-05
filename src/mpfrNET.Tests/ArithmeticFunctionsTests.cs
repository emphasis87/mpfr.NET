using FluentAssertions;
using NUnit.Framework;
using System;
using System.ArbitraryPrecision;

namespace mpfrNET.Tests
{
	public class ArithmeticFunctionsTests
	{
		[Test]
		public void Can_Add()
		{
			var x1 = new BigDecimal(1.1);
			x1.Add(new BigDecimal(2.123456789));

			((double)x1).Should().Be(3.223456789);

			x1.Add(new BigDecimal(0.0000000001234567));

			((double)x1).Should().Be(3.2234567891234567);

			x1.Add(new BigDecimal(0.000000000000000009));

			((double)x1).Should().Be(3.2234567891234567);
		}

		[Test]
		public void When_passed_null_Add_should_throw()
		{
			var x1 = new BigDecimal(1.1);

			Action act = () => x1.Add(null);

			act.ShouldThrow<NullReferenceException>();
		}
	}
}