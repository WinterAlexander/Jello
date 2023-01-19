//
// Created by Alexander Winter on 2023-01-19.
//

#ifndef JELLO_INPUTPROCESSOR_H
#define JELLO_INPUTPROCESSOR_H

#include "GLFW/glfw3.h"

namespace jello {
	class InputListener;
	struct InputListenerPointerContainer;
}

/**
 * Listens to mouse and keyboard inputs of a GLFWwindow
 */
class jello::InputListener {
public:
	virtual void mouseButtonPressed(GLFWwindow* window, double screenX, double screenY, int button, int mods) = 0;

	virtual void mouseButtonReleased(GLFWwindow* window, double screenX, double screenY, int button, int mods) = 0;

	virtual void mouseMoved(GLFWwindow* window, double screenX, double screenY) = 0;

	virtual void mouseScrolled(GLFWwindow* window, double amountX, double amountY) = 0;

	void registerOn(GLFWwindow* window);

	void unregisterFrom(GLFWwindow* window);
};

struct jello::InputListenerPointerContainer {
	InputListener* listener;

	explicit InputListenerPointerContainer(InputListener* listener)
		: listener(listener) {}
};


#endif //JELLO_INPUTPROCESSOR_H
