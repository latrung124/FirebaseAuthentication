/*
* FirebaseManager.cpp
* Author: Trung La
* Date: 2024-11-14
* Description: This class is responsible for managing the firebase cloud database.
*/

#include "FireBaseManager.h"
#include "FirebaseApp.h"

void FireBaseManager::initFirebaseApplication() {
    mFirebaseApp = std::make_shared<FirebaseApp>();
    //load json config file
    mFirebaseApp->createApp("path/to/config.json");
}

void FireBaseManager::destroyFirebaseApplication() {
}