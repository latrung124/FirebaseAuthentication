/*
* FirebaseApp.cpp
* Author: Trung La
* Date: 2024-11-13
* This class is responsible for initializing the Firebase App.
*/

#include "FirebaseApp.h"

#include <iostream>

namespace {
    using FireBaseAppPtr = std::shared_ptr<firebase::App>;
}

FirebaseApp::FirebaseApp() {
    // Initialize Firebase
}

FirebaseApp::~FirebaseApp() {
    // Clean up Firebase
    mApp.reset();
}

std::weak_ptr<firebase::App> FirebaseApp::getApp() const {
    return mApp;
}

bool FirebaseApp::createApp(const char* configPath) {
    // Initialize Firebase
    mAppOptions = std::make_unique<firebase::AppOptions>(firebase::AppOptions::LoadFromJsonConfig(configPath));
    mApp = std::make_shared<firebase::App>(*mAppOptions);
    return mApp != nullptr;
}