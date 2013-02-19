package smurf;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

@RunWith(JUnit4.class)
public class StringUtilTest {

	@Test public void test_isEveryCharUnique_null() {
		assertTrue(StringUtil.isEveryCharUnique_naive(null));
	}

	@Test public void test_isEveryCharUnique_1() {
		assertTrue(StringUtil.isEveryCharUnique_naive(""));
	}

	@Test public void test_isEveryCharUnique_2() {
		assertTrue(StringUtil.isEveryCharUnique_naive("a"));
	}

	@Test public void test_isEveryCharUnique_3() {
		assertFalse(StringUtil.isEveryCharUnique_naive("aa"));
	}

	@Test public void test_isEveryCharUnique_4() {
		//for (int i = 0; i < 300000; i ++)
			assertTrue(StringUtil.isEveryCharUnique_naive("abcdefghijklmnopqrstuvwx"));
	}
	
	@Test public void test_isEveryCharUnique_5() {
		assertFalse(StringUtil.isEveryCharUnique_naive("abcdefghijklmnopqrstuvwxa"));
	}

	@Test public void test_isEveryCharUnique_6() {
		assertFalse(StringUtil.isEveryCharUnique_naive("abcdefghijklwmnopqrstuvwx"));
	}

	@Test public void test_isEveryCharUnique_linear_time_null() {
		assertTrue(StringUtil.isEveryCharUnique_linear_time(null));
	}
	
	@Test public void test_isEveryCharUnique_linear_time_1() {
		assertTrue(StringUtil.isEveryCharUnique_linear_time(""));
	}

	@Test public void test_isEveryCharUnique_linear_time_2() {
		assertTrue(StringUtil.isEveryCharUnique_linear_time("a"));
	}

	@Test public void test_isEveryCharUnique_linear_time_3() {
		assertFalse(StringUtil.isEveryCharUnique_linear_time("aa"));
	}

	@Test public void test_isEveryCharUnique_linear_time_4() {
		//for (int i = 0; i < 300000; i ++)
			assertTrue(StringUtil.isEveryCharUnique_linear_time("abcdefghijklmnopqrstuvwx"));
	}
	
	@Test public void test_isEveryCharUnique_linear_time_5() {
		assertFalse(StringUtil.isEveryCharUnique_linear_time("abcdefghijklmnopqrstuvwxa"));
	}
	
	@Test public void test_isEveryCharUnique_linear_time_6() {
		assertFalse(StringUtil.isEveryCharUnique_linear_time("abcdefghijklwmnopqrstuvwx"));
	}

}