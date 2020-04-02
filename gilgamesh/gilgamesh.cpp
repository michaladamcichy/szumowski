#include "stdafx.h"
#include "Config.h"
#include "GLFW.h"

#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Texture.h"
#include "World.h"
#include "TimeManager.h"
#include "MathsUtils.h"

int main(int argc, char** argv)
{
	if (Config::isLogEnabled() == true) {
		Log::enable();
	}
	else {
		Log::disable();
	}

	GLFW::init();
	Renderer::init();

	Mouse mouse;
	Keyboard keyboard;

	World world;
	
	while (!glfwWindowShouldClose(GLFW::getWindow())) {
		GLFW::handleInput();
		TimeManager::handleTime();
		
		mouse.readInput();
		keyboard.readInput();
		
		world.handleInput(mouse, keyboard);

		Renderer::clear();

		world.draw();

		glfwSwapBuffers(GLFW::getWindow());

		ErrorHandler::handleErrors();
	}

	GLFW::exit();
	return 0;
}
