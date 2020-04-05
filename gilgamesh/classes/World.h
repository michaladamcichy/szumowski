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
	Light light;

	bool alreadyUpdated = false;

public:
	World() {
		globalCamera = Camera(vec3(0, 10, 10));

		int rows = 100;
		int columns = 100;

		float step = 2.0;

		float distance = rows * step;

		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < columns; c++) {
				GameObject* object = new GameObject(Primitives::getQuad(), TextureType(c%TEXTURES_COUNT), vec3(r * step - distance/2, 0, c * step - distance/2));
				objects.push_back(object);
			}
		}

		light.init(vec3(0, 10, 0), Directions::DOWN, Colors::WHITE, 0.1, 0.9, 0.0);
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
		for (auto& object : objects) {
			i++;
			float change = i % 2 == 0 ? 0.1 : -0.1;
			object->move(vec3(0, TimeManager::getFrameDuration() * change, 0));
			float angle = i % 2 == 0 ? 0.5 : -0.5;
			angle *= TimeManager::getFrameDuration();
			object->rotate(0, angle, 0);
		}

		updateObjects();
	}

	void draw() {
		Renderer::attachCamera(this->getActiveCamera());
		Renderer::attachLight(&light);
		
		for (GameObject* object : objects) {
			Renderer::addToQueue(object->getMesh());
		}
	}

private:
	void updateObjects() {
		if (Config::get(DYNAMIC_RENDERING_ENABLED) == true || !alreadyUpdated) {

			if (Config::get(MULTITHREADING_ENABLED) == true) {
				int threadsCount = Config::get(THREADS_COUNT);
				int work = objects.size() / threadsCount;

				thread** threads = new thread * [threadsCount];


				vector <GameObject*>* objects = &this->objects;

				for (int i = 0; i < threadsCount - 1; i++) {
					threads[i] = new thread([objects, i, threadsCount, work]() mutable {
						for (int j = i * work; j < i * work + work; j++) {
							(*objects)[j]->update();
						}
					});
				}

				threads[threadsCount - 1] = new thread([objects, threadsCount, work]() mutable {
					for (int j = (threadsCount - 1) * work; j < objects->size(); j++) {
						(*objects)[j]->update();
					}
				});

				for (int i = 0; i < threadsCount; i++) {
					threads[i]->join();
				}

				delete[] threads;
			}
			else {
				for (GameObject* object : objects) {
					object->update();
				}
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
