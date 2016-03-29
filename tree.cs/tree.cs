using System;
using System.Linq;
using System.Threading;
using System.Collections.Generic;

public class Node {
  public Node Parent = null;
  public Node Left = null;
  public Node Right = null;
  public String Label = null;

  public Node(String label) {
    this.Label = label;
  }
  public Node WithLeft(String label) {
    if (this.Left != null) {
      throw new InvalidOperationException("left already exists");
    }
    this.Left = new Node(label);
    return this.Left;
  }
  public Node WithRight(String label) {
    if (this.Right != null) {
      throw new InvalidOperationException("right already exists");
    }
    this.Right = new Node(label);
    return this.Right;
  }
  public Node WithBoth(String leftLabel, String rightLabel) {
    WithLeft(leftLabel);
    WithRight(rightLabel);
    return this;
  }

  private static void visitDfs(Node node, Action<Node,int> visitFn, int level) {
    visitFn(node, level);
    if (node.Left != null) {
      visitDfs(node.Left, visitFn, level + 1);
    }
    if (node.Right != null) {
      visitDfs(node.Right, visitFn, level + 1);
    }
  }
  public static void TraverseDfs(Node root, Action<Node,int> visitFn) {
    visitDfs(root, visitFn, 0);
  }

  private static void visitChildrenBfs(Queue<Node> nodes, Action<Node,int> visitFn, int level) {
    var children = new Queue<Node>();
    while(nodes.Count > 0) {
      var node = nodes.Dequeue();
      visitFn(node, level);
      if (node.Left != null) {
        children.Enqueue(node.Left);
      }
      if (node.Right != null) {
        children.Enqueue(node.Right);
      }
    }

    if (children.Count <= 0) {
      return;
    }
    visitChildrenBfs(children, visitFn, level + 1);
  }
  public static void TraverseBfs(Node root, Action<Node,int> visitFn) {
    visitChildrenBfs(new Queue<Node>(new Node[]{root}), visitFn, 0);
  }
}

public class TreeSmurf {
  private static Node testTree1() {
    var tree = new Node("0");
    tree.WithBoth("R", "L")
      .Left
      .WithLeft("A")
      .WithRight("B");
    var nodeX = tree.Right
      .WithRight("X");
    nodeX.WithBoth("Y", "Z").Left.WithLeft("M");
    return tree;
  }

  private static int g_curLevel = 0;
  public static void Main(string[] args) {
    Node.TraverseDfs(testTree1(), (o,i) => {
        if (g_curLevel != i) {
          Console.WriteLine(" level="+i);
          Console.Write("\n");
          g_curLevel = i;
        }
        Console.Write(o.Label+" ");
      });
  }
}
