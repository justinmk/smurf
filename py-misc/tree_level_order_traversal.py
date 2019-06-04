class Node:
    def __init__(self, info):
        self.info = info
        self.left = None
        self.right = None
        self.level = None

    def __str__(self):
        return str(self.info)

class BinarySearchTree:
    def __init__(self):
        self.root = None
    def create(self, val):
        if self.root == None:
            self.root = Node(val)
        else:
            current = self.root
            while True:
                if val < current.info:
                    if current.left:
                        current = current.left
                    else:
                        current.left = Node(val)
                        break
                elif val > current.info:
                    if current.right:
                        current = current.right
                    else:
                        current.right = Node(val)
                        break
                else:
                    break

def traverse(root, visitorfn, level):
    if root is None:
        return
    visitorfn(root, level)
    if root.left is not None:
        traverse(root.left, visitorfn, level + 1)
    if root.right is not None:
        traverse(root.right, visitorfn, level + 1)

def traverse_level_order(root, visitorfn, level, wantlevel):
    levelmap = {}
    def f(root, level):
        if level not in levelmap:
            levelmap[level] = []
        levelmap[level].append(root.info)

    traverse(root, f, level)
    i = 0
    while i in levelmap:
        for n in levelmap[i]:
            visitorfn(n)
        i += 1

# Print nodes in level-order.
def levelOrder(root):
    def printnode(n):
        print(str(n), end=' ')
    return traverse_level_order(root, printnode, 0, 0)

tree = BinarySearchTree()
# t = [4, 2, 3, 1, 7, 6]
t = [3, 3.3, 5, 2, 1, 4, 4.1, 6, 5.1, 6.1, 9]
# t = [0]
# t = [9,1,999,9999]
for i in range(len(t)):
    tree.create(t[i])
levelOrder(tree.root)
