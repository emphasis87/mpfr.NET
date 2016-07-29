using System;

namespace mpfrNET.TestApp
{
	internal class Program
	{
		private static void Main(string[] args)
		{
			Console.WriteLine("test1");

			try
			{
				var mpfr = new Mpfr();
				mpfr.Print();
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