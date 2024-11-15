def absValue(x):
    if x >= 0:
        return x
    else:
        return -x


def power(x, p):
    return x**p


def isPrime(x):
    if x <= 1:
        return False
    i = 2
    while i * i <= x:
        if x % i == 0:
            return False
        i += 1
    return True


def slowFib(x):
    if x == 0:
        return 0
    elif x == 1:
        return 1
    else:
        return slowFib(x - 1) + slowFib(x - 2)


def quickFib(x):
    return quickFibAux(x)[0]


def quickFibAux(x):
    if x == 0:
        return 0, 0
    elif x == 1:
        return 1, 0
    else:
        a, b = quickFibAux(x - 1)
        return (a + b, a)
