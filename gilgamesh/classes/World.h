#pragma once

#include "stdafx.h"
#include "InputHandler.h"
#include "Camera.h"
#include "GameObject.h"
#include "Shader.h"
#include "Mesh.h"
#include "Player.h"
#include "Primitives.h"

class World : public InputHandler {
private:
	Camera globalCamera;
	Player player;
	Mesh* mesh; //ALERT temp
	Texture* texture;
	Shader* shader;

	vector <Light> lights {Light()};

public:
	World() {
		globalCamera = Camera(vec3(0, 10, 10));

		texture = new Texture(Config::get(TEXTURES_PATH) + "sun_diffuse.png");
		shader = new Shader(Config::get(SHADERS_PATH) + "vs.glsl", Config::get(SHADERS_PATH) + "fs.glsl");
		mesh = new Mesh(Primitives::Cube::getVertices(), Primitives::Cube::getIndices(), texture, shader); //alert
	}

	void handleInput(Mouse& mouse, Keyboard& keyboard) {
		if (Config::get(CAMERA_MODE) == CAMERA_GLOBAL) {
			globalCamera.handleInput(mouse, keyboard);
		}
		else {
			player.handleInput(mouse, keyboard);
		}
	}


	void draw() {
		Renderer::addToQueue(mesh);
	}

private:
	Camera& getActiveCamera() {
		if (Config::get(CAMERA_MODE) == CAMERA_GLOBAL) {
			return globalCamera;
		}
		else {
			return player.getCamera();
		}
	}
};
