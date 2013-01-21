
public class BinaryTreeNode {
	public static interface BinaryTreeNodeVisitor {
		void apply(BinaryTreeNode n);
	}
	
	private BinaryTreeNode _left;
	private BinaryTreeNode _right;
	private BinaryTreeNode _parent;
	private int data;
	/** Creates a new leaf node. */
	public BinaryTreeNode(int data) {
		this(data, null, null);
	}
	/** Creates a new node. */
	public BinaryTreeNode(int data, BinaryTreeNode left, BinaryTreeNode right) {
		setData(data);
		setLeft(left);
		setRight(right);
	}
	public BinaryTreeNode left() {
		return _left;
	}
	public void setLeft(BinaryTreeNode left) {
		this._left = left;
	}
	public BinaryTreeNode right() {
		return _right;
	}
	public void setRight(BinaryTreeNode right) {
		this._right = right;
	}
	public BinaryTreeNode parent() {
		return _parent;
	}
	public void setParent(BinaryTreeNode parent) {
		this._parent = parent;
	}
	public int data() {
		return data;
	}
	public void setData(int data) {
		this.data = data;
	}
	public boolean hasChildren() {
		return null != _left || null != _right;
	}

	//three types of depth-first traversal: pre-order, in-order and post-order
	
	//in-order traversal: L P R
	public void traverse_inOrder_recursive(BinaryTreeNodeVisitor visitor) {
		if (null != left())
			left().traverse_inOrder_recursive(visitor);
		
		visitor.apply(this);
		
		if (null != right())
			right().traverse_inOrder_recursive(visitor);
	}
	
	public void traverse_inOrder_iterative(BinaryTreeNodeVisitor visitor) {
		BinaryTreeNode n = this;
		BinaryTreeNode leftMost = null;
		while (true) {
			if (null == n.left()) {
				if (null == n.right()) {
					visitor.apply(n);
				}
				else { 
					n = n.right();
				}

				visitor.apply(n);
			}
			else { //get leftmost
				n = n.left();
			}
		}
	}

}
