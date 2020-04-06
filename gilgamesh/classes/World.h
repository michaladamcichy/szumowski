#pragma once

#include "stdafx.h"
#include "InputHandler.h"
#include "Camera.h"
#include "GameObject.h"
#include "Shader.h"
#include "Mesh.h"
#include "Player.h"
#include "Primitives.h"
#include "Virus.h"

class World : public InputHandler {
private:
	Camera globalCamera;
	Player player;
	
	vector <GameObject*> objects;
	vector <Virus*> viruses;
	Light light;

	bool alreadyUpdated = false;

public:
	World() {
		globalCamera = Camera(vec3(0, 10, 10));

		int rows = 20;
		int columns = 20;

		float step = 40.0;

		float distance = rows * step;

		//for (int r = 0; r < rows; r++) {
		//	for (int c = 0; c < columns; c++) {
		//		GameObject* object = new GameObject(Primitives::getCube(), TEXTURE_GROUND, vec3(r * step - distance/2, 20.0, c * step - distance/2), Config::get(DEFAULT_BUILDING_DIMENSIONS));
		//		objects.push_back(object);
		//	}
		//}

		step = 2;
		distance = rows * step;

		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < columns; c++) {
				Virus* virus = new Virus(vec3(r * step - distance/2, 2.0, c * step - distance/2));
				viruses.push_back(virus);
			}
		}

		GameObject* ground = new GameObject(Primitives::getQuad(), TEXTURE_FIRE, vec3(0,0,0), Config::get(GROUND_DIMENSIONS));
		ground->rotatePitch(Constants::HALF_PI);

		objects.push_back(ground);

		light.init(vec3(0, 10, 0), Directions::DOWN, Colors::WHITE, 0.5, 0.9, 0.0);
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
		//for (auto& object : objects) {
		//	i++;
		//	float change = i % 2 == 0 ? 0.1 : -0.1;
		//	object->move(vec3(0, TimeManager::getFrameDuration() * change, 0));
		//	float angle = i % 2 == 0 ? 0.5 : -0.5;
		//	angle *= TimeManager::getFrameDuration();
		//	object->rotate(0, angle, 0);
		//}

		for (auto& virus : viruses) {
			virus->lookAtPlayer(getActiveCamera());
		}

		updateObjects();
	}

	void draw() {
		Renderer::attachCamera(this->getActiveCamera());
		Renderer::attachLight(&light);
		
		for (GameObject* object : objects) {
			Renderer::addToQueue(object->getMesh());
		}

		for (Virus* virus : viruses) {
			Renderer::addToQueue(virus->getMesh());
		}
	}

private:
	void updateObjects() {
		if (Config::get(DYNAMIC_RENDERING_ENABLED) == true || !alreadyUpdated) {
			for (GameObject* object : objects) {
				object->update();
			}
			for (Virus* virus : viruses) {
				virus->update();
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
