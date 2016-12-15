using System.Text;
using static System.Numerics.MPFR.MPFRLibrary;

namespace System.Numerics.MPFR
{
	public partial class BigFloat
	{
		private mpfr_struct _value;
		private ulong _precision = DefaultPrecision;

		/// <summary>
		/// The precision of the underlying number in bits.
		/// Note that setting this will erase the current value of this instance.
		/// </summary>
		public ulong Precision
		{
			get { return _precision; }
			set
			{
				if (_precision != value)
				{
					_precision = value;
					if (_value != null)
						mpfr_set_prec(_value, value);
				}
			}
		}

		public override string ToString()
		{
			long exp = 0;
			var capacity = (int)(Precision / 2 + 8);
			var sbase = 10;
			uint significantDigits = 0;
			var sb = new StringBuilder(capacity);
			mpfr_get_str(sb, ref exp, sbase, significantDigits, _value, GetRounding());
			return sb.ToString();
		}

		protected void Initialize(ulong? precision = null)
		{
			var v = new mpfr_struct();
			mpfr_init2(v, precision ?? Precision);
			_value = v;
		}
	}
}