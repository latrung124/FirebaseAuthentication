/*
* FirebaseApp.cpp
* Author: Trung La
* Date: 2024-11-13
* This class is responsible for initializing the Firebase App.
*/

#include "FirebaseApp.h"
#include <Logging.h>

#include <iostream>
#include <fstream>

FirebaseApp::FirebaseApp() {
    // Initialize Firebase
}

FirebaseApp::~FirebaseApp() {
    // Clean up Firebase
    exit();
}

bool FirebaseApp::initialize() {
    std::string configPath = std::string(FIREBASE_CONFIG_PATH) +"/google-services.json";
    //read json file
    std::cout << "Loading Firebase config file: " << configPath << std::endl;
    std::ifstream file(configPath);
    if (!file.is_open()) {
        LOG_WARNING("Failed to open Firebase config file!");
        return false;
    }
    std::string configJson = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    mAppOptions = firebase::AppOptions::LoadFromJsonConfig(configJson.c_str());
    if (mAppOptions == nullptr) {
        LOG_WARNING("Failed to load Firebase config!");
        return false;
    }

    // mApp = std::shared_ptr<firebase::App>(firebase::App::Create(appOption)); // Create a new Firebase App
    mApp = firebase::App::Create(*mAppOptions); // Create a new Firebase App

    return mApp != nullptr;
}

void FirebaseApp::exit() {
    if (mApp) {
        delete mApp;
        mApp = nullptr;
    }

    if (mAppOptions) {
        delete mAppOptions;
        mAppOptions = nullptr;
    }
}

firebase::App* FirebaseApp::getApp() const {
    return mApp;
}