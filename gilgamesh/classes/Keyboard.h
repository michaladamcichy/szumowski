#pragma once

#include "stdafx.h"
#include "GLFW.h"

class Keyboard {
private:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool shift = false;
	bool tab = false;
	bool leftMouse = false;
	bool f = false;
	bool space = false;
	int tabInertia = 0;
public:
	Keyboard() {
		glfwSetKeyCallback(GLFW::getWindow(), key_callback);
	}

	void readInput() {
		registerPresses();
		registerReleases();
	}

	bool isUpPressed() {
		return up;
	}

	bool isDownPressed() {
		return down;
	}

	bool isLeftPressed() {
		return left;
	}

	bool isRightPressed() {
		return right;
	}

	bool isShiftPressed() {
		return shift;
	}

	bool isTabPressed() {
		return tab;
	}

	bool isLeftMousePressed() {
		return leftMouse;
	}

	bool isFPressed() {
		return f;
	}

	bool isSpacePressed() {
		return space;
	}


private:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
			Config::toggleCameraMode();
		}
	}

	void registerPresses() {
		if (glfwGetKey(GLFW::getWindow(), GLFW_KEY_UP) == GLFW_PRESS ||
			glfwGetKey(GLFW::getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
			up = true;
		}
		if (glfwGetKey(GLFW::getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS ||
			glfwGetKey(GLFW::getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
			down = true;
		}
		if (glfwGetKey(GLFW::getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS ||
			glfwGetKey(GLFW::getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
			left = true;
		}
		if (glfwGetKey(GLFW::getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS ||
			glfwGetKey(GLFW::getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
			right = true;
		}
		if (glfwGetKey(GLFW::getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			shift = true;
		}
		if (glfwGetKey(GLFW::getWindow(), GLFW_KEY_F) == GLFW_PRESS) {
			f = true;
		}
		if (glfwGetKey(GLFW::getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
			space = true;
		}
		if (glfwGetMouseButton(GLFW::getWindow(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
			leftMouse = true;
		}
	}

	 void registerReleases() {
		if (glfwGetKey(GLFW::getWindow(), GLFW_KEY_UP) == GLFW_RELEASE &&
			glfwGetKey(GLFW::getWindow(), GLFW_KEY_W) == GLFW_RELEASE) {
			up = false;
		}
		if (glfwGetKey(GLFW::getWindow(), GLFW_KEY_DOWN) == GLFW_RELEASE &&
			glfwGetKey(GLFW::getWindow(), GLFW_KEY_S) == GLFW_RELEASE) {
			down = false;
		}
		if (glfwGetKey(GLFW::getWindow(), GLFW_KEY_LEFT) == GLFW_RELEASE &&
			glfwGetKey(GLFW::getWindow(), GLFW_KEY_A) == GLFW_RELEASE) {
			left = false;
		}
		if (glfwGetKey(GLFW::getWindow(), GLFW_KEY_RIGHT) == GLFW_RELEASE &&
			glfwGetKey(GLFW::getWindow(), GLFW_KEY_D) == GLFW_RELEASE) {
			right = false;
		}
		if (glfwGetKey(GLFW::getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
			shift = false;
		}
		if (glfwGetKey(GLFW::getWindow(), GLFW_KEY_F) == GLFW_RELEASE) {
			f = false;
		}
		if (glfwGetKey(GLFW::getWindow(), GLFW_KEY_SPACE) == GLFW_RELEASE) {
			space = false;
		}
		if (glfwGetMouseButton(GLFW::getWindow(), GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) {
			leftMouse = false;
		}
	}
};
