def fib_memo(n, memo):
    if n in (0,1):
        return n
    if n in memo:
        return memo[n]
    memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo)
    return memo[n]

def fibonacci(n):
    return fib_memo(n, {})

print(fibonacci(21))
