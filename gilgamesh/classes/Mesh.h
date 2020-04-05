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

	TextureType texture;

public:
	Mesh() {}

	Mesh(vector <Vertex> vertices, vector <uint> indices, TextureType texture, bool recursion = false) {
		this->vertices = vertices;
		this->indices = indices;
		this->texture = texture;

		updateTexture(texture);

		Log::done();
	}

	Mesh(Mesh* origin, TextureType texture) {
		this->origin = origin;
		this->texture = texture;

		vertices = origin->vertices;
		indices = origin->indices;

		updateTexture(texture);
	}

	void setTexture(TextureType texture) {
		this->texture = texture;
	}

	vector <Vertex>& getVertices() {
		return vertices;
	}

	vector <uint>& getIndices() {
		return indices;
	}

	void updateTexture(TextureType texture) {
		for (auto& vertex : vertices) {
			vertex.texture = texture;
		}
	}

	void update(mat4 transformation) {
		mat3 rotations = mat3(transformation); //ALERT nietestowane
		if (origin == NULL) {
			Log::print("Trying to modify origin!");
			assert(!"Trying to modify origin");
		}
		else {
			for (int i = 0; i < origin->getVertices().size(); i++) {
				vertices[i].position = vec3(transformation * vec4(origin->getVertices()[i].position, 1.0));
				vertices[i].normal = rotations * origin->getVertices()[i].normal; //ALERT nietestowane
			}
		}
	}
};
