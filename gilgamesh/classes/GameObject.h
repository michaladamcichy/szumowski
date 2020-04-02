#pragma once

#include "stdafx.h"
#include "Mesh.h"
#include "Light.h"

class GameObject {
private:
	vec3 position;
	Mesh mesh;
public:
	GameObject() {}

	GameObject(Mesh mesh, vec3 position = vec3(0, 0, 0)) {
		init(mesh, position);
	}

	void init(Mesh mesh, vec3 position = vec3(0,0,0)) {
		this->position = position;
		this->mesh = mesh;
	}

	void draw(Camera& camera, vector <Light>& lights) {
		mesh.draw(camera, lights);
	}

};