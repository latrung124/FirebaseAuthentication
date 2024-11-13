/*
* FirebaseApp.cpp
* Author: Trung La
* Date: 2024-11-13
* This class is responsible for initializing the Firebase App.
*/

#include "FirebaseApp.h"

#include <iostream>

FirebaseApp::FirebaseApp() {
    // Initialize Firebase
    firebase::AppOptions options;
    options.set_app_id(""); // Set the App ID
    options.set_api_key(""); // Set the API Key
    options.set_project_id(""); // Set the Project ID
    mApp = std::unique_ptr<firebase::App>(firebase::App::Create(options)); // Create a new Firebase App
}

FirebaseApp::~FirebaseApp() {
    // Clean up Firebase
    mApp.reset();
}

std::weak_ptr<firebase::App> FirebaseApp::getApp() const {
    return mApp;
}