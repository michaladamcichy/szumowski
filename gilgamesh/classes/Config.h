#pragma once
#include "stdafx.h"

enum CameraMode {
	CAMERA_PLAYER,
	CAMERA_GLOBAL
};

enum ConfigCameraMode {
	CAMERA_MODE
};

enum ConfigFloat {
	MOUSE_SENSITIVITY,
	PLAYER_SPEED,
	PLAYER_BOOST,
	CAMERA_FOV,
	CAMERA_NEAR_PLANE,
	CAMERA_FAR_PLANE,
	CAMERA_MIN_PITCH,
	CAMERA_MAX_PITCH,
	CAMERA_SPEED,
	CAMERA_BOOST
};

enum ConfigInt {
	SCREEN_WIDTH,
	SCREEN_HEIGHT,
	TOGGLE_KEY_INERTIA,
	FRAME_DELAY,

};

enum ConfigString {
	WINDOW_TITLE,
	TEXTURES_PATH,
	MODELS_PATH,
	SHADERS_PATH
};

enum ConfigBool {
	LOG_ENABLED,
};

enum ConfigVec3 {
	GROUND_DIMENSIONS,
	PLAYER_INITIAL_POSITION
};

class Config {
private:

	unordered_map <ConfigFloat, float> floats;
	unordered_map <ConfigInt, int> ints;
	unordered_map <ConfigString, string> strings;
	unordered_map <ConfigBool, bool> bools;
	unordered_map <ConfigVec3, vec3> vec3s;

	int screenWidth = 1200;
	int screenHeight = 720;
	int toggleKeyInertia = 100;
	int frameDelay = 15;

	string windowTitle = "szumowski";
	string texturesPath = "assets/textures/";
	string modelsPath = "assets/models/";
	string shadersPath = "shaders/";
	
	float mouseSensitivity = 0.001;
	float playerSpeed = 0.1;
	float playerBoost = 5;
	float cameraFov = 45;
	float cameraNearPlane = 0.1;
	float cameraFarPlane = 400;
	float cameraMinPitch = -Constants::HALF_PI + 0.1;
	float cameraMaxPitch = Constants::HALF_PI - 0.01;
	float cameraSpeed = 0.1;
	float cameraBoost = 5;
	
	bool logEnabled = true;
	
	vec3 groundDimensions = vec3(1000, 1000, 1000); //ALERT zrobilem uniformowe skalowanie, zeby nie psuc normalnych
	vec3 playerInitialPosition = vec3(0, 0, 0);

	CameraMode cameraMode = CAMERA_PLAYER;

public:
	void set(ConfigFloat variableName, float value) {
		floats[variableName] = value;
	}

	void set(ConfigInt variableName, int value) {
		ints[variableName] = value;
	}

	void set(ConfigString variableName, string value) {
		strings[variableName] = value;
	}

	void set(ConfigCameraMode variableName, CameraMode value) {
		cameraMode = value;
	}

	void set(ConfigBool variableName, bool value) {
		bools[variableName] = value;
	}

	void set(ConfigVec3 variableName, vec3 value) {
		vec3s[variableName] = value;
	}
	
	float get(ConfigFloat variableName) {
		return floats[variableName];
	}

	int get(ConfigInt variableName) {
		return ints[variableName];
	}

	string get(ConfigString variableName) {
		return strings[variableName];
	}

	CameraMode get(ConfigCameraMode variableName) {
		return cameraMode;
	}

	bool get(ConfigBool variableName) {
		return bools[variableName];
	}
	
	vec3 get(ConfigVec3 variableName) {
		return vec3s[variableName];
	}
	 
	void toggleCameraMode() {
		cameraMode == CAMERA_GLOBAL ? cameraMode = CAMERA_PLAYER : cameraMode = CAMERA_GLOBAL;
	}
};