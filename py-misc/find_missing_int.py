# given an array A, returns the value of the missing element.
# For example, given array A such that:
#   A[0] = 2
#   A[1] = 3
#   A[2] = 1
#   A[3] = 5
# the function should return 4, as it is the missing element.
# Write an efficient algorithm for the following assumptions:
#   N is an integer within the range [0..100,000];
#   the elements of A are all distinct;
#   each element of array A is an integer within the range [1..(N + 1)].

def solution(A):
    expected = 0
    actual = 0
    for i in range(0, len(A)):
        actual += A[i]
        expected += (i + 1)
    expected += (1 + len(A))
    return expected - actual


print(solution([2, 3, 1, 5]))
print(solution([4, 1, 3]))
print(solution([1, 3]))
print(solution([1]))
print(solution([]))
