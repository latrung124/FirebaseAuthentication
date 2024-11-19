/*
* AppAuthentication.cpp
* Author: Trung La
* Date: 2024-11-13
* This class is responsible for authenticating the user with Firebase.
*/

#include <Logging.h>
#include "Authentication/AppAuthentication.h"
#include "Authentication/AuthProvider/GoogleAuthProvider.h"
#include "Authentication/AuthProvider/EmailPwAuthProvider.h"

#include <iostream>
#include <chrono>

AppAuthentication::AppAuthentication(firebase::App* app) {
    if (app == nullptr) {
        LOG_WARNING("Firebase App is null!");
        return;
    }

    if (!app) {
        LOG_WARNING("Firebase App is null!");
        return;
    }

    mAuth = firebase::auth::Auth::GetAuth(app); // Get the Auth object from the App

    if (!mAuth) {
        LOG_WARNING("Failed to initialize Firebase Auth!");
        return;
    }
    initializeExternalAuthProviders(); // Initialize external authentication providers
    initializeInternalAuthProvider(); // Initialize internal authentication provider

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

bool AppAuthentication::createAccount(const std::string& email, const std::string& password) {

    return mIntAuthProvider->createAccount(email, password);
}

bool AppAuthentication::login(UtilAuthProviderType authType, const std::string& email, const std::string& password) {
    if (authType == UtilAuthProviderType::EmailPassword) {
        return mIntAuthProvider->login(email, password);
    }

    if (mExAuthProviders.find(authType) != mExAuthProviders.end()) {
        return mExAuthProviders[authType]->login();
    }

    LOG_WARNING("Login failed!");
    return false;
}

void AppAuthentication::signOut() {
    if(mAuth == nullptr) {
        LOG_WARNING("Firebase Auth is null!");
        return;
    }

    mAuth->SignOut();
}

bool AppAuthentication::deleteUser() {
    if (mIntAuthProvider == nullptr) {
        LOG_WARNING("Internal Auth Provider is null!");
        return false;
    }

    return mIntAuthProvider->deleteUser();
}

bool AppAuthentication::updatePassword(const std::string& newPassword) {
    if (mIntAuthProvider == nullptr) {
        LOG_WARNING("Internal Auth Provider is null!");
        return false;
    }

    return mIntAuthProvider->updatePassword(newPassword);
}