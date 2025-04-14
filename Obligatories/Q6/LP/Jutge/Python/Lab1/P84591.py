def absValue(x):
    return abs(x)


def power(x, p):
    if p == 0:
        return 1
    else:
        if p % 2:  # Is odd
            return x*power(x*x, (p-1)//2)

        else:
            return power(x*x, p//2)


def isPrime(x):
    if x < 2:
        return False
    else:
        i = 2
        while i*i <= x:
            if x % i == 0:
                return False
            i += 1
        return True


def slowFib(n):
    if n == 0:
        return 0
    elif n < 3:
        return 1
    else:
        return slowFib(n-1) + slowFib(n-2)


def dpFib(n):
    memo = {0: 0, 1: 1}

    def f(x):
        if x in memo:
            return memo[x]
        else:
            memo[x] = f(x-1) + f(x-2)
            return memo[x]
    return f(n)


def quickFib(n):
    def f(n):
        if n == 0:
            return (0, 0)
        elif n == 1:
            return (1, 0)
        else:
            a, b = f(n-1)
            return (a+b, a)
    return f(n)[0]
