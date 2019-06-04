#!/bin/python3

import math
import os
import random
import re
import sys

def maximumToys(prices, k):
    prices = sorted(prices)
    remaining = k
    got = 0
    for p in prices:
        if p <= remaining:
            got += 1
            remaining -= p
        else:
            break
    return got


print(maximumToys([1, 12, 5, 111, 200, 1000, 10], 50))
