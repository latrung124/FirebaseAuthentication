#include "Authentication/AppAuthentication.h"

#include <iostream>
#include <map>
#include <vector>

const std::map<char, std::string> gCommands {
    {'i', " - Login to firebase cloud with email and account! \n"},
    {'g', " - Login with Google account! \n"},
    {'o', " - Sign out! \n"},
    {'a', " - Create account with email and account! \n"},
    {'d', " - Delete current user account! \n"},
    {'e', " - Exit app! \n"},
};

void printCommandLine() {
    std::cout << "Firebase interact command line! \n";
    for (auto& it : gCommands) {
        std::cout << it.first << it.second;
    }

    std::cout << "Enter command line: ";
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    FirebaseApp firebaseApp;
    if (!firebaseApp.initialize()) {
        std::cout << "Error initializing Firebase App!" << std::endl;
        return -1;
    }

    AppAuthentication appAuth(firebaseApp.getApp());

    std::string email = "";
    std::string password = "";

    while(true) {
        printCommandLine();
        char commandOpt = ' ';
        std::cin >> commandOpt;

        switch (commandOpt)
        {
        case 'i':{
            //login
            std::cout << "Email: ";
            email = "";
            std::cin >> email;
            std::cout << "Password: ";
            password = "";
            std::cin >> password;
            if (appAuth.login(UtilAuthProviderType::EmailPassword, email, password)) {
                std::cout << "Logging in user..." << std::endl;
            } else {
                std::cout << "Error logging in user!" << std::endl;
            }
            break;
        }
        case 'g': {
            //login
            if (appAuth.login(UtilAuthProviderType::Google)) {
                std::cout << "Logging in user..." << std::endl;
            } else {
                std::cout << "Error logging in user!" << std::endl;
            }
            break;
        }
        case 'o': {
            //sign out
            appAuth.signOut();
            break;
        }
        case 'a': {
            std::cout << "Email: ";
            email = "";
            std::cin >> email;
            std::cout << "Password: ";
            password = "";
            std::cin >> password;
            if (appAuth.createAccount(email, password)) {
                std::cout << "Creating user account..." << std::endl;
            } else {
                std::cout << "Error create a user account!" << std::endl;
            }
            break;
        }
        case 'd': {
            if (appAuth.deleteUser()) {
                std::cout << "Delete user account..." << std::endl;
            } else {
                std::cout << "Delete user account failed!" << std::endl;
            }
        }
        case 'e': {
            std::cout << "Close app!\n";
            firebaseApp.exit();
            exit(0);
        }
        default: {
            std::cout << "Unknown command!\n";
            break;
        }
        }
    }

    return 0;
}