#include <iostream>
#include <fstream>

using namespace std;

// Constants
const int RECORD_SIZE = 100; // Size of each record in bytes

// Function to insert a record at a specific position in the file
void insertRecord(const string& filename, int position, const string& record) {
    ofstream file(filename, ios::binary | ios::in | ios::out);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    file.seekp(position * RECORD_SIZE); // Move file pointer to the specified position

    // Write the record to the file
    file.write(record.c_str(), RECORD_SIZE);
    file.close();

    cout << "Record inserted successfully at position " << position << endl;
}

// Function to delete a record at a specific position in the file
void deleteRecord(const string& filename, int position) {
    ofstream file(filename, ios::binary | ios::in | ios::out);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    file.seekp(position * RECORD_SIZE); // Move file pointer to the specified position

    // Replace the record with empty spaces
    string emptyRecord(RECORD_SIZE, ' ');
    file.write(emptyRecord.c_str(), RECORD_SIZE);
    file.close();

    cout << "Record deleted successfully at position " << position << endl;
}

int main() {
    string filename = "employees.txt";

    // Insert records
    insertRecord(filename, 0, "Record 1");
    insertRecord(filename, 1, "Record 2");
    insertRecord(filename, 2, "Record 3");

    // Delete record at position 1
    deleteRecord(filename, 1);

    return 0;
}
