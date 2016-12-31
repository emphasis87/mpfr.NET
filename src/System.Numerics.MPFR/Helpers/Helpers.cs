using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace System.Numerics.MPFR.Helpers
{
	public static class Helpers
	{
		/// <summary>
		/// Resolve the given path to a full absolute path.
		/// If the path is rooted, then the parent is not used.
		/// </summary>
		/// <param name="path">The path to resolve, either relative or absolute</param>
		/// <param name="parent">The optional parent for a relative path</param>
		/// <returns>The resolved full absolute path</returns>
		public static string ResolvePath(this string path, string parent = null)
		{
			if (path == null)
				return null;

			if (parent != null && !Path.IsPathRooted(path))
				path = Path.Combine(parent, path);

			return Path.GetFullPath(path);
		}

		public static string Collapse(this string str)
		{
			return string.IsNullOrWhiteSpace(str) ? null : str.Trim();
		}

		public static bool IsVoid(this string str) => string.IsNullOrWhiteSpace(str);

		public static string AtLeast(this string str, string atLeast)
		{
			return str.Collapse() ?? atLeast;
		}

		public static IEnumerable<string> NotVoid(this IEnumerable<string> items)
		{
			return items?.Where(x => !string.IsNullOrWhiteSpace(x)) ?? new string[0];
		}

		public static IEnumerable<string> Trim(this IEnumerable<string> items)
		{
			return items?.Select(x => x?.Trim()) ?? new string[0];
		}

		public static IEnumerable<string> Clean(this IEnumerable<string> items)
		{
			return items?.Trim().NotVoid() ?? new string[0];
		}

		public static void ForEach<T>(this IEnumerable<T> items, Action<T> action)
		{
			if (action == null || items == null)
				return;

			foreach (var item in items)
				action(item);
		}

		public static TValue Retrieve<TKey, TValue>(this IDictionary<TKey, TValue> dict, TKey key)
		{
			if (dict == null)
				return default(TValue);

			return dict.ContainsKey(key) ? dict[key] : default(TValue);
		}

		public static T2? ProduceNullable<T1, T2>(this T1 source, Func<T1, T2> selector)
			where T2 : struct
		{
			if (source == null || selector == null)
				return default(T2?);

			return selector(source);
		}

		public static T2 Produce<T1, T2>(this T1 source, Func<T1, T2> selector)
			where T2 : class
		{
			if (source == null || selector == null)
				return default(T2);

			return selector(source);
		}

		public static IEnumerable<object> ToEnumerable(this IEnumerable enumerable)
		{
			if (enumerable == null)
				yield break;

			var enm = enumerable.GetEnumerator();
			while (enm.MoveNext())
				yield return enm.Current;
		}

		public static void SplitParts(this string str, long index, out string left, out string right)
		{
			if (index > int.MaxValue)
				throw new FormatException($"Unable to split string to parts longer than {int.MaxValue}.");

			SplitParts(str, (int)index, out left, out right);
		}

		public static void SplitParts(this string str, int index, out string left, out string right)
		{
			if (index < 1)
			{
				left = "";
				right = str;
			}
			else if (index < str.Length)
			{
				left = str.Substring(0, index);
				right = str.Substring(index);
			}
			else
			{
				left = str;
				right = "";
			}
		}

		public static string PrependOnce(this string str, string prefix)
		{
			return str.StartsWith(prefix) ? str : prefix + str;
		}

		public static string SkipOnce(this string str, string prefix)
		{
			return str.StartsWith(prefix) ? str.Remove(0, prefix.Length) : str;
		}

		public static string TakeLast(this string str, int n = 1)
		{
			if (str.IsVoid())
				return string.Empty;

			if (n < 0)
			{
				if (str.Length + n < 0)
					return string.Empty;

				return str.Substring(str.Length + n);
			}

			if (n > str.Length)
				n = str.Length;

			return str.Substring(str.Length - n);
		}

		public static string SkipFirst(this string str, int n = 1) => str.TakeLast(-n);

		public static string TakeFirst(this string str, int n = 1)
		{
			if (str.IsVoid())
				return string.Empty;

			if (n < 0)
			{
				if (str.Length + n < 0)
					return str;

				return str.Substring(0, str.Length + n);
			}

			if (n > str.Length)
				n = str.Length;

			return str.Substring(0, n);
		}

		public static string SkipLast(this string str, int n = 1) => str.TakeFirst(-n);

		public static bool IsEmpty<T>(this IEnumerable<T> items)
		{
			if (items == null)
				return true;

			var items1 = items as T[];
			if (items1 != null)
				return items1.Length == 0;

			var collection1 = items as ICollection;
			if (collection1 != null)
				return collection1.Count == 0;

			var collection2 = items as ICollection<T>;
			if (collection2 != null)
				return collection2.Count == 0;

			return !items.Any();
		}
	}
}