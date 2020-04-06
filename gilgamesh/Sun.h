#pragma once

#include "stdafx.h"
#include "GameObject.h"
#include "Primitives.h"
#include "Config.h"

class Sun : public GameObject {
public:
	Sun() : GameObject(Primitives::getQuad(), TEXTURE_SUN, vec3(0, 0, -Config::get(GROUND_DIMENSIONS).z), vec3(Config::get(SUN_SIZE), Config::get(SUN_SIZE), Config::get(SUN_SIZE))) {

	}

	void fixPosition(Camera* camera) {
		this->setPosition(vec3(0, 0, -Config::get(GROUND_DIMENSIONS).z) + camera->getPosition());
	}
};