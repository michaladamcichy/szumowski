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
        TileMap tileMap;

	vector <GameObject*> objects;
	vector <Building*> buildings;
	vector <Virus*> viruses;
	vector <Virus*> deadViruses;
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

                tileMap.resize(4*rows);
		for (int r = 0; r < 4*rows; r++) {
                        tileMap[r].resize(4*columns);
			for (int c = 0; c < 4*columns; c++) {
                                tilemap[r][c] = (r%4 == 0) ? true : false;
                        }
                }

		step = 2;
		distance = rows * step;

		vec3 virusesTranslation = vec3(0, 0, Config::get(GROUND_DIMENSIONS).x / 2);

		//for (int r = 0; r < rows; r++) {
		//	for (int c = 0; c < columns; c++) {
		//		Virus* virus = new Virus(vec3(r * step - distance/2, 2.0, c * step - distance/2));
		//		viruses.push_back(virus);
		//		objects.push_back(virus);
		//	}
		//}

		float trans = Config::get(GROUND_DIMENSIONS).x / 40;
		float maxheight = 20;
		float range = Config::get(GROUND_DIMENSIONS).x / 40;;
		for (float x = -range; x < range; x+=1.0) {
			Virus* virus = new Virus(vec3(x, 2.0, cos(x) * range));
			viruses.push_back(virus);
			//objects.push_back(virus);
			virus = new Virus(vec3(x, 2.0, -cos(x) * range));
			viruses.push_back(virus);
			//objects.push_back(virus);
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
		//objects.push_back(playerMarker);
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
				hit->prepareForDeath();
				//deadViruses.push_back(hit);

				for (int i = 0; i > viruses.size(); i++) {
					if (viruses[i] == hit) {
						viruses.erase(viruses.begin() + i);
					}
				}
			}
		}

		for (int index = 0; index < deadViruses.size(); index++) {
			deadViruses[index]->handleDeathTimout();
			if (deadViruses[index]->isAlreadyDead()) {
				delete deadViruses[index];
				deadViruses.erase(deadViruses.begin() + index);
			}
		}

		Building* building = buildingsMap.getNearBuilding(&player);

		if (building != NULL) {
			building->startGrowth();
			player.handleCollision(building);
		}

		for (auto& virus : viruses) {
                        vec3 virusPos = virus->getPosition();
                        float dist = MathUtils::squareDistance(virusPos, player.position);
                        float followThreshold = 20.0f;
                        if (dist < followThreshold*followThreshold) {
                                vec2i virusTile = getTile(virusPos);
                                vec2i playerTile = getTile(player.position);
                                if (virusTile != playerTile) {
                                        virus->followPath(MathUtils::findPath(tileMap, virusTile, playerTile));
                                } else {
                                        virus->chasePlayer(&player);
                                }
                        }
                        else {
                                Building* building = buildingsMap.getNearBuilding(virus);
                                float nearestX = glm::clamp(virusPos.x
                                                            building.getPosition().x-5.0f,
                                                            building.getPosition().x+5.0f);
                                float nearestZ = glm::clamp(virusPos.z
                                                            building.getPosition().z-5.0f,
                                                            building.getPosition().z+5.0f);
                                vec3 nearest(nearestX, virusPos.y, nearestZ);
                                dist = MathUtils::sqareDistance(nearest, virus.getPosition());
                                if (dist > 2.0f) {
                                        vector<vec2i> path;
                                        path.push_back(getTile(building.getPosition()));
                                        virus->followPath(path);
                        }
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

		for (auto& virus : viruses) {
			Renderer::addToQueue(virus->getMesh());
		}

		for (auto& deadVirus : deadViruses) {
			Renderer::addToQueue(deadVirus->getMesh());
		}
	}

private:
        inline vec2i getTile(vec3 p) {
            return {(int)((p.x + 4.0f*40.0f + 5.0f) / 10.0f),
                    (int)((p.z + 4.0f*40.0f + 5.0f) / 10.0f)};
        }

	void updateObjects() {
		if (Config::get(DYNAMIC_RENDERING_ENABLED) == true || !alreadyUpdated) {
			for (GameObject* object : objects) {
				object->update();
			}

			for (auto& virus : viruses) {
				virus->update();
			}
			
			for (auto& deadVirus : deadViruses) {
				deadVirus->update();
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
