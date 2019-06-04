#!/bin/python3

import math
import os
import random
import re
import sys

# in: "ABABA" string
# out: string after removing matching adjacent chars.
#
# example:
#     AAAA        =>    3
#     BBBBB       =>    4
#     ABABABAB    =>    0
#     BABABA      =>    0
#     AAABBB      =>    4
def alternatingCharacters(s):
    last = ''
    deletions_needed = 0
    for c in s:
        if c == last:
            deletions_needed += 1
        last = c
    return deletions_needed


# if __name__ == '__main__':
#     assert 3 == alternatingCharacters('AAAA')
#     assert 4 == alternatingCharacters('BBBBB')
#     assert 0 == alternatingCharacters('ABABABAB')
#     assert 0 == alternatingCharacters('BABABA')
#     assert 4 == alternatingCharacters('AAABBB')
#     print('ok')

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')
    q = int(input())
    for q_itr in range(q):
        s = input()
        result = alternatingCharacters(s)
        fptr.write(str(result) + '\n')
    fptr.close()
