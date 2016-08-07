using System.ArbitraryPrecision;
using System.Globalization;
using FluentAssertions;
using NUnit.Framework;

namespace mpfrNET.Tests
{
    public class IOFunctionsTests
    {
        [Test]
        public void Can_create_from_string()
        {
            var x1 = new BigDecimal("100001.123456789876");
            x1.ToString(CultureInfo.InvariantCulture).Should().Be("100001.123456789876");

            var x2 = new BigDecimal("1.123456789");
            x2.ToString(CultureInfo.InvariantCulture).Should().Be("1.123456789");

            var x3 = new BigDecimal("0.123456789");
            x3.ToString(CultureInfo.InvariantCulture).Should().Be("0.123456789");

            var x4 = new BigDecimal("0.0000123456789");
            x4.ToString(CultureInfo.InvariantCulture).Should().Be("0.0000123456789");
        }
    }
}
