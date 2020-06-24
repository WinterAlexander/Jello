//
// Created by Alexander Winter on 2020-06-20.
//

#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <render/ShaderCompilationError.h>
#include <logging/StandardOutputLogger.h>
#include <render/VertexArrayObject.h>
#include "render/ShaderProgram.h"
#include <memory>
#include <sstream>
#include <math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
std::shared_ptr<jello::ShaderProgram> loadShader(const std::string& vsFile, const std::string& fsFile, const jello::Logger &logger);

int main() {

    jello::StandardOutputLogger logger;

    logger.info("Initialized logger to standard ouput.");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);

    if(!window)
    {
        logger.error("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGL()) {
        logger.error("glad failed to load");
        exit(-1);
    }

    logger.info(std::string("glad loaded OpenGL ") + std::to_string(GLVersion.major) + "." + std::to_string(GLVersion.minor));

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    logger.info(std::string("Maximum number of vertex attributes supported: ") + std::to_string(nrAttributes));

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, 800, 600);

    std::shared_ptr<jello::ShaderProgram> shaderProgram;

    try {
        shaderProgram = loadShader("res/default.vs.glsl", "res/default.fs.glsl", logger);
    } catch (const jello::ShaderCompilationError& error) {
        logger.error(error.what());
        return -1;
    }

    GLuint vbo, ebo;
    jello::VertexArrayObject vao;

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    float vertices[] = {
            0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f, // top right
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f, // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 1.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f, // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };

    vao.bind();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    vao.unbind();

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram->bind();
        float timeValue = glfwGetTime();
        glUniform2f(shaderProgram->getUniformLocation("offset"), sin(timeValue) / 5.0f, cos(timeValue) / 5.0f);
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vao.unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vbo);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

std::shared_ptr<jello::ShaderProgram> loadShader(const std::string& vsFile, const std::string& fsFile, const jello::Logger &logger) {
    std::ifstream vsSourceFile(vsFile);
    std::ifstream fsSourceFile(fsFile);

    if(!vsSourceFile.good() || !fsSourceFile.good())
        throw std::runtime_error("Shader file(s) not found");

    std::stringstream buffer;
    buffer << vsSourceFile.rdbuf();

    std::string vertexShaderSource = buffer.str();

    buffer.str(std::string());
    buffer.clear();
    buffer << fsSourceFile.rdbuf();

    std::string fragmentShaderSource = buffer.str();

    vsSourceFile.close();
    fsSourceFile.close();

    jello::ShaderProgram* shaderProgram = new jello::ShaderProgram(vertexShaderSource, fragmentShaderSource);
    shaderProgram->prepend("#version 330 core\n");
    shaderProgram->compile();

    return std::shared_ptr<jello::ShaderProgram>(shaderProgram);
}
