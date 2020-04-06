#pragma once

#include "stdafx.h"
#include "ErrorHandler.h"
#include "Shader.h"

//enum TextureType {
//	TEXTURE_SHOTGUN,
//	TEXTURE_GROUND,
//	TEXTURE_SUN,
//	TEXTURE_BUILDING,
//	TEXTURE_VIRUS,
//	TEXTURE_VIRUS_WOUNDED,
//	TEXTURE_FIRE,
//	TEXTURES_COUNT
//};

class Texture
{
private:
	static Texture shotgun;
	static Texture ground;
	static Texture sun;
	static Texture building;
	static Texture virus;
	static Texture virusWounded;
	static Texture fire;
public:
	Texture() {}

	Texture(string path, TextureType type) {
		init(path, type);
	}

	void init(string path, TextureType type)
	{
		this->type = type;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channelsCount, 0);

		if (data) {
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			GLenum format;
			if (channelsCount == 1) {
				format = GL_R;
			}
			else if (channelsCount == 4) {
				format = GL_RGBA;
			}
			else {
				format = GL_RGB;
			}
			try {
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			}
			catch (std::exception e) {
				cout << "Error while creating texture.\n";
			};
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);


			ErrorHandler::handleErrors();

			stbi_image_free(data);

			printInfo();
			Log::print("Texture created");
		}
		else {
			Log::print("Failed to load texture: ", path);
		}
	}

	static void loadTextures() {
		shotgun.init(Config::get(TEXTURES_PATH) + "shotgun.jpg", TEXTURE_SHOTGUN);
		ground.init(Config::get(TEXTURES_PATH) + "ground.jpg", TEXTURE_GROUND);
		sun.init(Config::get(TEXTURES_PATH) + "sun.png", TEXTURE_SUN);
		building.init(Config::get(TEXTURES_PATH) + "building.jpg", TEXTURE_BUILDING);
		virus.init(Config::get(TEXTURES_PATH) + "virusHD.png", TEXTURE_VIRUS);
		virusWounded.init(Config::get(TEXTURES_PATH) + "virusWounded.png", TEXTURE_VIRUS_WOUNDED);
		fire.init(Config::get(TEXTURES_PATH) + "fire.png", TEXTURE_FIRE);

		useTextures();
	}

	static void useTextures() {
		shotgun.use();
		ground.use();
		sun.use();
		building.use();
		virus.use();
		virusWounded.use();
		fire.use();
	}

	void printInfo() {
		Log::print(pair <string, int>("TEXTURE id", id));
	}

	void use()
	{
		glActiveTexture(GL_TEXTURE0 + this->type);
		ErrorHandler::handleErrors();
		glBindTexture(GL_TEXTURE_2D, id);
		ErrorHandler::handleErrors();
	}

	~Texture()
	{
		glDeleteTextures(1, &id);
	}

private:
	uint id = 0;
	TextureType type;
	int width = 0;
	int height = 0;
	int channelsCount = 0;
	std::string path = "";
};

Texture Texture::shotgun;
Texture Texture::ground;
Texture Texture::sun;
Texture Texture::building;
Texture Texture::virus;
Texture Texture::virusWounded;
Texture Texture::fire;
