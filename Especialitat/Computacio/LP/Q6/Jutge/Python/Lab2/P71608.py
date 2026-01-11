class Tree:
    def __init__(self, x):
        self.root = x
        self.child = []

    def add_child(self, a):
        self.child.append(a)

    def root(self):
        return self.root

    def ith_child(self, i):
        return self.child[i]

    def num_children(self):
        return len(self.child)


class Pre(Tree):

    def preorder(self):
        l = [self.root]
        for child in self.child:
            l += child.preorder()
        return l
