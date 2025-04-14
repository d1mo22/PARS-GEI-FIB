def my_map(f, L):
    return [f(x) for x in L]


def my_filter(f, L):
    return [x for x in L if f(x)]


def factors(n):
    return [x for x in range(1, n+1) if n % x == 0]


def triplets(n):
    return [
        (x, y, z)
        for x in range(1, n+1)
        for y in range(1, n+1)
        for z in range(1, n+1)
        if x*x+y*y == z*z]
