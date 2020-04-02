#pragma once

#include "stdafx.h"
#include "InputHandler.h"
#include "Camera.h"
#include "GameObject.h"
#include "Shader.h"
#include "Mesh.h"
#include "Player.h"
#include "Primitives.h"

class World : public InputHandler {
private:
	Camera globalCamera;
	Player player;


	vector <Light> lights {Light()};

public:
	World() {
		globalCamera = Camera(vec3(0, 10, 10));
	}

	void handleInput(Mouse& mouse, Keyboard& keyboard) {
		if (Config::get(CAMERA_MODE) == CAMERA_GLOBAL) {
			globalCamera.handleInput(mouse, keyboard);
		}
		else {
			player.handleInput(mouse, keyboard);
		}
	}


	void draw() {
	}

private:
	Camera& getActiveCamera() {
		if (Config::get(CAMERA_MODE) == CAMERA_GLOBAL) {
			return globalCamera;
		}
		else {
			return player.getCamera();
		}
	}
};
