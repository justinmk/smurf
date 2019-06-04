import math
import os
import random
import re
import sys
import collections

def isBalanced(s):
    stack = collections.deque()
    brackets = {'{':'}', '[':']', '(':')',}
    rbrackets = set(brackets.values())
    for c in s:
        if c in brackets.keys():
            stack.append(c)  # push to stack
        elif c in rbrackets:
            if len(stack) == 0:
                return False
            l = stack.pop()  # pop from stack
            if c != brackets[l]:
                return False
        else:
            print('skipped: {}'.format(c))
    return len(stack) == 0

print(isBalanced('()'))
print(isBalanced('())'))
print(isBalanced(')'))
print(isBalanced('[{()()()}]'))
print(isBalanced('[{()()()}][[['))
