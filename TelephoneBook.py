class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size
        self.num_elements = 0

    def hash_function(self, key):
        return hash(key) % self.size


class LinearProbingHashTable(HashTable):
    def __init__(self, size):
        super().__init__(size) 

    def insert(self, key, value):
        idx = self.hash_function(key)
        start_idx = idx
        while self.table[idx] is not None:
            if self.table[idx] and self.table[idx][0] == key: 
                self.table[idx] = (key, value)
                return

            idx = (idx + 1) % self.size
            if idx == start_idx:
                raise Exception("HashTable is Full")
        self.table[idx] = (key, value)
        self.num_elements += 1

    def find(self, key):
        idx = self.hash_function(key)
        start_idx = idx
        comparisons = 0
        while self.table[idx] is not None:
            comparisons += 1
            if self.table[idx] and self.table[idx][0] == key:
                return self.table[idx][1], comparisons  # Return the value, not the tuple
            idx = (idx + 1) % self.size
            if idx == start_idx:
                return None, comparisons
        return None, comparisons


class ChainingHashTable(HashTable):
    def __init__(self, size):
        super().__init__(size)  # Correct typo from __int__ to __init__
        self.table = [[] for _ in range(size)]

    def insert(self, key, value):
        idx = self.hash_function(key)
        for i, (k, v) in enumerate(self.table[idx]):
            if k == key:
                self.table[idx][i] = (key, value)
                return
        self.table[idx].append((key, value))
        self.num_elements += 1

    def find(self, key):
        idx = self.hash_function(key)
        chain = self.table[idx]
        comparisons = 0
        for k, v in chain:
            comparisons += 1
            if k == key:
                return v, comparisons
        return None, comparisons


def test_hash_tables(clients, searches):
    size = len(clients) * 2
    linear_table = LinearProbingHashTable(size)
    chaining_table = ChainingHashTable(size)

    for name, number in clients:
        linear_table.insert(name, number)
        chaining_table.insert(name, number)

    linear_comparisons = 0
    chaining_comparisons = 0
    for name in searches:
        _, comp = linear_table.find(name)
        linear_comparisons += comp
        _, comp = chaining_table.find(name)
        chaining_comparisons += comp

    print(f"Linear Probing Total Comparisons: {linear_comparisons}")
    print(f"Separate Chaining Total Comparisons: {chaining_comparisons}")


clients = [
    ("John Doe", "123456789"),
    ("Jane Smith", "987654321"),
    ("Alice Johnson", "111223344"),
    ("Bob Lee", "222333444")
]
searches = ["John Doe", "Jane Smith", "Alice Johnson", "Non Existing"]
test_hash_tables(clients, searches)


# command: python3 filename.py 
# command: python filename.py