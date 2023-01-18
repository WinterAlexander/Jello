//
// Created by Alexander Winter on 2023-01-18.
//

#ifndef JELLO_NULLSTREAM_H
#define JELLO_NULLSTREAM_H

#include <ostream>

class NullStream : public std::ostream {
	class NullBuffer : public std::streambuf {
	public:
		int overflow(int c) override {
			return c;
		}
	} nullBuffer;
public:
	NullStream() : std::ostream(&nullBuffer) {}
};


#endif //JELLO_NULLSTREAM_H
