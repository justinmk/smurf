import collections

class MyQueue(object):
    def __init__(self):
        self.in_ = collections.deque()
        self.out = collections.deque()
    def __len__(self):
        if len(self.in_) > 0:
            return len(self.in_)
        if len(self.out) > 0:
            return len(self.out)
        return 0
    def peek(self):
        if len(self.out) == 0:
            while len(self.in_) > 0:
                self.out.append(self.in_.pop())
        if len(self.out) > 0:
            return self.out[-1]
    def pop(self):
        if len(self.out) == 0:
            while len(self.in_) > 0:
                self.out.append(self.in_.pop())
        if len(self.out) > 0:
            return self.out.pop()
    def put(self, value):
        self.in_.append(value)

queue = MyQueue()
queue.put(1)
queue.put(2)
queue.put(3)
queue.put(4)
queue.put(5)
queue.put(6)
queue.put(7)
queue.put(8)
print(queue.peek())
print(queue.peek())
while len(queue) > 0:
    print(queue.pop())

