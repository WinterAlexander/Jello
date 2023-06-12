//
// Created by Alexander Winter on 2020-06-20.
//

#ifndef JELLO_SHADERPROGRAM_H
#define JELLO_SHADERPROGRAM_H

#include <string>
#include <glad/gl.h>
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
        : vertexShader(std::move(vertexShader)), 
          fragmentShader(std::move(fragmentShader)), 
          shaderProgramId(-1) {}

    ~ShaderProgram();

    /**
     * Prepends both vertex and fragment shader by the specified string
     *
     * @param prefix string to prepend shader code with
     */
    void prepend(const std::string& prefix);

    /**
     * Compiles the shader by sending it to the GPU
     * 
     * @throws ShaderCompilationError if any shaders fails to compile
     */
    void compile();

    /**
     * Checks if the shader is currently compiled. A shader must be compiled to
     * be bound
     * 
     * @return true if compiled, otherwise false
     */
    [[nodiscard]]
    bool isCompiled() const;

    /**
     * Binds the shader to the GPU as the currently active shader
     */
    void bind() const;

    /**
     * Retrieves the address of the uniform specified by name
     * 
     * @param uniformName name of the uniform
     * @return uniform location for the specified uniform 
     */
    [[nodiscard]]
    GLint getUniformLocation(const std::string& uniformName);
    
    /**
     * Sets the value of an integer uniform
     * 
     * @param uniformName name of the uniform
     * @param value integer value to set
     */
    void setUniformInt(const std::string& uniformName, int value);
    
    /**
     * Sets the value of a float uniform
     * 
     * @param uniformName name of the uniform
     * @param value float value to set
     */
    void setUniformFloat(const std::string& uniformName, float value);
    
    /**
     * Sets the value of an 3-valued vector uniform
     * 
     * @param uniformName name of the uniform
     * @param value vector value to set
     */
    void setUniformVec3(const std::string& uniformName, glm::vec3 vector);

    /**
     * Sets the value of an 3-valued vector array uniform using std::vector
     * 
     * @param uniformName name of the uniform
     * @param value vector array value to set
     */
    void setUniformVec3Array(const std::string& uniformName, std::vector<glm::vec3> array);

    /**
     * Sets the value of an 3-valued vector array uniform from a C++ array
     * 
     * @param uniformName name of the uniform
     * @param value vector array value to set
     */
    void setUniformVec3Array(const std::string& uniformName, glm::vec3* array, size_t count);

    /**
     * Sets the value of an 4x4 matrix uniform
     * 
     * @param uniformName name of the uniform
     * @param value matrix value to set
     */
    void setUniformMat4(const std::string& uniformName, glm::mat4 mat);

private:
    void dispose();

    static void throwError(GLuint id, const char* error_prefix, bool isProgram);
};


#endif //JELLO_SHADERPROGRAM_H
