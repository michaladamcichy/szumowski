#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Primitives.h"
#include "Player.h"

class Virus : public GameObject {
private:
public:
	Virus(vec3 position) : GameObject(Primitives::getQuad(), TEXTURE_VIRUS, position, Config::get(VIRUS_DIMENSIONS)) {
	}

	void lookAtPlayer(Camera* camera) {
		this->setYaw(-camera->getYaw() - Constants::HALF_PI);
		this->setPitch(camera->getPitch());
	}
private:
};