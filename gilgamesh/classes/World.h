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
	
	vector <GameObject*> objects;
	vector <Light> lights {Light()};

	bool alreadyUpdated = false;

public:
	World() {
		globalCamera = Camera(vec3(0, 10, 10));

		int rows = 10;
		int columns = 10;

		float step = 2.0;

		float distance = rows * step;

		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < columns; c++) {
				GameObject* object = new GameObject(Primitives::getCube(), vec3(r * step - distance/2, 0, c * step - distance/2));
				objects.push_back(object);
			}
		}
	}

	void handleInput(Mouse& mouse, Keyboard& keyboard) {
		if (Config::get(CAMERA_MODE) == CAMERA_GLOBAL) {
			globalCamera.handleInput(mouse, keyboard);
		}
		else {
			player.handleInput(mouse, keyboard);
		}
	}

	void update() {
		if (Config::get(DYNAMIC_RENDERING_ENABLED) == true || !alreadyUpdated) {
			for (GameObject* object : objects) {
				object->update();
			}
			alreadyUpdated = true;
		}
	}

	void draw() {
		Renderer::attachCamera(this->getActiveCamera());
		
		for (GameObject* object : objects) {
			Renderer::addToQueue(object->getMesh());
		}
	}

private:
	Camera* getActiveCamera() {
		if (Config::get(CAMERA_MODE) == CAMERA_GLOBAL) {
			return &globalCamera;
		}
		else {
			return &player.getCamera();
		}
	}
};
