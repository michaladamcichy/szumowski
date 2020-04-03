#pragma once

#include "stdafx.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"

class Primitives {
private:
	static Mesh* plane;
	static Mesh* cube;
	static Mesh* quad;

public:
	static void init() {
		plane = new Mesh(
			vector <Vertex> {
				Vertex(vec3(-0.5f, 0.0f, -0.5f), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
				Vertex(vec3(-0.5f, 0.0f, 0.5f), vec2(0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f)),
				Vertex(vec3(0.5f, 0.0f, 0.5f), vec2(1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f)),
				Vertex(vec3(0.5f, 0.0f, -0.5f), vec2(1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f))
			},
			vector <uint> {
				0, 3, 2,
				2, 1, 0
		});

		cube = new Mesh(
			vector <Vertex> {
				Vertex(vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f)),
				Vertex(vec3(0.5f, -0.5f, -0.5f), vec2(1.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f)),
				Vertex(vec3(0.5f, 0.5f, -0.5f), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f)),
				Vertex(vec3(0.5f, 0.5f, -0.5f), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f)),
				Vertex(vec3(-0.5f, 0.5f, -0.5f), vec2(0.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f)),
				Vertex(vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f)),

				Vertex(vec3(-0.5f, -0.5f, 0.5f), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)),
				Vertex(vec3(0.5f, -0.5f, 0.5f), vec2(1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)),
				Vertex(vec3(0.5f, 0.5f, 0.5f), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)),
				Vertex(vec3(0.5f, 0.5f, 0.5f), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)),
				Vertex(vec3(-0.5f, 0.5f, 0.5f), vec2(0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)),
				Vertex(vec3(-0.5f, -0.5f, 0.5f), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)),

				Vertex(vec3(-0.5f, 0.5f, 0.5f), -vec2(1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f)),
				Vertex(vec3(-0.5f, 0.5f, -0.5f), -vec2(1.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f)),
				Vertex(vec3(-0.5f, -0.5f, -0.5f), -vec2(0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f)),
				Vertex(vec3(-0.5f, -0.5f, -0.5f), -vec2(0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f)),
				Vertex(vec3(-0.5f, -0.5f, 0.5f), -vec2(0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f)),
				Vertex(vec3(-0.5f, 0.5f, 0.5f), -vec2(1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f)),

				Vertex(vec3(0.5f, 0.5f, 0.5f), vec2(1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f)),
				Vertex(vec3(0.5f, 0.5f, -0.5f), vec2(1.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f)),
				Vertex(vec3(0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f)),
				Vertex(vec3(0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f)),
				Vertex(vec3(0.5f, -0.5f, 0.5f), vec2(0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f)),
				Vertex(vec3(0.5f, 0.5f, 0.5f), vec2(1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f)),

				Vertex(vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f)),
				Vertex(vec3(0.5f, -0.5f, -0.5f), vec2(1.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f)),
				Vertex(vec3(0.5f, -0.5f, 0.5f), vec2(1.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f)),
				Vertex(vec3(0.5f, -0.5f, 0.5f), vec2(1.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f)),
				Vertex(vec3(-0.5f, -0.5f, 0.5f), vec2(0.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f)),
				Vertex(vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f)),

				Vertex(vec3(-0.5f, 0.5f, -0.5f), vec2(0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f)),
				Vertex(vec3(0.5f, 0.5f, -0.5f), vec2(1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f)),
				Vertex(vec3(0.5f, 0.5f, 0.5f), vec2(1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
				Vertex(vec3(0.5f, 0.5f, 0.5f), vec2(1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
				Vertex(vec3(-0.5f, 0.5f, 0.5f), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
				Vertex(vec3(-0.5f, 0.5f, -0.5f), vec2(0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f))
		},
			vector <uint> {
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 //ALERT
		});

		quad = new Mesh(
			vector <Vertex> {
				Vertex(vec3(1.0f,  1.0f, 0.0f),   vec2(1.0f, 1.0f), vec3(0,0,1)), //ALERT
				Vertex(vec3(1.0f, -1.0f, 0.0f),   vec2(1.0f, 0.0f), vec3(0,0,1)),
				Vertex(vec3(-1.0f, -1.0f, 0.0f),   vec2(0.0f, 0.0f), vec3(0,0,1)),
				Vertex(vec3(-1.0f,  1.0f, 0.0f),   vec2(0.0f, 1.0f), vec3(0,0,1))
				},
			vector <unsigned int> {
				0, 1, 3,
				1, 2, 3
		});
	}

	static Mesh* getPlane() {
		return plane;
	}
	
	static Mesh* getCube() {
		return plane;
	}
	
	static Mesh* getQuad() {
		return plane;
	}

	static void cleanUp() {
		delete plane;
		delete cube;
		delete quad;
	}
};

Mesh* Primitives::plane;
Mesh* Primitives::cube;
Mesh* Primitives::quad;