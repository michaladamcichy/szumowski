#pragma once

#include "stdafx.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

class Primitives {
public:
	static Mesh* cube;

	/*namespace Plane {
		vector <Vertex> vertices{
				Vertex(vec3(-0.5f, 0.0f, -0.5f), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
				Vertex(vec3(-0.5f, 0.0f, 0.5f), vec2(0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f)),
				Vertex(vec3(0.5f, 0.0f, 0.5f), vec2(1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f)),
				Vertex(vec3(0.5f, 0.0f, -0.5f), vec2(1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f))
		};
		vector <uint> indices{
				0, 3, 2,
				2, 1, 0
		};

		vector <Vertex>& getVertices() {
			return vertices;
		}

		vector <uint>& getIndices() {
			return indices;
		}
	}*/

	static void init() {
		vector <Vertex> vertices = {
			Vertex(vec3(-0.5f, -0.5f, -0.5f),  vec2(0.0f,  0.0f), vec3(0.0f,  0.0f, -1.0f)),
			Vertex(vec3(0.5f, -0.5f, -0.5f),  vec2(1.0f,  0.0f), vec3(0.0f,  0.0f, -1.0f)),
			Vertex(vec3(0.5f,  0.5f, -0.5f),  vec2(1.0f,  1.0f), vec3(0.0f,  0.0f, -1.0f)),
			Vertex(vec3(0.5f,  0.5f, -0.5f),  vec2(1.0f,  1.0f), vec3(0.0f,  0.0f, -1.0f)),
			Vertex(vec3(-0.5f,  0.5f, -0.5f),  vec2(0.0f,  1.0f), vec3(0.0f,  0.0f, -1.0f)),
			Vertex(vec3(-0.5f, -0.5f, -0.5f),  vec2(0.0f,  0.0f), vec3(0.0f,  0.0f, -1.0f)),

			Vertex(vec3(-0.5f, -0.5f,  0.5f),  vec2(0.0f,  0.0f), vec3(0.0f,  0.0f,  1.0f)),
			Vertex(vec3(0.5f, -0.5f,  0.5f),  vec2(1.0f,  0.0f), vec3(0.0f,  0.0f, 1.0f)),
			Vertex(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f,  1.0f), vec3(0.0f,  0.0f,  1.0f)),
			Vertex(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f,  1.0f), vec3(0.0f,  0.0f,  1.0f)),
			Vertex(vec3(-0.5f,  0.5f,  0.5f),  vec2(0.0f,  1.0f), vec3(0.0f,  0.0f,  1.0f)),
			Vertex(vec3(-0.5f, -0.5f,  0.5f),  vec2(0.0f,  0.0f), vec3(0.0f,  0.0f,  1.0f)),

			Vertex(vec3(-0.5f,  0.5f,  0.5f), -vec2(1.0f,  0.0f), vec3(1.0f,  0.0f,  0.0f)),
			Vertex(vec3(-0.5f,  0.5f, -0.5f), -vec2(1.0f,  1.0f), vec3(1.0f,  0.0f,  0.0f)),
			Vertex(vec3(-0.5f, -0.5f, -0.5f), -vec2(0.0f,  1.0f), vec3(1.0f,  0.0f,  0.0f)),
			Vertex(vec3(-0.5f, -0.5f, -0.5f), -vec2(0.0f,  1.0f), vec3(1.0f,  0.0f,  0.0f)),
			Vertex(vec3(-0.5f, -0.5f,  0.5f), -vec2(0.0f,  0.0f), vec3(1.0f,  0.0f,  0.0f)),
			Vertex(vec3(-0.5f,  0.5f,  0.5f), -vec2(1.0f,  0.0f), vec3(1.0f,  0.0f,  0.0f)),

			Vertex(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f,  0.0f), vec3(1.0f,  0.0f,  0.0f)),
			Vertex(vec3(0.5f,  0.5f, -0.5f),  vec2(1.0f,  1.0f), vec3(1.0f,  0.0f,  0.0f)),
			Vertex(vec3(0.5f, -0.5f, -0.5f),  vec2(0.0f,  1.0f), vec3(1.0f,  0.0f,  0.0f)),
			Vertex(vec3(0.5f, -0.5f, -0.5f),  vec2(0.0f,  1.0f), vec3(1.0f,  0.0f,  0.0f)),
			Vertex(vec3(0.5f, -0.5f,  0.5f),  vec2(0.0f,  0.0f), vec3(1.0f,  0.0f,  0.0f)),
			Vertex(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f,  0.0f), vec3(1.0f,  0.0f,  0.0f)),

			Vertex(vec3(-0.5f, -0.5f, -0.5f),  vec2(0.0f,  1.0f), vec3(0.0f, -1.0f,  0.0f)),
			Vertex(vec3(0.5f, -0.5f, -0.5f),  vec2(1.0f,  1.0f), vec3(0.0f, -1.0f,  0.0f)),
			Vertex(vec3(0.5f, -0.5f,  0.5f),  vec2(1.0f,  0.0f), vec3(0.0f, -1.0f,  0.0f)),
			Vertex(vec3(0.5f, -0.5f,  0.5f),  vec2(1.0f,  0.0f), vec3(0.0f, -1.0f,  0.0f)),
			Vertex(vec3(-0.5f, -0.5f,  0.5f),  vec2(0.0f,  0.0f), vec3(0.0f, -1.0f,  0.0f)),
			Vertex(vec3(-0.5f, -0.5f, -0.5f),  vec2(0.0f,  1.0f), vec3(0.0f, -1.0f,  0.0f)),

			Vertex(vec3(-0.5f,  0.5f, -0.5f),  vec2(0.0f,  1.0f), vec3(0.0f,  1.0f,  0.0f)),
			Vertex(vec3(0.5f,  0.5f, -0.5f),  vec2(1.0f,  1.0f), vec3(0.0f,  1.0f,  0.0f)),
			Vertex(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f,  0.0f), vec3(0.0f,  1.0f,  0.0f)),
			Vertex(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f,  0.0f), vec3(0.0f,  1.0f,  0.0f)),
			Vertex(vec3(-0.5f,  0.5f,  0.5f),  vec2(0.0f,  0.0f), vec3(0.0f,  1.0f,  0.0f)),
			Vertex(vec3(-0.5f,  0.5f, -0.5f),  vec2(0.0f,  1.0f), vec3(0.0f,  1.0f,  0.0f))
		};

		vector <uint> indices{
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 //ALERT
		};

		cube = new Mesh(vertices, indices);
	}

	//	vector <Vertex>& getVertices() {
	//		return vertices;
	//	}

	//	vector <uint>& getIndices() {
	//		return indices;
	//	}
	//}

	//namespace Quad {
	//	vector <Vertex> vertices{ //ALERT!!
	//	Vertex(vec3(1.0f,  1.0f, 0.0f),   vec2(1.0f, 1.0f), vec3(0,0,1)),
	//	Vertex(vec3(1.0f, -1.0f, 0.0f),   vec2(1.0f, 0.0f), vec3(0,0,1)),
	//	Vertex(vec3(-1.0f, -1.0f, 0.0f),   vec2(0.0f, 0.0f), vec3(0,0,1)),
	//	Vertex(vec3(-1.0f,  1.0f, 0.0f),   vec2(0.0f, 1.0f), vec3(0,0,1))
	//	};
	//	vector <unsigned int> indices = {
	//		0, 1, 3,
	//		1, 2, 3
	//	};

	//	vector <Vertex>& getVertices() {
	//		return vertices;
	//	}

	//	vector <uint>& getIndices() {
	//		return indices;
	//	}
	//}
};


Mesh* Primitives::cube;