public class BinaryTreeNode<T> {
  public static interface BinaryTreeNodeVisitor<T> {
    void apply(BinaryTreeNode<T> n);
  }

  private BinaryTreeNode<T> _left;
  private BinaryTreeNode<T> _right;
  private BinaryTreeNode<T> _parent;
  private T data;
  /** Creates a new leaf node. */
  public BinaryTreeNode(T data) {
    this(data, null, null);
  }
  /** Creates a new node. */
  public BinaryTreeNode(T data, BinaryTreeNode<T> left, BinaryTreeNode<T> right) {
    setData(data);

    if (null != left) {
      setLeft(left);
      left.setParent(this);
    }

    if (null != right) {
      setRight(right);
      right.setParent(this);
    }
  }
  public BinaryTreeNode<T> left() {
    return _left;
  }
  public void setLeft(BinaryTreeNode<T> left) {
    this._left = left;
  }
  public BinaryTreeNode<T> right() {
    return _right;
  }
  public void setRight(BinaryTreeNode<T> right) {
    this._right = right;
  }
  public BinaryTreeNode<T> parent() {
    return _parent;
  }
  public void setParent(BinaryTreeNode<T> parent) {
    this._parent = parent;
  }
  public T data() {
    return data;
  }
  public void setData(T data) {
    this.data = data;
  }
  public boolean hasChildren() {
    return null != _left || null != _right;
  }

  // three types of depth-first traversal: pre-order, in-order and post-order

  // in-order traversal: L P R
  public void traverse_inOrder_recursive(BinaryTreeNodeVisitor<T> visitor) {
    if (null != left())
      left().traverse_inOrder_recursive(visitor);

    visitor.apply(this);

    if (null != right())
      right().traverse_inOrder_recursive(visitor);
  }

  // in-order traversal: L P R
  //
  // break down the problem:
  // - _last_ step should be the _outermost_ loop: percolate up the ancestors
  // - first ("preorder") step: recurse left descendants
  // - next ("inorder") step: visit parent
  // - next ("postorder") step: visit parent's right node (go to _first_ step)
  public void traverse_inOrder_iterative(BinaryTreeNodeVisitor<T> visitor) {
    BinaryTreeNode<T> n = this;

    // part [1] of the outer loop traverses down the current left-subtree.
    // after a left-subtree is processed, part [2] "backtracks" until it finds a right-subtree.
    do {
      //[1] drill down
      
      // find the leftmost subtree
      while (null != n.left()) {
        n = n.left();
      }

      if (null != n.right()) {
        visitor.apply(n);
        n = n.right();
        continue;
      }
      
      visitor.apply(n);
      
      if (null != n.parent() && null != n.parent().right() && n != n.parent().right()) {
        visitor.apply(n.parent());
        n = n.parent().right();
        continue;
      }
      
      //[2] backtracking

      // this subtree is done; percolate up to an unvisited right-subtree
      while (null != n.parent() && n == n.parent().right()) {
        //we know the parent was already visited, because L-P-R.
        n = n.parent();
      }
      
      while (null != n.parent() && n == n.parent().left()) {
        visitor.apply(n.parent());
        if (null != n.parent().right()) {
          n = n.parent().right();
          break; // now we are in a right-subtree
        }
        n = n.parent();
        if (null != n.parent() && n != n.parent().left()) {
          while (null != n.parent() && n == n.parent().right()) {
            n = n.parent();
          }
        }
      }
      
    } while (null != n && null != n.parent());
  }

}
