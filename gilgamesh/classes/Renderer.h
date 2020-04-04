#pragma once

#include "stdafx.h"
#include "Primitives.h"
#include "Mesh.h"
#include "RenderBuffer.h"
#include "TimeManager.h"

class Renderer {
private:
	static vector <Mesh*> queue;
	
	static RenderBuffer buffer;

	static Camera* camera;

	static bool alreadyUpdated;
public:
	static void init() {
		Log::print("Initializing Renderer");
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		

		buffer.init(1000000, 1000000);
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

	static void attachCamera(Camera* camera) {
		Renderer::camera = camera;
	}

	static void addToQueue(Mesh* mesh) {
		queue.push_back(mesh);
	}

	static void render() {
		TimeManager::stopCpu();
		TimeManager::startGpu();

		if (Config::get(DYNAMIC_RENDERING_ENABLED) == true || !alreadyUpdated) {
			buffer.update(queue);
		}
		alreadyUpdated = true;
		queue.clear();

		TimeManager::startRendering();
		Shader::getMainShader()->use();
		Shader::getMainShader()->setUniform("near", Config::get(CAMERA_NEAR_PLANE));
		Shader::getMainShader()->setUniform("far", Config::get(CAMERA_FAR_PLANE));

		Shader::getMainShader()->setUniform("cameraPosition", vec3(0, 0, 1));
		Shader::getMainShader()->setUniform("cameraDirection", vec3(0, 0, -1));
		Shader::getMainShader()->setUniform("cameraTransformation", camera->getTransformation());
		Shader::getMainShader()->setUniform("cameraRotations", camera->getRotations());

		buffer.render();
		TimeManager::stopRendering();

		ErrorHandler::handleErrors();

		TimeManager::stopGpu();
	}
};
	
vector<Mesh*> Renderer::queue;
RenderBuffer Renderer::buffer;
Camera* Renderer::camera;
bool Renderer::alreadyUpdated = false;