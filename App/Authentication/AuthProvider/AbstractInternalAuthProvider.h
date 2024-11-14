/*
* AbstractAuthProvider.h
* Author: Trung La
* Date: 2024-11-14
* Description: This class is responsible for authenticating the user with Firebase.
*/

#ifndef INTERNAL_ABSTRACTAUTHPROVIDER_H
#define INTERNAL_ABSTRACTAUTHPROVIDER_H
#include <firebase/auth.h>

#include <string>

class AbstractInternalAuthProvider {
public:
    AbstractInternalAuthProvider(firebase::auth::Auth* authApp) : mAuth(authApp) {}

    AbstractInternalAuthProvider() = delete;
    AbstractInternalAuthProvider(const AbstractInternalAuthProvider&) = delete;
    AbstractInternalAuthProvider& operator=(const AbstractInternalAuthProvider&) = delete;
    AbstractInternalAuthProvider(AbstractInternalAuthProvider&&) = delete;
    AbstractInternalAuthProvider& operator=(AbstractInternalAuthProvider&&) = delete;

    virtual ~AbstractInternalAuthProvider() = default;

    virtual bool createAccount(const std::string& email, const std::string& password) = 0;
    virtual bool login(const std::string& email, const std::string& password) = 0;

    virtual bool deleteUser() = 0;
    virtual bool updatePassword(const std::string& newPassword) = 0;

protected:
    firebase::auth::Auth* mAuth;
};

#endif //INTERNAL_ABSTRACTAUTHPROVIDER_H