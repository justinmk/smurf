# Doubly-linked list
class LinkedList:
    class Node:
        def __init__(self, data):
            self.prev = None
            self.next = None
            self.data = data
        def __str__(self):
            return str(self.data)
        def __repr__(self):
            return 'Node({})'.format(self.data)
    def __init__(self):
        self.head = None
        self.tail = None
        self.len = 0
    def __str__(self):
        return '{}'.format(','.join([str(o) for o in self]))
    def __repr__(self):
        return 'LinkedList({})'.format(','.join([repr(o) for o in self]))
    def _validate(self, node):
        if not isinstance(node, LinkedList.Node):
            raise RuntimeError()
    def __len__(self):  # O(1)
        return self.len
    def __iter__(self):
        node = self.head
        while node is not None:
            yield node
            node = node.next
    def append(self, data):  # O(1)
        node = LinkedList.Node(data)
        if self.head is None:
            print('xx')
            self.head = node
            self.tail = node
        else:
            self.tail.next = node
            node.prev = self.tail
            self.tail = node
        self.len += 1
    def find(self, data):
        node = self.head
        while node is not None:
            if node.data == data:
                return node
            node = node.next
        return None
    def delete(self, node):  # O(1)
        self._validate(node)
        # Remove the link.
        if self.head is node:
            self.head = node.next
        if node.prev is not None:
            node.prev.next = node.next
        if node.next is not None:
            node.next.prev = node.prev
        self.len -= 1
    def delete_val(self, data):  # O(n)
        '''Delete by value.'''
        node = self.find(data)
        if node is not None:
            self.delete(node)
            return True
        return False
    def clear(self):
        for n in self:
            self.delete(n)

if __name__ == '__main__':
    ll = LinkedList()
    ll.append(1)
    ll.append(2)
    ll.append(3)
    ll.append('foo')
    ll.append('bar')
    print(ll)
    n = ll.find('foo')
    ll.delete(n)
    print(ll.find(1))
    ll.delete_val(1)
    print(ll)
    ll.delete_val('bar')
    print(ll)
