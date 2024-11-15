/*
* FirebaseCloudImpl.cpp
* Author: Trung La
* Date: 2024-11-14
* Description: This class is responsible for implementing the methods to interact with Firebase Cloud.
*/

#include "FirebaseCloudImpl.h"
#include "Authentication/AppAuthentication.h"

FirebaseCloudImpl::FirebaseCloudImpl() {
    mFirebaseApp = new FirebaseApp();
}

FirebaseCloudImpl::~FirebaseCloudImpl() {
    delete mFirebaseApp;
}

bool FirebaseCloudImpl::connect() {
    bool mIsConnected = mFirebaseApp->initialize();
    if (mIsConnected) {
        mAppAuthentication = new AppAuthentication(mFirebaseApp->getApp());
    }

    return mIsConnected;
}

void FirebaseCloudImpl::disconnect() {
    mFirebaseApp->exit();
}

bool FirebaseCloudImpl::login(UtilAuthProviderType authType,
                              const std::string &email,
                              const std::string &password) {
    if (!mIsConnected) {
        return false;
    }
    return mAppAuthentication->login(authType, email, password);
}

bool FirebaseCloudImpl::signOut() {
    if (!mIsConnected) {
        return false;
    }
    mAppAuthentication->signOut();
    return true;
}

bool FirebaseCloudImpl::createAccount(const std::string &email, const std::string &password) {
    if (!mIsConnected) {
        return false;
    }
    return mAppAuthentication->createAccount(email, password);
}

bool FirebaseCloudImpl::deleteAccount() {
    if (!mIsConnected) {
        return false;
    }
    return mAppAuthentication->deleteUser();
}

bool FirebaseCloudImpl::updatePassword(const std::string &newPassword) {
    if(!mIsConnected) {
        return false;
    }
    return mAppAuthentication->updatePassword(newPassword);
}

