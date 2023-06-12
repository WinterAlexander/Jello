//
// Created by Alexander Winter on 2020-06-20.
//

#include "render/ShaderProgram.h"
#include "glm/gtc/type_ptr.hpp"
#include <glad/gl.h>
#include <render/ShaderCompilationError.h>
#include <cstring>
#include <vector>

jello::ShaderProgram::~ShaderProgram() {
    dispose();
}

void jello::ShaderProgram::compile() {
    if(isCompiled()) {
        dispose();
    }

    GLuint vsId;
    vsId = glCreateShader(GL_VERTEX_SHADER);

    const char* vs_c_str = vertexShader.c_str();

    glShaderSource(vsId, 1, &vs_c_str, nullptr);
    glCompileShader(vsId);

    int success;
    glGetShaderiv(vsId, GL_COMPILE_STATUS, &success);

    if(!success)
        throwError(vsId, "Vertex shader compilation failed\n", false);

    GLuint fsId;
    fsId = glCreateShader(GL_FRAGMENT_SHADER);

    const char* fs_c_str = fragmentShader.c_str();

    glShaderSource(fsId, 1, &fs_c_str, nullptr);
    glCompileShader(fsId);

    glGetShaderiv(fsId, GL_COMPILE_STATUS, &success);

    if(!success)
        throwError(fsId, "Fragment shader compilation failed\n", false);

    shaderProgramId = glCreateProgram();

    glAttachShader(shaderProgramId, vsId);
    glAttachShader(shaderProgramId, fsId);
    glLinkProgram(shaderProgramId);

    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);

    if(!success)
        throwError(shaderProgramId, "Shader linking failed\n", true);

    glDeleteShader(vsId);
    glDeleteShader(fsId);
}

void jello::ShaderProgram::prepend(const std::string& prefix) {
    vertexShader = prefix + vertexShader;
    fragmentShader = prefix + fragmentShader;
}

bool jello::ShaderProgram::isCompiled() const {
    return shaderProgramId != (GLuint)-1;
}

void jello::ShaderProgram::bind() const {
    glUseProgram(shaderProgramId);
}

void jello::ShaderProgram::throwError(GLuint id, const char* error_prefix, bool isProgram) {

    int infoLogLen;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLen);
    size_t prefix_len = strlen(error_prefix);
    char* infoLog = (char*)malloc(infoLogLen + prefix_len);
    strcpy(infoLog, error_prefix);
    if(isProgram)
        glGetProgramInfoLog(id, infoLogLen, nullptr, infoLog + prefix_len);
    else
        glGetShaderInfoLog(id, infoLogLen, nullptr, infoLog + prefix_len);

    throw ShaderCompilationError(infoLog);
}

void jello::ShaderProgram::dispose() {
    glDeleteProgram(shaderProgramId);
    shaderProgramId = -1;
}

GLint jello::ShaderProgram::getUniformLocation(const std::string& uniformName) {
    return glGetUniformLocation(shaderProgramId, uniformName.c_str());
}

void jello::ShaderProgram::setUniformInt(const std::string& uniformName, int value) {
    glUniform1i(getUniformLocation(uniformName), value);
}

void jello::ShaderProgram::setUniformFloat(const std::string& uniformName, float value) {
    glUniform1f(getUniformLocation(uniformName), value);
}

void jello::ShaderProgram::setUniformVec3(const std::string& uniformName, glm::vec3 vector) {
    glUniform3f(getUniformLocation(uniformName), vector.x, vector.y, vector.z);
}

void jello::ShaderProgram::setUniformVec3Array(const std::string& uniformName, 
                                               std::vector<glm::vec3> array) {
    glUniform3fv(getUniformLocation(uniformName), 
                 static_cast<GLint>(array.size()), 
                 glm::value_ptr(array.front()));
}

void jello::ShaderProgram::setUniformVec3Array(const std::string& uniformName, 
                                               glm::vec3* array,
                                               size_t count) {
    glUniform3fv(getUniformLocation(uniformName),
                 static_cast<GLint>(count),
                 glm::value_ptr(array[0]));
}

void jello::ShaderProgram::setUniformMat4(const std::string& uniformName, glm::mat4 mat) {
    glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(mat));
}