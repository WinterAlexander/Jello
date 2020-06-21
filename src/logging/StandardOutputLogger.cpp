//
// Created by Alexander Winter on 2020-06-20.
//

#include "logging/StandardOutputLogger.h"
#include <iostream>
#include <ctime>

void jello::StandardOutputLogger::debug(std::string message) const {
    if(getLogLevel() <= DEBUG)
        std::cout << getTimeString() << "[DEBUG] " << message << std::endl;
}

void jello::StandardOutputLogger::info(std::string message) const {
    if(getLogLevel() <= INFO)
        std::cout << getTimeString() << "[INFO] " << message << std::endl;
}

void jello::StandardOutputLogger::warning(std::string message) const {
    if(getLogLevel() <= WARNING)
        std::cout << getTimeString() << "[WARNING] " << message << std::endl;
}

void jello::StandardOutputLogger::error(std::string message) const {
    if(getLogLevel() <= ERROR)
        std::cout << getTimeString() << "[ERROR] " << message << std::endl;
}

std::string jello::StandardOutputLogger::getTimeString() const {
    std::time_t t = std::time(nullptr); // gets time now
    char c_str[512];

    std::strftime(c_str, 512, "[%H:%M:%S]", std::localtime(&t));
    return std::string(c_str);
}
