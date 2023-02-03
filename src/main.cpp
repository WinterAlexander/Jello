//
// Created by Alexander Winter on 2020-06-20.
//

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <logging/StandardOutputLogger.h>
#include <render/VertexArrayObject.h>
#include "render/ShaderProgram.h"
#include "render/Camera.h"
#include "asset/AssetLoader.h"
#include "asset/ShaderAsset.h"
#include "asset/TextureAsset.h"
#include <cmath>
#include <render/Texture.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/aabb.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float deltaTime);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

jello::Camera camera;
float lastX = NAN, lastY = NAN;
float pitch = 0.0f, yaw = -90.0f;

struct aiAABB aabb;

float vertices[] = {
		-0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,   0.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     1.0f, 0.0f,   0.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     1.0f, 1.0f,   0.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     1.0f, 1.0f,   0.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 1.0f,   0.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,   0.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     1.0f, 0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 1.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 1.0f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 1.0f,   0.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     1.0f, 1.0f,   0.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     1.0f, 0.0f,   0.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     1.0f, 0.0f,   0.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,   0.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 1.0f,   0.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 1.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     1.0f, 1.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     1.0f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,     1.0f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 1.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
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

glm::vec3 lightPositions[] = {
		glm::vec3(0.0f, 5.0f, 0.0f)
};

glm::vec3 lightColors[] = {
		glm::vec3(1.0, 0.9, 0.9)
};

int main() {
	aabb.mMax.x = 2.0f;
    jello::StandardOutputLogger logger;

    logger.info() << "Initialized logger to standard ouput.";

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1200, 900, "LearnOpenGL", nullptr, nullptr);

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

    logger.info() << "glad loaded OpenGL " << GLVersion.major << "." << GLVersion.minor;

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    logger.info() << "Maximum number of vertex attributes supported: " << nrAttributes;

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, 1200, 900);
    
    jello::AssetLoader loader(logger);

    jello::ShaderAsset shaderAsset("res/shader/default.vs.glsl", "res/shader/default.fs.glsl");
    jello::TextureAsset brickWallAsset("res/gfx/brickwall.jpg");
	jello::TextureAsset brickWallNormalAsset("res/gfx/brickwall_n.jpg");
    jello::TextureAsset containerAsset("res/gfx/container2.png");
    jello::TextureAsset containerSpecularAsset("res/gfx/container2_specular.png");
    jello::TextureAsset flatNormalAsset("res/gfx/flat_normal.png");
    
    loader.load(shaderAsset);
    loader.load(brickWallAsset);
	loader.load(brickWallNormalAsset);
    loader.load(containerAsset);
    loader.load(containerSpecularAsset);
    loader.load(flatNormalAsset);
    
    loader.finishLoading(shaderAsset);
    loader.finishLoading(brickWallAsset);
	loader.finishLoading(brickWallNormalAsset);
    loader.finishLoading(containerAsset);
    loader.finishLoading(containerSpecularAsset);
    loader.finishLoading(flatNormalAsset);
    
    jello::ShaderProgram* shaderProgram = loader.get(shaderAsset);
    jello::Texture* texture = loader.get(containerAsset);
    jello::Texture* specular = loader.get(containerSpecularAsset);
	jello::Texture* normal = loader.get(flatNormalAsset);

    GLuint vbo;
    jello::VertexArrayObject vao;

    glGenBuffers(1, &vbo);
    
    vao.bind();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	// color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

	// texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

	// normal attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	// tangent attribute
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
	glEnableVertexAttribArray(4);

    vao.unbind();

    glEnable(GL_DEPTH_TEST);

    shaderProgram->bind();
    
    shaderProgram->setUniformInt("u_material.diffuse", 0);
    shaderProgram->setUniformInt("u_material.normalMap", 1);
    shaderProgram->setUniformInt("u_material.specularMap", 2);
    shaderProgram->setUniformFloat("u_material.shininess", 32.0f);

	glm::mat4 view;
	camera.getPosition() = { 0.0, 0.0, 3.0 };
	camera.getDirection() = { 0.0, 0.0, -1.0 };

	shaderProgram->setUniformVec3("u_viewPosition", camera.getPosition());

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

	    shaderProgram->setUniformInt("u_lightCount", 1);
	    shaderProgram->setUniformVec3Array("u_lightPositions", lightPositions, 1);
	    shaderProgram->setUniformVec3Array("u_lightColors", lightColors, 1);

        glActiveTexture(GL_TEXTURE0);
        texture->bind();
		glActiveTexture(GL_TEXTURE1);
	    normal->bind();
        glActiveTexture(GL_TEXTURE2);
        specular->bind();
        vao.bind();

        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            glm::mat4 proj = glm::perspective(glm::radians(camera.getFieldOfView()), 800.0f / 600.0f, 0.1f, 100.0f);
            glm::mat4x4 trans = proj * view * model;

            shaderProgram->setUniformMat4("u_transform", trans);
            shaderProgram->setUniformMat4("u_model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

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

	if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {

		if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			lightPositions[0].y += cameraSpeed;

		if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			lightPositions[0].y -= cameraSpeed;

		if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			lightPositions[0].x -= cameraSpeed;

		if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			lightPositions[0].x += cameraSpeed;

		if(glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
			lightPositions[0].z -= cameraSpeed;

		if(glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
			lightPositions[0].z += cameraSpeed;
	}

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.getPosition() += cameraSpeed * camera.getDirection();

	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.getPosition() -= cameraSpeed * camera.getDirection();

	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.getPosition() -= cameraSpeed * glm::normalize(glm::cross(camera.getDirection(), camera.getUp()));

	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.getPosition() += cameraSpeed * glm::normalize(glm::cross(camera.getDirection(), camera.getUp()));

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.getPosition() += cameraSpeed * camera.getUp();

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.getPosition() -= cameraSpeed * camera.getUp();
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

