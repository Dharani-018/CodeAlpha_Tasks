#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class AuthSystem {
private:
    const string db_file = "users.txt";

    // Helper to check if a username already exists
    bool userExists(string username) {
        ifstream file(db_file);
        string u, p;
        while (file >> u >> p) {
            if (u == username) return true;
        }
        return false;
    }

public:
    void registerUser() {
        string username, password;
        cout << "\n--- Registration ---" << endl;
        cout << "Enter username: ";
        cin >> username;

        if (userExists(username)) {
            cout << "Error: Username already taken!" << endl;
            return;
        }

        cout << "Enter password: ";
        cin >> password;

        // Open file in Append mode
        ofstream file(db_file, ios::app);
        if (file.is_open()) {
            file << username << " " << password << endl;
            file.close();
            cout << "Registration successful!" << endl;
        }
    }

    bool loginUser() {
        string username, password, u, p;
        cout << "\n--- Login ---" << endl;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        ifstream file(db_file);
        while (file >> u >> p) {
            if (u == username && p == password) {
                cout << "Login successful! Welcome, " << username << ".\n";
                return true;
            }
        }
        cout << "Invalid username or password." << endl;
        return false;
    }
};

int main() {
    AuthSystem system;
    int choice;

    while (true) {
        cout << "\n1. Register\n2. Login\n3. Exit\nSelect: ";
        cin >> choice;

        if (choice == 1) system.registerUser();
        else if (choice == 2) {
            if (system.loginUser()) {
                // Here you could trigger the Banking System from Task 4!
                break; 
            }
        }
        else break;
    }
    return 0;
}