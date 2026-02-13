import bisect

class BTreeNode:
    def __init__(self, is_leaf=True):
        self.keys = []
        self.children = []
        self.is_leaf = is_leaf

    def __repr__(self):
        return f"BTreeNode(keys={self.keys}, leaf={self.is_leaf})"

class BTree:
    def __init__(self, degree=2):
        if degree < 2:
            raise ValueError("Degree must be at least 2.")
        self.root = BTreeNode()
        self.t = degree

    def search(self, key, node=None):
        node = node or self.root
        i = bisect.bisect_left(node.keys, key)
        
        if i < len(node.keys) and node.keys[i] == key:
            return (node, i)
        return None if node.is_leaf else self.search(key, node.children[i])

    def insert(self, key):
        root = self.root
        if len(root.keys) == (2 * self.t) - 1:
            new_root = BTreeNode(is_leaf=False)
            new_root.children.append(self.root)
            self._split_child(new_root, 0)
            self.root = new_root
        self._insert_non_full(self.root, key)

    def _insert_non_full(self, node, key):
        i = bisect.bisect_left(node.keys, key)
        if node.is_leaf:
            node.keys.insert(i, key)
        else:
            if len(node.children[i].keys) == (2 * self.t) - 1:
                self._split_child(node, i)
                if key > node.keys[i]:
                    i += 1
            self._insert_non_full(node.children[i], key)

    def _split_child(self, parent, i):
        t = self.t
        full_node = parent.children[i]
        new_node = BTreeNode(is_leaf=full_node.is_leaf)
        
        parent.keys.insert(i, full_node.keys[t - 1])
        parent.children.insert(i + 1, new_node)
        
        new_node.keys = full_node.keys[t:]
        full_node.keys = full_node.keys[:t - 1]
        
        if not full_node.is_leaf:
            new_node.children = full_node.children[t:]
            full_node.children = full_node.children[:t]

    def delete(self, key):
        self._delete_recursive(self.root, key)
        if not self.root.keys and not self.root.is_leaf:
            self.root = self.root.children[0]

    def _delete_recursive(self, node, key):
        i = bisect.bisect_left(node.keys, key)
        
        if i < len(node.keys) and node.keys[i] == key:
            if node.is_leaf:
                node.keys.pop(i)
            else:
                self._delete_from_internal(node, i)
        elif not node.is_leaf:
            if len(node.children[i].keys) < self.t:
                self._fill_child(node, i)
                i = bisect.bisect_left(node.keys, key)
            self._delete_recursive(node.children[i], key)

    def _delete_from_internal(self, node, i):
        key = node.keys[i]
        left_child, right_child = node.children[i], node.children[i+1]
        
        if len(left_child.keys) >= self.t:
            node.keys[i] = self._get_predecessor(left_child)
            self._delete_recursive(left_child, node.keys[i])
        elif len(right_child.keys) >= self.t:
            node.keys[i] = self._get_successor(right_child)
            self._delete_recursive(right_child, node.keys[i])
        else:
            self._merge(node, i)
            self._delete_recursive(left_child, key)

    def _get_predecessor(self, node):
        while not node.is_leaf: node = node.children[-1]
        return node.keys[-1]

    def _get_successor(self, node):
        while not node.is_leaf: node = node.children[0]
        return node.keys[0]

    def _fill_child(self, node, i):
        if i > 0 and len(node.children[i-1].keys) >= self.t:
            self._borrow_prev(node, i)
        elif i < len(node.children) - 1 and len(node.children[i+1].keys) >= self.t:
            self._borrow_next(node, i)
        else:
            self._merge(node, i if i < len(node.keys) else i - 1)

    def _borrow_prev(self, node, i):
        child, sibling = node.children[i], node.children[i-1]
        child.keys.insert(0, node.keys[i-1])
        node.keys[i-1] = sibling.keys.pop()
        if not child.is_leaf:
            child.children.insert(0, sibling.children.pop())

    def _borrow_next(self, node, i):
        child, sibling = node.children[i], node.children[i+1]
        child.keys.append(node.keys[i])
        node.keys[i] = sibling.keys.pop(0)
        if not child.is_leaf:
            child.children.append(sibling.children.pop(0))

    def _merge(self, node, i):
        left, right = node.children[i], node.children[i+1]
        left.keys.append(node.keys.pop(i))
        left.keys.extend(right.keys)
        if not left.is_leaf:
            left.children.extend(right.children)
        node.children.pop(i+1)

    def traverse(self, node=None):
        node = node or self.root
        res = []
        for i in range(len(node.keys)):
            if not node.is_leaf:
                res.extend(self.traverse(node.children[i]))
            res.append(node.keys[i])
        if not node.is_leaf:
            res.extend(self.traverse(node.children[-1]))
        return res