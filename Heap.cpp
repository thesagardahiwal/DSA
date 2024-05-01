#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Max heapify function
void maxHeapify(vector<int>& heap, int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left = 2*i + 1
    int right = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (left < n && heap[left] > heap[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && heap[right] > heap[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(heap[i], heap[largest]);

        // Recursively heapify the affected sub-tree
        maxHeapify(heap, n, largest);
    }
}

// Build max heap function
void buildMaxHeap(vector<int>& heap) {
    int n = heap.size();

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(heap, n, i);
}

// Function to find maximum marks
int findMaxMarks(vector<int>& marks) {
    buildMaxHeap(marks);
    return marks.front();
}

// Function to find minimum marks
int findMinMarks(vector<int>& marks) {
    return *min_element(marks.begin(), marks.end());
}

int main() {
    vector<int> marks = {90, 85, 95, 80, 75, 100, 70};

    int maxMarks = findMaxMarks(marks);
    int minMarks = findMinMarks(marks);

    cout << "Maximum Marks: " << maxMarks << endl;
    cout << "Minimum Marks: " << minMarks << endl;

    return 0;
}
