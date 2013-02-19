package smurf;

import java.util.HashSet;
import java.util.Set;

public class StringUtil {

	// time:  O(n^2) for alphabet of size n
	// space: constant
	public static boolean isEveryCharUnique_naive(String s) {
		if (null == s)
			return true;
		System.out.print("testing string: " + s + " ");
		char[] chars = s.toCharArray();
		for (int i = 0; i < chars.length; i++) {
			for (int j = i+1; j < chars.length; j++) {
				if (chars[i] == chars[j]) {
					System.out.println("| dup: " + chars[i]);
					return false;
				}
			}			
		}
		System.out.println();
		return true;
	}
	
	// time:  O(n) for alphabet of size n
	// space: O(n) for alphabet of size n
	public static boolean isEveryCharUnique_linear_time(String s) {
		if (null == s)
			return true;
		System.out.print("testing string: " + s + " ");
		Set<Character> found = new HashSet<Character>();
		char[] chars = s.toCharArray();
		for (int i = 0; i < chars.length; i++) {
			if (!found.add(chars[i])) {
				System.out.println("| dup: " + chars[i]);
				return false;
			}
		}
		System.out.println();
		return true;
	}

}
