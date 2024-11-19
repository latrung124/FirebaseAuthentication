/*
* GoogleOauth.cpp
* Author: Trung La
* Date: 2024-11-19
* Description: This class is responsible for init a Google Oauth2.0 authentication.
*/

#include "Authentication/AuthProvider/GoogleOauth.h"

#include <fstream>
#include <thread>
#include <iostream>
#include <curl/curl.h>
#include <httplib.h>
#include <cstdlib>

GoogleOauth::GoogleOauth(const std::string &configPath) {
    if (!readConfig(configPath)) {
        std::cout << "Error reading config!" << std::endl;
    }
}

bool GoogleOauth::readConfig(const std::string& configPath) {
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
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error reading config: " << e.what() << std::endl;
        return false;
    }
}

std::string GoogleOauth::generateAuthorizationUrl() {
    std::string url = mOAuthConfig.authUri + "?";
    url += "&scope=email%20profile";
    url += "&response_type=code";
    url += "state=security_token%3D138r5719ru3e1%26url%3Dhttps%3A%2F%2Foauth2.example.com%2Ftoken&";
    url += "&redirect_uri=" + mOAuthConfig.redirectUri;
    //get available port with libcurl
    CURL *curl = curl_easy_init();
    if (curl) {
        char *port = nullptr;
        CURLcode res = curl_easy_getinfo(curl, CURLINFO_LOCAL_PORT, &port);
        if (res == CURLE_OK) {
            mCurrentPort = std::string(port);
            url += "&port=" + mCurrentPort;
        }
        curl_easy_cleanup(curl);
    }
    url += "&client_id=" + mOAuthConfig.clientId;
    return url;
}

std::string GoogleOauth::getAccessToken() {
    std::system(("start " + generateAuthorizationUrl()).c_str());

    httplib::Server server;
    std::string authorizationCode;

    server.Get("/", [&](const httplib::Request& req, httplib::Response& res) {
        if (req.has_param("code")) {
            authorizationCode = req.get_param_value("code");
            res.set_content("Authorization code received!", "text/plain");
            server.stop();
        } else {
            res.set_content("No authorization code received!", "text/plain");
        }
    });

    std::thread serverThread([&](){
        server.listen("localhost", std::stoi(mCurrentPort));
    });
    serverThread.join();
    if (authorizationCode.empty()) {
        return "";
    }

    httplib::Client client(mOAuthConfig.tokenUri.c_str());
    httplib::Params params = {
        {"code", authorizationCode.c_str()},
        {"client_id", mOAuthConfig.clientId.c_str()},
        {"client_secret", mOAuthConfig.clientSecret.c_str()},
        {"redirect_uri", mOAuthConfig.redirectUri.c_str()},
        {"grant_type", "authorization_code"}
    };

    auto res = client.Post("/token", params);
    if (res && res->status == 200) {
        auto json = nlohmann::json::parse(res->body);
        return json["access_token"].get<std::string>();
    }

    return "";
}

std::string GoogleOauth::getUserInfo(const std::string& accessToken) {
    // Implementation
    return "";
}