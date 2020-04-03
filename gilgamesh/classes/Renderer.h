#pragma once

#include "stdafx.h"
#include "Primitives.h"
#include "Mesh.h"

class Renderer {
private:
	static vector <Mesh*> queue;
	
	static uint vao;
	static uint vbo;
	static uint ebo;

	static int bufferSize;
	static int bufferVertexCount;
	static int bufferIndicesCount;

public:
	static void init() {
		Log::print("Initializing Renderer");
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);

		bufferSize = 1000;
		bufferVertexCount = 0;
		bufferIndicesCount = 0;

		prepareBuffer();
		Log::print("DONE");
	}

	static void clear() {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	static void drawColor(vec4 color) {
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	static void addToQueue(Mesh* mesh) {
		queue.push_back(mesh);
	}

	static void render() {
		updateBuffer();
		renderBuffer();
	}

	static void renderBuffer() {
		Log::print("Rendering queue");

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, Primitives::getCube()->getIndices().size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		ErrorHandler::handleErrors();
		Log::print("DONE");
	}

	static void prepareBuffer() {
		Log::print("Preparing buffer");
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);


		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(
			GL_ARRAY_BUFFER,
			bufferSize * sizeof(Vertex),
			nullptr,
			GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			bufferSize * sizeof(uint),
			nullptr,
			GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(vec3)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(vec3) + sizeof(vec2)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);

		ErrorHandler::handleErrors();
		Log::print("DONE");
	}

	static void updateBuffer() {
		Log::print("UPDATING BUFFER");
		
		//if (queue.size() == 0) return; //ALERT
		Mesh* mesh = queue[0];
		bufferVertexCount = mesh->getVertices().size();
		bufferIndicesCount = mesh->getIndices().size();

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(
			GL_ARRAY_BUFFER,
			0,
			Primitives::getCube()->getVertices().size() * sizeof(Vertex),
			&Primitives::getCube()->getVertices()[0]
		);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferSubData(
			GL_ELEMENT_ARRAY_BUFFER,
			0,
			Primitives::getCube()->getIndices().size() * sizeof(uint),
			&Primitives::getCube()->getIndices()[0]
		);

		glBindVertexArray(0);

		queue.clear();

		ErrorHandler::handleErrors();
		Log::print("DONE");
	}
};

vector<Mesh*> Renderer::queue;
int Renderer::bufferSize;
int Renderer::bufferVertexCount;
int Renderer::bufferIndicesCount;
uint Renderer::vao;
uint Renderer::vbo;
uint Renderer::ebo;