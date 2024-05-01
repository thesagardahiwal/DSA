#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Define a structure to represent a graph node
struct GraphNode {
    string name;
    vector<GraphNode*> neighbors;

    GraphNode(string n) : name(n) {}
};

// Function to perform Depth-First Search (DFS) on the graph
void dfs(GraphNode* node, unordered_set<GraphNode*>& visited) {
    if (!node || visited.count(node)) return;

    cout << node->name << " ";
    visited.insert(node);

    for (GraphNode* neighbor : node->neighbors) {
        dfs(neighbor, visited);
    }
}

// Function to perform Breadth-First Search (BFS) on the graph
void bfs(GraphNode* node) {
    if (!node) return;

    queue<GraphNode*> q;
    unordered_set<GraphNode*> visited;

    q.push(node);
    visited.insert(node);

    while (!q.empty()) {
        GraphNode* current = q.front();
        q.pop();
        cout << current->name << " ";

        for (GraphNode* neighbor : current->neighbors) {
            if (!visited.count(neighbor)) {
                q.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }
}

int main() {
    // Construct the graph representing the map of the area around the college
    unordered_map<string, GraphNode*> graph;

    // Add nodes (landmarks) to the graph
    graph["Main Gate"] = new GraphNode("Main Gate");
    graph["Library"] = new GraphNode("Library");
    graph["Cafeteria"] = new GraphNode("Cafeteria");
    graph["Admin Building"] = new GraphNode("Admin Building");
    graph["Football Ground"] = new GraphNode("Football Ground");
    graph["Auditorium"] = new GraphNode("Auditorium");

    // Add edges (connections between landmarks) to the graph
    graph["Main Gate"]->neighbors.push_back(graph["Library"]);
    graph["Main Gate"]->neighbors.push_back(graph["Cafeteria"]);
    graph["Library"]->neighbors.push_back(graph["Admin Building"]);
    graph["Library"]->neighbors.push_back(graph["Football Ground"]);
    graph["Cafeteria"]->neighbors.push_back(graph["Auditorium"]);
    graph["Admin Building"]->neighbors.push_back(graph["Football Ground"]);
    graph["Football Ground"]->neighbors.push_back(graph["Auditorium"]);

    // Perform Depth-First Search (DFS)
    cout << "Depth-First Search (DFS): ";
    unordered_set<GraphNode*> visited_dfs;
    dfs(graph["Main Gate"], visited_dfs);
    cout << endl;

    // Perform Breadth-First Search (BFS)
    cout << "Breadth-First Search (BFS): ";
    bfs(graph["Main Gate"]);
    cout << endl;

    // Deallocate memory
    for (auto& entry : graph) {
        delete entry.second;
    }

    return 0;
}


