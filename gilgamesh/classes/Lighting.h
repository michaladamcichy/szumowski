#pragma once

#include "stdafx.h"

class Lighting {
public:
	Lighting() {}

	Lighting(float ambient, float diffuse, float specular, vec3 direction, vec3 color) {
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->direction = direction;
		this->color = color;
	}

	float ambient;
	float diffuse;
	float specular;

	vec3 direction;
	vec3 color;

	vec3 getDirection() {
		return direction;
	}
};