def my_map(f, l):
    return [f(x) for x in l]


def my_filter(f, l):
    return [x for x in l if f(x)]


def factors(n):
    return [x for x in range(1, n + 1) if n % x == 0]


def triplets(n):
    return [
        (a, b, c)
        for a in range(1, n + 1)
        for b in range(1, n + 1)
        for c in range(1, n + 1)
        if a * a + b * b == c * c
    ]
