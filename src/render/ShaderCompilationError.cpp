//
// Created by Alexander Winter on 2020-06-20.
//

#include "render/ShaderCompilationError.h"

const char *jello::ShaderCompilationError::what() const noexcept {
    return error.c_str();
}
