#!/bin/python3
import math
import os
import random
import re
import sys

# [GOOD] Computes the difference between two strings.
def strdiff2(a, b):
    m = {}
    diff = 0
    for c in a:
        if c not in m:
            m[c] = 0
        m[c] += 1
    for c in b:
        if c in m and m[c] > 0:
            m[c] -= 1
        else:
            diff += 1
    for k in m:
        diff += m[k]
    return diff

# [BUG] Computes the difference between two strings.
def strdiff(a, b):
    rv = 0
    a = sorted(a)
    b = sorted(b)
    cura = 0
    curb = 0
    while True:
        end = cura == len(a) - 1 or curb == len(b) - 1
        if a[cura] == b[curb]:
            if end:
                break
            cura += 1
            curb += 1
        elif a[cura] < b[curb]:
            rv += 1
            if end:
                break
            cura += 1
        elif b[curb] < a[cura]:
            rv += 1
            if end:
                break
            curb += 1
        else:
            raise RuntimeError()
        # print('rv={}, a[cura]={}, b[curb]={}'.format(rv, a[cura], b[curb]))
    extra = (((len(a) - 1) - cura) + ((len(b) - 1) - curb))
    rv += extra
    return rv

def makeAnagram(a, b):
    return strdiff(a, b)
# cdex
#    ^
# abceeeeee
#         ^
# 7

print(makeAnagram('abcxx', 'bbxx'))
print(strdiff2('abcxx', 'bbxx'))
print(makeAnagram('cdex', 'xabceeeeee'))
print(strdiff2('cdex', 'xabceeeeee'))
print(makeAnagram('cdex', 'abceeeeee'))
print(strdiff2('cdex', 'abceeeeee'))
