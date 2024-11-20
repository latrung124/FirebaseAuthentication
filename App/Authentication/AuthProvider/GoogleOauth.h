/*
* GoogleOauth.h
* Author: Trung La
* Date: 2024-11-19
* Description: This class is responsible for init a Google Oauth2.0 authentication.
*/

#include "Authentication/Utils/AuthUtils.h"

#include <string>
#include <nlohmann/json.hpp>

class GoogleOauth {
public:
    explicit GoogleOauth(const std::string &configPath);
    ~GoogleOauth() = default;

    std::string getAccessToken();
    std::string exchangeAccessToken(const std::string& accessToken);

private:
    bool readConfig(const std::string &configPath);
    std::string generateAuthorizationUrl();

    authentication::OAuth::UriSchemeConfig mOAuthConfig;
};