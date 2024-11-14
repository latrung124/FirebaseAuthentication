/*
* FireBaseManager.h
* Author: Trung La
* Date: 2024-11-14
* Description: This class is responsible for managing the firebase cloud database.
*/

#ifndef FIREBASEMANAGER_H
#define FIREBASEMANAGER_H

#include <memory>

class FirebaseApp;

class FireBaseManager {
public:
    FireBaseManager() = default;
    ~FireBaseManager() = default;

    using FirebaseAppPtr = std::shared_ptr<FirebaseApp>;

    void initFirebaseApplication();
    void destroyFirebaseApplication();

private:
    FirebaseAppPtr mFirebaseApp;
};

#endif //FIREBASEMANAGER_H