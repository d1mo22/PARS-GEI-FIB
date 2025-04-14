# Tots els codis es poden escriure sense utilitzar bucles.
def count_unique(L):
    return len(set(L))


def remove_duplicates(L):
    return list(set(L))


def flatten(L):
    return sum(L, [])


def flatten_rec(L):
    if not isinstance(L, list):  # Si no es una llista
        return [L]
    if not L:
        return []
    return flatten_rec(L[0]) + flatten_rec(L[1:])
