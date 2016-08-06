using FluentAssertions;
using NUnit.Framework;
using System;
using System.ArbitraryPrecision;

namespace mpfrNET.Tests
{
	public class ArithmeticFunctionsTests
	{
		[TestCase(0, 0)]
		[TestCase(1.1, -1.1)]
		[TestCase(3.0123456789012345, -3.0123456789012345)]
		[TestCase(-3.0123456789012345, 3.0123456789012345)]
		public void Can_Neg(double left, double result)
		{
			var x = (double)new BigDecimal(left).Neg();
			x.Should().Be(result);
		}

		[TestCase(0, 0)]
		[TestCase(-1.1, 1.1)]
		[TestCase(1.1, 1.1)]
		[TestCase(3.0123456789012345, 3.0123456789012345)]
		[TestCase(-3.0123456789012345, 3.0123456789012345)]
		public void Can_Abs(double left, double result)
		{
			var x = (double)new BigDecimal(left).Abs();
			x.Should().Be(result);
		}

		[TestCase(0, 0, 0)]
		[TestCase(0, 1, 1)]
		[TestCase(-1, 1, 0)]
		[TestCase(1.1, 2.123456789, 3.223456789)]
		[TestCase(1.1, 2.1234567890123456, 3.2234567890123456)]
		[TestCase(1.123456789123456, 2.876543210876544, 4.0)]
		public void Can_Add(double left, double right, double result)
		{
			var x = (double)new BigDecimal(left).Add(new BigDecimal(right));
			x.Should().Be(result);
		}

		[TestCase(0, 0, 0)]
		[TestCase(0, 1, -1)]
		[TestCase(1, 0, 1)]
		[TestCase(1.1, 0.1, 1)]
		[TestCase(3.0123456789012345, 1, 2.0123456789012345)]
		public void Can_Sub(double left, double right, double result)
		{
			var x = (double)new BigDecimal(left).Sub(new BigDecimal(right));
			x.Should().Be(result);
		}

		[TestCase(0, 1, 0)]
		[TestCase(1, 1, 1)]
		[TestCase(1, -1, -1)]
		[TestCase(3, 1, 3)]
		[TestCase(0.3333333333333333, 3, 1)]
		public void Can_Mul(double left, double right, double result)
		{
			var x = (double)new BigDecimal(left).Mul(new BigDecimal(right));
			x.Should().Be(result);
		}

		[TestCase(0, 1, 0)]
		[TestCase(1, 1, 1)]
		[TestCase(1, -1, -1)]
		[TestCase(3, 1, 3)]
		[TestCase(1, 3, 0.3333333333333333)]
		public void Can_Div(double left, double right, double result)
		{
			var x = (double)new BigDecimal(left).Div(new BigDecimal(right));
			x.Should().Be(result);
		}

		[TestCase(0, 0, 1)]
		[TestCase(0, 1, 0)]
		[TestCase(1, 0, 1)]
		[TestCase(1, 1, 1)]
		[TestCase(-1, 2, 1)]
		[TestCase(-1, 3, -1)]
		[TestCase(10, 2, 100)]
		[TestCase(2, 10, 1024)]
		[TestCase(4, -2, 0.0625)]
		[TestCase(3.3, 3.3, 51.41572944406660529715428336039799250538522979598295133355291551603310643)]
		[TestCase(4, 1.25, 5.656854249492380195206754896838792314278687501507792292706718951962929913)]
		public void Can_Pow(double left, double right, double result)
		{
			var x = (double)new BigDecimal(left, 1024).Pow(new BigDecimal(right, 1024));
			x.Should().Be(result);
		}

		[TestCase(1, 1)]
		[TestCase(2, 1.414213562373095048801688724209698078569671875376948073176679737990732478)]
		[TestCase(6.1, 2.469817807045693805907099461628775179194144925820212858228439090302867211)]
		public void Can_Sqrt(double left, double result)
		{
			var x = (double)new BigDecimal(left).Sqrt();
			x.Should().Be(result);
		}

		[TestCase(1, 1)]
		[TestCase(4, 0.5)]
		[TestCase(3, 0.577350269189625764509148780501957455647601751270126876018602326483977672)]
		[TestCase(4.25, 0.485071250072665947037812924232244355899670497102778874635133361540582864)]
		public void Can_RecSqrt(double left, double result)
		{
			var x = (double)new BigDecimal(left).RecSqrt();
			x.Should().Be(result);
		}

		[TestCase(1, 1)]
		[TestCase(8, 2)]
		[TestCase(3, 1.442249570307408382321638310780109588391869253499350577546416194541687596)]
		[TestCase(10.25, 2.172240742884305950861175273027287963596802126904442410000785269899687397)]
		public void Can_Cbrt(double left, double result)
		{
			var x = (double)new BigDecimal(left).Cbrt();
			x.Should().Be(result);
		}

		[TestCase(1, 1, 1)]
		[TestCase(-27, 3, -3)]
		[TestCase(1024, 10, 2)]
		[TestCase(3, 7, 1.169930812758686886462975725513734667699404196420934209030218965589333936)]
		public void Can_Root(double left, int right, double result)
		{
			var x = (double)new BigDecimal(left).Root((ulong)right);
			x.Should().Be(result);
		}

		[TestCase(0, 0, 0)]
		[TestCase(1, 1, 0)]
		[TestCase(1, 2, 0)]
		[TestCase(3, 1, 2)]
		[TestCase(10, 1, 9)]
		[TestCase(-1, -2, 1)]
		public void Can_Dim(double left, double right, double result)
		{
			var x = (double)new BigDecimal(left).Dim(new BigDecimal(right));
			x.Should().Be(result);
		}

		[Test]
		public void Binary_functions_should_throw_for_null_argument()
		{
			var x1 = new BigDecimal(1.1);

			((Action)(() => x1.Add(null))).ShouldThrow<NullReferenceException>();
			((Action)(() => x1.Sub(null))).ShouldThrow<NullReferenceException>();
			((Action)(() => x1.Mul(null))).ShouldThrow<NullReferenceException>();
			((Action)(() => x1.Div(null))).ShouldThrow<NullReferenceException>();
			((Action)(() => x1.Pow(null))).ShouldThrow<NullReferenceException>();
			((Action)(() => x1.Dim(null))).ShouldThrow<NullReferenceException>();
		}
	}
}