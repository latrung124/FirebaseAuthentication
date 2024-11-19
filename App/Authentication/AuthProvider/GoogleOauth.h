/*
* GoogleOauth.h
* Author: Trung La
* Date: 2024-11-19
* Description: This class is responsible for init a Google Oauth2.0 authentication.
*/

#include "Authentication/Utils/AuthUtils.h"

#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

class GoogleOauth {
public:
    explicit GoogleOauth(const std::string &configPath);
    ~GoogleOauth() = default;

    std::string getAccessToken();
    std::string getUserInfo(const std::string& accessToken);

private:
    bool readConfig(const std::string& configPath);
    std::string generateAuthorizationUrl();

    authentication::OAuthConfig mOAuthConfig;
    std::string mCurrentPort = "0";
};