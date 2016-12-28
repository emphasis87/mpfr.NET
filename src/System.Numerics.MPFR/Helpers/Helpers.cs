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

		public static T2? With<T1, T2>(this T1 source, Func<T1, T2> selector)
			where T2 : struct
		{
			if (source == null || selector == null)
				return default(T2?);

			return selector(source);
		}
	}
}