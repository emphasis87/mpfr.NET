using FluentAssertions;
using NUnit.Framework;
using System;
using System.ArbitraryPrecision;

namespace mpfrNET.Tests
{
	public class ConstructorTests
	{
		[Test]
		public void Can_construct()
		{
			new BigDecimal((sbyte)-1).ToString().Should().Be("-1");
			new BigDecimal((short)-1).ToString().Should().Be("-1");
			new BigDecimal((int)-1).ToString().Should().Be("-1");
			new BigDecimal((long)-1).ToString().Should().Be("-1");
			new BigDecimal((byte)1).ToString().Should().Be("1");
			new BigDecimal((ushort)1).ToString().Should().Be("1");
			new BigDecimal((uint)1).ToString().Should().Be("1");
			new BigDecimal((ulong)1).ToString().Should().Be("1");
			Math.Round((double)new BigDecimal((float)1.1), 1).Should().Be(1.1);
			Math.Round((double)new BigDecimal((double)1.1), 1).Should().Be(1.1);
			Math.Round((double)new BigDecimal(1.1m), 1).Should().Be(1.1);
			Math.Round((double)new BigDecimal("1.1"), 1).Should().Be(1.1);
		}
	}
}