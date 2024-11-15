/*
* IFirebaseCloud.h
* Author: Trung La
* Date: 2024-11-14
* Description: This interface class is responsible for defining the methods to interact with Firebase Cloud.
*/

#ifndef INTERFACE_IFIREBASECLOUD_H
#define INTERFACE_IFIREBASECLOUD_H

#include "Authentication/Utils/AuthUtils.h"

#include <string>

class IFirebaseCloud {
public:
    IFirebaseCloud() = default;
    virtual ~IFirebaseCloud() = default;

    IFirebaseCloud(const IFirebaseCloud&) = delete;
    IFirebaseCloud& operator=(const IFirebaseCloud&) = delete;

    virtual bool connect() = 0;
    virtual void disconnect() = 0;

    virtual bool login(UtilAuthProviderType authType,
                        const std::string &email,
                        const std::string &password) = 0;

    virtual bool signOut() = 0;
    virtual bool createAccount(const std::string &email, const std::string &password) = 0;
    virtual bool deleteAccount() = 0;

    virtual bool updatePassword(const std::string &newPassword) = 0;
};

#endif //INTERFACE_IFIREBASECLOUD_H