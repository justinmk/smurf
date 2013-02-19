package smurf;

import java.util.Stack;


public class StackUtil {
	/**
	 * "Ugly" version: using 2 extra stacks. 
	 * Sorts a stack in ascending order, using <i>only</i> the following 
	 * methods: push, pop, peek, isEmpty.
	 * @return the argument, after sorting
	 */
	public static Stack<Integer> sortAscending_ugly(Stack<Integer> s) {
		if (null == s || s.isEmpty())
			return s;
		
		Stack<Integer> s2 = new Stack<Integer>();
		Stack<Integer> s3 = new Stack<Integer>();
		
		while (!s.isEmpty()) {
			int i = s.pop();
			while (!s2.isEmpty() && i < s2.peek()) {
				s3.push(s2.pop());
			}
			s2.push(i);
			while (!s3.isEmpty()) {
				s2.push(s3.pop());
			}
		}
		
		return s2;
	}
	
	/**
	 * "Fancy" version: uses only 1 extra stack. 
	 * Sorts a stack in ascending order, using <i>only</i> the following 
	 * methods: push, pop, peek, isEmpty.
	 * @return the argument, after sorting
	 */
	public static Stack<Integer> sortAscending_fancy(Stack<Integer> s) {
		if (null == s || s.isEmpty())
			return s;
		
		Stack<Integer> s2 = new Stack<Integer>();
		
		while (!s.isEmpty()) {
			int i = s.pop();
			while (!s2.isEmpty() && i < s2.peek()) {
				s.push(s2.pop());
			}
			s2.push(i);
		}
		
		return s2;
	}

}
