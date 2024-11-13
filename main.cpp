#include "Authentication/AppAuthentication.h"

#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    FirebaseApp firebaseApp;
    AppAuthentication appAuth(firebaseApp.getApp());

    std::cout << "Enter email and password: " << std::endl;
    std::string email = "";
    std::string password = "";
    std::cin >> email;
    std::cin >> password;

    if (appAuth.loginUserWithEmailAndPassword(email, password)) {
        std::cout << "Logging in user..." << std::endl;
    } else {
        std::cout << "Error logging in user!" << std::endl;
    }

    std::cout << "Enter new password: " << std::endl;
    std::string newPassword = "";
    std::cin >> newPassword;
    if (appAuth.updatePassword(newPassword)) {
        std::cout << "Updating password..." << std::endl;
    } else {
        std::cout << "Error updating password!" << std::endl;
    }

    appAuth.signOut();

    return 0;
}