/*
* GoogleAuthProvider.cpp
* Author: Trung La
* Date: 2024-11-14
* This class is responsible for authenticating the user with Firebase using Google.
*/

#include "Authentication/AuthProvider/GoogleAuthProvider.h"

#include <iostream>

bool GoogleAuthProvider::createAccount(const std::string& email, const std::string& password) {
    std::cerr << "GoogleAuthProvider does not support creating an account!" << std::endl;
    return false;
}

bool GoogleAuthProvider::login(const std::string& email, const std::string& password) {
    std::cerr << "GoogleAuthProvider does not support logging in with email and password!" << std::endl;
    return false;
}