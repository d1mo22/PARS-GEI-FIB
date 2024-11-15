def count_unique(L):
    seen = set()
    i = 0
    for x in L:
        if x not in seen:
            seen.add(x)
            i += 1
    return i


def remove_duplicates(L):
    l = []
    seen = set()
    for x in L:
        if x not in seen:
            l.append(x)
            seen.add(x)
    return l


def flatten(L):
    result = []
    for item in L:
        if isinstance(item, list):
            result.extend(item)
        else:
            result.append(item)
    return result


def flatten_rec(L):
    result = []
    for item in L:
        if isinstance(item, list):
            result.extend(flatten_rec(item))
        else:
            result.append(item)
    return result
