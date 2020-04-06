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
#include "Sun.h"
#include "Building.h"
#include "BuildingsMap.h"
#include "MathsUtils.h"

class World : public InputHandler {
private:
	Camera globalCamera;
	Player player;
	
	BuildingsMap buildingsMap;

	vector <GameObject*> objects;
	vector <Building*> buildings;
	vector <Virus*> viruses;
	Sun* sun;

	bool alreadyUpdated = false;

	GameObject* aim;
	GameObject* playerMarker;

public:
	World() {
		globalCamera = Camera(vec3(0, 10, 10));

		//ALERT obowiazkowo parzyste! nie wiem czemu inaczej nie dziala
		int rows = 8;
		int columns = 8;

		float step = 40.0;

		float distance = rows * step;

		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < columns; c++) {
				Building* building = new Building(vec3(float(r) * step - distance / 2.0, Config::get(DEFAULT_BUILDING_DIMENSIONS).y / 2.0, float(c) * step - distance / 2.0));
				buildings.push_back(building);
				objects.push_back(building);
			}
		}

		buildingsMap.init(buildings, step);

		step = 2;
		distance = rows * step;

		vec3 virusesTranslation = vec3(0, 0, Config::get(GROUND_DIMENSIONS).x / 2);

		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < columns; c++) {
				Virus* virus = new Virus(vec3(r * step - distance/2, 2.0, c * step - distance/2));
				viruses.push_back(virus);
				objects.push_back(virus);
			}
		}

		GameObject* ground = new GameObject(Primitives::getQuad(), TEXTURE_FIRE, vec3(0,0,0), Config::get(GROUND_DIMENSIONS));
		ground->rotatePitch(Constants::HALF_PI);
		objects.push_back(ground);

		sun = new Sun();
		objects.push_back(sun);

		vec3 markerSize = vec3(0.05);
		aim = new GameObject(Primitives::getCube(), TEXTURE_FIRE, player.getPosition(), markerSize);
		objects.push_back(aim);
		playerMarker = new GameObject(Primitives::getCube(), TEXTURE_VIRUS, vec3(0,0,0), markerSize);
		objects.push_back(playerMarker);
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

		if (player.isShooting()) {
			vector <Virus*> potentiallyHit;
			for (auto& virus : viruses) {
				if (virus->isHit(player.getPosition(), player.getAimingDirection())) {
					potentiallyHit.push_back(virus);
				}
			}

			if (potentiallyHit.size() > 0) {
				Player* playerPointer = &player;

				std::sort(std::begin(potentiallyHit), std::end(potentiallyHit), [playerPointer] (Virus* a, Virus* b)
					{return  MathsUtils::squareDistance(a->getPosition(), playerPointer->getPosition()) > MathsUtils::squareDistance(b->getPosition(), playerPointer->getPosition()); }
			);

				Virus* hit = potentiallyHit[0];
				hit->move(vec3(0, 2, 0));
			}
		}

		Building* building = buildingsMap.getNearBuilding(&player);

		if (building != NULL) {
			building->startGrowth();
			player.handleCollision(building);
		}

		for (auto& virus : viruses) {
			virus->lookAtPlayer(getActiveCamera());
		}

		sun->fixPosition(getActiveCamera());

		aim->setPosition(player.getPosition() + player.getAimingDirection());
		playerMarker->setPosition(player.getPosition());

		player.update();
		updateObjects();
	}

	void draw() {
		Renderer::attachCamera(this->getActiveCamera());
		Renderer::attachLight(sun->getLight());
		
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
