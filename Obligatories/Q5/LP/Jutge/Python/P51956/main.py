def myLength(L):
    i = 0
    for x in L:
        i += 1
    return i


def myMaximum(L):
    i = L[0]
    for x in L:
        i = max(i, x)
    return i


def average(L):
    return sum(L) / len(L)


def buildPalindrome(L):
    return list(reversed(L)) + L


def remove(L1, L2):
    return [x for x in L1 if x not in L2]


def flatten(L):
    result = []
    for item in L:
        if isinstance(item, list):
            result.extend(flatten(item))
        else:
            result.append(item)
    return result


def oddsNevens(L):
    odd = []
    even = []
    for x in L:
        if x % 2 == 0:
            even.append(x)
        else:
            odd.append(x)
    return odd, even


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
