//
// Created by Alexander Winter on 2023-01-19.
//

#include <stdexcept>
#include "input/InputListener.h"

using namespace jello;

void mouseScrolledCallback(GLFWwindow* window, double amountX, double amountY) {
	InputListener* listener = static_cast<InputListenerPointerContainer*>(glfwGetWindowUserPointer(window))->listener;
	listener->mouseScrolled(window, amountX, amountY);
}

void mouseMovedCallback(GLFWwindow* window, double screenX, double screenY) {
	InputListener* listener = static_cast<InputListenerPointerContainer*>(glfwGetWindowUserPointer(window))->listener;
	listener->mouseMoved(window, screenX, screenY);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	InputListener* listener = static_cast<InputListenerPointerContainer*>(glfwGetWindowUserPointer(window))->listener;

	double x, y;

	glfwGetCursorPos(window, &x, &y);

	if(action == GLFW_PRESS)
		listener->mouseButtonPressed(window, x, y, button, mods);
	else if(action == GLFW_RELEASE)
		listener->mouseButtonReleased(window, x, y, button, mods);
}

void InputListener::registerOn(GLFWwindow* window) {
	if(glfwGetWindowUserPointer(window) != nullptr)
		throw std::runtime_error("WindowUserPointer already set!");

	glfwSetWindowUserPointer(window, new InputListenerPointerContainer(this));
	glfwSetScrollCallback(window, mouseScrolledCallback);
	glfwSetCursorPosCallback(window, mouseMovedCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void InputListener::unregisterFrom(GLFWwindow* window) {
	InputListenerPointerContainer* container = static_cast<InputListenerPointerContainer*>(glfwGetWindowUserPointer(window));
	InputListener* listener = container->listener;

	if(glfwGetWindowUserPointer(window) != listener)
		throw std::runtime_error("Not registered or something else overwrote the WindowUserPointer");

	glfwSetWindowUserPointer(window, nullptr);
	delete container;
	glfwSetScrollCallback(window, nullptr);
	glfwSetCursorPosCallback(window, nullptr);
	glfwSetMouseButtonCallback(window, nullptr);
}
