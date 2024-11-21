/*
* GoogleOauth.cpp
* Author: Trung La
* Date: 2024-11-19
* Description: This class is responsible for init a Google Oauth2.0 authentication.
*/

#include "Authentication/AuthProvider/GoogleOauth.h"

#include <nlohmann/json.hpp>
#include <Logging.h>
#include <fstream>
#include <httplib.h>

GoogleOauth::GoogleOauth(const std::string &configPath)
    : mOAuthConfig({})
    , mToken("")
    , mServer(std::make_unique<httplib::Server>())
    , mAuthCode("")
{
    if (!readConfig(configPath)) {
        LOG_WARNING("Error reading config file!");
    }
}

GoogleOauth::~GoogleOauth() {
    if (mServer) {
        mServer->stop();
    }
}

std::string GoogleOauth::getAccessToken() {
    std::string url = generateAuthorizationUrl();
    std::system(("start \"\" \"" + url + "\"").c_str());

    mAuthCode = "";

    // httplib::Server server;
    mServer->Get("/", [&](const httplib::Request& req, httplib::Response& res) {
        {
            std::lock_guard<std::mutex> lock(mMutex);
            if (req.has_param("code")) {
                mAuthCode = req.get_param_value("code");
                res.set_content("Authorization code received! You can close this window now!", "text/html");
                mCodeReceived = true;
            } else {
                res.set_content("Authorization code not received! You can close this window now!", "text/html");
            }
        }
        mCondVar.notify_one();
    });

    mServerThread = std::thread([this] {
        mServer->listen("localhost", 8080);
    });

    {
        std::unique_lock<std::mutex> lock(mMutex);
        mCondVar.wait(lock, [this] { return mCodeReceived; });
    }

    mServerThread.join();

    return mAuthCode;
}

std::string GoogleOauth::exchangeAccessToken(const std::string& accessToken) {
    httplib::Client client(mOAuthConfig.tokenUri.c_str());
    httplib::Params params = {
        {"code", accessToken.c_str()},
        {"client_id", mOAuthConfig.clientId.c_str()},
        {"client_secret", mOAuthConfig.clientSecret.c_str()},
        {"redirect_uri", std::string(mOAuthConfig.redirectUri + ":8080").c_str()},
        {"grant_type", "refresh_token"},
    };

    auto response = client.Post("/token", params);
    if (response && response->status == 200) {
        return response->body;
    }

    return "";
}

bool GoogleOauth::readConfig(const std::string &configPath) {
    // Implementation
        using json = nlohmann::json;
    try {
        std::ifstream file(configPath);
        if (!file.is_open()) {
            return false;
        }
        json config = json::parse(file);
        //currently only support installed desktop app
        const auto& googleConfig = config["installed"];
        mOAuthConfig = {
            .clientId = googleConfig["client_id"].get<std::string>(),
            .projectId = googleConfig["project_id"].get<std::string>(),
            .clientSecret = googleConfig["client_secret"].get<std::string>(),
            .redirectUri = googleConfig["redirect_uris"][0].get<std::string>(),
            .authUri = googleConfig["auth_uri"].get<std::string>(),
            .tokenUri = googleConfig["token_uri"].get<std::string>(),
            .platform = "desktop",
        };
        std::cout << "Config read successfully!" << std::endl;
        std::cout << "Client ID: " << mOAuthConfig.clientId << std::endl;
        std::cout << "Project ID: " << mOAuthConfig.projectId << std::endl;
        std::cout << "Client Secret: " << mOAuthConfig.clientSecret << std::endl;
        std::cout << "Redirect URI: " << mOAuthConfig.redirectUri << std::endl;
        std::cout << "Auth URI: " << mOAuthConfig.authUri << std::endl;
        std::cout << "Token URI: " << mOAuthConfig.tokenUri << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error reading config: " << e.what() << std::endl;
        return false;
    }
    return true;
}

std::string GoogleOauth::generateAuthorizationUrl() {
    std::string url = mOAuthConfig.authUri + "?";
    url += "scope=email%20profile&";
    url += "response_type=code&";
    url += "state=security_token%3D138r5719ru3e1%26url%3Dhttps%3A%2F%2Foauth2.example.com%2Ftoken&";
    url += "redirect_uri=" + mOAuthConfig.redirectUri + ":8080";
    url += "&client_id=" + mOAuthConfig.clientId;
    std::cout << "Generated URL: " << url << std::endl;
    return url;
}