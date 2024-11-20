/*
* GoogleAuthProvider.h
* Author: Trung La
* Date: 2024-11-14
* Description: This class is responsible for authenticating the user with Firebase using Google.
*/

#ifndef GOOGLEAUTHPROVIDER_H
#define GOOGLEAUTHPROVIDER_H

#include "Authentication/AuthProvider/AbstractExternalAuthProvider.h"
#include "Authentication/AuthProvider/GoogleOauth.h"

#include <memory>

class GoogleAuthProvider : public AbstractExternalAuthProvider {

public:
    GoogleAuthProvider(firebase::auth::Auth* authApp);
    ~GoogleAuthProvider() = default;

    bool login() override;

private:
    std::unique_ptr<GoogleOauth> mGoogleOauth;
};

#endif //GOOGLEAUTHPROVIDER_H