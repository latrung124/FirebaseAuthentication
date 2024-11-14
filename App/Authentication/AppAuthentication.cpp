/*
* AppAuthentication.cpp
* Author: Trung La
* Date: 2024-11-13
* This class is responsible for authenticating the user with Firebase.
*/

#include "Authentication/AppAuthentication.h"
#include "Authentication/AuthProvider/GoogleAuthProvider.h"
#include "Authentication/AuthProvider/EmailPwAuthProvider.h"

#include <iostream>
#include <chrono>

AppAuthentication::AppAuthentication(firebase::App* app) {
    if (app == nullptr) {
        std::cerr << "Firebase App is null!" << std::endl;
        return;
    }

    if (!app) {
        std::cerr << "Firebase App is null!" << std::endl;
        return;
    }

    mAuth = firebase::auth::Auth::GetAuth(app); // Get the Auth object from the App

    if (!mAuth) {
        std::cerr << "Failed to initialize Firebase Auth!" << std::endl;
        return;
    }

    // Add an authentication state listener
    addAppAuthStateListener();
}

AppAuthentication::~AppAuthentication() {
    if (mAuth) {
        delete mAuth;
        mAuth = nullptr;
    }
}

void AppAuthentication::initializeExternalAuthProviders() {
    // Initialize external authentication providers
    mExAuthProviders[UtilAuthProviderType::Google] = std::make_unique<GoogleAuthProvider>(mAuth);
}

void AppAuthentication::initializeInternalAuthProvider() {
    // Initialize internal authentication provider
    mIntAuthProvider = std::make_unique<EmailPwAuthProvider>(mAuth);
}

bool AppAuthentication::isValid() const {
    return mAuth != nullptr;
}

void AppAuthentication::addAppAuthStateListener() {
    mAuth->AddAuthStateListener(new AppAuthStateListener());
}

bool AppAuthentication::createAccount(UtilAuthProviderType authType, const std::string& email, const std::string& password) {
    if (authType == UtilAuthProviderType::EmailPassword) {
        return mIntAuthProvider->createAccount(email, password);
    }

    if (mExAuthProviders.find(authType) != mExAuthProviders.end()) {
        return mExAuthProviders[authType]->createAccount(email, password);
    }

    std::cerr << "Invalid authentication provider type!" << std::endl;
    return false;
}

bool AppAuthentication::login(UtilAuthProviderType authType, const std::string& email, const std::string& password) {
    if (authType == UtilAuthProviderType::EmailPassword) {
        return mIntAuthProvider->login(email, password);
    }

    if (mExAuthProviders.find(authType) != mExAuthProviders.end()) {
        return mExAuthProviders[authType]->login(email, password);
    }

    std::cerr << "Invalid authentication provider type!" << std::endl;
    return false;
}

void AppAuthentication::signOut() {
    if(mAuth == nullptr) {
        std::cerr << "Firebase Auth is null!" << std::endl;
        return;
    }

    mAuth->SignOut();
}

bool AppAuthentication::deleteUser() {
    if (mIntAuthProvider == nullptr) {
        std::cerr << "Internal Auth Provider is null!" << std::endl;
        return false;
    }

    return mIntAuthProvider->deleteUser();
}

bool AppAuthentication::updatePassword(const std::string& newPassword) {
    if (mIntAuthProvider == nullptr) {
        std::cerr << "Internal Auth Provider is null!" << std::endl;
        return false;
    }

    return mIntAuthProvider->updatePassword(newPassword);
}