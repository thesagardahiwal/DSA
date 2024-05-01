#include <iostream>
#include <vector>

using namespace std;

// Define a class for representing a node in the book structure
class Node {
public:
    string name;
    vector<Node*> children;

    Node(string n) : name(n) {}

    // Add a child node
    void addChild(Node* child) {
        children.push_back(child);
    }
};

// Function to print the nodes of the tree using depth-first traversal

void printNodes(Node* node) {
    cout << node->name << endl;
    for (Node* child : node->children) {
        printNodes(child);
    }
}

int main() {
    // Construct the book structure
    Node* book = new Node("Book");

    Node* chapter1 = new Node("Chapter 1");
    Node* chapter2 = new Node("Chapter 2");

    Node* section1_1 = new Node("Section 1.1");
    Node* section1_2 = new Node("Section 1.2");

    Node* section2_1 = new Node("Section 2.1");
    Node* section2_2 = new Node("Section 2.2");

    Node* subsection1_1_1 = new Node("Subsection 1.1.1");
    Node* subsection1_1_2 = new Node("Subsection 1.1.2");

    Node* subsection2_1_1 = new Node("Subsection 2.1.1");
    Node* subsection2_1_2 = new Node("Subsection 2.1.2");

    // Add nodes to form the tree structure
    book->addChild(chapter1);
    book->addChild(chapter2);

    chapter1->addChild(section1_1);
    chapter1->addChild(section1_2);

    chapter2->addChild(section2_1);
    chapter2->addChild(section2_2);

    section1_1->addChild(subsection1_1_1);
    section1_1->addChild(subsection1_1_2);

    section2_1->addChild(subsection2_1_1);
    section2_1->addChild(subsection2_1_2);

    // Print the nodes of the book
    cout << "Nodes of the book structure:" << endl;
    printNodes(book);

    // Calculate time and space requirements
    // Time complexity: O(N), where N is the total number of nodes in the tree
    // Space complexity: O(N), as the tree nodes are stored in memory
    return 0;
}
