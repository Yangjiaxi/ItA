from typing import Union

from rb_tree import RBNode, RBTree, BLACK, RED


class OSNode(RBNode):
    def __init__(self,
                 data,
                 left=None,
                 right=None,
                 parent=None,
                 color=None,
                 size=None):
        super().__init__(
            data, left=left, right=right, parent=parent, color=color)
        self.size = size

    def __repr__(self):
        s = super().__repr__()
        s += "\n\t(7) Size\t: {}".format(self.size)
        return s


class OSTree(RBTree):
    def __init__(self, comp=None, node_type=None, allow_duplicate=False):
        super().__init__(comp, node_type, allow_duplicate)
        if node_type is None:
            self.node_type = OSNode
        else:
            self.node_type = node_type

        self.nil = self.node_type(-1, color=BLACK, size=0)
        self._root = self.nil

    def __str__(self):
        def mtd(node):
            return "{}{}{}".format(node.data, node.color, node.size)

        s = "\n------[OST]------"
        lines = self._tree_repr(self.root, mtd)[0]
        s += '\n' + '\n'.join((line.rstrip() for line in lines))
        s += "******[END]******\n"
        return s

    def insert(self, z: Union[int, float, OSNode]):
        if not isinstance(z, self.node_type):
            z = self.node_type(
                z, left=self.nil, right=self.nil, color=BLACK, size=0)
        return self._insert(z)

    def insert_fixup(self, z):
        y = z
        while y is not self.nil:
            y.size += 1
            y = y.p
        super().insert_fixup(z)

    def delete(self, z):
        if not isinstance(z, self.node_type):
            raise ValueError("Must be a OS-Tree Node")
        y = z
        while y is not self.nil:
            y.size -= 1
            y = y.p
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
            y.size = z.size
        if y_original_color == BLACK:
            self.delete_fixup(x)

    def left_rotate(self, x):
        y = super().left_rotate(x)
        y.size = x.size
        x.size = x.left.size + x.right.size + 1

    def right_rotate(self, x):
        y = super().right_rotate(x)
        y.size = x.size
        x.size = x.left.size + x.right.size + 1

    def select(self, k):
        if k > self.root.size:
            return None
        return self._select_it(self.root, k)

    def _select(self, x, k):
        r = x.left.size + 1
        if k == r:
            return x
        elif k < r:
            return self._select(x.left, k)
        else:
            return self._select(x.right, k - r)

    @staticmethod
    def _select_it(x, k):
        while True:
            r = x.left.size + 1
            if k == r:
                break
            elif k > r:
                x = x.right
                k -= r
            else:
                x = x.left
        return x

    def rank(self, x):
        if x is not None:
            r = x.left.size + 1
            y = x
            while y is not self.root:
                if y is y.p.right:
                    r += y.p.left.size + 1
                y = y.p
            return r
        return -1


if __name__ == "__main__":
    ost = OSTree(allow_duplicate=True)
    insert_list = [
        26, 17, 41, 14, 21, 30, 47, 10, 16, 19, 21, 28, 38, 7, 12, 14, 20, 35,
        39, 3
    ]
    for insert_item in insert_list:
        # print("-+" * 20)
        # print("Insert: ", insert_item)
        ost.insert(insert_item)
        # print(ost)

    print(ost)

    query_list = [17, 20, 21, 13, 1]
    for query_item in query_list:
        res = ost.select(query_item)
        print("{}-th smallest item: {}".format(query_item, res))
        print("Then, this item is {}-th\n".format(ost.rank(res)))

    a = 0
    while ost.root is not ost.nil:
        if a == 0:
            print("Delete:", ost.root.data)
            ost.delete(ost.root)
        elif a == 1:
            print("Delete:", ost.maximum().data)
            ost.delete(ost.maximum())
        else:
            print("Delete:", ost.minimum().data)
            ost.delete(ost.minimum())
        a = (a + 1) % 3
        print(ost)

    # print(rbt)
    # rbt.left_rotate(rbt.search(60))
    # print(rbt)
    # rbt.right_rotate(rbt.search(81))
    # print(rbt)
