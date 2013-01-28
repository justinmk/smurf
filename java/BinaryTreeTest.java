import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;

import java.util.ArrayList;
import java.util.Arrays;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

@RunWith(JUnit4.class)
public class BinaryTreeTest {
	
  private ArrayList<Integer> visit_seq_int;
  private ArrayList<String> visit_seq_string;
  private BinaryTreeNode<Integer> tree1;
  private final Integer[] tree1_inorder = new Integer[] {5,4,6,3,7,2,9,8,10,1,11,0,16,15,17,14,18,13,20,19,21,12,22};
  private BinaryTreeNode<String> tree2;
  private final String[] tree2_inorder = new String[] {"A","B","C","D","E","F","G","H","I"};
  private BinaryTreeNode<String> allLeftNodes;
  private final String[] allLeftNodes_inorder = new String[] {"D","C","B","A"};
  private BinaryTreeNode<String> allRightNodes;
  private final String[] allRightNodes_inorder = new String[] {"A","B","C","D"};

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
		
        allLeftNodes = new BinaryTreeNode("A", 
            new BinaryTreeNode("B", 
                new BinaryTreeNode("C",
                    new BinaryTreeNode("D"),
                    null), 
                null),
            null);		
        
        allRightNodes = new BinaryTreeNode("A", 
            null,
            new BinaryTreeNode("B", 
                null,
                new BinaryTreeNode("C",
                    null,
                    new BinaryTreeNode("D"))));
        
		visit_seq_int = new ArrayList<Integer>();
		visit_seq_string = new ArrayList<String>();
	}
	
	@After public void teardown() {
	  System.out.println();
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
	      Arrays.equals(tree1_inorder, visit_seq_int.toArray()));
	}

	@Test public void test_traverseInOrder_iterative() {
	  tree1.traverse_inOrder_iterative(getVisitor_int());
	  assertTrue("actual visit sequence: " + Arrays.toString(visit_seq_int.toArray()), 
	      Arrays.equals(tree1_inorder, visit_seq_int.toArray()));
	}
	
	@Test public void test_traverseInOrder_recursive_singleNode() {
	  new BinaryTreeNode<String>("A").traverse_inOrder_recursive(getVisitor_string());
	  assertTrue("actual visit sequence: " + Arrays.toString(visit_seq_string.toArray()), 
	      Arrays.equals(new String[] {"A"}, visit_seq_string.toArray()));
	}

	@Test public void test_traverseInOrder_iterative_singleNode() {
	  new BinaryTreeNode<String>("A").traverse_inOrder_iterative(getVisitor_string());
	  assertTrue("actual visit sequence: " + Arrays.toString(visit_seq_string.toArray()), 
	      Arrays.equals(new String[] {"A"}, visit_seq_string.toArray()));
	}

	@Test public void test_traverseInOrder_recursive_2() {
	  tree2.traverse_inOrder_recursive(getVisitor_string());
	  assertTrue("actual visit sequence: " + Arrays.toString(visit_seq_string.toArray()), 
	      Arrays.equals(tree2_inorder, visit_seq_string.toArray()));
	}

	@Test public void test_traverseInOrder_iterative_2() {
	  tree2.traverse_inOrder_iterative(getVisitor_string());
	  assertTrue("actual visit sequence: " + Arrays.toString(visit_seq_string.toArray()), 
	      Arrays.equals(tree2_inorder, visit_seq_string.toArray()));
	}
	
    @Test public void test_traverseInOrder_recursive_allLeftNodes() {
      allLeftNodes.traverse_inOrder_recursive(getVisitor_string());
      assertTrue("actual visit sequence: " + Arrays.toString(visit_seq_string.toArray()), 
          Arrays.equals(allLeftNodes_inorder, visit_seq_string.toArray()));
    }

    @Test public void test_traverseInOrder_iterative_allLeftNodes() {
      allLeftNodes.traverse_inOrder_iterative(getVisitor_string());
      assertTrue("actual visit sequence: " + Arrays.toString(visit_seq_string.toArray()), 
          Arrays.equals(allLeftNodes_inorder, visit_seq_string.toArray()));
    }
    
    @Test public void test_traverseInOrder_recursive_allRightNodes() {
      allRightNodes.traverse_inOrder_recursive(getVisitor_string());
      assertTrue("actual visit sequence: " + Arrays.toString(visit_seq_string.toArray()), 
          Arrays.equals(allRightNodes_inorder, visit_seq_string.toArray()));
    }

    @Test public void test_traverseInOrder_iterative_allRightNodes() {
      allRightNodes.traverse_inOrder_iterative(getVisitor_string());
      assertTrue("actual visit sequence: " + Arrays.toString(visit_seq_string.toArray()), 
          Arrays.equals(allRightNodes_inorder, visit_seq_string.toArray()));
    }

}