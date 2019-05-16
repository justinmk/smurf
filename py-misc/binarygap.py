# maximal seq of 0s surounded by 1s
# 9=1001 has gap of 2
# 529=1000010001 has max gap of 4

# Return max binary gap, or 0.
# N in the range [1..2^31]
def solution(N):
    # 0001110001010
    # 1110001010
    # 0. right-shift to each bit; AND with 1
    # 1. find first 1
    # 2. count 0s until 1
    # 3. save max
    # 4. find next 1, goto (1).
    #
    # optimizations?
    #   - N less than 2^31, 2^30, 2^29, ...
    #   -

    a = [0] * 31
    for i in range(0,31):
        lsb = (1 & (N >> i))
        a[len(a)-i-1] = lsb
    #print(a)
    max0s = 0
    nr0s = 0
    lhs1 = -1
    for i in range(0,31):
        if a[i] == 1:
            if lhs1 == -1:
                lhs1 = i
            else:
                max0s = nr0s if nr0s > max0s else max0s
                lhs1 = i
                nr0s = 0
        elif a[i] == 0:
            if lhs1 >= 0:
                nr0s += 1
            else:
                continue
        else:
            raise RuntimeError()
    return max0s
