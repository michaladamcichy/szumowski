#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Primitives.h"
#include "Player.h"
#include "MathsUtils.h"

class Virus : public GameObject {
private:
	float radius;
public:
	Virus(vec3 position) : GameObject(Primitives::getQuad(), TEXTURE_VIRUS, position, Config::get(VIRUS_DIMENSIONS)) {
		radius = Config::get(VIRUS_DIMENSIONS).x;
	}

	void lookAtPlayer(Camera* camera) {
		this->setYaw(-camera->getYaw() - Constants::HALF_PI);
		this->setPitch(camera->getPitch());
	}

	bool isHit(vec3 rayOrigin, vec3 rayDirection) {
		//bool rayHitsSphere(vec3 rayOrigin, vec3 rayDirection, vec3 spherePosition, float sphereRadius) {
		vec3 spherePosition = this->getPosition();
		float sphereRadius = this->radius;
		vec3 translatedOrigin = rayOrigin - spherePosition;
		vec3 normalizedDirection = normalize(rayDirection);
		float b = MathsUtils::dotProduct(translatedOrigin, normalizedDirection);
		float c = MathsUtils::dotProduct(translatedOrigin, translatedOrigin) - sphereRadius * sphereRadius;

		if (c > 0.0f && b > 0.0f)
			return false;

		float discriminant = b * b - c;
		if (discriminant < 0.0f) return false;
		else return true;
		//}
	}
private:
};