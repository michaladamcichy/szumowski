#pragma once

class Vertex {
public:
	Vertex() {}
	Vertex(vec3 position, vec2 uv, vec3 normal, float texture) {
		this->position = position;
		this->uv = uv;
		this->normal = normal;
		this->texture = texture;
	}
	vec3 position = { 0,0,0 };
	vec2 uv = { 0,0 };
	vec3 normal = { 0,0,0 };
	float texture = 0.0f;
};