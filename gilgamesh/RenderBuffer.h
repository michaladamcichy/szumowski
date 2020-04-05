#pragma once

#include "stdafx.h"
#include "Vertex.h"
#include "Mesh.h"
#include "ErrorHandler.h"

class RenderBuffer {
private:
	uint vao;
	uint vbo;
	uint ebo;

	vector <Vertex> vertices;
	vector <uint> indices;

	int verticesCount = 0;
	int indicesCount = 0;

	int maxVerticesCount = 0;
	int maxIndicesCount = 0;

public:
	RenderBuffer() {}

	RenderBuffer(int maxVerticesCount, int maxIndicesCount) {
		init(maxVerticesCount, maxIndicesCount);
	}

	void init(int maxVerticesCount, int maxIndicesCount) {
		this->maxVerticesCount = maxVerticesCount;
		this->maxIndicesCount = maxIndicesCount;

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);


		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(
			GL_ARRAY_BUFFER,
			maxVerticesCount * sizeof(Vertex),
			nullptr,
			GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			maxIndicesCount * sizeof(uint),
			nullptr,
			GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(vec3)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(vec3) + sizeof(vec2)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 1, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(vec3) + sizeof(vec2) + sizeof(vec3)));
		glEnableVertexAttribArray(3);



		glBindVertexArray(0);

		ErrorHandler::handleErrors();
	}

	void update(vector <Mesh*> meshes) {
		mergeMeshes(meshes, &vertices, &indices);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(
			GL_ARRAY_BUFFER,
			0,
			vertices.size() * sizeof(Vertex),
			&vertices[0]
			//Primitives::getCube()->getVertices().size() * sizeof(Vertex),
			//&Primitives::getCube()->getVertices()[0]
		);
		ErrorHandler::handleErrors();
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferSubData(
			GL_ELEMENT_ARRAY_BUFFER,
			0,
			indices.size() * sizeof(uint),
			&indices[0]
			//Primitives::getCube()->getIndices().size() * sizeof(uint),
			//&Primitives::getCube()->getIndices()[0]
		);
		ErrorHandler::handleErrors();

		glBindVertexArray(0);

		ErrorHandler::handleErrors();
	}

	void render() {
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

private:
	void mergeMeshes(vector <Mesh*>& meshes, vector <Vertex>* vertices, vector <uint>* indices) {
		verticesCount = 0;
		indicesCount = 0;

		for (Mesh* mesh : meshes) {
			verticesCount += mesh->getVertices().size();
			indicesCount += mesh->getIndices().size();
		}

		vertices->clear();
		vertices->reserve(verticesCount);
		indices->clear();
		indices->reserve(indicesCount);

		int offset = 0;
		int index = 0;
		for (Mesh* mesh : meshes) {
			vertices->insert(vertices->end(), mesh->getVertices().begin(), mesh->getVertices().end());
			indices->insert(indices->end(), mesh->getIndices().begin(), mesh->getIndices().end());

			for (int i = index; i < index + mesh->getIndices().size(); i++) {
				(*indices)[i] += offset;
			}
			offset += mesh->getVertices().size();
			index += mesh->getIndices().size();
		}
	}
};