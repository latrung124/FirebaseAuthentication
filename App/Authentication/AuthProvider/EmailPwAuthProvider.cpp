/*
* EmailPwAuthProvider.cpp
* Author: Trung La
* Date: 2024-11-14
* This class is responsible for authenticating the user with Firebase using email and password.
*/

#include "Authentication/AuthProvider/EmailPwAuthProvider.h"

#include <iostream>

bool EmailPwAuthProvider::createAccount(const std::string& email, const std::string& password) {
    if (mAuth == nullptr) {
        std::cerr << "Firebase Auth is null!" << std::endl;
        return false;
    }

    firebase::Future<firebase::auth::AuthResult> result = mAuth->CreateUserWithEmailAndPassword(email.c_str(), password.c_str());
    while (result.status() == firebase::kFutureStatusPending) {
        // Wait until the result is available
        std::cout << "Signing in...\n";
    }

    result.OnCompletion([](const firebase::Future<firebase::auth::AuthResult>& result_data, void* user_data) {
        if (result_data.error() == firebase::auth::kAuthErrorNone) {
            std::cout << "User created successfully!" << std::endl;
        } else {
            std::cout << "Error creating user: " << result_data.error_message() << std::endl;
        }
    }, nullptr);
    return true;
}

bool EmailPwAuthProvider::login(const std::string& email, const std::string& password) {
    if (mAuth == nullptr) {
        std::cerr << "Firebase Auth is null!" << std::endl;
        return false;
    }

    firebase::Future<firebase::auth::AuthResult> result = mAuth->SignInWithEmailAndPassword(email.c_str(), password.c_str());

    result.OnCompletion([](const firebase::Future<firebase::auth::AuthResult>& result_data, void* user_data) {
        if (result_data.error() == firebase::auth::kAuthErrorNone) {
            std::cout << "User logged in successfully!" << std::endl;
        } else {
            std::cout << "Error logging in user: " << result_data.error_message() << std::endl;
        }
    }, nullptr);
    return true;
}

bool EmailPwAuthProvider::deleteUser() {
    if (mAuth == nullptr) {
        std::cerr << "Firebase Auth is null!" << std::endl;
        return false;
    }

    auto user = mAuth->current_user();
    if (!user.is_valid()) {
        std::cerr << "No user signed in!" << std::endl;
        return false;
    }
    auto result = user.Delete();

    result.OnCompletion([](const firebase::Future<void>& result_data, void* user_data) {
        if (result_data.error() == firebase::auth::kAuthErrorNone) {
            std::cout << "User deleted successfully!" << std::endl;
        } else {
            std::cout << "Error deleting user: " << result_data.error_message() << std::endl;
        }
    }, nullptr);

    return true;
}

bool EmailPwAuthProvider::updatePassword(const std::string& newPassword) {
    if (mAuth == nullptr) {
        std::cerr << "Firebase Auth is null!" << std::endl;
        return false;
    }

    auto user = mAuth->current_user();
    if (!user.is_valid()) {
        std::cerr << "No user signed in!" << std::endl;
        return false;
    }

    auto result = user.UpdatePassword(newPassword.c_str());
    result.OnCompletion([](const firebase::Future<void>& result_data, void* user_data) {
        if (result_data.error() == firebase::auth::kAuthErrorNone) {
            std::cout << "Password updated successfully!" << std::endl;
        } else {
            std::cout << "Error updating password: " << result_data.error_message() << std::endl;
        }
    }, nullptr);

    return true;
}