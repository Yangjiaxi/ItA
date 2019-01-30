from typing import Union

from binary_search_tree import TreeNode, BinarySearchTree

BLACK = "■"
RED = "□"


class RBNode(TreeNode):
    def __init__(self, data, left=None, right=None, parent=None, color=None):
        super().__init__(data, left=left, right=right, parent=parent)
        self.color = color

    def __repr__(self):
        s = super().__repr__()
        s += "\n\t(6) Color\t: {}".format(self.color)
        return s


class RBTree(BinarySearchTree):
    def __init__(self, comp=None, node_type=None):
        super().__init__(comp, node_type)
        if comp is None:
            self.comp = lambda l, r: l.data - r.data
        else:
            self.comp = comp

        if node_type is None:
            self.node_type = RBNode
        else:
            self.node_type = node_type

        self.nil = self.node_type(-1, color=BLACK)
        self._root = self.nil

    def __str__(self):
        s = "\n------[RBT]------"
        lines = self._tree_repr(
            self.root, lambda node: str(node.color) + str(node.data))[0]
        s += '\n' + '\n'.join((line.rstrip() for line in lines))
        s += "******[END]******\n"
        return s

    def insert(self, z: Union[int, float, RBNode]):
        if not isinstance(z, self.node_type):
            z = self.node_type(z, left=self.nil, right=self.nil, color=BLACK)
        return self._insert(z)

    def _insert(self, z):
        y = self.nil
        x = self.root
        while x is not self.nil:
            y = x
            if self.comp(z, x) < 0:
                x = x.left
            elif self.comp(z, x) > 0:
                x = x.right
            else:
                return x
        z.p = y
        if y is self.nil:
            self.root = z
        elif self.comp(z, y) < 0:
            y.left = z
        else:
            y.right = z
        z.left = self.nil
        z.right = self.nil
        z.color = RED
        self.insert_fixup(z)
        return z

    def insert_fixup(self, z):
        while z.p.color == RED:
            if z.p is z.p.p.left:
                y = z.p.p.right
                if y.color == RED:
                    z.p.color = BLACK
                    y.color = BLACK
                    z.p.p.color = RED
                    z = z.p.p
                else:
                    if z is z.p.right:
                        z = z.p
                        self.left_rotate(z)
                    z.p.color = BLACK
                    z.p.p.color = RED
                    self.right_rotate(z.p.p)
            else:
                y = z.p.p.left
                if y.color == RED:
                    z.p.color = BLACK
                    y.color = BLACK
                    z.p.p.color = RED
                    z = z.p.p
                else:
                    if z is z.p.left:
                        z = z.p
                        self.right_rotate(z)
                    z.p.color = BLACK
                    z.p.p.color = RED
                    self.left_rotate(z.p.p)
        self.root.color = BLACK

    def left_rotate(self, x):
        y = x.right
        x.right = y.left
        if y.left is not self.nil:
            y.left.p = x
        y.p = x.p
        if x.p is self.nil:
            self.root = y
        elif x is x.p.left:
            x.p.left = y
        else:
            x.p.right = y
        y.left = x
        x.p = y

    def right_rotate(self, x):
        y = x.left
        x.left = y.right
        if y.right is not self.nil:
            y.right.p = x
        y.p = x.p
        if x.p is self.nil:
            self.root = y
        elif x is x.p.right:
            x.p.right = y
        else:
            x.p.left = y
        y.right = x
        x.p = y

    def transplant(self, u, v):
        if u.p is self.nil:
            self.root = v
        elif u is u.p.left:
            u.p.left = v
        else:
            u.p.right = v
        v.p = u.p

    def delete(self, z):
        if not isinstance(z, self.node_type):
            z = self.node_type(z)
        self._delete(z)

    def _delete(self, z):
        y = z
        y_original_color = y.color
        if z.left is self.nil:
            x = z.right
            self.transplant(z, z.right)
        elif z.right is self.nil:
            x = z.left
            self.transplant(z, z.left)
        else:
            y = self.minimum(z.right)
            y_original_color = y.color
            x = y.right
            if y.p is z:
                x.p = y
            else:
                self.transplant(y, y.right)
                y.right = z.right
                y.right.p = y
            self.transplant(z, y)
            y.left = z.left
            y.left.p = y
            y.color = z.color
        if y_original_color == BLACK:
            self.delete_fixup(x)

    def delete_fixup(self, x):
        while x != self._root and x.color == BLACK:
            if x is x.p.left:
                w = x.p.right
                if w.color == RED:
                    w.color = BLACK
                    x.p.color = RED
                    self.left_rotate(x.p)
                    w = x.p.right
                if w.left.color == BLACK and w.right.color == BLACK:
                    w.color = RED
                    x = x.p
                else:
                    if w.right.color == BLACK:
                        w.left.color = BLACK
                        w.color = RED
                        self.right_rotate(w)
                        w = x.p.right
                    w.color = x.p.color
                    x.p.color = BLACK
                    w.right.color = BLACK
                    self.left_rotate(x.p)
                    x = self.root
            else:
                w = x.p.left
                if w.color == RED:
                    w.color = BLACK
                    x.p.color = RED
                    self.right_rotate(x.p)
                    w = x.p.left
                if w.left.color == BLACK and w.right.color == BLACK:
                    w.color = RED
                    x = x.p
                else:
                    if w.left.color == BLACK:
                        w.right.color = BLACK
                        w.color = RED
                        self.left_rotate(w)
                        w = x.p.left
                    w.color = x.p.color
                    x.p.color = BLACK
                    w.left.color = BLACK
                    self.right_rotate(x.p)
                    x = self.root
        x.color = BLACK


if __name__ == "__main__":
    rbt = RBTree()
    insert_list = [81, 60, 52, 63, 67, 25, 61, 94, 82, 1, 1, 1]
    for insert_item in insert_list:
        rbt.insert(insert_item)
        # print(rbt)

    print(rbt)

    while rbt.root is not rbt.nil:
        rbt.delete(rbt.root)
        print(rbt)

    # print(rbt)
    # rbt.left_rotate(rbt.search(60))
    # print(rbt)
    # rbt.right_rotate(rbt.search(81))
    # print(rbt)
