/*
* EmailPwAuthProvider.h
* Author: Trung La
* Date: 2024-11-14
* Description: This class is responsible for authenticating the user with Firebase using email and password.
*/

#ifndef EMAILPW_AUTHPROVIDER_H
#define EMAILPW_AUTHPROVIDER_H

#include "Authentication/AuthProvider/AbstractInternalAuthProvider.h"

class EmailPwAuthProvider : public AbstractInternalAuthProvider {

public:
    EmailPwAuthProvider(firebase::auth::Auth* authApp) : AbstractInternalAuthProvider(authApp) {}
    ~EmailPwAuthProvider() = default;

    bool createAccount(const std::string& email, const std::string& password) override;
    bool login(const std::string& email, const std::string& password) override;
    bool deleteUser() override;
    bool updatePassword(const std::string& newPassword) override;
};

#endif //EMAILPW_AUTHPROVIDER_H