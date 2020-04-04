#pragma once

#include "stdafx.h"
#include "Mesh.h"
#include "Light.h"

class GameObject {
private:
	Mesh* mesh = NULL;

	vec3 dimensions = vec3(1, 1, 1);
	vec3 position = vec3(0,0,0);
	float yaw = 0;
	float pitch = 0;
	float roll = 0;

public:
	GameObject() {}

	GameObject(Mesh* mesh, vec3 position = vec3(0,0,0)) {
		init(mesh, position);
	}

	void init(Mesh* mesh, vec3 position = vec3(0,0,0)) {
		this->position = position;
		this->mesh = mesh;
	}

	void scale(float multiplier) {
		dimensions *= multiplier;
	}

	void scale(vec3 multiplier) {
		dimensions *= multiplier;
	}

	void setDimensions(vec3 dimensions) {
		this->dimensions = dimensions;
	}

	void move(vec3 translation) {
		this->position += translation;
	}

	void rotate(float yaw, float pitch = 0, float roll = 0) {
		this->yaw += yaw;
		this->pitch += pitch;
		this->roll += roll;
	}

	void setRotations(float yaw, float pitch = 0, float roll = 0) {
		this->yaw = yaw;
		this->pitch = pitch;
		this->roll = roll;
	}

	void rotateYaw(float yaw) {
		this->yaw += yaw;
	}

	void rotatePitch(float pitch) {
		this->pitch += pitch;
	}

	void rotateRoll(float roll) {
		this->roll += roll;
	}

	void setYaw(float yaw) {
		this->yaw = yaw;
	}

	void setPitch(float pitch) {
		this->pitch = pitch;
	}

	void setRoll(float roll) {
		this->roll = roll;
	}
};