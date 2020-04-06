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

void init() {
	Config::init();

	if (Config::get(LOG_ENABLED) == true) {
		Log::enable();
	}
	else {
		Log::disable();
	}

	GLFW::init();
	Renderer::init();
	Primitives::init();
	Shader::init();
	Texture::loadTextures();
}

int main(int argc, char** argv)
{
	init();

	Mouse mouse;
	Keyboard keyboard;

	World world;
	
	while (!glfwWindowShouldClose(GLFW::getWindow())) {
		Sleep(Config::get(FRAME_DELAY));
		TimeManager::startCpu();

		GLFW::handleInput();
		TimeManager::handleTime();
		
		mouse.readInput();
		keyboard.readInput();
		
		//world.handleInput(mouse, keyboard);

		Renderer::clear();


		world.handleInput(mouse, keyboard);
		world.update();
		world.draw();


		Renderer::render();

		GLFW::updateScreen();  

		ErrorHandler::handleErrors();
	}

	GLFW::exit();
	Config::cleanUp();

	return 0;
}
