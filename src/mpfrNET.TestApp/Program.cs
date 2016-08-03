using System;
using System.ArbitraryPrecision;
using System.Globalization;

namespace mpfrNET.TestApp
{
	internal class Program
	{
		private static void Main(string[] args)
		{
			Console.WriteLine("test1");

			try
			{
				var dec = new BigDecimal(2.1, 200);
				//var dec = BigDecimal.NegativeInfinity;
				dec.IncreaseBy(1.2);
				Console.WriteLine(dec.ToString());
				//var mpfr = new Mpfr();
				//mpfr.Print();
			}
			catch (Exception ex)
			{
				Console.Write(ex);
			}

			Console.WriteLine("test2");
			Console.Read();
		}
	}
}