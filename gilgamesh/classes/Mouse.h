#pragma once

#include "stdafx.h"
#include "GLFW.h"

class Mouse {
private:
	vec2 lastMovement = vec2(0,0);
	vec2 currentPosition = vec2(0,0);

public:
	Mouse() {
		glfwSetInputMode(GLFW::getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
		double x, y;
		glfwGetCursorPos(GLFW::getWindow(), &x, &y);
		currentPosition = vec2(x, y);
	}

	void readInput() {
		double x;
		double y;
		glfwGetCursorPos(GLFW::getWindow(), &x, &y);
		
		lastMovement = vec2(x - currentPosition.x, y - currentPosition.y);
		currentPosition = vec2(x, y);
	}

	vec2 getMovement() {
		return lastMovement;
	}
};

