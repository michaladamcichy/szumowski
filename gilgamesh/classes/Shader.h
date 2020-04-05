#pragma once

#include "stdafx.h"
#include "Texture.h"
#include "Lighting.h"
#include "ErrorHandler.h"

class Shader {
private:
	uint id;
	static Shader* shader;
public:
	static Shader* getMainShader() {
		return shader;
	}

	static void init() {
		shader = new Shader(Config::get(SHADERS_PATH) + "vs.glsl", Config::get(SHADERS_PATH) + "fs.glsl");
		shader->setTextures();
	}

	Shader() {
	}

	Shader(string vertexShaderPath, string fragmentShaderPath) {
		string vertexShaderCode = "";
		ifstream vertexShaderFile;
		vertexShaderFile.open(vertexShaderPath);
		if (vertexShaderFile.good() == false) {
			cout << "Cannot open " << vertexShaderPath << '\n';
		}
		else {
			while (vertexShaderFile.eof() == false) {
				string line;
				getline(vertexShaderFile, line);
				vertexShaderCode += line + '\n';
			}
		}
		uint vertexId;
		vertexId = glCreateShader(GL_VERTEX_SHADER);

		const char* vertexShaderSource = vertexShaderCode.c_str();
		glShaderSource(vertexId, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexId);

		printCompilationError(vertexId, GL_VERTEX_SHADER);
			ErrorHandler::handleErrors();

		string fragmentShaderCode = "";
		ifstream fragmentShaderFile;
		fragmentShaderFile.open(fragmentShaderPath);
		if (fragmentShaderFile.good() == false) {
			cout << "Cannot open " << fragmentShaderPath << '\n';
		}
		else {
			while (fragmentShaderFile.eof() == false) {
				string line;
				getline(fragmentShaderFile, line);
				fragmentShaderCode += line + '\n';
			}
		}
		uint fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

		const char* fragmentShaderSource = fragmentShaderCode.c_str();
		glShaderSource(fragmentId, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentId);

		printCompilationError(fragmentId, GL_FRAGMENT_SHADER);
		ErrorHandler::handleErrors();

		this->id = glCreateProgram();
		glAttachShader(this->id, vertexId);
		glAttachShader(this->id, fragmentId);
		glLinkProgram(this->id);

		printLinkingError(this->id);

		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);
	}

	void use() {
		glUseProgram(id);
	}

	void setUniform(const string& name, int value) {
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}

	void setUniform(const string& name, uint value) {
		glUniform1ui(glGetUniformLocation(id, name.c_str()), value);
	}

	void setUniform(const string& name, float value) {
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}

	void setUniform(const string& name, bool value) {
		glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
	}

	void setUniform(const string& name, const mat3& value) {
		glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}

	void setUniform(const string& name, const mat4& value) {
		glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}

	void setUniform(const string& name, const vec3& value) {
		glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
	}


	void setUniform(const string& name, int size, int* value) {
		glUniform1iv(glGetUniformLocation(id, name.c_str()), size, value);
	}

	void setLighting(Lighting& lighting) {
		setUniform("ambientLighting", lighting.ambient);
		setUniform("diffuseLighting", lighting.diffuse);
		setUniform("specularLighting", lighting.specular);
		setUniform("lightDirection", lighting.direction);
		setUniform("lightColor", lighting.color);
	}

	void setTextures() {
		int textures[] = {
			TEXTURE_SHOTGUN,
			TEXTURE_GROUND,
			TEXTURE_SUN,
			TEXTURE_BUILDING,
			TEXTURE_VIRUS,
			TEXTURE_VIRUS_WOUNDED,
			TEXTURE_FIRE,
		};

		setUniform("textures", TEXTURES_COUNT, textures);
	}

private:
	void printCompilationError(uint id, int shaderType) {
		char* log = new char[1024];
		int success;

		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (success == false)
		{
			glGetShaderInfoLog(id, 1024, NULL, log);
			cout << (shaderType == GL_VERTEX_SHADER) ? ("VERTEX") : ("FRAGMENT");
			cout << " SHADER COMPILATION ERROR " << log << '\n';
		}

		delete[] log;
	}

	void printLinkingError(uint id) {
		char* log = new char[1024];
		int success;

		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (success == false)
		{
			glGetProgramInfoLog(id, 1024, NULL, log);
			cout << "PROGRAM LINKING ERROR " << log << '\n';
		}

		delete[] log;
	}
};

Shader* Shader::shader;