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
			glm::radians(Config::get(CAMERA_FOV)),
			float(Config::get(SCREEN_WIDTH)) / float(Config::get(SCREEN_HEIGHT)),
			Config::get(CAMERA_NEAR_PLANE),
			Config::get(CAMERA_FAR_PLANE)
		);
	}

	void move(vec3 translation) {
		position += translation;
	}

	void rotate(float pitchOffset, float yawOffset) {
		pitch += pitchOffset;
		yaw += yawOffset;

		if (pitch > Config::get(CAMERA_MAX_PITCH)) {
			pitch = Config::get(CAMERA_MAX_PITCH);
		}
		else if (pitch < Config::get(CAMERA_MIN_PITCH)) {
			pitch = Config::get(CAMERA_MIN_PITCH);
		}

		if (yaw > Constants::DOUBLE_PI) {
			yaw -= Constants::DOUBLE_PI;
		}
		else if (yaw < -Constants::DOUBLE_PI) {
			yaw += Constants::DOUBLE_PI;
		}

		updateVectors();
	}

	vec3 createRelativePoint(vec3 vec) { //ALERT NOT TESTED
		return vec3(getTransformation() * vec4(vec, 1.0f));
	}

	vec3 createRelativeDirection(vec3 vec) { //ALERT NOT TESTED
		return vec3(getRotations() * vec4(vec, 1.0f));
	}

	void handleInput(Mouse& mouse, Keyboard& keyboard) {
		this->rotate(-mouse.getMovement().y * Config::get(MOUSE_SENSITIVITY), mouse.getMovement().x * Config::get(MOUSE_SENSITIVITY));

		float speed = Config::get(CAMERA_SPEED);
		if (keyboard.isShiftPressed()) {
			speed *= Config::get(CAMERA_BOOST);
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
		return normalize(front);
	}

	float getPitch() {
		return pitch;
	}

	float getYaw() {
		return yaw;
	}

	vec3 getFront() {
		return normalize(front); //ALERT NOT NECESSARY
	}

	vec3 getRight() {
		return normalize(right);
	}

	vec3 getLeft() {
		return normalize(-right);
	}

	vec3 getBack() {
		return normalize(-front);
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
