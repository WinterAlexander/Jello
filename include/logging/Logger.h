//
// Created by Alexander Winter on 2020-06-20.
//

#ifndef JELLO_LOGGER_H
#define JELLO_LOGGER_H

#include <string>
#include "LogLevel.h"

namespace jello {
    class Logger;
}

class jello::Logger {
    jello::LogLevel level;

public:
    Logger() : level(DEBUG) {}
    Logger(jello::LogLevel level) : level(level) {}

    virtual void debug(std::string message) const = 0;
    virtual void info(std::string message) const = 0;
    virtual void warning(std::string message) const = 0;
    virtual void error(std::string message) const = 0;

    [[nodiscard]]
    jello::LogLevel getLogLevel() const;
    void setLogLevel(jello::LogLevel level);
};


#endif //JELLO_LOGGER_H
