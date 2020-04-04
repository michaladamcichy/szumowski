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

	GameObject(Mesh* mesh, vec3 position = vec3(0,0,0), vec3 dimensions = vec3(1,1,1), float yaw = 0, float pitch = 0, float roll = 0) {
		init(mesh, position, dimensions, yaw, pitch, roll);
	}

	GameObject(Mesh* mesh, Texture* texture, vec3 position = vec3(0, 0, 0), vec3 dimensions = vec3(1, 1, 1), float yaw = 0, float pitch = 0, float roll = 0) {
		init(mesh, texture, position, dimensions, yaw, pitch, roll);
	}

	void init(Mesh* mesh, vec3 position = vec3(0,0,0), vec3 dimensions = vec3(1,1,1), float yaw = 0, float pitch = 0, float roll = 0) {
		this->mesh = mesh;
		this->position = position;
		this->dimensions = dimensions;
		this->yaw = yaw;
		this->pitch = pitch;
		this->roll = roll;
	}

	void init(Mesh* mesh, Texture* texture, vec3 position = vec3(0, 0, 0), vec3 dimensions = vec3(1, 1, 1), float yaw = 0, float pitch = 0, float roll = 0) {
		this->mesh = mesh;
		this->mesh->setTexture(texture);
		this->position = position;
		this->dimensions = dimensions;
		this->yaw = yaw;
		this->pitch = pitch;
		this->roll = roll;
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