#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

// Employee class to represent employee information
class Employee {
private:
    int id;
    string name;
    string designation;
    double salary;

public:
    // Constructor
    Employee(int id, const string& name, const string& designation, double salary)
        : id(id), name(name), designation(designation), salary(salary) {}

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    string getDesignation() const { return designation; }
    double getSalary() const { return salary; }

    // Function to display employee details
    void display() const {
        cout << "Employee ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Designation: " << designation << endl;
        cout << "Salary: " << fixed << setprecision(2) << salary << endl;
    }
};

// EmployeeDatabase class to manage indexed sequential file
class EmployeeDatabase {
private:
    string filename;
    vector<Employee> employees;

public:
    // Constructor
    EmployeeDatabase(const string& filename) : filename(filename) {}

    // Function to load employee data from file
    void loadFromFile() {
        employees.clear();
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        int id;
        string name, designation;
        double salary;
        while (file >> id >> name >> designation >> salary) {
            employees.push_back(Employee(id, name, designation, salary));
        }
        file.close();
    }

    // Function to write employee data to file
    void writeToFile() {
        ofstream file(filename);
        if (!file) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        for (const auto& emp : employees) {
            file << emp.getId() << " " << emp.getName() << " " << emp.getDesignation() << " " << emp.getSalary() << endl;
        }
        file.close();
    }

    // Function to add an employee
    void addEmployee(const Employee& emp) {
        employees.push_back(emp);
    }

    // Function to delete an employee by ID
    void deleteEmployee(int id) {
        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if (it->getId() == id) {
                employees.erase(it);
                return;
            }
        }
        cout << "Employee with ID " << id << " not found." << endl;
    }

    // Function to display employee details by ID
    void displayEmployeeDetails(int id) {
        for (const auto& emp : employees) {
            if (emp.getId() == id) {
                emp.display();
                return;
            }
        }
        cout << "Employee with ID " << id << " not found." << endl;
    }
};

int main() {
    EmployeeDatabase empDB("employees.txt");

    // Load employee data from file
    empDB.loadFromFile();

    // Add some employees
    empDB.addEmployee(Employee(101, "John Doe", "Manager", 50000));
    empDB.addEmployee(Employee(102, "Jane Smith", "Developer", 40000));
    empDB.addEmployee(Employee(103, "Alice Johnson", "Tester", 35000));

    // Display employee details
    cout << "Employee Details:" << endl;
    empDB.displayEmployeeDetails(101);
    empDB.displayEmployeeDetails(102);
    empDB.displayEmployeeDetails(104);

    // Delete an employee
    empDB.deleteEmployee(102);

    // Write employee data back to file
    empDB.writeToFile();

    return 0;
}
