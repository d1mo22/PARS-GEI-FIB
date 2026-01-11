def myLength(L):
    l = 0
    for x in L:
        l += 1
    return l


def myMaximum(L):
    m = L[0]
    for x in L:
        if x > m:
            m = x
    return m


def average(L):
    return sum(L)/len(L)


def buildPalindrome(L):
    return L[::-1] + L


def remove(L1, L2):
    return [x for x in L1 if x not in L2]


def flatten(L):
    res = []
    for x in L:
        if isinstance(x, list):
            res.extend(flatten(x))
        else:
            res.append(x)
    return res


def oddsNevens(L):
    odds, evens = [], []
    for x in L:
        if x % 2:
            odds.append(x)
        else:
            evens.append(x)
    return (odds, evens)


def isPrime(x):
    if x <= 1:
        return False
    i = 2
    while i * i <= x:
        if x % i == 0:
            return False
        i += 1
    return True


def primeDivisors(n):
    divisors = []
    for x in range(2, n + 1):
        if isPrime(x) and n % x == 0:
            divisors.append(x)
    return divisors
