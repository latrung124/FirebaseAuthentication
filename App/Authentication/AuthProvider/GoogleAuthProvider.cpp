/*
* GoogleAuthProvider.cpp
* Author: Trung La
* Date: 2024-11-14
* This class is responsible for authenticating the user with Firebase using Google.
*/

#include "Authentication/AuthProvider/GoogleAuthProvider.h"

#include <iostream>

GoogleAuthProvider::GoogleAuthProvider(firebase::auth::Auth* authApp) : AbstractExternalAuthProvider(authApp) {
    mGoogleOauth = std::make_unique<GoogleOauth>(std::string(FIREBASE_CONFIG_PATH) + "/client_secret_desktop.json");
}

bool GoogleAuthProvider::login() {
    if (mGoogleOauth->getAccessToken() == "") {
        std::cout << "Error getting access token!" << std::endl;
        return false;
    } else {
        std::cout << "Successfully logged in with Google!" << std::endl;
        return true;
    }
}