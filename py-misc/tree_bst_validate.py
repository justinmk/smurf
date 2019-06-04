class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.level = None
    def __repr__(self):
        return str(self.data)
    def __str__(self):
        return str(self.data)
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

def validate(n, curmin, curmax):
    ok = True
    if n is None:
        return True
    if n.data <= curmin or n.data >= curmax:
        return False
    if n.left is not None:
        ok = ok and validate(n.left, curmin, n.data)
    if n.right is not None:
        ok = ok and validate(n.right, n.data, curmax)
    return ok

def checkBST(n):
    return (validate(n.left, 0, n.data)
            and validate(n.right, n.data, 99999))

tree = BinarySearchTree()
# t = [23, 16, 15, 9, 6, 17, 10, 13, 8, 26, 18, 2, 22, 24, 12, 5, 20, 25, 21, 4, 19, 1, 3, 14, 7, ]
# t = [4, 2, 3, 1, 7, 6]
# t = [3, 3.3, 5, 2, 1, 4, 4.1, 6, 5.1, 6.1, 9]
# t = [4, 2, 3, 1, 7, 6, 8, 9, 10, 11]
# t = [0]
# t = [9,1,999,9999]
t = [1, 2, 4, 3, 5, 6, 7]
for i in range(len(t)):
    tree.create(t[i])
n = Node(2)
n.left = Node(1)
n4 = Node(4)
n.right = n4
n4.left = Node(3)
n5 = Node(5)
n4.right = n5
n5.left = Node(6)
n5.right = Node(7)
print(checkBST(n))
