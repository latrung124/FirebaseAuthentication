/*
* GoogleOauth.h
* Author: Trung La
* Date: 2024-11-19
* Description: This class is responsible for init a Google Oauth2.0 authentication.
*/
#ifndef GOOGLEOAUTH_H
#define GOOGLEOAUTH_H

#include "Authentication/Utils/AuthUtils.h"

#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>

namespace httplib {
    class Server;
}
class GoogleOauth {
public:
    explicit GoogleOauth(const std::string &configPath);
    ~GoogleOauth();

    std::string getAccessToken();
    std::string exchangeAccessToken(const std::string& accessToken);

private:
    bool readConfig(const std::string &configPath);
    std::string generateAuthorizationUrl();

    authentication::OAuth::UriSchemeConfig mOAuthConfig;
    std::string mToken;
    std::thread mServerThread;
    std::unique_ptr<httplib::Server> mServer;
    std::mutex mMutex;
    std::string mAuthToken;
    std::condition_variable mCondVar;
    bool mCodeReceived = false;
};

#endif //GOOGLEOAUTH_H
