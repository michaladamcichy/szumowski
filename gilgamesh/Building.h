#pragma once

#include "stdafx.h"
#include "GameObject.h"
#include "Primitives.h"

enum BuildingState {
	BUILDING_DEFAULT,
	BUILDING_GROWING,
	BUILDING_DECREASING
};

class Building : public GameObject {
private:
	static int maxId;
	int id;
	BuildingState state = BUILDING_DEFAULT;
public:
	Building(vec3 position) : GameObject(Primitives::getCube(), TEXTURE_BUILDING, position, Config::get(DEFAULT_BUILDING_DIMENSIONS)) {
		this->id = ++maxId;
	}	

	int getId() {
		return id;
	}

	void startGrowth() {
		state = BUILDING_GROWING;
		this->getMesh()->setTexture(TEXTURE_BUILDING_GROWING);
	}

	void update() {
		GameObject::update();

		if (state != BUILDING_DEFAULT) {
			state = BUILDING_DEFAULT;
			this->getMesh()->setTexture(TEXTURE_BUILDING);
		}
	}

private:
};

int Building::maxId = 0;