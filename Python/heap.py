from utils import *


class Heap:
    def __init__(self, is_max_heap=True, comp=None):
        self.data = []
        self.heap_size = 0
        self.max_heap = is_max_heap
        if comp is None:
            self.comp = self.make_default_comp()
        else:
            self.comp = comp

    def make_default_comp(self):
        def inner(left, right):
            return left - right if self.max_heap else right - left

        return inner

    @staticmethod
    def _parent(idx):
        return idx >> 1

    @staticmethod
    def _left(idx):
        return idx << 1

    @staticmethod
    def _right(idx):
        return (idx << 1) + 1

    def heap_init(self, arr):
        self.data = [-999] + [a for a in arr]
        self.heap_size = len(arr)
        self.build_heap()

    def build_heap(self):
        for idx in close_ranger(self.heap_size >> 1, 1):
            self.heapify(idx)

    def heapify(self, idx):
        left = self._left(idx)
        right = self._right(idx)

        if left <= self.heap_size and self.comp(self[left], self[idx]) > 0:
            largest = left
        else:
            largest = idx
        if right <= self.heap_size and self.comp(self[right],
                                                 self[largest]) > 0:
            largest = right

        if largest != idx:
            self[idx], self[largest] = self[largest], self[idx]
            self.heapify(largest)

    def heap_sort(self, inplace=True):
        data = self.data.copy()
        for idx in close_ranger(self.heap_size, 2):
            self[1], self[idx] = self[idx], self[1]
            self.heap_size -= 1
            self.heapify(1)
        self.heap_size = len(data) - 1
        if not inplace:
            self.data, data = data, self.data
            return data[1:]
        else:
            return self.data[1:]

    def __getitem__(self, idx):
        return self.data[idx]

    def __setitem__(self, idx, data):
        self.data[idx] = data

    def __repr__(self):
        ss = "heap:"
        ss += "\n  size:{}".format(self.heap_size)
        ss += "\n  {}".format(self.data[1:1 + self.heap_size])
        return ss


if __name__ == "__main__":
    max_heap = Heap()
    max_heap.heap_init([4, 1, 3, 2, 16, 9, 10, 14, 8, 7])
    print(max_heap)

    res = max_heap.heap_sort(inplace=False)
    print(max_heap)
    print(res)

    min_heap = Heap(is_max_heap=False)
    min_heap.heap_init([4, 1, 3, 2, 16, 9, 10, 14, 8, 7])
    print(min_heap)

    res = min_heap.heap_sort(inplace=False)
    print(min_heap)
    print(res)
