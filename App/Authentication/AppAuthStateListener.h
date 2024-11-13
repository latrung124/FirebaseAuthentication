/*
* AppAuthStateListener.h
* Author: Trung La
* Date: 2024-11-13
* This class is responsible for listening to the authentication state of the user.
*/

#ifndef APP_APPAUTHSTATELISTENER_H
#define APP_APPAUTHSTATELISTENER_H

#include <firebase/auth.h>

class AppAuthStateListener : public firebase::auth::AuthStateListener {
public:
    AppAuthStateListener();
    ~AppAuthStateListener();

    void OnAuthStateChanged(firebase::auth::Auth* auth) override;
};

#endif //APP_APPAUTHSTATELISTENER_H