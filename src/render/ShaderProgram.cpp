//
// Created by Alexander Winter on 2020-06-20.
//

#include "render/ShaderProgram.h"
#include <glad/glad.h>
#include <render/ShaderCompilationError.h>
#include <cstring>

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
    int prefix_len = strlen(error_prefix);
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

GLint jello::ShaderProgram::getUniformLocation(const std::string& str) const {
    return glGetUniformLocation(shaderProgramId, str.c_str());
}
