using FluentAssertions;
using NUnit.Framework;
using System.ArbitraryPrecision;
using System.Globalization;
using System.Threading;

namespace mpfrNET.Tests
{
	public class IOFunctionsTests
	{
		[Test]
		public void Can_parse_and_print_string()
		{
			Thread.CurrentThread.CurrentCulture = CultureInfo.InvariantCulture;

			new BigDecimal("NaN").ToString().Should().Be("NaN");
			new BigDecimal("+NaN").ToString().Should().Be("NaN");
			new BigDecimal("-NaN").ToString().Should().Be("NaN");
			new BigDecimal("Inf").ToString().Should().Be("Infinity");
			new BigDecimal("+Inf").ToString().Should().Be("Infinity");
			new BigDecimal("-Inf").ToString().Should().Be("-Infinity");
			new BigDecimal("+0").ToString().Should().Be("0");
			new BigDecimal("-0").ToString().Should().Be("-0");
			new BigDecimal("2").ToString().Should().Be("2");
			new BigDecimal("-2").ToString().Should().Be("-2");
			new BigDecimal("20").ToString().Should().Be("20");
			new BigDecimal("-20").ToString().Should().Be("-20");
			new BigDecimal("1000000").ToString().Should().Be("1000000");
			new BigDecimal("-1000000").ToString().Should().Be("-1000000");
			new BigDecimal("100001.12345").ToString().Should().Be("100001.12345");
			new BigDecimal("1.123456789").ToString().Should().Be("1.123456789");
			new BigDecimal("0.123456789").ToString().Should().Be("0.123456789");
			new BigDecimal("0.0000123456789").ToString().Should().Be("0.0000123456789");
			new BigDecimal("+100001.12345").ToString().Should().Be("100001.12345");
			new BigDecimal("+1.123456789").ToString().Should().Be("1.123456789");
			new BigDecimal("+0.123456789").ToString().Should().Be("0.123456789");
			new BigDecimal("+0.0000123456789").ToString().Should().Be("0.0000123456789");
			new BigDecimal("-100001.12345").ToString().Should().Be("-100001.12345");
			new BigDecimal("-1.123456789").ToString().Should().Be("-1.123456789");
			new BigDecimal("-0.123456789").ToString().Should().Be("-0.123456789");
			new BigDecimal("-0.0000123456789").ToString().Should().Be("-0.0000123456789");

			var str = "";
			for (var i = 0; i < 100; i++)
				str += "1234567890";
			str = str + "." + str + "1234";
			str = "-" + str;

			var x = new BigDecimal(str, 10, (ulong)(str.Length * 4));
			var y = new BigDecimal(x.ToString(), 10, (ulong)(str.Length * 4));

			x.ToString().Should().Be(y.ToString());
		}
	}
}