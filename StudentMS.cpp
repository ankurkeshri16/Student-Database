#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

// Email Validation Pattern
bool isEmailValid(string email) {
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email, pattern);
}

class Student {
private:
    string name, rollNumber, course, address, email;
    long long int contactNumber;

public:
    void displayMenu();
    void addRecord();
    void displayRecords();
    void modifyRecord();
    void searchRecord();
    void deleteRecord();
};

void Student::displayMenu() {
    while (true) {
        int choice;
        char response;
        cout << "\n-------------------------------" << endl;
        cout << "| STUDENT MANAGEMENT SYSTEM   |" << endl;
        cout << "-------------------------------" << endl;
        cout << " 1. Add New Record" << endl;
        cout << " 2. Display Records" << endl;
        cout << " 3. Modify Record" << endl;
        cout << " 4. Search Record" << endl;
        cout << " 5. Delete Record" << endl;
        cout << " 6. Exit\n" << endl;
        cout << " Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                do {
                    addRecord();
                    cout << "\n Add Another Student Record? (Y/N): ";
                    cin >> response;
                } while (response == 'y' || response == 'Y');
                break;
            case 2:
                displayRecords();
                break;
            case 3:
                modifyRecord();
                break;
            case 4:
                searchRecord();
                break;
            case 5:
                deleteRecord();
                break;
            case 6:
                cout << "\n Exiting the program." << endl;
                exit(0);
            default:
                cout << "\n Invalid choice. Please try again." << endl;
        }
    }
}

void Student::addRecord() {
    system("cls");
    ofstream file("studentRecord.txt", ios::app);
    cout << "\n-------------------------------" << endl;
    cout << "------- Add Student Record -----" << endl;
    cout << " Enter Name: ";
    cin >> name;
    cout << " Enter Roll No.: ";
    cin >> rollNumber;
    cout << " Enter Course: ";
    cin >> course;
    cout << " Enter Email Id (name@gmail.com): ";
    cin >> email;
    while (!isEmailValid(email)) {
        cout << " Invalid Email format. Enter a valid email: ";
        cin >> email;
    }
    cout << " Enter Contact No (9639xxxxxx): ";
    cin >> contactNumber;
    while (contactNumber < 1000000000 || contactNumber > 9999999999) {
        cout << " Please enter a 10-digit contact number: ";
        cin >> contactNumber;
    }
    cout << " Enter Address: ";
    cin >> address;
    file << name << " " << rollNumber << " " << course << " " << email << " " << contactNumber << " " << address << "\n";
    cout << "\n Record added successfully." << endl;
    file.close();
}

void Student::displayRecords() {
    system("cls");
    ifstream file("studentRecord.txt");
    int totalRecords = 0;
    cout << "\n-------------------------------" << endl;
    cout << "------ Student Record Table ----" << endl;
    if (!file) {
        cout << "\n No records found." << endl;
    } else {
        while (file >> name >> rollNumber >> course >> email >> contactNumber >> address) {
            totalRecords++;
            cout << "\n Student No.: " << totalRecords << endl;
            cout << " Name: " << name << endl;
            cout << " Roll No.: " << rollNumber << endl;
            cout << " Course: " << course << endl;
            cout << " Email: " << email << endl;
            cout << " Contact No.: " << contactNumber << endl;
            cout << " Address: " << address << endl;
        }
        if (totalRecords == 0) {
            cout << "\n No records found." << endl;
        }
    }
    file.close();
}

void Student::modifyRecord() {
    system("cls");
    ifstream inputFile("studentRecord.txt");
    ofstream outputFile("temp.txt");
    string rollToModify;
    int found = 0;
    cout << "\n-------------------------------" << endl;
    cout << "----- Modify Student Details -----" << endl;
    if (!inputFile) {
        cout << "\n No records found." << endl;
        inputFile.close();
        outputFile.close();
    } else {
        cout << " Enter Roll No. of Student to modify: ";
        cin >> rollToModify;
        while (inputFile >> name >> rollNumber >> course >> email >> contactNumber >> address) {
            if (rollToModify != rollNumber) {
                outputFile << name << " " << rollNumber << " " << course << " " << email << " " << contactNumber << " " << address << "\n";
            } else {
                found++;
                cout << "\n Enter New Details for Roll No. " << rollNumber << ":" << endl;
                cout << " Name: ";
                cin >> name;
                cout << " Course: ";
                cin >> course;
                cout << " Email: ";
                cin >> email;
                while (!isEmailValid(email)) {
                    cout << " Invalid Email format. Enter a valid email: ";
                    cin >> email;
                }
                cout << " Contact No.: ";
                cin >> contactNumber;
                while (contactNumber < 1000000000 || contactNumber > 9999999999) {
                    cout << " Please enter a 10-digit contact number: ";
                    cin >> contactNumber;
                }
                cout << " Address: ";
                cin >> address;
                outputFile << name << " " << rollNumber << " " << course << " " << email << " " << contactNumber << " " << address << "\n";
                cout << "\n Record modified successfully." << endl;
            }
        }
        if (found == 0) {
            cout << "\n No records found with Roll No. " << rollToModify << "." << endl;
        }
        inputFile.close();
        outputFile.close();
        remove("studentRecord.txt");
        rename("temp.txt", "studentRecord.txt");
    }
}

void Student::searchRecord() {
    system("cls");
    ifstream file("studentRecord.txt");
    int found = 0;
    string rollToSearch;
    cout << "\n-------------------------------" << endl;
    cout << "------ Search Student Record ------" << endl;
    if (!file) {
        cout << "\n No records found." << endl;
    } else {
        cout << " Enter Roll No. of Student to search: ";
        cin >> rollToSearch;
        while (file >> name >> rollNumber >> course >> email >> contactNumber >> address) {
            if (rollToSearch == rollNumber) {
                cout << "\n Name: " << name << endl;
                cout << " Roll No.: " << rollNumber << endl;
                cout << " Course: " << course << endl;
                cout << " Email: " << email << endl;
                cout << " Contact No.: " << contactNumber << endl;
                cout << " Address: " << address << endl;
                found++;
            }
        }
        if (found == 0) {
            cout << "\n No records found with Roll No. " << rollToSearch << "." << endl;
        }
    }
    file.close();
}

void Student::deleteRecord() {
    system("cls");
    ifstream inputFile("studentRecord.txt");
    ofstream outputFile("temp.txt");
    string rollToDelete;
    int found = 0;
    cout << "\n-------------------------------" << endl;
    cout << "------ Delete Student Details -----" << endl;
    if (!inputFile) {
        cout << "\n No records found." << endl;
        inputFile.close();
        outputFile.close();
    } else {
        cout << " Enter Roll No. of Student to delete: ";
        cin >> rollToDelete;
        while (inputFile >> name >> rollNumber >> course >> email >> contactNumber >> address) {
            if (rollToDelete != rollNumber) {
                outputFile << name << " " << rollNumber << " " << course << " " << email << " " << contactNumber << " " << address << "\n";
            } else {
                found++;
                cout << "\n Record for Roll No. " << rollNumber << " has been deleted." << endl;
            }
        }
        if (found == 0) {
            cout << "\n No records found with Roll No. " << rollToDelete << "." << endl;
        }
        inputFile.close();
        outputFile.close();
        remove("studentRecord.txt");
        rename("temp.txt", "studentRecord.txt");
    }
}

int main() {
    Student studentSystem;
    studentSystem.displayMenu();
    return 0;
}
