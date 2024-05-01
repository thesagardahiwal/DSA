#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Node structure for AVL tree
struct Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;
    int height;

    Node(string key, string val) : keyword(key), meaning(val), left(nullptr), right(nullptr), height(1) {}
};

// AVL tree class
class AVLTree {
private:
    Node* root;

    // Helper function to get the height of a node
    int getHeight(Node* node) {
        if (!node) return 0;
        return node->height;
    }

    // Helper function to get the balance factor of a node
    int getBalance(Node* node) {
        if (!node) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Helper function to update the height of a node
    void updateHeight(Node* node) {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    // Helper function to perform left rotation
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Helper function to perform right rotation
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Helper function to balance the AVL tree
    Node* balance(Node* node) {
        updateHeight(node);

        int balanceFactor = getBalance(node);

        // Left Heavy
        if (balanceFactor > 1) {
            // Left-Right Case
            if (getBalance(node->left) < 0) {
                node->left = leftRotate(node->left);
            }
            // Left-Left Case
            return rightRotate(node);
        }
        // Right Heavy
        else if (balanceFactor < -1) {
            // Right-Left Case
            if (getBalance(node->right) > 0) {
                node->right = rightRotate(node->right);
            }
            // Right-Right Case
            return leftRotate(node);
        }
        return node;
    }

    // Helper function to insert a node into the AVL tree
    Node* insert(Node* node, string key, string val) {
        if (!node) return new Node(key, val);

        if (key < node->keyword) {
            node->left = insert(node->left, key, val);
        } else if (key > node->keyword) {
            node->right = insert(node->right, key, val);
        } else {
            node->meaning = val; // Update value if key already exists
            return node;
        }

        return balance(node);
    }

    // Helper function to find the node with minimum value in a subtree
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left) {
            current = current->left;
        }
        return current;
    }

    // Helper function to delete a node from the AVL tree
    Node* deleteNode(Node* node, string key) {
        if (!node) return nullptr;

        if (key < node->keyword) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->keyword) {
            node->right = deleteNode(node->right, key);
        } else {
            // Node with only one child or no child
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                // Node with two children: Get the inorder successor (smallest in the right subtree)
                Node* temp = minValueNode(node->right);
                node->keyword = temp->keyword;
                node->meaning = temp->meaning;
                node->right = deleteNode(node->right, temp->keyword);
            }
        }

        if (!node) return node;

        return balance(node);
    }

    // Helper function to print the AVL tree in ascending order
    void printAscending(Node* node) {
        if (node) {
            printAscending(node->left);
            cout << node->keyword << " : " << node->meaning << endl;
            printAscending(node->right);
        }
    }

    // Helper function to print the AVL tree in descending order
    void printDescending(Node* node) {
        if (node) {
            printDescending(node->right);
            cout << node->keyword << " : " << node->meaning << endl;
            printDescending(node->left);
        }
    }

    // Helper function to find the maximum comparisons required for finding a keyword
    int maxComparisons(Node* node, string key, int& comparisons) {
        if (!node) return comparisons;

        comparisons++;

        if (key == node->keyword) {
            return comparisons;
        } else if (key < node->keyword) {
            return maxComparisons(node->left, key, comparisons);
        } else {
            return maxComparisons(node->right, key, comparisons);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    // Function to add a keyword and its meaning
    void addKeyword(string key, string val) {
        root = insert(root, key, val);
    }

    // Function to delete a keyword
    void deleteKeyword(string key) {
        root = deleteNode(root, key);
    }

    // Function to update the meaning of a keyword
    void updateMeaning(string key, string val) {
        root = deleteNode(root, key);
        root = insert(root, key, val);
    }

    // Function to display the data sorted in ascending order
    void displayAscending() {
        cout << "Dictionary in Ascending Order:" << endl;
        printAscending(root);
        cout << endl;
    }

    // Function to display the data sorted in descending order
    void displayDescending() {
        cout << "Dictionary in Descending Order:" << endl;
        printDescending(root);
        cout << endl;
    }

    // Function to find the maximum comparisons required for finding a keyword
    int findMaxComparisons(string key) {
        int comparisons = 0;
        return maxComparisons(root, key, comparisons);
    }
};

int main() {
    AVLTree dictionary;

    // Adding keywords and meanings
    dictionary.addKeyword("apple", "a fruit");
    dictionary.addKeyword("banana", "another fruit");
    dictionary.addKeyword("cat", "a domestic animal");
    dictionary.addKeyword("dog", "another domestic animal");

    // Displaying the dictionary in ascending order
    dictionary.displayAscending();

    // Displaying the dictionary in descending order
    dictionary.displayDescending();

    // Deleting a keyword
    dictionary.deleteKeyword("banana");
    cout << "Dictionary after deleting 'banana':" << endl;
    dictionary.displayAscending();

    // Updating the meaning of a keyword
    dictionary.updateMeaning("apple", "a delicious fruit");
    cout << "Dictionary after updating the meaning of 'apple':" << endl;
    dictionary.displayAscending();

    // Finding the maximum comparisons required for finding a keyword
    string searchKey = "dog";
    int maxComparisons = dictionary.findMaxComparisons(searchKey);
    cout << "Maximum comparisons required to find '" << searchKey << "': " << maxComparisons << endl;

    return 0;
}
