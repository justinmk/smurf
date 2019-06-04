import math
import os
import random
import re
import sys

# local
import trie

def longest_common_substring(s1, s2):
    t1 = trie.Trie()
    lcstr = ''
    lcstrlen = 0
    for i in range(0, len(s1)):
        for j in range(0, len(s1)):
            k = s1[i:j+1]
            if len(k) > 0:
                t1.put(k, '.')
    for i in range(0, len(s2)):
        for j in range(0, len(s2)):
            k = s2[i:j+1]
            if len(k) > lcstrlen and t1.get(k) is not None:
                # print('k={} v={}'.format(k, t1.get(k)))
                lcstr = k
                lcstrlen = len(k)
    return (lcstr, lcstrlen)

print(longest_common_substring('abc', 'foobc123'))
print(longest_common_substring('xxxabc', 'fxxxxxxoobc123'))
print(longest_common_substring('zzYabS', 'fxxxxxxooXc123'))
