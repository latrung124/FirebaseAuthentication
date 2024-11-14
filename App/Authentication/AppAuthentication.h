/*
* AppAuthentication.h
* Author: Trung La
* Date: 2024-11-13
* This class is responsible for authenticating the user with Firebase.
*/

#ifndef APP_APPAUTHENTICATION_H
#define APP_APPAUTHENTICATION_H

#include "FirebaseApp.h"
#include "Authentication/AppAuthStateListener.h"
#include "Authentication/Utils/AuthUtils.h"

#include <firebase/auth.h>

#include <string>
#include <memory>
#include <map>

class AbstractExternalAuthProvider;
class AbstractInternalAuthProvider;
class AppAuthentication {
public:
    explicit AppAuthentication(firebase::App* app);
    ~AppAuthentication();

    AppAuthentication(const AppAuthentication&) = delete;
    AppAuthentication& operator=(const AppAuthentication&) = delete;
    AppAuthentication(AppAuthentication&&) = delete;
    AppAuthentication& operator=(AppAuthentication&&) = delete;

    bool isValid() const;

    bool login(UtilAuthProviderType authType, const std::string& email, const std::string& password);
    bool createAccount(UtilAuthProviderType authType, const std::string& email, const std::string& password);

    void signOut();

    bool deleteUser();
    bool updatePassword(const std::string& newPassword);

private:
    void initializeExternalAuthProviders();
    void initializeInternalAuthProvider();
    void addAppAuthStateListener();

    firebase::auth::Auth* mAuth;
    std::unique_ptr<AppAuthStateListener> mAuthStateListener;
    std::map<UtilAuthProviderType, std::unique_ptr<AbstractExternalAuthProvider>> mExAuthProviders;
    std::unique_ptr<AbstractInternalAuthProvider> mIntAuthProvider;
};

#endif //APP_APPAUTHENTICATION_H