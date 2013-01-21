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
	
	private BinaryTreeNode tree1;
	final Integer[] tree1_expected_inorder_seq = new Integer[] { 5, 4, 6, 3, 7, 2, 9, 8, 10, 1, 11, 0, 16, 15, 17, 14, 18, 13, 20, 19, 21, 12, 22 };
	private ArrayList<Integer> visit_seq;

	@Before public void setup() {
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
		
		visit_seq = new ArrayList<Integer>();
	}
	
	BinaryTreeNode.BinaryTreeNodeVisitor getVisitor() {
		return new BinaryTreeNode.BinaryTreeNodeVisitor() {
			@Override public void apply(BinaryTreeNode n) {
				visit_seq.add(n.getData());
				System.out.print(n.getData() + " ");
			}
		};
	}

	@Test public void test_traverseInOrder_recursive() {
		tree1.traverse_inOrder_recursive(getVisitor());
		assertTrue("actual visit sequence: " + Arrays.toString(visit_seq.toArray()), 
				Arrays.equals(tree1_expected_inorder_seq, visit_seq.toArray()));
	}
	
	@Test public void test_traverseInOrder_iterative() {
		tree1.traverse_inOrder_iterative(getVisitor());
		assertTrue("actual visit sequence: " + Arrays.toString(visit_seq.toArray()), 
				Arrays.equals(tree1_expected_inorder_seq, visit_seq.toArray()));
	}

}