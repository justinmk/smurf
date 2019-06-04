#!/bin/python3

import math
import os
import random
import re
import sys

# queue front-to-back:
#   1 2 3 4 5
#
# example:
#   2 1 5 3 4

# item can swap with the immmediate next item
# return minimum number of swaps that took place to get the queue into its current state!
# return None if the state would require a given item to swap more than 2 times with some other item.
def minimumBribes(q):
    swaps = 0  # total swaps
    for i,v in enumerate(q):
        diff = v - (i + 1)
        if diff > 2:
            return None
        # for (int j = max(0, q[i] - 2); j < i; j++)
        #     if (q[j] > q[i]) ans++;
        j = max(0, q[i] - 2)
        while j < i:
            if q[j] > q[i]:
                swaps += 1
            j += 1
    return swaps

def test(q):
    rv = minimumBribes(q)
    print('swaps={}'.format(rv))
    return rv

def test_all():
    test([1,2,3,4,5])
    test([1,3,2,4,5])
    test([1,5,3,4,2])
    test([5,3,2,4,1])
    test([2, 1, 5, 3, 4])
    # assert 3 == test([2, 1, 5, 3, 4])
    test([1, 2, 5, 3, 4, 7, 8, 6])
    #     0  0 +2 -1 +2 +2 -1 -4
    test([1, 2, 5, 3, 7, 8, 6, 4])

# 1 <= t <= 10
# 1 <= n <= 10^5
if __name__ == '__main__':
    # test_all()
    # sys.exit()

    t = int(input())
    for t_itr in range(t):
        n = int(input())
        q = list(map(int, input().rstrip().split()))
        rv = minimumBribes(q)
        print('Too chaotic' if rv is None else str(rv))
