import math
import os
import random
import re
import sys
import bisect
import collections

def getmidpoints(a):
    mid1 = math.floor(len(a) / 2.0)
    mid2 = mid1
    if len(a) % 2 == 0:
        mid2 = mid1-1
    return mid1, mid2

# Flag if daily spend is >=2x the median from `d` trailing days.
# No flag if fewer than `d` trailing days.
#
# a: list of expenditures
# d: number of trailing days to analyze
def activityNotifications(a, d):
    if len(a) <= d:
        return 0
    notifs = 0
    even = d % 2 == 0
    # OPTIM: sort once, use bisect-insert thereafter.
    sorted_a = sorted(a[0:d])
    # OPTIM: Keep track of oldest item.
    fifo = collections.deque(a[0:d])  # Use deque.popleft() for FIFO behavior.
    # OPTIM: calculate midpoints once.
    mid1, mid2 = getmidpoints(sorted_a)
    for i in range(d, len(a)):
        median = float((sorted_a[mid1] + sorted_a[mid2]) / 2)
        # if i % 1000 == 0:
        #     print('sorted_a={}, len(sorted_a)={} a[i]={} median={}, (2*median)={}'.format(sorted_a[:10], len(sorted_a), a[i], median, (2*median)))
        if a[i] >= (2 * median):
            notifs += 1
        # Delete oldest item.
        i_oldest = bisect.bisect_left(sorted_a, fifo.popleft())
        del sorted_a[i_oldest]
        # Track newest item.
        fifo.append(a[i])
        # Insert new item in-order.
        bisect.insort_left(sorted_a, a[i])
    return notifs

print(activityNotifications([10, 20, 30, 40, 50], 3))
print(activityNotifications([2, 3, 4, 2, 3, 6, 8, 4, 5], 5))
print(activityNotifications([1, 2, 3, 4, 4], 4))

# bigggg = []
# with open('bank_validation-test-input01.txt','r') as f:
#     for l in f:
#         bigggg = [int(i) for i in l.split(' ')]
# print('len(bigggg)={}'.format(len(bigggg)))
# print(activityNotifications(bigggg, 10000))
