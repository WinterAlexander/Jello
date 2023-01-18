//
// Created by Alexander Winter on 2020-06-20.
//

#include "logging/StandardOutputLogger.h"
#include <iostream>
#include <ctime>

std::ostream& jello::StandardOutputLogger::debug() const {
	if(getLogLevel() <= DEBUG)
		return std::cout << "\n[DEBUG] ";
	return nullStream;
}

std::ostream& jello::StandardOutputLogger::info() const {
	if(getLogLevel() <= INFO)
		return std::cout << "\n[INFO] ";
	return nullStream;
}

std::ostream& jello::StandardOutputLogger::warning() const {
	if(getLogLevel() <= WARNING)
		return std::cout << "\n[WARNING] ";
	return nullStream;
}

std::ostream& jello::StandardOutputLogger::error() const {
	if(getLogLevel() <= ERROR)
		return std::cout << "\n[ERROR] ";
	return nullStream;
}

std::string jello::StandardOutputLogger::getTimeString() const {
	std::time_t t = std::time(nullptr); // gets time now
	char c_str[512];

	std::strftime(c_str, 512, "[%H:%M:%S]", std::localtime(&t));
	return std::string(c_str);
}
