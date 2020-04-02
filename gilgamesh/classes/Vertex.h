
#pragma once

class Vertex {
public:
	Vertex() {}
	Vertex(vec3 position, vec2 uv, vec3 normal) {
		this->position = position;
		this->uv = uv;
		this->normal = normal;
	}
	vec3 position = { 0,0,0 };
	vec2 uv = { 0,0 };
	vec3 normal = { 0,0,0 };
};