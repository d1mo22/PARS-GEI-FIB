from functools import reduce


def evens_product(L):
    return reduce(lambda x, y: x * y, filter((lambda x: x % 2 == 0), L), 1)


def reverse(L):
    return reduce(lambda acc, x: [x] + acc, L, [])


def zip_with(f, L1, L2):
    return list(map(f, L1, L2))


def count_if(f, L):
    return len(list(filter(f, L)))
