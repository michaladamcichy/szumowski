#pragma once

#include "stdafx.h"
#include "Camera.h"

class Player {
public:
	Camera camera;
	vec3 position;
	float height = 2;

	bool isShooting = false;
	bool isHurt = false;
	int hp = 100;

public:
	Player() {
		position = Config::get(PLAYER_INITIAL_POSITION);
		vec3 cameraTranslation = position;
		cameraTranslation.y = height;
		camera.move(cameraTranslation);
	}

	vec2 getPosition() {
		return vec2(position.x, position.z);
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

		if (keyboard.isLeftMousePressed()) {
			isShooting = true;
		}
		else {
			isShooting = false;
		}
		
		vec3 cameraPosition = position;
		cameraPosition.y = height;
		camera.setPosition(cameraPosition);
	}
private:
};