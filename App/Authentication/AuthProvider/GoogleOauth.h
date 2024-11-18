/*
* GoogleOauth.h
* Author: Trung La
* Date: 2024-11-19
* Description: This class is responsible for init a Google Oauth2.0 authentication.
*/

#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

class GoogleOauth {
public:
    GoogleOauth() = default;
    ~GoogleOauth() = default;

    std::string getAccessToken(const std::string& code);
    std::string getUserInfo(const std::string& accessToken);

private:
    std::string clientId = "YOUR_CLIENT_ID";
    std::string projectId = "project-id";
    std::string platform = "android/desktop";
    std::string auth_uri = "https://accounts.google.com/o/oauth2/auth";
    std::string token_uri = "https://oauth2.googleapis.com/token";
    std::string redirect_uri = "http://localhost:8080";
    std::string auth_provider_x509_cert_url = "https://www.googleapis.com/oauth2/v1/certs";
    std::string client_secret = "YOUR_CLIENT";
};