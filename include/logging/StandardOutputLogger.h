//
// Created by Alexander Winter on 2020-06-20.
//

#ifndef JELLO_STANDARDOUTPUTLOGGER_H
#define JELLO_STANDARDOUTPUTLOGGER_H

#include "Logger.h"
#include "NullStream.h"

namespace jello {
    class StandardOutputLogger;
}

class jello::StandardOutputLogger : public jello::Logger {
	mutable NullStream nullStream;

public:
	std::ostream& debug() const override;

	std::ostream& info() const override;

	std::ostream& warning() const override;

	std::ostream& error() const override;

private:
    std::string getTimeString() const;
};


#endif //JELLO_STANDARDOUTPUTLOGGER_H
