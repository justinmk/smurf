# binary search tree:
#   - Nodes on the left branch are less than the node value.
#   - Nodes on the right branch are greater than the node value.

import math
import collections

class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
    def __str__(self):
        h = height(self)
        s = ''
        fill_fake_nodes_to_level(self, height(self))
        for level in range(0, h+1):
            nodes = get_nodes_at_level(self, None, level, 0)
            # print(nodes)
            print(f'len(nodes)={len(nodes)}')
            for i,n in enumerate(nodes):
                fill = (h - level + 1) * (2 if i % 2 == 0 else 1)
                if n is not None:
                    s += (fill * ' ') + str(n)
            s+= '\n'
        return s

def bfs_traverse(n, visitorfn):
    q = collections.deque()
    if n is not None:
        q.appendleft(n)
    while len(q) > 0:
        n = q.pop()
        visitorfn(n)
        if n.left is not None:
            q.appendleft(n.left)
        if n.right is not None:
            q.appendleft(n.right)

def dfs_inorder_traverse(n, visitorfn):
    thisfn = dfs_inorder_traverse
    if n is None:
        return
    if n.left is not None:
        thisfn(n.left, visitorfn)
    visitorfn(n)
    if n.right is not None:
        thisfn(n.right, visitorfn)

def dfs_outorder_traverse(n, visitorfn):
    thisfn = dfs_outorder_traverse
    if n is None:
        return
    if n.right is not None:
        thisfn(n.right, visitorfn)
    visitorfn(n)
    if n.left is not None:
        thisfn(n.left, visitorfn)

def dfs_preorder_traverse(n, visitorfn):
    thisfn = dfs_preorder_traverse
    if n is None:
        return
    visitorfn(n)
    if n.left is not None:
        thisfn(n.left, visitorfn)
    if n.right is not None:
        thisfn(n.right, visitorfn)

def fill_fake_nodes_to_level(root, level, curlevel=0):
    if root is None:
        return
    if root.left is None:
        root.left = Node('L')
    if root.right is None:
        root.right = Node('R')
    if curlevel < level:
        fill_fake_nodes_to_level(root.left, level, curlevel+1)
        fill_fake_nodes_to_level(root.right, level, curlevel+1)

# Must do fill_fake_nodes_to_level() first.
#
# nodes = get_nodes_at_level(root, None, 3, 0)  # => [None, 1, None, None, 9, None]
def get_nodes_at_level(root, nodes, level, curlevel):
    if nodes is None:
        # "grid" row, each cell is:
        #   None:   no node here
        #   ".":    fake/dummy node
        #   other:  actual data
        row_width = (pow(2, height(root) - 1) + 1)
        # Remove nodes. These will be filled as the tree is walked.
        # Remove half of all, plus half of level^2.
        row_width = (row_width
                - int(row_width/2) + math.floor(pow(2, level)/2) - 1)
        nodes = [None] * row_width
        print(f'level={level}, len(nodes)={len(nodes)} row_width={row_width}')
    if root is None:
        return nodes
    if curlevel == level:
        # print(f'{i}: {root.data}')
        nodes.append(root.data)
        return nodes
    if root.left:
        get_nodes_at_level(root.left, nodes, level, curlevel+1)
    if root.right:
        get_nodes_at_level(root.right, nodes, level, curlevel+1)
    return nodes

class BinarySearchTree:
    def __init__(self):
        self.root = None
    def create(self, val):
        if self.root == None:
            self.root = Node(val)
        else:
            current = self.root
            while True:
                if val < current.data:
                    if current.left:
                        current = current.left
                    else:
                        current.left = Node(val)
                        break
                elif val > current.data:
                    if current.right:
                        current = current.right
                    else:
                        current.right = Node(val)
                        break
                else:
                    break

def height(root):
    return heightrec(root, 0)
def heightrec(root, h):
    if root is None or (root.left is None and root.right is None):
        return h
    hl = 1
    hr = 1
    # print('left={} right={}'.format(root.left,root.right))
    if root.left:
        hl += heightrec(root.left, h)
    if root.right:
        hr += heightrec(root.right, h)
    if hl > hr:
        return h + hl
    return h + hr

tree = BinarySearchTree()
# t = [4, 2, 3, 1, 7, 6]
t = [3, 3.3, 5, 2, 1, 4, 4.1, 6, 5.1, 6.1, 9]
# t = [0]
# t = [9,1,999,9999]
for i in range(len(t)):
    tree.create(t[i])

dfs_outorder_traverse(tree.root, lambda n: print(n.data))

# print(height(tree.root))
# print(get_nodes_at_level(tree.root, None, 3, 0, 0))
print(tree.root)

# Level-order traversal.
# s = ''
# def visitor(n):
#     global s
#     if n.data not in ('L', 'R'):
#         s += ('{}, '.format(n.data))
# bfs_traverse(tree.root, visitor)
# print(s)
