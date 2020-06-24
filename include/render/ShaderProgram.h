//
// Created by Alexander Winter on 2020-06-20.
//

#ifndef JELLO_SHADERPROGRAM_H
#define JELLO_SHADERPROGRAM_H

#include <string>
#include <glad/glad.h>

namespace jello {
    class ShaderProgram;
}

class jello::ShaderProgram {
    std::string vertexShader;
    std::string fragmentShader;

    GLuint shaderProgramId;
public:
    ShaderProgram()
        : vertexShader(), fragmentShader(), shaderProgramId(-1) {}

    ShaderProgram(std::string vertexShader, std::string fragmentShader)
        : vertexShader(std::move(vertexShader)), fragmentShader(std::move(fragmentShader)), shaderProgramId(-1) {}

    ~ShaderProgram();

    /**
     * Prepends both vertex and fragment shader by the specified string
     *
     * @param prefix string to prepend shader code with
     */
    void prepend(const std::string& prefix);

    /**
     * @throws ShaderCompilationError if any shaders fails to compile
     */
    void compile();

    [[nodiscard]]
    bool isCompiled() const;

    void bind();

    [[nodiscard]]
    GLint getUniformLocation(const std::string& str);

private:
    void dispose();

    static void throwError(GLuint id, const char* error_prefix, bool isProgram);
};


#endif //JELLO_SHADERPROGRAM_H
