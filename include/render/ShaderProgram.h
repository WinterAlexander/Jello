//
// Created by Alexander Winter on 2020-06-20.
//

#ifndef JELLO_SHADERPROGRAM_H
#define JELLO_SHADERPROGRAM_H

#include <string>
#include <glad/glad.h>
#include <vector>
#include "glm/vec3.hpp"
#include "glm/fwd.hpp"

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

    void bind() const;

    [[nodiscard]]
    GLint getUniformLocation(const std::string& uniformName);
    
    void setUniformInt(const std::string& uniformName, int value);
    
    void setUniformFloat(const std::string& uniformName, float value);
    
    void setUniformVec3(const std::string& uniformName, glm::vec3 vector);
    
    void setUniformVec3Array(const std::string& uniformName, std::vector<glm::vec3> array);
    
    void setUniformVec3Array(const std::string& uniformName, glm::vec3* array, size_t count);
    
    void setUniformMat4(const std::string& uniformName, glm::mat4 mat);

private:
    void dispose();

    static void throwError(GLuint id, const char* error_prefix, bool isProgram);
};


#endif //JELLO_SHADERPROGRAM_H
