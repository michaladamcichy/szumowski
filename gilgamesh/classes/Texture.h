#pragma once

#include "stdafx.h"
#include "Shader.h"
#include "ErrorHandler.h"

enum TextureType
{
	TEXTURE_DIFFUSE,
	TEXTURE_SPECULAR,
	TEXTURE_NORMALS,
};

class Texture
{
public:
	Texture() {}

	Texture(string path, TextureType type = TEXTURE_DIFFUSE) {
		init(path, type);
	}

	void init(string path, TextureType type = TEXTURE_DIFFUSE)
	{
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channelsCount, 0);
		this->type = type;

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

	void printInfo() {
		Log::print(pair <string, int> ("TEXTURE id", id));
		Log::print(pair <string, int> ("TEXTURE type", type));
	}

	void use()
	{
		glActiveTexture(GL_TEXTURE0 + type);
		ErrorHandler::handleErrors();
		glBindTexture(GL_TEXTURE_2D, id);
		ErrorHandler::handleErrors();
	}

	TextureType getType()
	{
		return type;
	}

	~Texture()
	{
		glDeleteTextures(1, &id);
	}

private:
	TextureType type;
	uint id = 0;
	int width = 0;
	int height = 0;
	int channelsCount = 0;
	std::string path = "";
};