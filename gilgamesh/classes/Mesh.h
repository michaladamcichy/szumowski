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
	Shader* shader = NULL;

public:
	Mesh() {}

	Mesh(vector <Vertex> vertices, vector <uint> indices, Texture* texture = NULL, Shader* shader = NULL) {
		this->vertices = vertices;
		this->indices = indices;
		this->texture = texture;
		this->shader = shader;
	}

	Mesh(Mesh* origin, Texture* texture = NULL, Shader* shader = NULL) {
		this->origin = origin;
		this->texture = texture;
		this->shader = shader;

		vertices = origin->vertices;
		indices = origin->indices;
	}

	vector <Vertex>& getVertices() {
		return vertices;
	}

	vector <uint> getIndices() {
		return indices;
	}

	void update(mat4 transformation) {

	}
};