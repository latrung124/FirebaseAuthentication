/*
* AppAuthStateListener.cpp
* Author: Trung La
* Date: 2024-11-13
* This class is responsible for listening to the authentication state of the user.
*/

#include "Authentication/AppAuthStateListener.h"

#include <iostream>

AppAuthStateListener::AppAuthStateListener() {
    // Constructor
}

AppAuthStateListener::~AppAuthStateListener() {
    // Destructor
}

void AppAuthStateListener::OnAuthStateChanged(firebase::auth::Auth* auth) {
    // Handle authentication state changes
    auto user = auth->current_user();
    if (user.is_valid()) {
        // User is signed in
        std::cout << "User invalid." << std::endl;
    } else if (user.is_anonymous()) {
        // User is signed in
        std::cout << "User is anonymous." << std::endl;
    } else if (user.is_email_verified()) {
        // User is signed in
        std::cout << "User email is verified." << std::endl;
    } else {
        // User is signed out
        std::cout << "Unknown." << std::endl;
    }
}