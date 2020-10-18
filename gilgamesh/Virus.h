#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Primitives.h"
#include "Player.h"

class Sprite : public GameObject {
private:
public:
	Sprite(int texture, vec3 position, vec3 dimensions) : GameObject(Primitives::getQuad(), texture, position, dimensions) {
	}

	void lookAtPlayer(Camera* camera) {
		this->setYaw(-camera->getYaw() - Constants::HALF_PI);
		this->setPitch(camera->getPitch());
	}
private:
};