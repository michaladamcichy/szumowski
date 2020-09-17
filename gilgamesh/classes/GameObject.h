#pragma once

#include "stdafx.h"
#include "Mesh.h"
#include "Light.h"

class GameObject {
private:
	Mesh* mesh = NULL;

	vec3 position = vec3(0, 0, 0);
	vec3 dimensions = vec3(1, 1, 1);
	
	float yaw = 0;
	float pitch = 0;
	float roll = 0;

public:
	GameObject() {}

	GameObject(Mesh* origin, TextureType texture, vec3 position = vec3(0, 0, 0), vec3 dimensions = vec3(1, 1, 1), float yaw = 0, float pitch = 0, float roll = 0) {
		init(origin, texture, position, dimensions, yaw, pitch, roll);
	}

	void init(Mesh* origin, TextureType texture, vec3 position = vec3(0, 0, 0), vec3 dimensions = vec3(1, 1, 1), float yaw = 0, float pitch = 0, float roll = 0) {
		this->mesh = new Mesh(origin, texture);
		this->mesh->setTexture(texture);
		this->position = position;
		this->dimensions = dimensions;
		this->yaw = yaw;
		this->pitch = pitch;
		this->roll = roll;
	}

	void update() {
		mat4 transformation = glm::translate(mat4(1), position) *
			glm::rotate(mat4(1), yaw, Directions::Y_AXIS) *
			glm::rotate(mat4(1), pitch, Directions::X_AXIS) *
			glm::rotate(mat4(1), roll, Directions::Z_AXIS) *
			glm::scale(mat4(1), dimensions);
		mesh->update(transformation);
	}

	Mesh* getMesh() {
		return mesh;
	}

	vec3 getPosition() {
		return position;
	}

	vec3 getDimensions() {
		return dimensions;
	}

	float getYaw() {
		return yaw;
	}

	float getPitch() {
		return pitch;
	}

	float getRoll() {
		return roll;
	}

	void scale(float multiplier) {
		dimensions *= multiplier;
	}

	void scale(vec3 multiplier) {
		dimensions *= multiplier;
	}

	void setHeight(float height) {
		dimensions.y = height;
	}

	void setDimensions(vec3 dimensions) {
		this->dimensions = dimensions;
	}

	void move(vec3 translation) {
		this->position += translation;
	}

	void setPosition(vec3 position) {
		this->position = position;
	}

	void rotate(float yaw, float pitch = 0, float roll = 0) {
		this->yaw += yaw;
		handleAngleOverflow(this->yaw);
		this->pitch += pitch;
		handleAngleOverflow(this->pitch);
		this->roll += roll;
		handleAngleOverflow(this->roll);
	}

	void setRotations(float yaw, float pitch = 0, float roll = 0) {
		this->yaw = yaw;
		handleAngleOverflow(this->yaw);
		this->pitch = pitch;
		handleAngleOverflow(this->pitch);
		this->roll = roll;
		handleAngleOverflow(this->roll);
	}

	void rotateYaw(float yaw) {
		this->yaw += yaw;
		handleAngleOverflow(this->yaw);
	}

	void rotatePitch(float pitch) {
		this->pitch += pitch;
		handleAngleOverflow(this->pitch);
	}

	void rotateRoll(float roll) {
		this->roll += roll;
		handleAngleOverflow(this->roll);
	}

	void setYaw(float yaw) {
		this->yaw = yaw;
		handleAngleOverflow(this->yaw);
	}

	void setPitch(float pitch) {
		this->pitch = pitch;
		handleAngleOverflow(this->pitch);
	}

	void setRoll(float roll) {
		this->roll = roll;
		handleAngleOverflow(this->roll);
	}

private:
	void handleAngleOverflow(float& angle) {
		if (angle > Constants::DOUBLE_PI) {
			angle - int(angle / Constants::DOUBLE_PI) * Constants::HALF_PI;
		} else if (angle < -Constants::DOUBLE_PI) {
			angle - int(angle / Constants::DOUBLE_PI) * Constants::HALF_PI;
		}
	}
};