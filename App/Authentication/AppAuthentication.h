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

#include <firebase/auth.h>

#include <string>
#include <memory>

class AppAuthentication {
public:
    AppAuthentication(const std::weak_ptr<firebase::App>& app);
    ~AppAuthentication();

    bool createUserWithEmailAndPassword(const std::string& email, const std::string& password);
    bool loginUserWithEmailAndPassword(const std::string& email, const std::string& password);

    void signOut();

    bool deleteUser();
    bool updatePassword(const std::string& newPassword);

private:
    void addAppAuthStateListener();

    std::unique_ptr<firebase::auth::Auth> mAuth;
    std::unique_ptr<AppAuthStateListener> mAuthStateListener;
};

#endif //APP_APPAUTHENTICATION_H