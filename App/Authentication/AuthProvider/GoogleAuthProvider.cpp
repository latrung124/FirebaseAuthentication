/*
* GoogleAuthProvider.cpp
* Author: Trung La
* Date: 2024-11-14
* This class is responsible for authenticating the user with Firebase using Google.
*/

#include <Logging.h>
#include "Authentication/AuthProvider/GoogleAuthProvider.h"

#include <iostream>

GoogleAuthProvider::GoogleAuthProvider(firebase::auth::Auth* authApp) : AbstractExternalAuthProvider(authApp) {
    mGoogleOauth = std::make_unique<GoogleOauth>(std::string(FIREBASE_CONFIG_PATH) + "/client_secret_desktop.json");
}

bool GoogleAuthProvider::login() {
    std::string code = mGoogleOauth->getAccessToken();

    if (code.empty()) {
        LOG_WARNING("Failed to get access token!");
        return false;
    }

    std::string token = mGoogleOauth->exchangeAccessToken(code);
    auto json = nlohmann::json::parse(token);
    auto accessToken = json["access_token"].get<std::string>();
    auto refresh_token = json["refresh_token"].get<std::string>();

    firebase::auth::Credential credential = firebase::auth::GoogleAuthProvider::GetCredential("", accessToken.c_str());
    return true;
}