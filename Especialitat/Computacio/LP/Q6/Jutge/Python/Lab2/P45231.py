import time
from itertools import count


def fibs():
    a = 0
    yield a
    b = 1
    while True:
        yield b
        a, b = b, a+b


def roots(x):
    yield x
    y = x
    while True:
        y = 1/2*(y + x / y)
        yield y


def primes():
    x = 2
    while True:
        if isPrime(x):
            yield x
        x += 1


def isPrime(x):
    if x < 2:
        return False
    i = 2
    while i*i <= x:
        if x % i == 0:
            return False
        i += 1
    return True


def sieve(ilist):
    p = next(ilist)
    yield p
    for q in sieve(n for n in ilist if n % p != 0):
        yield q


def primes2(): return sieve(count(2))


def gmul(n, f):
    n *= f
    while True:
        yield n
        n *= f


def merge(s1, s2):
    x1, x2 = next(s1), next(s2)
    while True:
        if x1 < x2:
            yield x1
            x1 = next(s1)
        elif x1 > x2:
            yield x2
            x2 = next(s2)
        else:
            yield x1
            x1, x2 = next(s1), next(s2)


def hammings():
    n = 1
    g = merge(gmul(n, 2), merge(gmul(n, 3), gmul(n, 5)))
    while True:
        yield n
        g = merge(g, merge(gmul(n, 2), merge(gmul(n, 3), gmul(n, 5))))
        n = next(g)
