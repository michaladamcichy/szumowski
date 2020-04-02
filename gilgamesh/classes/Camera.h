#pragma once

#include "stdafx.h"
#include "Constants.h"
#include "Config.h"
#include "Mouse.h"
#include "Keyboard.h"

class Camera {
private:
	vec3 position;
	float pitch = 0;
	float yaw = -Constants::HALF_PI;

	vec3 front;
	vec3 up;
	vec3 right;

public:
	Camera(vec3 position = vec3(0,0,0)) {
		this->position = position;

		front = vec3(0, 0, -1);
		up = Directions::UP;
		right = glm::cross(front, up);

		updateVectors();
	}

	mat4 getTransformation() {
		mat4 view = glm::lookAt(position, position + front, up);

		return getPerspective() * view;
	}

	mat4 getRotations() {
		mat4 view = glm::lookAt(vec3(0,0,0), front, up);

		return getPerspective() * view;
	}

	mat4 getPerspective() {
		return  glm::perspective(
			glm::radians(Config::getCameraFov()),
			float(Config::getScreenWidth()) / float(Config::getScreenHeight()),
			Config::getCameraNearPlane(),
			Config::getCameraFarPlane()
		);
	}

	void move(vec3 translation) {
		position += translation;
	}

	void rotate(float pitchOffset, float yawOffset) {
		pitch += pitchOffset;
		yaw += yawOffset;

		if (pitch > Config::getCameraMaxPitch()) {
			pitch = Config::getCameraMaxPitch();
		}
		else if (pitch < Config::getCameraMinPitch()) {
			pitch = Config::getCameraMinPitch();
		}

		if (yaw > Constants::DOUBLE_PI) {
			yaw -= Constants::DOUBLE_PI;
		}
		else if (yaw < -Constants::DOUBLE_PI) {
			yaw += Constants::DOUBLE_PI;
		}

		updateVectors();
	}

	void handleInput(Mouse& mouse, Keyboard& keyboard) {
		this->rotate(-mouse.getMovement().y * Config::getMouseSensitivity(), mouse.getMovement().x * Config::getMouseSensitivity());

		float speed = Config::getCameraSpeed();
		if (keyboard.isShiftPressed()) {
			speed *= Config::getCameraBoost();
		}

		if (keyboard.isUpPressed()) {
			this->move(front * speed);
		}
		if (keyboard.isDownPressed()) {
			this->move(-front * speed);
		}if (keyboard.isLeftPressed()) {
			this->move(-right * speed);
		}if (keyboard.isRightPressed()) {
			this->move(right * speed);
		}
	}
	
	void setPosition(vec3 position) {
		this->position = position;
	}

	vec3 getPosition() {
		return position;
	}

	vec3 getDirection() {
		return front;
	}

	float getPitch() {
		return pitch;
	}

	float getYaw() {
		return yaw;
	}

	vec3 getFront() {
		return front;
	}

	vec3 getRight() {
		return right;
	}

	vec3 getLeft() {
		return -right;
	}

	vec3 getBack() {
		return -front;
	}

private:
	void updateVectors() {
		front.x = cos(pitch) * cos(yaw);
		front.y = sin(pitch);
		front.z = cos(pitch) * sin(yaw);
		front = glm::normalize(front);

		right = glm::normalize(glm::cross(front, Directions::UP));
		up = -glm::normalize(glm::cross(front, right));
	}
};
