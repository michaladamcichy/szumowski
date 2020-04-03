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


public:
	static void init() {
		Log::print("Initializing Renderer");
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);

		bufferSize = 100;

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
		renderQueue();
	}

	static void renderQueue() {
		Log::print("Rendering queue");

		Shader::getMainShader()->use();
		Shader::getMainShader()->setUniform("near", Config::get(CAMERA_NEAR_PLANE));
		Shader::getMainShader()->setUniform("far", Config::get(CAMERA_FAR_PLANE));

		Shader::getMainShader()->setUniform("cameraPosition", vec3(0, 0, 1));
		Shader::getMainShader()->setUniform("cameraDirection", vec3(0, 0, -1));

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
		//vector<Vertex> vertices = Primitives::getCube()->getVertices();
		
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

		ErrorHandler::handleErrors();
		Log::print("DONE");
	}
};

vector<Mesh*> Renderer::queue;
int Renderer::bufferSize;
uint Renderer::vao;
uint Renderer::vbo;
uint Renderer::ebo;
