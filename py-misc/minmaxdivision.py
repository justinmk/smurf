# Given integers K, M and non-empty array A of N integers.
# Every element of the array is not greater than M.
# Divide this array into K blocks of consecutive elements. The size of the
# block is any integer between 0 and N. Every element of the array should
# belong to some block.

# The sum of the block from X to Y equals A[X] + A[X + 1] + ... + A[Y]. The sum of empty block equals 0.
# The large sum is the maximal sum of any block.
# For example, you are given integers K = 3, M = 5 and array A such that:
#   A[0] = 2
#   A[1] = 1
#   A[2] = 5
#   A[3] = 1
#   A[4] = 2
#   A[5] = 2
#   A[6] = 2   => 6  # minimal large sum
# The array can be divided, for example, into the following blocks:
# [2, 1, 5, 1, 2, 2, 2], [], [] with a large sum of 15;
# [2], [1, 5, 1, 2], [2, 2] with a large sum of 9;
# [2, 1, 5], [], [1, 2, 2, 2] with a large sum of 8;
# [2, 1], [5, 1], [2, 2, 2] with a large sum of 6.

# given integers K, M and a non-empty array A consisting of N integers, returns
# the minimal large sum.
#
# assumptions:
#   N and K are integers within the range [1..100,000];
#   M is an integer within the range [0..10,000];
#   each element of array A is an integer within the range [0..M].
def solution(K, M, A):
    blocks = [A]
    maxblock = A
    minmaxsum_all = -1
    for k in range(K, 1, -1):
        i, minmaxsum, maxblock, b1, b2 = divide2minmax(maxblock)
        if minmaxsum > minmaxsum_all:
            minmaxsum_all = minmaxsum
        # print('k={} maxblock={}'.format(k, maxblock))
        blocks.append(b1)
        blocks.append(b2)
    # print('minmaxsum_all={} blocks={}'.format(minmaxsum_all, blocks))
    return minmaxsum_all

def sum(a):
    num = 0
    for n in a:
        num += n
    return num

def divide2minmax(A):
    b1 = []
    b2 = []
    sumofall = sum(A)
    b1sum = 0
    b2sum = sumofall
    minmaxsum = -1
    maxblock = None
    ibest = -1
    for i in range(0, len(A)):
        b1 = A[:i]
        b2 = A[i:]
        if i > 0:
            b1sum = b1sum + A[i-1]
            b2sum = b2sum - A[i-1]
        if maxblock is None or max(b1sum, b2sum) < minmaxsum:
            minmaxsum = max(b1sum, b2sum)
            maxblock = b1 if b1sum > b2sum else b2
            ibest = i
        # print('{} {} = {}, {}'.format(b1, b2, b1sum, b2sum))
    # print('minmaxsum={}, ibest={}'.format(minmaxsum, ibest))
    return ibest, minmaxsum, maxblock, b1, b2

print(solution(3, 5, [2,1,5,1,2,2,2]))
