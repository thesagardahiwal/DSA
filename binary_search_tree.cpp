#include <iostream>
#include <queue>

using namespace std;

// Define a structure for a node in the binary search tree
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Function to insert a new node into the binary search tree
void insert(TreeNode*& root, int val) {
    if (!root) {
        root = new TreeNode(val);
        return;
    }
    if (val < root->data) {
        insert(root->left, val);
    } else {
        insert(root->right, val);
    }
}

// Function to find the number of nodes in the longest path from the root
int findLongestPath(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(findLongestPath(root->left), findLongestPath(root->right));
}

// Function to find the minimum data value in the tree
int findMin(TreeNode* root) {
    if (!root) return INT_MAX;
    int leftMin = findMin(root->left);
    int rightMin = findMin(root->right);
    return min(root->data, min(leftMin, rightMin));
}

// Function to swap the left and right pointers at every node
void swapLeftRight(TreeNode* root) {
    if (!root) return;
    swap(root->left, root->right);
    swapLeftRight(root->left);
    swapLeftRight(root->right);
}

// Function to search for a value in the binary search tree
bool search(TreeNode* root, int val) {
    if (!root) return false;
    if (root->data == val) return true;
    if (val < root->data) return search(root->left, val);
    return search(root->right, val);
}

// Function to print the level order traversal of the binary search tree
void levelOrderTraversal(TreeNode* root) {
    if (!root) return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        cout << current->data << " ";

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

int main() {
    // Construct the binary search tree
    TreeNode* root = nullptr;
    int values[] = {10, 5, 15, 3, 8, 12, 18};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; ++i) {
        insert(root, values[i]);
    }

    // i. Insert new node
    insert(root, 20);
    cout << "BST after inserting 20: ";
    levelOrderTraversal(root);
    cout << endl;

    // ii. Find number of nodes in longest path from root
    cout << "Number of nodes in the longest path from root: " << findLongestPath(root) << endl;

    // iii. Minimum data value found in the tree
    cout << "Minimum value in the tree: " << findMin(root) << endl;

    // iv. Change the tree so that the roles of the left and right pointers are swapped
    swapLeftRight(root);
    cout << "BST after swapping left and right pointers: ";
    levelOrderTraversal(root);
    cout << endl;

    // v. Search for a value
    int valueToSearch = 12;
    cout << "Searching for value " << valueToSearch << ": ";
    if (search(root, valueToSearch)) {
        cout << "Found!" << endl;
    } else {
        cout << "Not found!" << endl;
    }

    return 0;
}
