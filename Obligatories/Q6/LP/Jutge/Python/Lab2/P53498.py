class Tree:
    def __init__(self, x):
        self.root = x
        self.child = []

    def __iter__(self):
        queue = [self]
        while queue:
            actual_node = queue.pop(0)
            yield actual_node.root
            queue.extend(actual_node.child)

    def addChild(self, a):
        self.child.append(a)

    def root(self):
        return self.root

    def ithChild(self, i):
        return self.child[i]

    def num_children(self):
        return len(self.child)
