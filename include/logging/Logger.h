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

    virtual std::ostream& debug() const = 0;
    virtual std::ostream& info() const = 0;
    virtual std::ostream& warning() const = 0;
    virtual std::ostream& error() const = 0;

	/**
	 * @return log level of this logger
	 */
    [[nodiscard]]
    jello::LogLevel getLogLevel() const;

	/**
	 * Set the log level of this logger
	 *
	 * @param level level to set
	 */
    void setLogLevel(jello::LogLevel level);
};


#endif //JELLO_LOGGER_H
