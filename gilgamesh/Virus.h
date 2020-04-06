#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Primitives.h"
#include "Player.h"
#include "MathsUtils.h"

class Virus : public GameObject {
private:
	float radius;
	float restTimeout;
	float deathTimeout = 0;
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

	void chasePlayer(Player* player) {
		float threshold = 0.2;
		float maxRestTimeout = 5;

		float maxActiveTime = 10;

		if (MathsUtils::squareDistance(player->getPosition(), this->getPosition()) > this->radius + player->getRadius() - threshold) {
			vec3 direction = glm::normalize(player->getPosition() - this->getPosition());
			float amount = Config::get(VIRUS_SPEED);
			vec3 translation = direction * amount;

			this->move(translation);
		}
	}


        void followPath(vector<vec2i> path) {
            if (path.size() > 0) {
                auto nextTile = path.back();
                auto currentTile = getTile(this->getPosition());
                if (currentTile != nextTile) {
                    auto nextPos = getPos(nextTile);
                    vec3 direction = glm::normalize(nextPos - this->getPosition());
                    float amount = Config::get(VIRUS_SPEED);
                    vec3 translation = direction * amount;
                    this->move(translation);
                } else {
                    path.pop_back();
                }
            }
        }

        inline vec2i getTile(vec3 p) {
                return {(int)((p.x + 4.0f*40.0f + 5.0f) / 10.0f),
                        (int)((p.z + 4.0f*40.0f + 5.0f) / 10.0f)};
        }

        inline vec3 getPos(vec2i p) {
                return {((float)p.x*10) - 4.0f*40.0f,
                        0.0f,
                        ((float)p.x*10) - 4.0f*40.0f};
        }

	void prepareForDeath() {
		deathTimeout = -Config::get(VIRUS_DEATH_DURATION);
	}

	bool isAlreadyDead() {
		if (deathTimeout > 0) return true; else return false;
	}

	void handleDeathTimout() {
		deathTimeout += 0.1;
	}
	//void update() {
	//	GameObject::update();
	//}
private:
};
