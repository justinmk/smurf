class Node:
    def __init__(self, info):
        self.info = info
        self.left = None
        self.right = None
        self.level = None
    def __repr__(self):
        return str(self.info)
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

def collect_ancestors(n, v, ancestors):
    if n.left is not None and v <= n.info:
        ancestors.append(n)
        collect_ancestors(n.left, v, ancestors)
    elif n.right is not None and v >= n.info:
        ancestors.append(n)
        collect_ancestors(n.right, v, ancestors)

# Gets the lowest common ancestor, where "lowest" means "deepest in the tree"
# (greatest depth).
# def lca(root, v1, v2):
#     v1_ancestors = []
#     v2_ancestors = []
#     collect_ancestors(root, v1, v1_ancestors)
#     collect_ancestors(root, v2, v2_ancestors)
#     print(v1_ancestors)
#     print(v2_ancestors)
#     lowest_common_ancestor = root
#     for i in range(0, min(len(v1_ancestors), len(v2_ancestors))):
#         a1 = v1_ancestors[i]
#         a2 = v2_ancestors[i]
#         # print('a1={}, a2={}'.format(a1,a2))
#         if a1.info == a2.info:  # common?
#             lowest_common_ancestor = a1
#     return lowest_common_ancestor

# The value of a common ancestor always must be between the two target values.
def lca(root, v1, v2):
    if v1 < root.info and v2 < root.info:
        return lca(root.left, v1, v2)
    if v1 > root.info and v2 > root.info:
        return lca(root.right, v1, v2)
    return root

tree = BinarySearchTree()
# t = [23, 16, 15, 9, 6, 17, 10, 13, 8, 26, 18, 2, 22, 24, 12, 5, 20, 25, 21, 4, 19, 1, 3, 14, 7, ]
# t = [4, 2, 3, 1, 7, 6]
t = [3, 3.3, 5, 2, 1, 4, 4.1, 6, 5.1, 6.1, 9]
# t = [4, 2, 3, 1, 7, 6, 8, 9, 10, 11]
# t = [0]
# t = [9,1,999,9999]
for i in range(len(t)):
    tree.create(t[i])
print(lca(tree.root, 6.1,9))
