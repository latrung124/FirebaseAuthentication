/*
* FirebaseApp.h
* Author: Trung La
* Date: 2024-11-13
* This class is responsible for initializing Firebase.
*/

#ifndef APP_FIREBASEAPP_H
#define APP_FIREBASEAPP_H

#include <firebase/app.h>

#include <memory>
class FirebaseApp {
public:
    FirebaseApp();
    ~FirebaseApp();

    bool initialize();
    void exit();

    firebase::App* getApp() const;

private:
    firebase::App* mApp = nullptr;
    firebase::AppOptions* mAppOptions = nullptr;
};

#endif //APP_FIREBASEAPP_H