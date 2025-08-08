# C++ Password Manager

A simple, interactive Password Manager written in **C++**. This application allows you to register, securely log in, and manage multiple account credentials with basic encryption and password strength checks. 

***

## 🚀 Features

- **User Registration & Login**: Create a secure account and log in.
- **Store Multiple Credentials**: Add, update, delete, display, and search credentials for various accounts.
- **Basic File-Based Encryption**: Data is encrypted and decrypted using XOR cipher for basic security.
- **Password Strength Checker**: Assess your password strength (Strong/Medium/Weak) and receive feedback to enhance it.
- **Email Format Validation**: Ensures email IDs are valid when adding Gmail/Email accounts.

***

## 🛠️ How It Works

- All your data (on successful login/registration) is stored in a file named after your username (e.g., `john.txt`), encrypted with an XOR cipher.
- Credentials (username, password, and account name) can be managed interactively through a menu-driven interface.
- Password strength is checked according to: length, uppercase, lowercase, digit, and special character requirements.

***

## 📦 File Structure

```
PasswordManager.cpp   # Main C++ source file
(username).txt        # Encrypted data file for each registered user
```

***

## 🏁 Getting Started

### Prerequisites

- C++17 or newer
- A standard C++ compiler (**g++**, **clang++**, or MSVC)
- Windows (uses `system("cls")` for clearing screen; replace with `system("clear")` for Linux/Mac)

### Build & Run

```sh
g++ -std=c++17 PasswordManager.cpp -o PasswordManager
./PasswordManager
```

***

## 🎮 Usage

- **Register**: Create a new user account.
- **Login**: Access your stored credentials.
- **Add User**: Store credentials for different accounts (Gmail, Facebook, etc.).
- **Delete/Update/Display/Search User**: Manage and view your stored accounts.
- **Logout**: Safely exit and save data.

***

## 🔒 Security Notice

- This program uses a very basic XOR cipher for encryption, which is not secure for real-world applications.
- Do **not** use this for storing sensitive or important passwords!
- For production, consider using industry-grade encryption libraries and secure data handling.

***

## 👤 Author

Created by Lalitendra.  

**Happy password managing!** 😊🔑

***
