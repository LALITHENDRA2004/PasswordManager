#include<iostream>
#include<algorithm>
#include<fstream>
#include<string>
#include<vector>
#include<regex>

using namespace std;

struct User { 
    string userName;
    string password;
    string accountName;
};

ostream& operator<<(ostream& out, User& Data) {
    out << "--------------------------------" << endl;
    out << "User Name   : " << Data.userName << endl;
    out << "Password    : " << Data.password << endl;
    out << "Account Name: " << Data.accountName << endl;
    return out;
}

bool isValidEmail(const string& email) {
    const regex valid(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return regex_match(email, valid);
}

string passwordStrengthChecker(const string& password) {
    bool hasLower = false;
    bool hasUpper = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    bool passwordLength = password.length() >= 8 ? 1 : 0;
    string specialChars = "!@#$%^&*()-+";
    int totalConditionsLength = 0;

    for(auto ch : password) {
        if(islower(ch)) {
            hasLower = true;
        }
        else if(isupper(ch)) {
            hasUpper = true;
        }
        else if(isdigit(ch)) {
            hasDigit = true;
        }
        else if(specialChars.find(ch) != string::npos) {
            hasSpecial = true; 
        }
    }

    totalConditionsLength = hasLower + hasUpper + hasDigit + hasSpecial + passwordLength;

    if(totalConditionsLength >= 5) {
        return "Strong";
    }
    else if(totalConditionsLength >= 3) {
        return "Medium";
    }
    else {
        return "Weak";
    }
}

class PasswordManager {
    private:
        string LoginUserName;
        string LoginPassword;
        vector<User> listOfUsers;

    public:
        ~PasswordManager() {         
        if (!LoginUserName.empty())
            saveToFile();
        }

        string xorEncryptDecrypt(const string &data, char key = 'K');
        void saveToFile();
        void loadFromFile();
        void mainMenu();
        void addUser();
        void deleteUser();
        void updateUser();
        void displayUsers();
        void searchUser();
        void loginMainMenu();
        void registerUser(); 
        void login();
        void logout();
        void passwordCheck(const string);
};

string PasswordManager::xorEncryptDecrypt(const string &data, const char key) {
    string result = data;
    for (char& ch : result) {
        ch ^= key;
    }
    return result;
}


void PasswordManager::saveToFile() {
    // overwrite
    ofstream file(LoginUserName + ".txt"); 
    if(file.is_open()) {
        // encrypt
        file << xorEncryptDecrypt(LoginUserName) << "\n";  
        file << xorEncryptDecrypt(LoginPassword) << "\n";  

        for(const auto& user : listOfUsers) {
            file << xorEncryptDecrypt(user.userName) << "\n";
            file << xorEncryptDecrypt(user.password) << "\n";
            file << xorEncryptDecrypt(user.accountName) << "\n";
        }
        file.close();
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}


void PasswordManager::loadFromFile() {
    // reading
    ifstream file(LoginUserName + ".txt"); 
    if(file.is_open()) {
        string tempUserName;
        getline(file, tempUserName);
        getline(file, LoginPassword);

        // decrypt
        LoginUserName = xorEncryptDecrypt(tempUserName); 
        LoginPassword = xorEncryptDecrypt(LoginPassword);

        User user;
        while(getline(file, user.userName) &&
            getline(file, user.password) &&
            getline(file, user.accountName)) {
            // decrypt
            user.userName = xorEncryptDecrypt(user.userName);
            user.password = xorEncryptDecrypt(user.password);
            user.accountName = xorEncryptDecrypt(user.accountName);
            listOfUsers.push_back(user);
        }
        file.close();
    } else {
        cout << "Unable to open file for reading." << endl;
    }
}


void PasswordManager::loginMainMenu() {
    int choice;
    do {
        cout << "Welcome to the Password Manager!" << endl;
        cout << "--------------------------------" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Please select an option: ";
        cin >> choice;

        // Ignore the newline character left in the buffer
        cin.ignore(); 
        
        system("cls");
        switch(choice) {
            case 1:
                registerUser();
                break;
            case 2:
                login();
                break;
            case 3:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 3);
}

void PasswordManager::registerUser() {
    string inputUserName;
    string inputPassword;
    cout << "Registering a new user..." << endl;
    cout << "Enter username: ";
    getline(cin, inputUserName);
    cout << "Enter password: ";
    getline(cin, inputPassword);

    // Check if the file already exists 
    ifstream file(inputUserName + ".txt");
    if(file.is_open()) {
        cout << "Username already exists. Please choose a different username.";
        file.close();
    }
    else {
        LoginUserName = inputUserName;
        LoginPassword = inputPassword;
        saveToFile();
        cout << "User registered successfully!" << endl;
        file.close();
    }
}

void PasswordManager::login() {
    string inputUserName;
    string inputPassword;
    cout << "Logging in..." << endl;
    cout << "Enter username: ";
    getline(cin, inputUserName);

    ifstream file(inputUserName + ".txt");
    if(file.is_open()) {
        file.close();
        LoginUserName = inputUserName;
        loadFromFile();
        cout << "Enter password: ";
        getline(cin, inputPassword);

        if(inputPassword == LoginPassword) {
            cout << "Login successful" << endl;
            mainMenu();
        }
        else {
            cout << "Incorrect password. Please try again." << endl;
        }
    }
    else {
        cout << "Username not found. Please register. first." << endl;
    }
    
}

void PasswordManager::mainMenu() {
    int choice;
    do {
        cout << "--------------------------------" << endl;
        cout << "1. Add User" << endl;
        cout << "2. Delete User" << endl;
        cout << "3. Update User" << endl; 
        cout << "4. Display Users" << endl;
        cout << "5. Search User" << endl;
        cout << "6. Logout" << endl;
        cout << "Please select an option: ";
        cin >> choice;
        cin.ignore();
        system("cls");
        switch (choice)
        {
        case 1:
            addUser();
            break;
        case 2:
            deleteUser();
            break;
        case 3:
            updateUser();
            break;
        case 4:
            displayUsers();
            break;
        case 5:
            searchUser();
            break;
        case 6:
            logout();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 6);
}

void PasswordManager::addUser() {
    User newUser;
    cout << "--------------------------------" << endl;
    cout << "Adding a new user..." << endl;
    cout << "Enter username: ";
    getline(cin, newUser.userName);
    cout << "Enter password: ";
    getline(cin, newUser.password);
    cout << "Enter account name: ";
    getline(cin, newUser.accountName);
    passwordCheck(newUser.password);
    for(int x = 0 ; x < newUser.accountName.size() ; x++) {
        newUser.accountName[x] = tolower(newUser.accountName[x]);
    }
    if(newUser.accountName == "gmail" || newUser.accountName == "email") {
        if(isValidEmail(newUser.userName)) {
            listOfUsers.push_back(newUser);
            cout << "User added successfully!" << endl;
            saveToFile();
        }
        else {
            cout << "Email Id is invalid." << endl;
            cout << "--------------------------------" << endl;
            addUser();
        }
    }
    else {
        listOfUsers.push_back(newUser);
        cout << "User added successfully!" << endl;
        saveToFile();
    }

}

void PasswordManager::deleteUser() {
    string userName;
    bool found = false;
    cout << "Deleting a user..." << endl;
    cout << "Enter username to delete: ";
    getline(cin, userName);

    for(auto it = listOfUsers.begin() ; it != listOfUsers.end() ; ++it) {
        if(it -> userName == userName) {
            found = true;
            listOfUsers.erase(it);
            cout << "User deleted successfully!" << endl;
            saveToFile();
            break;
        }
    }
    if(!found) {
        cout << "User not found." << endl;
    }
}

void PasswordManager::updateUser() {
    string userName;
    cout << "Updating a user..." << endl;
    cout << "Enter username to update: ";
    getline(cin, userName);

    bool found = false;
    for(auto &user : listOfUsers) { 
        if(user.userName == userName) {
            found = true;
            cout << "Enter new password: ";
            getline(cin, user.password);
            cout << "User updated successfully!" << endl;
            saveToFile();
        }
    }
    if(!found) {
        cout << "User not found." << endl;
    }
}

void PasswordManager::displayUsers() {
    if(!listOfUsers.empty()) {
        cout << "Displaying all users..." << endl;
        for(auto &user : listOfUsers) {
            cout << user;
        }
    }
    else {
        cout << "Database is empty." << endl;
    }
}

void PasswordManager::searchUser() {
    string userName;
    bool found = false;
    cout << "Searching for a user..." << endl;
    cout << "-----------------------" << endl;
    cout << "Enter username to search: ";
    getline(cin, userName);
    
    for(auto &user : listOfUsers) {
        if(user.userName == userName) {
            found = true;
            cout << user; 
        }
    }
    if(!found) {
        cout << "User not found." << endl;
    }
}

void PasswordManager::logout() {
    cout << "Logging out..." << endl;
    saveToFile();
    LoginUserName = "";
    LoginPassword = "";
    listOfUsers.clear();
    cout << "Logged out successfully!" << endl;
}

void PasswordManager::passwordCheck(const string password) {
    string strength = passwordStrengthChecker(password);
    cout << "Password strength: " << strength << endl;

    if(!any_of(password.begin(), password.end(), ::isupper)) {
        cout << "Password must contain at least one uppercase letter." << endl;
    }
    if(!any_of(password.begin(), password.end(), ::islower)) {
        cout << "Password must contain at least one lowercase letter." << endl;
    }
    if(!any_of(password.begin(), password.end(), ::isdigit)) {
        cout << "Password must contain at least one digit." << endl;
    }
    if(password.find_first_of("!@#$%^&*()-+") == string::npos) {
        cout << "Password must contain at least one special character." << endl;
    }
    if(password.length() < 8) {
        cout << "Password must contain at least 8 characters." << endl;
    }
}

int main() {
    PasswordManager passwordManager;
    passwordManager.loginMainMenu();
    cout << endl;
    return 0;
}