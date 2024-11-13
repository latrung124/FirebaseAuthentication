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

    std::weak_ptr<firebase::App> getApp() const;

private:
    std::shared_ptr<firebase::App> mApp;
};
#endif //APP_FIREBASEAPP_H