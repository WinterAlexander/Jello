//
// Created by Alexander Winter on 2020-06-20.
//

#include "logging/Logger.h"

jello::LogLevel jello::Logger::getLogLevel() const {
    return level;
}

void jello::Logger::setLogLevel(jello::LogLevel level) {
    this->level = level;
}
