#pragma once

#include "stdafx.h"
#include "Building.h"

class BuildingsMap {
private:
	vector <vector <Building*>> map;
	float mapSize;
	float gridSize;
public:
	BuildingsMap() {}

	BuildingsMap(vector<Building*> buildings, float gridSize) {
		init(buildings, gridSize);
	}

	void init(vector<Building*> buildings, float gridSize) {
		this->gridSize = gridSize;

		Log::print("CREATING BUILDINGS MAP");

		float maxCoordinate = 0;

		if (buildings.size() > 0) {
			maxCoordinate = max(abs(buildings[0]->getPosition().x), abs(buildings[0]->getPosition().z));
		}

		for (int i = 1; i < buildings.size(); i++) {
			float currentMax = max(abs(buildings[i]->getPosition().x), abs(buildings[i]->getPosition().z));
			if (currentMax > maxCoordinate) {
				maxCoordinate = currentMax;
			}
		}

		int mapSize = (maxCoordinate / gridSize * 2) + 1;
		
		for (int x = 0; x < mapSize; x++) {
			map.push_back(vector<Building*>());
			for (int y = 0; y < mapSize; y++) {
				map[x].push_back(NULL);
			}
		}

		for (auto& building : buildings) {
			float x = round(building->getPosition().x / gridSize) + map.size() / 2;
			float z = round(building->getPosition().z / gridSize) + map.size() / 2;
			int xx = round(x);
			int zz = round(z);

			map[x][z] = building;
		}

		Log::done();
	}

	Building* getNearBuilding(Player* player) {
		int x = round(player->getPosition().x / gridSize) + map.size() / 2;
		int z = round(player->getPosition().z / gridSize) + map.size() / 2;
		
		if (x < 0 || x >= map.size() || z < 0 || z >= map.size()) {
			return NULL;
		}
		else {
			return map[x][z];
		}
	}
private:
};