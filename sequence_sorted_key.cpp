#include <iostream>
#include <vector>

using namespace std;

// Structure for a node in the binary search tree
struct Node {
    int key;
    double probability;
    Node* left;
    Node* right;

    Node(int k, double p) : key(k), probability(p), left(nullptr), right(nullptr) {}
};

// Function to construct the optimal binary search tree recursively
Node* constructOptimalBST(vector<int>& keys, vector<double>& probabilities, int start, int end) {
    if (start > end) return nullptr;

    // Find the root of the subtree with minimum cost
    int minCostIndex = -1;
    double minCost = numeric_limits<double>::max();
    for (int i = start; i <= end; ++i) {
        double cost = 0;
        for (int j = start; j <= end; ++j) {
            cost += probabilities[j];
        }
        Node* leftSubtree = constructOptimalBST(keys, probabilities, start, i - 1);
        Node* rightSubtree = constructOptimalBST(keys, probabilities, i + 1, end);

        if (leftSubtree) cost += leftSubtree->probability;
        if (rightSubtree) cost += rightSubtree->probability;

        if (cost < minCost) {
            minCost = cost;
            minCostIndex = i;
        }
    }

    // Construct the subtree rooted at the optimal root
    Node* root = new Node(keys[minCostIndex], probabilities[minCostIndex]);
    root->left = constructOptimalBST(keys, probabilities, start, minCostIndex - 1);
    root->right = constructOptimalBST(keys, probabilities, minCostIndex + 1, end);

    return root;
}

// Function to construct the optimal binary search tree
Node* constructOptimalBST(vector<int>& keys, vector<double>& probabilities) {
    return constructOptimalBST(keys, probabilities, 0, keys.size() - 1);
}

// Function to print the inorder traversal of a binary search tree
void inorderTraversal(Node* root) {
    if (!root) return;
    inorderTraversal(root->left);
    cout << "(" << root->key << ", " << root->probability << ") ";
    inorderTraversal(root->right);
}

int main() {
    // Example keys and probabilities
    vector<int> keys;
    keys.push_back(10);
    keys.push_back(20);
    keys.push_back(30);
    keys.push_back(40);
    keys.push_back(50);

    vector<double> probabilities;
    probabilities.push_back(0.1);
    probabilities.push_back(0.2);
    probabilities.push_back(0.3);
    probabilities.push_back(0.2);
    probabilities.push_back(0.2);

    // Construct the optimal binary search tree
    Node* root = constructOptimalBST(keys, probabilities);

    // Print the inorder traversal of the optimal binary search tree
    cout << "Inorder Traversal of Optimal BST: ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}
