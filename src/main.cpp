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
#include "render/Camera.h"
#include <memory>
#include <sstream>
#include <cmath>
#include <stb_image.h>
#include <render/Texture.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float deltaTime);

std::shared_ptr<jello::ShaderProgram> loadShader(const std::string& vsFile,
												 const std::string& fsFile,
												 const jello::Logger& logger);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

jello::Camera camera;
float lastX = NAN, lastY = NAN;
float pitch = 0.0f, yaw = -90.0f;

int main() {

    jello::StandardOutputLogger logger;

    logger.info() << "Initialized logger to standard ouput.";

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);

    if(!window)
    {
        logger.error() << "Failed to create GLFW window";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGL()) {
        logger.error() << "glad failed to load";
        exit(-1);
    }

    logger.info() << std::string("glad loaded OpenGL ") + std::to_string(GLVersion.major) + "." + std::to_string(GLVersion.minor);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    logger.info() << (std::string("Maximum number of vertex attributes supported: ") + std::to_string(nrAttributes));

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, 800, 600);

    std::shared_ptr<jello::ShaderProgram> shaderProgram;

    try {
        shaderProgram = loadShader("res/shader/default.vs.glsl", "res/shader/default.fs.glsl", logger);
    } catch (const jello::ShaderCompilationError& error) {
        logger.error() << (error.what());
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("res/gfx/brickwall.jpg", &width, &height, &nrChannels, 0);

    if(!data)
    {
        logger.error() << "Failed to load texture";
        return -1;
    }

    jello::Texture texture(width, height, data);

    stbi_image_free(data);

    GLuint vbo, ebo;
    jello::VertexArrayObject vao;

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    //float vertices[] = {
    //        // pos                  color               tex coords
    //        0.5f, 0.5f, 0.0f,       1.0f, 1.0f, 0.0f,   1.0f, 1.0f, // top right
    //        0.5f, -0.5f, 0.0f,      1.0f, 0.0f, 1.0f,   1.0f, 0.0f, // bottom right
    //        -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
    //        -0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 1.0f,   0.0f, 1.0f, // top left
    //};
//
    //unsigned int indices[] = {  // note that we start from 0!
    //        0, 1, 3,   // first triangle
    //        1, 2, 3    // second triangle
    //};

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    vao.bind();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    vao.unbind();

    glEnable(GL_DEPTH_TEST);

    shaderProgram->bind();
    glUniform1i(shaderProgram->getUniformLocation("tex"), 0);

	glm::mat4 view;
	camera.getPosition() = { 0.0, 0.0, 3.0 };
	camera.getDirection() = { 0.0, 0.0, -1.0 };

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	while(!glfwWindowShouldClose(window))
    {
		float currentFrame = static_cast<float>(glfwGetTime());
	    deltaTime = currentFrame - lastFrame;
	    lastFrame = currentFrame;

	    processInput(window, deltaTime);
	    view = camera.getView();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram->bind();

        glActiveTexture(GL_TEXTURE0);
        texture.bind();
        vao.bind();

        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            glm::mat4 proj = glm::perspective(glm::radians(camera.getFieldOfView()), 800.0f / 600.0f, 0.1f, 100.0f);
            glm::mat4x4 trans = proj * view * model;

            glUniformMatrix4fv(shaderProgram->getUniformLocation("transform"), 1, GL_FALSE, glm::value_ptr(trans));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        vao.unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vbo);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window, float deltaTime) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
	 const float cameraSpeed = 5.0f * deltaTime; // adjust accordingly
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.getPosition() += cameraSpeed * camera.getDirection();
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.getPosition() -= cameraSpeed * camera.getDirection();
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.getPosition() -= cameraSpeed * glm::normalize(glm::cross(camera.getDirection(), camera.getUp()));
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.getPosition() += cameraSpeed * glm::normalize(glm::cross(camera.getDirection(), camera.getUp()));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if(std::isnan(lastX)) {
		lastX = xpos;
		lastY = ypos;
		camera.setDirectionFromAngles(yaw, pitch);
		return;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if(pitch > 89.0f)
		pitch = 89.0f;

	if(pitch < -89.0f)
		pitch = -89.0f;

	camera.setDirectionFromAngles(yaw, pitch);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	float fov = camera.getFieldOfView() - (float)yoffset;

	if(fov < 1.0f)
		fov = 1.0f;

	if(fov > 90.0f)
		fov = 90.0f;
	camera.setFieldOfView(fov);
}

std::shared_ptr<jello::ShaderProgram> loadShader(const std::string& vsFile,
												 const std::string& fsFile,
												 const jello::Logger& logger) {
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
