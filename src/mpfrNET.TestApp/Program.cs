using System;
using System.ArbitraryPrecision;

namespace mpfrNET.TestApp
{
	internal class Program
	{
		private static void Main(string[] args)
		{
			try
			{
				var dec = new BigDecimal("2.1", 10, 300);
				//dec.Add(new BigDecimal("1.2", 10, 100));

				Console.WriteLine(dec);
			}
			catch (Exception ex)
			{
				Console.Write(ex);
			}
		}
	}
}