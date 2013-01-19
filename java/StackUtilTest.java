import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;

import java.util.Arrays;
import java.util.Stack;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

@RunWith(JUnit4.class)
public class StackUtilTest {
	
	private int[] unsortedInts;
	private int[] sortedInts;
	private int length;
	private Stack<Integer> inputStack;
	private Stack<Integer> sortedStack;

	@Before public void setup() {
		unsortedInts = new int[] {3,4,5345,2,2,7,9,0,1,2,23,45,79,9,7,54,34};
		sortedInts = unsortedInts.clone();
		Arrays.sort(sortedInts);
		length = sortedInts.length;
		
		inputStack = new Stack<Integer>();
		sortedStack = new Stack<Integer>();
		
		//sanity check
		assert unsortedInts[0] == 3;
		assert unsortedInts[length-1] == 34;
		assert sortedInts[0] == 0;
		assert sortedInts[length-1] == 5345;
		assert !inputStack.equals(sortedStack);
		
		for (int i = 0; i < length; i++) {
			inputStack.add(unsortedInts[i]);
			sortedStack.add(sortedInts[i]);
		}
	}

	@Test public void test_sortAscending_ugly() {
		assertTrue(sortedStack.equals(StackUtil.sortAscending_ugly(inputStack)));

	}
	
	@Test public void test_sortAscending_fancy() {
		assertTrue(sortedStack.equals(StackUtil.sortAscending_fancy(inputStack)));

	}

}