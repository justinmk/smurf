def minimumAbsoluteDifference(arr):
    a_sorted = sorted(arr)
    minabsdiff = -1
    for i,v in enumerate(a_sorted):
        offset = 1
        if i + offset == len(a_sorted):
            break
        v2 = a_sorted[i + offset]
        diff = abs(v - v2)
        if minabsdiff == -1 or diff < minabsdiff:
            minabsdiff = diff
    return minabsdiff


print(minimumAbsoluteDifference([-2, 2, 4]))
print(minimumAbsoluteDifference([3, -7, 0]))
print(minimumAbsoluteDifference([-59, -36, -13, 1, -53, -92, -2, -96, -54, 75]))
