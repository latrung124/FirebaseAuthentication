/*
* ExternalAuthProvider.h
* Author: Trung La
* Date: 2024-11-14
* Description: This class is responsible for authenticating the user with Firebase using an external provider.
*/

#ifndef EXTERNAL_ABSTRACTAUTHPROVIDER_H
#define EXTERNAL_ABSTRACTAUTHPROVIDER_H

#include <firebase/auth.h>

class AbstractExternalAuthProvider {

public:
    AbstractExternalAuthProvider(firebase::auth::Auth* authApp) : mAuth(authApp) {}
    AbstractExternalAuthProvider() = delete;
    AbstractExternalAuthProvider(const AbstractExternalAuthProvider&) = delete;
    AbstractExternalAuthProvider& operator=(const AbstractExternalAuthProvider&) = delete;
    AbstractExternalAuthProvider(AbstractExternalAuthProvider&&) = delete;
    AbstractExternalAuthProvider& operator=(AbstractExternalAuthProvider&&) = delete;
    ~AbstractExternalAuthProvider() = default;

    virtual bool createAccount(const std::string& email, const std::string& password) = 0;
    virtual bool login(const std::string& email, const std::string& password) = 0;

protected:
    firebase::auth::Auth* mAuth;
};

#endif //EXTERNAL_ABSTRACTAUTHPROVIDER_H