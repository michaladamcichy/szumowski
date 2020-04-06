#pragma once

#include "stdafx.h"
#include "GameObject.h"
#include "Primitives.h"
#include "Config.h"
#include "Light.h"

class Sun : public GameObject {
private:
	Light light;
public:
	Sun() : GameObject(Primitives::getQuad(), TEXTURE_SUN, vec3(0, 0, -Config::get(GROUND_DIMENSIONS).z), vec3(Config::get(SUN_SIZE), Config::get(SUN_SIZE), Config::get(SUN_SIZE))) {
		light.init(this->getPosition(), vec3(0,0,1), Colors::WHITE, 0.4, 0.6);
	}

	void fixPosition(Camera* camera) {
		this->setPosition(vec3(0, 0, -Config::get(GROUND_DIMENSIONS).z) + camera->getPosition());
	}

	Light* getLight() {
		return &light;
	}
};