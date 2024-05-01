#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Define a structure to represent a flight path
struct FlightPath {
    string destination;
    int cost;

    FlightPath(string dest, int c) : destination(dest), cost(c) {}
};

// Define a structure to represent a node (airport or city) in the graph
struct GraphNode {
    string name;
    vector<FlightPath> flights;

    GraphNode(string n) : name(n) {}
};

// Define a graph class
class Graph {
private:
    unordered_map<string, GraphNode*> nodes;

public:
    // Function to add a node to the graph
    void addNode(string name) {
        nodes[name] = new GraphNode(name);
    }

    // Function to add a flight path between two cities
    void addFlight(string from, string to, int cost) {
        if (!nodes.count(from) || !nodes.count(to)) {
            cout << "Invalid cities. Please add nodes for both cities first." << endl;
            return;
        }
        nodes[from]->flights.push_back(FlightPath(to, cost));
    }

    // Function to check if the graph is connected
    bool isConnected() {
        if (nodes.empty()) return false;

        unordered_set<string> visited;
        dfs(nodes.begin()->second, visited);

        return visited.size() == nodes.size();
    }

private:
    // Depth-First Search (DFS) traversal
    void dfs(GraphNode* node, unordered_set<string>& visited) {
        if (!node || visited.count(node->name)) return;

        visited.insert(node->name);

        for (const FlightPath& flight : node->flights) {
            dfs(nodes[flight.destination], visited);
        }
    }
};

int main() {
    // Create a graph representing flight paths between cities
    Graph graph;

    // Add cities to the graph
    graph.addNode("New York");
    graph.addNode("London");
    graph.addNode("Tokyo");
    graph.addNode("Paris");

    // Add flight paths between cities
    graph.addFlight("New York", "London", 6);
    graph.addFlight("London", "New York", 6);
    graph.addFlight("New York", "Tokyo", 14);
    graph.addFlight("Tokyo", "New York", 14);
    graph.addFlight("Paris", "London", 2);

    // Check if the graph is connected
    cout << "Is the graph connected? " << (graph.isConnected() ? "Yes" : "No") << endl;

    return 0;
}
