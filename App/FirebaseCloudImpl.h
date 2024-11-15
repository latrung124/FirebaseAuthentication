/*
* FirebaseCloudImpl.h
* Author: Trung La
* Date: 2024-11-14
* Description: This class is responsible for implementing the methods to interact with Firebase Cloud.
*/

#ifndef APP_FIREBASECLOUDIMPL_H
#define APP_FIREBASECLOUDIMPL_H

#include <IFirebaseCloud.h>
#include <FirebaseApp.h>
#include "Authentication/AppAuthentication.h"

class FirebaseCloudImpl : public IFirebaseCloud {
public:
    FirebaseCloudImpl();
    ~FirebaseCloudImpl() override;

    FirebaseCloudImpl(const FirebaseCloudImpl&) = delete;
    FirebaseCloudImpl& operator=(const FirebaseCloudImpl&) = delete;

    bool connect() override;
    void disconnect() override;

    bool login(UtilAuthProviderType authType,
               const std::string &email,
               const std::string &password) override;

    bool signOut() override;
    bool createAccount(const std::string &email, const std::string &password) override;
    bool deleteAccount() override;

    bool updatePassword(const std::string &newPassword) override;

private:
    bool mIsConnected = false;
    FirebaseApp* mFirebaseApp;
    AppAuthentication* mAppAuthentication;
};

#endif //APP_FIREBASECLOUDIMPL_H
