class TreeNode:
    def __init__(self, data, left=None, right=None, parent=None):
        self.data = data
        self.left = left
        self.right = right
        self.p = parent

        if left is not None:
            left.p = self
        if right is not None:
            right.p = self

    def __repr__(self):
        s = "Binary Search Tree Node:"
        s += "\n\t(1) self\t: {}".format(id(self))
        s += "\n\t(2) left\t: {}".format(id(self.left))
        s += "\n\t(3) right\t: {}".format(id(self.right))
        s += "\n\t(4) parent\t: {}".format(id(self.p))
        s += "\n\t(5) data\t: {}".format(self.data)
        return s


class BinarySearchTree:
    def __init__(self, comp=None):
        if comp is None:
            self.comp = lambda a, b: a.data - b.data
        else:
            self.comp = comp
        self.nil = TreeNode(-1)
        self._root = self.nil

    @property
    def root(self):
        return self._root

    @root.setter
    def root(self, root):
        if not isinstance(root, TreeNode):
            raise ValueError("value must be a tree node")
        self._root = root

    def search(self, k):
        x = self.root
        while x is not self.nil and k != x.data:
            if k < x.data:
                x = x.left
            else:
                x = x.right
        return x

    def insert(self, z):
        if not isinstance(z, TreeNode):
            z = TreeNode(z, self.nil, self.nil)
        return self._insert(z)

    def _insert(self, z):
        assert isinstance(z, TreeNode)
        y = self.nil
        x = self.root
        while x is not self.nil:
            y = x
            if self.comp(z, x) < 0:
                x = x.left
            # 1. if do not allow duplicate value:
            elif self.comp(z, x) > 0:
                x = x.right
            else:
                return x
            # 2. otherwise:
            # else:
            #     x = x.right
        z.p = y
        if y is self.nil:
            self.root = z
        elif z.data < y.data:
            y.left = z
        else:
            y.right = z

        return z

    def inorder_walk(self):
        print("Inorder tree walk:")
        self.node_inorder_walk(self.root)
        print()
        print("*" * 25)

    def preorder_walk(self):
        print("Preorder tree walk:")
        self.node_preorder_walk(self.root)
        print()
        print("*" * 25)

    def postorder_walk(self):
        print("Postorder tree walk:")
        self.node_postorder_walk(self.root)
        print()
        print("*" * 25)

    def node_preorder_walk(self, x):
        if x is not self.nil:
            print(x.data, end=" ")
            self.node_preorder_walk(x.left)
            self.node_preorder_walk(x.right)

    def node_inorder_walk(self, x):
        if x is not self.nil:
            self.node_inorder_walk(x.left)
            print(x.data, end=" ")
            self.node_inorder_walk(x.right)

    def node_postorder_walk(self, x):
        if x is not self.nil:
            self.node_postorder_walk(x.left)
            self.node_postorder_walk(x.right)
            print(x.data, end=" ")
            # print(x)

    def minimum(self, x=None):
        if x is None:
            x = self.root
        if x is not self.nil:
            while x.left is not self.nil:
                x = x.left
        return x

    def maximum(self, x=None):
        if x is None:
            x = self.root
        if x is not self.nil:
            while x.right is not self.nil:
                x = x.right
        return x

    def transplant(self, u, v):
        if u.p is self.nil:
            self.root = v
        elif u is u.p.left:
            u.p.left = v
        else:
            u.p.right = v
        if v is not self.nil:
            v.p = u.p

    def delete(self, z):
        if not isinstance(z, TreeNode):
            z = TreeNode(z, self.nil, self.nil)
        self._delete(z)

    def _delete(self, z):
        if z.left is self.nil:
            self.transplant(z, z.right)
        elif z.right is self.nil:
            self.transplant(z, z.left)
        else:
            y = self.minimum(z.right)
            if y.p is not z:
                self.transplant(y, y.right)
            y.right = z.right
            y.right.p = y
            self.transplant(z, y)
            y.left = z.left
            y.left.p = y

    def node_height(self, z):
        if z is self.nil:
            return -1
        else:
            return 1 + max(self.node_height(z.left), self.node_height(z.right))

    def __str__(self):
        s = "\n------[BST]------"
        lines = self._tree_repr(self.root)[0]
        s += '\n' + '\n'.join((line.rstrip() for line in lines))
        s += "******[END]******\n"
        return s

    def _tree_repr(self, root, fmt=None):
        if root is self.nil:
            return [], 0, 0, 0

        line1 = []
        line2 = []

        if fmt is None:
            node_repr = str(root.data)
        else:
            node_repr = str(fmt(root))

        new_root_width = gap_size = len(node_repr)

        # Get the left and right sub-boxes, their widths, and root repr positions
        l_box, l_box_w, l_root_start, l_root_end = self._tree_repr(
            root.left, fmt)
        r_box, r_box_w, r_root_start, r_root_end = self._tree_repr(
            root.right, fmt)

        # Draw the branch connecting the current root node to the left sub-box
        # Pad the line with whitespaces where necessary
        if l_box_w > 0:
            l_root = (l_root_start + l_root_end) // 2 + 1
            line1.append(' ' * (l_root + 1))
            line1.append('_' * (l_box_w - l_root))
            line2.append(' ' * l_root + '/')
            line2.append(' ' * (l_box_w - l_root))
            new_root_start = l_box_w + 1
            gap_size += 1
        else:
            new_root_start = 0

        # Draw the representation of the current root node
        line1.append(node_repr)
        line2.append(' ' * new_root_width)

        # Draw the branch connecting the current root node to the right sub-box
        # Pad the line with whitespaces where necessary
        if r_box_w > 0:
            r_root = (r_root_start + r_root_end) // 2
            line1.append('_' * r_root)
            line1.append(' ' * (r_box_w - r_root + 1))
            line2.append(' ' * r_root + '\\')
            line2.append(' ' * (r_box_w - r_root))
            gap_size += 1
        new_root_end = new_root_start + new_root_width - 1

        # Combine the left and right sub-boxes with the branches drawn above
        gap = ' ' * gap_size
        new_box = [''.join(line1), ''.join(line2)]
        for i in range(max(len(l_box), len(r_box))):
            l_line = l_box[i] if i < len(l_box) else ' ' * l_box_w
            r_line = r_box[i] if i < len(r_box) else ' ' * r_box_w
            new_box.append(l_line + gap + r_line)

        # Return the new box, its width and its root repr positions
        return new_box, len(new_box[0]), new_root_start, new_root_end


if __name__ == "__main__":
    bst = BinarySearchTree()
    l = [81, 60, 52, 63, 67, 25, 61, 94, 82, 1]
    for il in l:
        bst.insert(il)
        print(bst)

    bst.preorder_walk()
    bst.inorder_walk()
    bst.postorder_walk()

    print("max: ", bst.maximum().data)
    print("min: ", bst.minimum().data)

    while bst.root is not bst.nil:
        a = bst.minimum()
        print("-> delete : ", a.data)
        bst.delete(bst.maximum())
        print(bst)
