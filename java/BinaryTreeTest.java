import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;

import java.util.ArrayList;
import java.util.Arrays;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

@RunWith(JUnit4.class)
public class BinaryTreeTest {
	
	private BinaryTreeNode<Integer> tree1;
	private BinaryTreeNode<String> tree2;
	final Integer[] tree1_expected_inorder_seq = new Integer[] { 5, 4, 6, 3, 7, 2, 9, 8, 10, 1, 11, 0, 16, 15, 17, 14, 18, 13, 20, 19, 21, 12, 22 };
	final String[] tree2_expected_inorder_seq = new String[] {"A","B","C","D","E","F","G","H","I"};
	private ArrayList<Integer> visit_seq_int;
	private ArrayList<String> visit_seq_string;

	@SuppressWarnings({ "unchecked", "rawtypes" }) @Before public void setup() {
		tree1 = new BinaryTreeNode(0, 
				new BinaryTreeNode(1, 
						new BinaryTreeNode(2, 
								new BinaryTreeNode(3, 
										new BinaryTreeNode(4, 
												new BinaryTreeNode(5), 
												new BinaryTreeNode(6)), 
										new BinaryTreeNode(7)), 
								new BinaryTreeNode(8, 
										new BinaryTreeNode(9), 
										new BinaryTreeNode(10))), 
						new BinaryTreeNode(11)), 
				new BinaryTreeNode(12, 
						new BinaryTreeNode(13, 
								new BinaryTreeNode(14, 
										new BinaryTreeNode(15, 
												new BinaryTreeNode(16), 
												new BinaryTreeNode(17)), 
										new BinaryTreeNode(18)), 
								new BinaryTreeNode(19, 
										new BinaryTreeNode(20), 
										new BinaryTreeNode(21))), 
						new BinaryTreeNode(22)));

		tree2 = new BinaryTreeNode("F", 
				new BinaryTreeNode("B", 
						new BinaryTreeNode("A"), 
						new BinaryTreeNode("D",
								new BinaryTreeNode("C"),
								new BinaryTreeNode("E"))), 
				new BinaryTreeNode("G", 
						null,
						new BinaryTreeNode("I", 
								new BinaryTreeNode("H"),
								null)));

		visit_seq_int = new ArrayList<Integer>();
		visit_seq_string = new ArrayList<String>();
	}
	
	BinaryTreeNode.BinaryTreeNodeVisitor<Integer> getVisitor_int() {
		return new BinaryTreeNode.BinaryTreeNodeVisitor<Integer>() {
			@Override public void apply(BinaryTreeNode<Integer> n) {
				visit_seq_int.add(n.data());
				System.out.print(n.data() + " ");
			}
		};
	}
	
	BinaryTreeNode.BinaryTreeNodeVisitor<String> getVisitor_string() {
		return new BinaryTreeNode.BinaryTreeNodeVisitor<String>() {
			@Override public void apply(BinaryTreeNode<String> n) {
				visit_seq_string.add(n.data());
				System.out.print(n.data() + " ");
			}
		};
	}

	@Test public void test_traverseInOrder_recursive() {
		tree1.traverse_inOrder_recursive(getVisitor_int());
		assertTrue("actual visit sequence: " + Arrays.toString(visit_seq_int.toArray()), 
				Arrays.equals(tree1_expected_inorder_seq, visit_seq_int.toArray()));
	}
	
	@Test public void test_traverseInOrder_iterative() {
		tree1.traverse_inOrder_iterative(getVisitor_int());
		assertTrue("actual visit sequence: " + Arrays.toString(visit_seq_int.toArray()), 
				Arrays.equals(tree1_expected_inorder_seq, visit_seq_int.toArray()));
	}
	
	@Test public void test_traverseInOrder_recursive_2() {
		tree2.traverse_inOrder_recursive(getVisitor_string());
		assertTrue("actual visit sequence: " + Arrays.toString(visit_seq_string.toArray()), 
				Arrays.equals(tree2_expected_inorder_seq, visit_seq_string.toArray()));
	}
	
	@Test public void test_traverseInOrder_iterative_2() {
		tree2.traverse_inOrder_iterative(getVisitor_string());
		assertTrue("actual visit sequence: " + Arrays.toString(visit_seq_string.toArray()), 
				Arrays.equals(tree2_expected_inorder_seq, visit_seq_string.toArray()));
	}

}