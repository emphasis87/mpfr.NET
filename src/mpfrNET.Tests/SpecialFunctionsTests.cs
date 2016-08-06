using FluentAssertions;
using NUnit.Framework;
using System.ArbitraryPrecision;

namespace mpfrNET.Tests
{
	public class SpecialFunctionsTests
	{
		[TestCase(double.NaN, double.NaN)]
		[TestCase(double.NegativeInfinity, double.NaN)]
		[TestCase(double.PositiveInfinity, double.PositiveInfinity)]
		[TestCase(0, double.NegativeInfinity)]
		[TestCase(1, 0)]
		[TestCase(-1, double.NaN)]
		[TestCase(0.4, -0.916290731874155065183527211768011071450101219908262467791967881980785365)]
		[TestCase(2, 0.693147180559945309417232121458176568075500134360255254120680009493393621)]
		[TestCase(9.999, 2.302485087993712325682657954670077243204266090894201900519238035204856264)]
		public void Can_Ln(double left, double result)
		{
			var x = (double)new BigDecimal(left).Ln();
			x.Should().Be(result);
		}

		[TestCase(double.NaN, double.NaN)]
		[TestCase(double.NegativeInfinity, double.NaN)]
		[TestCase(double.PositiveInfinity, double.PositiveInfinity)]
		[TestCase(0, double.NegativeInfinity)]
		[TestCase(1, 0)]
		[TestCase(-1, double.NaN)]
		[TestCase(0.4, -1.321928094887362347870319429489390175864831393024580612054756395815934776)]
		[TestCase(1024, 10)]
		[TestCase(9.999, 3.321783818169317312667541759643564948423217700960905620325686812784034478)]
		public void Can_Log2(double left, double result)
		{
			var x = (double)new BigDecimal(left).Log2();
			x.Should().Be(result);
		}

		[TestCase(double.NaN, double.NaN)]
		[TestCase(double.NegativeInfinity, double.NaN)]
		[TestCase(double.PositiveInfinity, double.PositiveInfinity)]
		[TestCase(0, double.NegativeInfinity)]
		[TestCase(1, 0)]
		[TestCase(-1, double.NaN)]
		[TestCase(0.4, -0.397940008672037609572522210551013946463620237075782917379145077745783621)]
		[TestCase(1000, 3)]
		[TestCase(9.999, 0.999956568380192489615443955976192773326249274054297415662088936238659348)]
		public void Can_Log10(double left, double result)
		{
			var x = (double)new BigDecimal(left).Log10();
			x.Should().Be(result);
		}

		[TestCase(double.NaN, double.NaN)]
		[TestCase(double.NegativeInfinity, 0)]
		[TestCase(double.PositiveInfinity, double.PositiveInfinity)]
		[TestCase(0, 1)]
		[TestCase(1, 2.718281828459045235360287471352662497757247093699959574966967627724076630)]
		[TestCase(-2, 0.135335283236612691893999494972484403407631545909575881468158872654073374)]
		[TestCase(4.999, 148.2648201253242342339591225627208985720458425149174668922941623858720050)]
		[TestCase(9.999, 22004.45033857464715721623840438148225727827858565599427258232680618244485)]
		public void Can_Exp(double left, double result)
		{
			var x = (double)new BigDecimal(left).Exp();
			x.Should().Be(result);
		}

		[TestCase(double.NaN, double.NaN)]
		[TestCase(double.NegativeInfinity, 0)]
		[TestCase(double.PositiveInfinity, double.PositiveInfinity)]
		[TestCase(0, 1)]
		[TestCase(1, 2)]
		[TestCase(-2, 0.25)]
		[TestCase(4.999, 31.97782697569448070151613937163205819747369486211219520368146244813466876)]
		[TestCase(9.999, 1023.290463222223382448516459892225862319158235587590246517806798340309400)]
		public void Can_Exp2(double left, double result)
		{
			var x = (double)new BigDecimal(left).Exp2();
			x.Should().Be(result);
		}

		[TestCase(double.NaN, double.NaN)]
		[TestCase(double.NegativeInfinity, 0)]
		[TestCase(double.PositiveInfinity, double.PositiveInfinity)]
		[TestCase(0, 1)]
		[TestCase(1, 10)]
		[TestCase(-2, 0.01)]
		[TestCase(4.999, 99770.00638225533171944219428537623105521186139457315462487823089094547653)]
		[TestCase(-3.999, 0.000100230523807789967191540488932811055405366845354216064641163485230474)]
		public void Can_Exp10(double left, double result)
		{
			var x = (double)new BigDecimal(left).Exp10();
			x.Should().Be(result);
		}
	}
}