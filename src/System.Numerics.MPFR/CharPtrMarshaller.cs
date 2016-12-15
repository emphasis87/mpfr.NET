using System.Runtime.InteropServices;

namespace System.Numerics.MPFR
{
	internal class CharPtrMarshaler : ICustomMarshaler
	{
		internal static readonly CharPtrMarshaler _instance = new CharPtrMarshaler();

		public static ICustomMarshaler GetInstance(string cookie) => _instance;

		public object MarshalNativeToManaged(IntPtr pNativeData) => Marshal.PtrToStringAnsi(pNativeData);
		public IntPtr MarshalManagedToNative(object managedObj) => IntPtr.Zero;

		public void CleanUpNativeData(IntPtr pNativeData)
		{
		}

		public void CleanUpManagedData(object managedObj)
		{
		}

		public int GetNativeDataSize() => IntPtr.Size;
	}
}