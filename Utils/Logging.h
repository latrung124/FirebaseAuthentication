/*
* Logging.h
* Author: Trung La
* Date: 2024-11-14
* Description: This class is responsible for logging messages.
*/

#ifndef UTILS_LOGGING_H
#define UTILS_LOGGING_H

#include <iostream>
#include <string>

#ifdef LOGGING_ENABLED
#define LOG_INFO(message) \
    std::cout << "[INFO]: " << __FILE__ << ":" << __LINE__ << " - " << message << std::endl;
#endif

#define LOG_WARNING(message) \
    std::cout << "[WARNING]: " << __FILE__ << ":" << __LINE__ << " - " << message << std::endl;

#endif //UTILS_LOGGING_H