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
    bool createApp(const char* configPath);

private:
    std::shared_ptr<firebase::App> mApp;
    std::unique_ptr<firebase::AppOptions> mAppOptions;
};
using FirebaseAppPtr = std::shared_ptr<FirebaseApp>;
#endif //APP_FIREBASEAPP_H