#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Employee {
        
    public:
        string password;
        string username;
        string name;
        string role;
        int uid;

        Employee(string name, int uid, string username, string password) {
            this -> name = name;
            this -> uid = uid;
            this -> username = username;
            this -> password = password;
            this -> role = "GeneralEmployee";
        };
};

class Manager : public Employee {
    public:
        Manager(string name, int uid, string username, string password) : Employee(name, uid, username, password) {
            this -> role = "Manager";
        };
};

class HumanResources : public Employee {
    public:
        HumanResources(string name, int uid, string username, string password) : Employee(name, uid, username, password) {
            this -> role = "HumanResources";
        }
};

class EmployeeService {
    public:
        bool authenticate(string username, string password, vector<Employee> employees, Employee currUser) {
            for(int i = 0; i < employees.size(); i++) {
                if(employees[i].username == username && employees[i].password == password) {
                    currUser = employees[i];
                    return true;
                }
            }
            return false;
        };

        void viewProfile(Employee currUser) {
            cout << "User ID: " << currUser.uid << endl;
            cout << "Name: " << currUser.name << endl;
            cout << "Username: " << currUser.username << endl;
            cout << "Role: " << currUser.role << endl;
        }

        void viewEmployees(Employee currUser, vector<Employee> employees) {
            if(currUser.role == "Manager" || currUser.role == "HumanResources") {
                for(int i = 0; i < employees.size(); i++) {
                    cout << "Name: " << employees[i].name << endl;
                }
            }
        }
};

// Create a vector of employees globally
vector<Employee> employees;
Employee currUser("Guest", 0, "guest", "guest");

int main() {

    EmployeeService employeeService;

    // Create dummy data of employees
    Employee employee1("John Doe", 1, "johndoe", "password");
    Employee employee2("Jane Doe", 2, "janedoe", "password");
    employees.push_back(employee1);
    employees.push_back(employee2);

    string currUserName;
    string currPassword;
    bool isAuthenticated = false;

    while(isAuthenticated == false) {
        // User enters their username here
        cout << "Enter your username: " << endl;
        getline(cin, currUserName);

        // User enters their password here
        cout << "Enter your password: " << endl;
        getline(cin, currPassword);

        // Check if the user is authenticated
        isAuthenticated = employeeService.authenticate(currUserName, currPassword, employees, currUser);
        if (isAuthenticated == true) {
            cout << "You are authenticated!" << endl;
        } else {
            cout << "Authentication failed! Try again" << endl;
        }
    }

    cout << "List of commands: " << endl;
    if (currUser.role == "GeneralEmployee") {
        cout << "1. View your profile" << endl;
        cout << "2. Exit" << endl;
    } else if (currUser.role == "Manager") {
        cout << "1. View your profile" << endl;
        cout << "2. View all employees" << endl;
        cout << "3. Exit" << endl;
    } else if (currUser.role == "HumanResources") {
        cout << "1. View your profile" << endl;
        cout << "2. View all employees" << endl;
        cout << "3. Add new employee" << endl;
        cout << "4. Exit" << endl;
    };

    cout << "Enter your command: " << endl;
    string command;
    getline(cin, command);

    if(command == "1") {
        employeeService.viewProfile(currUser);
    } else if(command == "2") {
        if (currUser.role == "GeneralEmployee") {
            cout << "Exiting..." << endl;
            return 0;
        } else if(currUser.role == "Manager") {
            cout << "List of employees: " << endl;
            employeeService.viewEmployees(currUser, employees);
        }
    }
 
    return 0;
};