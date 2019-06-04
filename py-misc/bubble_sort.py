#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the countSwaps function below.
def countSwaps(a):
    nrswaps = 0
    for i in range(0, len(a)):
        for j in range(0, i):
            if a[i] < a[j]:
                tmp = a[i]
                a[i] = a[j]
                a[j] = tmp
                nrswaps += 1
    print('Array is sorted in {} swaps.'.format(nrswaps))
    print('First Element: {}'.format(a[0]))
    print('Last Element: {}'.format(a[-1]))



if __name__ == '__main__':
    n = int(input())
    a = list(map(int, input().rstrip().split()))
    countSwaps(a)


