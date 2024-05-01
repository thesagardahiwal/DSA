#include <iostream>

using namespace std;

// Define the structure of a node in the threaded binary tree
struct Node {
    int data;
    Node* left;
    Node* right;
    bool leftThread;
    bool rightThread;

    Node(int val) : data(val), left(nullptr), right(nullptr), leftThread(false), rightThread(false) {}
};

// Function to find the inorder successor of a node
Node* findSuccessor(Node* node) {
    if (!node)
        return nullptr;
    if (node->rightThread)
        return node->right;
    node = node->right;
    while (node && !node->leftThread)
        node = node->left;
    return node;
}

// Function to perform threaded preorder traversal without using stack
void threadedPreorderTraversal(Node* root) {
    Node* current = root;

    while (current) {
        cout << current->data << " ";

        if (current->left) {
            current = current->left;
        } else if (current->rightThread) { // Check if the right child is a thread
            current = current->right;
        } else {
            current = findSuccessor(current);
        }
    }
}

int main() {
    // Construct the threaded binary tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    
    root->left->left->right = root->left;
    root->left->right->left = root->left->left;
    root->left->right->right = root->left->right;
    root->right->left->right = root->right->left;
    root->right->right->left = root->right;

    // Perform threaded preorder traversal
    cout << "Threaded Preorder Traversal: ";
    threadedPreorderTraversal(root);
    cout << endl;

    return 0;
}
