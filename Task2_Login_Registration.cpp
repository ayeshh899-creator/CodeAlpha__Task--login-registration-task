#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct User {
    string username;
    string password;
};

// Registration function
void registerUser() {
    User user;
    
    cout << "\n===== REGISTRATION =====" << endl;
    cout << "Enter username: ";
    cin >> user.username;
    
    cout << "Enter password: ";
    cin >> user.password;
    
    // Check if username already exists
    ifstream checkFile("users.txt");
    string line;
    bool exists = false;
    
    while (getline(checkFile, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos && line.substr(0, pos) == user.username) {
            exists = true;
            break;
        }
    }
    checkFile.close();
    
    if (exists) {
        cout << "\n⚠️ Username already taken! Please choose another." << endl;
        return;
    }
    
    // Save new user to file
    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << user.username << "," << user.password << endl;
        file.close();
        cout << "\n✅ Registration successful! You can now login." << endl;
    } else {
        cout << "\n❌ Error: Could not save user data." << endl;
    }
}

// Login function
void loginUser() {
    string username, password;
    
    cout << "\n===== LOGIN =====" << endl;
    cout << "Enter username: ";
    cin >> username;
    
    cout << "Enter password: ";
    cin >> password;
    
    // Check credentials
    ifstream file("users.txt");
    string line;
    bool loginSuccess = false;
    
    while (getline(file, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            string savedUser = line.substr(0, pos);
            string savedPass = line.substr(pos + 1);
            
            if (savedUser == username && savedPass == password) {
                loginSuccess = true;
                break;
            }
        }
    }
    file.close();
    
    if (loginSuccess) {
        cout << "\n🎉 Login successful! Welcome, " << username << "!" << endl;
    } else {
        cout << "\n❌ Invalid username or password!" << endl;
    }
}

// Main menu
int main() {
    int choice;
    
    cout << "========== LOGIN AND REGISTRATION SYSTEM ==========" << endl;
    
    do {
        cout << "\n1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (choice == 1) {
            registerUser();
        }
        else if (choice == 2) {
            loginUser();
        }
        else if (choice == 3) {
            cout << "\nThank you! Exiting..." << endl;
        }
        else {
            cout << "\n⚠️ Invalid choice! Please try again." << endl;
        }
        
    } while (choice != 3);
    
    return 0;
}
