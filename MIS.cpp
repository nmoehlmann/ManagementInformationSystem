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
        bool authenticate(string username, string password, vector<Employee> employees, Employee &currUser) {
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
                cout << "Names: " << endl;
                for(int i = 0; i < employees.size(); i++) {
                    cout << employees[i].name << endl;
                }
            }
        }

        void searchEmployee(string name, vector<Employee> employees) {
            for(int i = 0; i < employees.size(); i++) {
                if(employees[i].name == name) {
                    cout << "Employee found!" << endl;
                    cout << "Name: " << employees[i].name << endl;
                    cout << "Username: " << employees[i].username << endl;
                    cout << "Role: " << employees[i].role << endl;
                    return;
                }
            }
            cout << "Employee not found!" << endl;
        }

        void addEmployee(vector<Employee> &employees) {
            string name;
            int uid;
            string username;
            string password;
            string role;
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            cout << "Select role: " << endl;
            cout << "1. General Employee" << endl;
            cout << "2. Manager" << endl;
            cout << "3. Human Resources" << endl;
            
            // select role
            string roleChoice;
            while (roleChoice != "1" && roleChoice != "2" && roleChoice != "3") {
                cout << "Select role: ";
                getline(cin, roleChoice);
                if(roleChoice == "1") {
                    role = "GeneralEmployee";
                } else if(roleChoice == "2") {
                    role = "Manager";
                } else if(roleChoice == "3") {
                    role = "HumanResources";
                } else {
                    cout << "Invalid role! Please enter number beside role name" << endl;
                }
            }

            // generate unique id, increment by 1 because its easy lol
            uid = employees.size() + 1;

            if(role == "GeneralEmployee") {
                Employee employee(name, uid, username, password);
                employees.push_back(employee);
            } else if(role == "Manager") {
                Manager employee(name, uid, username, password);
                employees.push_back(employee);
            } else if(role == "HumanResources") {
                HumanResources employee(name, uid, username, password);
                employees.push_back(employee);
            }
            cout << "Employee added!" << endl;
        }

        bool removeEmployee(int uid, vector<Employee> &employees, Employee currUser) {
            if (uid == currUser.uid) {
                cout << "You cannot remove yourself!" << endl;
                return false;
            }
            for(int i = 0; i < employees.size(); i++) {
                if(employees[i].uid == uid) {
                    string confirm;
                    cout << "Are you sure you want to remove this employee? (y/n): ";
                    getline(cin, confirm);
                    if(confirm != "y") {
                        cout << "Employee not removed!" << endl;
                        return false;
                    }
                    employees.erase(employees.begin() + i);
                    cout << "Employee removed!" << endl;
                    return true;
                }
            }
            cout << "Employee not found!" << endl;
            return false;
        }

        void updateEmployee(int uid, vector<Employee> &employees, Employee &currUser) {
            for(int i = 0; i < employees.size(); i++) {
                if(employees[i].uid == uid) {
                    string name;
                    string username;
                    string password;
                    string choice;
        
                    while (choice != "0") {
                        cout << "Enter '0' to exit" << endl;
                        cout << "1. Update name: " << employees[i].name << endl;
                        cout << "2. Update username: " << employees[i].username << endl;
                        cout << "3. Update password: " << employees[i].password << endl;
                        getline(cin, choice);

                        if(choice == "0") {
                            break;
                        } else if(choice == "1") {
                            cout << "Enter new name: ";
                            getline(cin, name);
                            employees[i].name = name;
                            // update name of current user if they are updating their own profile
                            if(uid == currUser.uid) {
                                currUser.name = name;
                            }
                            cout << "Name updated!" << endl;
                        } else if(choice == "2") {
                            cout << "Enter new username: ";
                            getline(cin, username);
                            employees[i].username = username;
                            if(uid == currUser.uid) {
                                currUser.username = username;
                            }
                            cout << "Username updated!" << endl;
                        } else if(choice == "3") {
                            cout << "Enter new password: ";
                            getline(cin, password);
                            employees[i].password = password;
                            if(uid == currUser.uid) {
                                currUser.password = password;
                            }
                            cout << "Password updated!" << endl;
                        } else {
                            cout << "Invalid command!" << endl;
                        }
                    }
                }
            }
            return;
        }
};

    // Create a vector of employees globally
    vector<Employee> employees;
    Employee currUser = Employee("", 0, "", "");

    // Display commands based on user role:
    string displayCommands(Employee currUser) {
        cout << "List of commands: " << endl;
        if (currUser.role == "GeneralEmployee") {
            cout << "0. Exit" << endl;
            cout << "1. View your profile" << endl;
        } else if (currUser.role == "Manager") {
            cout << "0. Exit" << endl;
            cout << "1. View your profile" << endl;
            cout << "2. View all employees" << endl;
            cout << "3. Search for an employee" << endl;
        } else if (currUser.role == "HumanResources") {
            cout << "0. Exit" << endl;
            cout << "1. View your profile" << endl;
            cout << "2. View all employees" << endl;
            cout << "3. Search for an employee" << endl;
            cout << "4. Add new employee" << endl;
            cout << "5. Remove employee" << endl;
            cout << "6. Update employee" << endl;
        };
        string command;
        cout << "Enter your command: ";
        getline(cin, command);
        return command;
    };

    // Command function
    void executeCommand(string command) {
        EmployeeService employeeService;
        string search;
        int uid;
        if (command == "0") {
            cout << "Goodbye ✋" << endl;
            return;
        } else if(command == "1") {
            employeeService.viewProfile(currUser);
            return;
        } else if(command == "2") {
            if(currUser.role == "Manager" || currUser.role == "HumanResources") {
                cout << "List of employees: " << endl;
                employeeService.viewEmployees(currUser, employees);
                return;
            }
        } else if(command == "3") {
            if(currUser.role == "Manager" || currUser.role == "HumanResources") {
                cout << "Enter name of employee: "; 
                getline(cin, search);
                employeeService.searchEmployee(search, employees);
                return;
            }
        } else if(command == "4") {
            if(currUser.role == "HumanResources") {
                employeeService.addEmployee(employees);
                return;
            }
        } else if(command == "5") {
            if(currUser.role == "HumanResources") {
                // input validation for uid. If user enters a string, it will clear the cin and ask for number again
                while (true) {
                    cout << "Enter uid of employee to remove: ";
                    cin >> uid;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore();
                        cout << "Invalid input! Please enter a number" << endl;
                    } else {
                        cin.ignore();
                        break;
                    }
                }
                bool removalSuccess = employeeService.removeEmployee(uid, employees, currUser);
                if (!removalSuccess) {
                    return;
                }
                return;
            }
        } else if(command == "6") {
            if(currUser.role == "HumanResources") {
                // input validation for uid. If user enters a string, it will clear the cin and ask for number again
                while (true) {
                    cout << "Enter uid of employee to remove: ";
                    cin >> uid;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore();
                        cout << "Invalid input! Please enter a number" << endl;
                    } else {
                        cin.ignore();
                        break;
                    }
                }
                employeeService.updateEmployee(uid, employees, currUser);
            }
            return;
        }
        else {
            cout << "Invalid command!" << endl;
            return;
        }
    }

    void signIn() {
        EmployeeService employeeService;
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
        return;
    }

int main() {

    EmployeeService employeeService;

    // Create dummy data of employees
    // Use to sign in and execute commands!
    Employee employee1("Jimmy Brown", 1, "jimmyneutron", "1234");
    Employee employee2("Jane Linn", 2, "janedoe", "password");
    Manager manager1("Manny Valentine", 3, "MannyTheManager", "admin");
    HumanResources hr1("Scott Sock", 4, "coolguy", "admin123");
    employees.push_back(employee1);
    employees.push_back(employee2);
    employees.push_back(manager1);
    employees.push_back(hr1);

    // Sign in
    signIn();

    // Loop that will keep asking for commands until user exits or signs out
    string command;
    while(command != "0") {
        cout << "Enter 'l' to list commands or 's' to sign out" << endl;
        getline(cin, command);
        if (command == "l") {
            command = displayCommands(currUser);
        } else if (command == "s") {
            cout << "You have been signed out!" << endl;
            signIn();
        }
        executeCommand(command);
    }
    
    return 0;
};