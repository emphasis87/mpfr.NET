using System.Runtime.InteropServices;

namespace System.Numerics.MPFR
{
	[StructLayout(LayoutKind.Sequential)]
	public class mpfr_struct
	{
		public ulong mpfr_prec;
		public int mpfr_sign;
		public long mpfr_exp;
		public IntPtr mpfr_d;
	}
}