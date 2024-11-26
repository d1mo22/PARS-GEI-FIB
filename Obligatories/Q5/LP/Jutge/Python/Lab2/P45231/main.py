from itertools import count


def fibs():
    a = 0
    yield a
    b = 1
    while True:
        yield b
        a, b = b, a + b


def roots(x):
    yield x
    y = x
    while True:
        y = 1 / 2 * (y + x / y)
        yield y


def gmul(n, f):
    n *= f
    while True:
        yield n
        n *= f


def sieve(ilist):
    p = next(ilist)
    yield p
    for q in sieve(n for n in ilist if n % p != 0):
        yield q


primes = lambda: sieve(count(2))


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
