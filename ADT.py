
class HashNode:
    """ Node containing key, value, and a reference to the next node """
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None


class HashTable:
    def __init__(self, size=10):
        self.size = size
        self.table = [None] * size
        self.num_elements = 0

    def hash_function(self, key):
        """ Simple hash function that uses modulo operation """
        return hash(key) % self.size

    def insert(self, key, value):
        """ Insert a new key-value pair or update an existing key """
        idx = self.hash_function(key)
        node = self.table[idx]
        last = None
        while node is not None:
            if node.key == key:
                node.value = value

            last = node
            node = node.next
        new_node = HashNode(key, value)
        if last is None:
            self.table[idx] = new_node
        else:
            last.next = new_node
        self.num_elements += 1

    def find(self, key):
        """ Find and return the value associated with the key """
        idx = self.hash_function(key)
        node = self.table[idx]
        while node is not None:
            if node.key == key:
                return node.value
            node = node.next

        return None

    def delete(self, key):
        """ Delete the key-value pair if the key exists """
        idx = self.hash_function(key)
        node = self.table[idx]
        prev = None
        while node is not None:
            if node.key == key:
                if prev is None:
                    self.table[idx] = node.next
                else:
                    prev.next = node.next
                self.num_elements -= 1
                return True
            prev = node
            node = node.next
        return False

    def __str__(self):
        """ Visualize the hash table for debugging purposes """
        result = ""
        for i, node in enumerate(self.table):
            result += f"Bucket {i}: "
            n = node
            while n is not None:
                result += f"({n.key}, {n.value}) -> "
                n = n.next
            result += "None\n"
        return result


ht = HashTable(size=5)
ht.insert("name", "Alice")
ht.insert("age", 30)
ht.insert("country", "Canada")
ht.insert("city", "Toronto")

print("Current Hash Table:")
print(ht)

# command: python3 filename.py 
# command: python filename.py