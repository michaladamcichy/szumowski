#pragma once

#include "stdafx.h"
#include "Camera.h"

class Player {
public:
	Camera camera;
	vec3 position;
	float radius;

	bool shooting = false;
	bool hurt = false;
	int hp = 100;

	float shootingTimeout = 0;

public:
	Player() {
		position = Config::get(PLAYER_INITIAL_POSITION);
		radius = Config::get(PLAYER_RADIUS);
		vec3 cameraTranslation = position;
		camera.move(cameraTranslation);
	}

	vec3 getPosition() {
		return position;
	}

	float getRadius() {
		return radius;
	}

	Camera& getCamera() {
		return camera;
	}

	vec3 getAimingDirection() {
		return camera.getFront();
	}

	void handleInput(Mouse& mouse, Keyboard& keyboard) {
		camera.rotate(-mouse.getMovement().y * Config::get(MOUSE_SENSITIVITY), mouse.getMovement().x * Config::get(MOUSE_SENSITIVITY));

		vec3 forward = glm::normalize(glm::cross(Directions::UP, camera.getRight()));
		vec3 left = camera.getLeft();
		vec3 right = camera.getRight();
		vec3 back = -forward;

		float boost = 1;

		if (keyboard.isShiftPressed()) {
			boost = Config::get(PLAYER_BOOST);
		}

		if (keyboard.isUpPressed()) {
			position += forward * Config::get(PLAYER_SPEED) * boost;
		}
		if (keyboard.isDownPressed()) {
			position += back * Config::get(PLAYER_SPEED) * boost;
		}
		if (keyboard.isLeftPressed()) {
			position += left * Config::get(PLAYER_SPEED) * boost;
		}
		if (keyboard.isRightPressed()) {
			position += right * Config::get(PLAYER_SPEED) * boost;
		}

		if (keyboard.isLeftMousePressed() || keyboard.isSpacePressed()) {
			if (shootingTimeout == 0) {
				shooting = true;

				shootingTimeout = Config::get(SHOOTING_TIMEOUT);
			}
		}
		else {
			shooting = false;
		}

		vec3 cameraPosition = position;
		camera.setPosition(cameraPosition);
	}

	bool isShooting() {
		return shooting;
	}

	void handleCollision(GameObject* object)
	{
		float objectMinX = object->getPosition().x - object->getDimensions().x / 2.0f;
		float objectMinZ = object->getPosition().z - object->getDimensions().z / 2.0f;
		float objectMaxX = object->getPosition().x + object->getDimensions().x / 2.0f;
		float objectMaxZ = object->getPosition().z + object->getDimensions().z / 2.0f;

		float closestX = glm::clamp(position.x, objectMinX, objectMaxX);
		float closestZ = glm::clamp(position.z, objectMinZ, objectMaxZ);
		float dx = position.x - closestX;
		float dz = position.z - closestZ;
		float distSquared = dx * dx + dz * dz;
		float rSquared = radius * radius;

		// if closest object point overlaps with player circle
		if (distSquared < rSquared)
		{
			if (std::abs(dx) > std::abs(dz))
			{
				// correct by x
				float sign = (dx > 0.0f) ? 1.0f : -1.0f;
				this->position.x = closestX + sign * std::sqrt(rSquared - dz * dz);
			}
			else
			{
				// correct by z
				float sign = (dz > 0.0f) ? 1.0f : -1.0f;
				this->position.z = closestZ + sign * std::sqrt(rSquared - dx * dx);
			}
		}
	}

	void update() {
		shootingTimeout -= TimeManager::getFrameDuration();
		if (shootingTimeout < 0) shootingTimeout = 0;
	}

private:
};