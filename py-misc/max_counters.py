# You are given N counters, initially set to 0, and you have two possible
# operations on them:

# increase(X) − counter X is increased by 1,
# max counter − all counters are set to the maximum value of any counter.
# Non-empty array A of M integers is given, representing consecutive
# operations:
#   if A[K] = X, such that 1 ≤ X ≤ N, then operation K is increase(X),
#   if A[K] = N + 1 then operation K is max counter.
# For example, given integer N = 5 and array A such that:
#     A[0] = 3
#     A[1] = 4
#     A[2] = 4
#     A[3] = 6
#     A[4] = 1
#     A[5] = 4
#     A[6] = 4
# the values of the counters after each consecutive operation will be:
#     (0, 0, 1, 0, 0)
#     (0, 0, 1, 1, 0)
#     (0, 0, 1, 2, 0)
#     (2, 2, 2, 2, 2)
#     (3, 2, 2, 2, 2)
#     (3, 2, 2, 3, 2)
#     (3, 2, 2, 4, 2)

# Given integer N and non-empty array A of M integers, returns
# a sequence of integers representing the values of the counters.
#   - N and M are integers within the range [1..100,000];
#   - each element of array A is an integer within the range [1..N + 1].
def solution(N, A):
    counters = [0] * N
    ops = A
    curmax = 0
    curmin = 0  # result of the last "max counter" operation.
    for i in range(0, len(ops)):
        x = ops[i]
        if x >= 1 and x <= N:
            # increase(x)
            if counters[x - 1] < curmin:
                counters[x - 1] = curmin + 1
            else:
                counters[x - 1] = counters[x - 1] + 1
            if counters[x - 1] > curmax:
                curmax = counters[x - 1]
        elif x == N + 1:
            # max counters: set all counters to the current max.
            #
            # OPTIMIZATION: do not iterate the counter list, only save
            # the most-recent "max" value.
            curmin = curmax
        else:
            pass  # ?
    # OPTIMIZATION: now resolve the "curmin".
    for i,v in enumerate(counters):
        if v < curmin:
            counters[i] = curmin
    return counters

print(solution(5, [3,4,4,6,1,4,4]))
print(solution(5, [3]))
print(solution(5, [1,6]))
