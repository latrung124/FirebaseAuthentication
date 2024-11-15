/*
* GoogleAuthProvider.h
* Author: Trung La
* Date: 2024-11-14
* Description: This class is responsible for authenticating the user with Firebase using Google.
*/

#ifndef GOOGLEAUTHPROVIDER_H
#define GOOGLEAUTHPROVIDER_H

#include "Authentication/AuthProvider/AbstractExternalAuthProvider.h"

class GoogleAuthProvider : public AbstractExternalAuthProvider {

public:
    GoogleAuthProvider(firebase::auth::Auth* authApp) : AbstractExternalAuthProvider(authApp) {}
    ~GoogleAuthProvider() = default;

    bool login() override;
};

#endif //GOOGLEAUTHPROVIDER_H