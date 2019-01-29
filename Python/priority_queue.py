from heap import Heap


class PriorityQueue(Heap):
    def __init__(self, max_queue=True, comp=None):
        super().__init__(is_max_heap=max_queue, comp=comp)

    def queue_init(self, arr):
        return super().heap_init(arr)

    def root(self):
        return self[1]

    def extract_root(self):
        if self.heap_size < 1:
            raise IndexError("Empty heap")
        root = self[1]
        self[1] = self[self.heap_size]
        self.heap_size -= 1
        self.heapify(1)
        return root

    def change_key(self, idx, key):
        if self.comp(key, self[idx]) < 0:
            self[idx] = key
            self.heapify(idx)
        else:
            self[idx] = key
            pidx = self._parent(idx)
            while idx > 1 and self.comp(self[pidx], self[idx]) < 0:
                self[idx], self[pidx] = self[pidx], self[idx]
                idx = pidx
                pidx = self._parent(idx)

    def insert(self, key):
        self.heap_size += 1
        self.data.append(float("-inf"))
        self.change_key(self.heap_size, key)


if __name__ == "__main__":
    max_queue = PriorityQueue(max_queue=False)
    max_queue.heap_init([1, 2, 3, 4])
    print(max_queue)
    max_queue.insert(15)
    print(max_queue)
    for _ in range(5):
        print("get max : ", max_queue.extract_root())
        print(max_queue)
