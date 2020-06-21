//
// Created by Alexander Winter on 2020-06-20.
//

#ifndef JELLO_SHADERCOMPILATIONERROR_H
#define JELLO_SHADERCOMPILATIONERROR_H

#include <exception>
#include <string>

namespace jello {
    class ShaderCompilationError;
};

class jello::ShaderCompilationError : public std::exception {
    const std::string error;
public:
    ShaderCompilationError(std::string error) : error(std::move(error)) {}

    [[nodiscard]]
    const char* what() const noexcept override;
};


#endif //JELLO_SHADERCOMPILATIONERROR_H
