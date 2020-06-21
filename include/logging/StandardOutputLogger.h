//
// Created by Alexander Winter on 2020-06-20.
//

#ifndef JELLO_STANDARDOUTPUTLOGGER_H
#define JELLO_STANDARDOUTPUTLOGGER_H

#include "Logger.h"

namespace jello {
    class StandardOutputLogger;
}

class jello::StandardOutputLogger : public jello::Logger {
public:
    void debug(std::string message) const override;

    void info(std::string message) const override;

    void warning(std::string message) const override;

    void error(std::string message) const override;

private:
    std::string getTimeString() const;
};


#endif //JELLO_STANDARDOUTPUTLOGGER_H
