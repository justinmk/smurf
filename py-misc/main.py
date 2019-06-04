#!/bin/python3

import math
import os
import random
import re
import sys

# Given an array `a` of `n` integers, perform `d` left rotations on the
# array.
#
# constraints:
#   1 <= d <= n
#
# idea:


def rotLeft(a, d):
    #   [1,2,3,4,5]  left-rotate 2 times
    #   =>
    #   [3,4,5] + [1,2]
    if d == len(a):
        return a
    if d > len(a):
        d = d % len(a)
    a1 = a[0:d]
    a2 = a[d:]
    return a2 + a1

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    nd = input().split()

    n = int(nd[0])
    d = int(nd[1])
    a = list(map(int, input().rstrip().split()))

    result = rotLeft(a, d)

    fptr.write(' '.join(map(str, result)))
    fptr.write('\n')

    fptr.close()

