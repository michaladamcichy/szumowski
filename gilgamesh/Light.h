#pragma once

#include "stdafx.h"

class Light {
public:
	vec3 position;

	float ambient;
	float diffuse;
	float specular;

	vec3 direction;
	vec3 color;
	
	Light(vec3 position = vec3(0.0, 0.0, 0.0), vec3 direction = Directions::DOWN, vec3 color = Colors::WHITE, float ambient = 1.0, float diffuse = 1.0, float specular = 1.0) {
		init(position, direction, color, ambient, diffuse, specular);
	}

	void init(vec3 position = vec3(0.0, 0.0, 0.0), vec3 direction = Directions::DOWN, vec3 color = Colors::WHITE, float ambient = 1.0, float diffuse = 1.0, float specular = 1.0) {
		this->position = position;
		this->direction = glm::normalize(direction);
		this->color = color;

		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
	}

	vec3 getPosition() {
		return position;
	}

	vec3 getDirection() {
		return direction;
	}

	vec3 getColor() {
		return color;
	}

	float getAmbient() {
		return ambient;
	}

	float getDiffuse() {
		return diffuse;
	}

	float getSpecular() {
		return specular;
	}
};