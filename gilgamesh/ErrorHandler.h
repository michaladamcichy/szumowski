#pragma once

#include "stdafx.h"

class ErrorHandler {

	static GLenum lastError;

public:
	static void handleErrors() {
		GLenum error = glGetError();
		if (error != GL_NO_ERROR /*&& error != lastError*/) {
			lastError = error;
			cout << "GL_ERROR code: " << error << '\n';
		}
	}
};

GLenum ErrorHandler::lastError = GL_NO_ERROR;