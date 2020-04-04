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

	Mesh(vector <Vertex> vertices, vector <uint> indices, Texture* texture = NULL) {
		this->vertices = vertices;
		this->indices = indices;
		this->texture = texture;
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
		if (this->origin == NULL) {
			
		}
		else {

		}
	}
};