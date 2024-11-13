/*
* AppAuthentication.cpp
* Author: Trung La
* Date: 2024-11-13
* This class is responsible for authenticating the user with Firebase.
*/

#include "Authentication/AppAuthentication.h"

#include <iostream>
#include <chrono>

AppAuthentication::AppAuthentication(const std::weak_ptr<firebase::App>& app) {
    auto appPtr = app.lock();

    if (!appPtr) {
        std::cerr << "Firebase App is null!" << std::endl;
        return;
    }

    mAuth = std::unique_ptr<firebase::auth::Auth>(firebase::auth::Auth::GetAuth(appPtr.get())); // Get the Auth object from the App

    if (!mAuth) {
        std::cerr << "Failed to initialize Firebase Auth!" << std::endl;
        return;
    }

    // Add an authentication state listener
    addAppAuthStateListener();
}

AppAuthentication::~AppAuthentication() {
    mAuth.reset();
}

void AppAuthentication::addAppAuthStateListener() {
    mAuth->AddAuthStateListener(new AppAuthStateListener());
}

bool AppAuthentication::createUserWithEmailAndPassword(const std::string& email, const std::string& password) {
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

bool AppAuthentication::loginUserWithEmailAndPassword(const std::string& email, const std::string& password) {
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

void AppAuthentication::signOut() {
    // Sign out the current user
    mAuth->SignOut();
}

bool AppAuthentication::deleteUser() {
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
}

bool AppAuthentication::updatePassword(const std::string& newPassword) {
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
}