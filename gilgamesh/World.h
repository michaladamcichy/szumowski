#pragma once

#include "stdafx.h"
#include "InputHandler.h"
#include "Camera.h"
#include "GameObject.h"
#include "Shader.h"
#include "Mesh.h"
#include "Player.h"
#include "Primitives.h"
#include "Sun.h"

class World : public InputHandler {
private:
	Camera globalCamera;
	Player player;
	
	vector <GameObject*> objects;
	Sun* sun;
	Light light;

	bool alreadyUpdated = false;

public:
	World() {
		globalCamera = Camera(vec3(0, 10, 10));

		//ALERT obowiazkowo parzyste! nie wiem czemu inaczej nie dziala
		int rows = 8;
		int columns = 8;

		float step = 5.0;

		float distance = rows * step;

		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < columns; c++) {
				objects.push_back(new GameObject(Primitives::getCube(), TEXTURE_GROUND, vec3(r * step - distance / 2, 1.0, c * step - distance/2), vec3(3,3,3)));
			}
		}

		/*for (int r = 0; r < rows; r++) {
			for (int c = 0; c < columns; c++) {
				objects.push_back(new GameObject(Primitives::getCube(), TEXTURE_GROUND, vec3(r * step - distance / 2, 1.0, c * step - distance / 2), vec3(3, 3, 3)));
			}
		}*/


		GameObject* ground = new GameObject(Primitives::getQuad(), TEXTURE_FIRE, vec3(0,0,0), Config::get(GROUND_DIMENSIONS));
		ground->rotatePitch(-Constants::HALF_PI);

		objects.push_back(ground);

		sun = new Sun();
		objects.push_back(sun);

		light.init(vec3(0, 0, -100), vec3(glm::rotate(mat4(1), 0.2f, Directions::X_AXIS) * vec4(Directions::Z_AXIS, 1)) , Colors::WHITE, 0.1, 1.0, 0.0);
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
		int i = 0;

		sun->fixPosition(getActiveCamera());

		updateObjects();
	}

	void draw() {
		Renderer::attachCamera(this->getActiveCamera());

		Camera lightCamera = globalCamera;
		Light temp(lightCamera.getPosition(), lightCamera.getDirection(), Colors::WHITE, 0.0);
		light = temp;
		Renderer::attachLight(&light);
		
		for (GameObject* object : objects) {
			Renderer::addToQueue(object->getMesh());
		}
	}

private:
	void updateObjects() {
		if (Config::get(DYNAMIC_RENDERING_ENABLED) == true || !alreadyUpdated) {
			for (GameObject* object : objects) {
				object->update();
			}
			
			alreadyUpdated = true;
		}
	}

	Camera* getActiveCamera() {
		if (Config::get(CAMERA_MODE) == CAMERA_GLOBAL) {
			return &globalCamera;
		}
		else {
			return &player.getCamera();
		}
	}
};
