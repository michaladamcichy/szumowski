#pragma once

#include "stdafx.h"
#include "Config.h"

class GLFW {
private:
	static GLFWwindow* window;
public:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		Config::set(SCREEN_WIDTH, width);
		Config::set(SCREEN_HEIGHT, height);
	}

	static bool init() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(
			Config::get(SCREEN_WIDTH),
			Config::get(SCREEN_HEIGHT),
			Config::get(WINDOW_TITLE).c_str(),
			NULL,
			NULL);

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			Log::print("Cannot initialize Glad\n");

			return false;
		}

		return true;
	}

	static void exit() {
		glfwTerminate();
	}

	static void updateScreen() {
		glfwSwapBuffers(window);
	}

	static void handleInput() {
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}

	static GLFWwindow* getWindow() { return window; }
};

GLFWwindow* GLFW::window = NULL;