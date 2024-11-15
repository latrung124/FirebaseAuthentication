/*
* EmailPwAuthProvider.cpp
* Author: Trung La
* Date: 2024-11-14
* This class is responsible for authenticating the user with Firebase using email and password.
*/

#include <Logging.h>
#include "Authentication/AuthProvider/EmailPwAuthProvider.h"

#include <iostream>

bool EmailPwAuthProvider::createAccount(const std::string& email, const std::string& password) {
    if (mAuth == nullptr) {
        LOG_WARNING("Firebase Auth is null!");
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
            LOG_WARNING(result_data.error_message());
        }
    }, nullptr);
    return true;
}

bool EmailPwAuthProvider::login(const std::string& email, const std::string& password) {
    if (mAuth == nullptr) {
        LOG_WARNING("Firebase Auth is null!");
        return false;
    }

    firebase::Future<firebase::auth::AuthResult> result = mAuth->SignInWithEmailAndPassword(email.c_str(), password.c_str());

    result.OnCompletion([](const firebase::Future<firebase::auth::AuthResult>& result_data, void* user_data) {
        if (result_data.error() == firebase::auth::kAuthErrorNone) {
            LOG_WARNING("User logged in successfully!");
        } else {
            LOG_WARNING(result_data.error_message());
        }
    }, nullptr);
    return true;
}

bool EmailPwAuthProvider::deleteUser() {
    if (mAuth == nullptr) {
        LOG_WARNING("Firebase Auth is null!");
        return false;
    }

    auto user = mAuth->current_user();
    if (!user.is_valid()) {
        LOG_WARNING("No user signed in!");
        return false;
    }
    auto result = user.Delete();

    result.OnCompletion([](const firebase::Future<void>& result_data, void* user_data) {
        if (result_data.error() == firebase::auth::kAuthErrorNone) {
            LOG_WARNING("User deleted successfully!");
        } else {
            LOG_WARNING(result_data.error_message());
        }
    }, nullptr);

    return true;
}

bool EmailPwAuthProvider::updatePassword(const std::string& newPassword) {
    if (mAuth == nullptr) {
        LOG_WARNING("Firebase Auth is null!");
        return false;
    }

    auto user = mAuth->current_user();
    if (!user.is_valid()) {
        LOG_WARNING("No user signed in!");
        return false;
    }

    auto result = user.UpdatePassword(newPassword.c_str());
    result.OnCompletion([](const firebase::Future<void>& result_data, void* user_data) {
        if (result_data.error() == firebase::auth::kAuthErrorNone) {
            LOG_WARNING("Password updated successfully!");
        } else {
            LOG_WARNING(result_data.error_message());
        }
    }, nullptr);

    return true;
}