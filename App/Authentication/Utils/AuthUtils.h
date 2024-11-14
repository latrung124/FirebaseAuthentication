/*
* AuthUtils.h
* Author: Trung La
* Date: 2024-11-14
* Description: This class is responsible for authenticating the user with Firebase.
*/

#ifndef AUTHUTILS_H
#define AUTHUTILS_H

#include <cstdint>

namespace authentication {

namespace utils {

    enum class AuthProviderType : uint16_t {
        EmailPassword,
        Google,
        Facebook,
        Twitter,
        GitHub,
        Anonymous,
        Phone,
        Custom,
        PlayGames,
        Apple,
        GameCenter,
        Steam,
        Microsoft,
        Yahoo,
        Huawei,
        WeChat,
        Last,
    };
} // namespace authentication::utils

} // namespace authentication

using UtilAuthProviderType = authentication::utils::AuthProviderType;
#endif //AUTHUTILS_H

