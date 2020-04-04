#pragma once

#include "stdafx.h"
#include "Drawable.h"
#include "Vertex.h"
#include "ErrorHandler.h"
#include "Camera.h"
#include "Importer.h"
#include "Texture.h"
#include "Shader.h"
#include "MathsUtils.h"
#include "Light.h"

class Mesh : public Drawable {
private:
	Mesh* origin = NULL;

	vector <Vertex> vertices;
	vector <uint> indices;

	Texture* texture = NULL;

public:
	Mesh() {}

	Mesh(vector <Vertex> vertices, vector <uint> indices, Texture* texture = NULL, bool recursion = false) {
		this->vertices = vertices;
		this->indices = indices;
		this->texture = texture;

		//if (recursion == false) {
		//	origin = new Mesh(vertices, indices, NULL, true);
		//}
	}

	Mesh(Mesh* origin, Texture* texture = NULL) {
		this->origin = origin;
		this->texture = texture;

		vertices = origin->vertices;
		indices = origin->indices;
	}

	void setTexture(Texture* texture) {
		this->texture = texture;
	}

	vector <Vertex>& getVertices() {
		return vertices;
	}

	vector <uint>& getIndices() {
		return indices;
	}

	void update(mat4 transformation) {
		mat3 rotations = mat3(transformation); //ALERT nietestowane
		if (this->origin == NULL) {
			/*for (Vertex& vertex : vertices) {
				vertex.position = vec3(transformation * vec4(vertex.position, 1.0));
				vertex.normal = rotations * vertex.normal;
			}*/
			Log::print("Trying to modify origin!");
		}
		else {
			for (int i = 0; i < origin->getVertices().size(); i++) {
				vertices[i].position = vec3(transformation * vec4(origin->getVertices()[i].position, 1.0));
				vertices[i].normal = rotations * origin->getVertices()[i].normal; //ALERT nietestowane
			}
		}
	}
};
