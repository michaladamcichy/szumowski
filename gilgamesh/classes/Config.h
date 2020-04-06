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
	TIME_MEASUREMENT_FREQUENCY,
	THREADS_COUNT
};

enum ConfigString {
	WINDOW_TITLE,
	TEXTURES_PATH,
	MODELS_PATH,
	SHADERS_PATH
};

enum ConfigBool {
	LOG_ENABLED,
	DYNAMIC_RENDERING_ENABLED,
	MULTITHREADING_ENABLED
};

enum ConfigVec3 {
	GROUND_DIMENSIONS,
	PLAYER_INITIAL_POSITION,
	VIRUS_DIMENSIONS
};

class Config {
private:
	static Config* config;

	unordered_map <ConfigFloat, float> floats;
	unordered_map <ConfigInt, int> ints;
	unordered_map <ConfigString, string> strings;
	unordered_map <ConfigBool, bool> bools;
	unordered_map <ConfigVec3, vec3> vec3s;
	unordered_map <int, int> others;

public:
	static void init() {
		config = new Config();
	}

	static void cleanUp() {
		delete config;
	}

	Config() {
		ints[SCREEN_WIDTH] = 1920;
		ints[SCREEN_HEIGHT] = 1080;
		ints[TOGGLE_KEY_INERTIA] = 100;
		ints[FRAME_DELAY] = 15;
		ints[TIME_MEASUREMENT_FREQUENCY] = 100;
		ints[THREADS_COUNT] = 12;

		strings[WINDOW_TITLE] = "Szumowski";
		strings[TEXTURES_PATH] = "assets/textures/";
		strings[MODELS_PATH] = "assets/models/";
		strings[SHADERS_PATH] = "shaders/";

		floats[MOUSE_SENSITIVITY] = 0.001;
		floats[PLAYER_SPEED] = 0.1;
		floats[PLAYER_BOOST] = 5;
		floats[CAMERA_FOV] = 45;
		floats[CAMERA_NEAR_PLANE] = 0.1;
		floats[CAMERA_FAR_PLANE] = 400;
		floats[CAMERA_MIN_PITCH] = -Constants::HALF_PI + 0.1;
		floats[CAMERA_MAX_PITCH] = Constants::HALF_PI - 0.01;
		floats[CAMERA_SPEED] = 0.1;
		floats[CAMERA_BOOST] = 5;

		bools[LOG_ENABLED] = true;
		bools[DYNAMIC_RENDERING_ENABLED] = true;
		bools[MULTITHREADING_ENABLED] = false;

		vec3s[GROUND_DIMENSIONS] = vec3(1000, 1000, 1000); //ALERT ZROBILEM UNIFORMOWE SKALOWANIE, ZEBY NIE PSUC NORMALNYCH. ALE CHYBA JEST OK
		vec3s[PLAYER_INITIAL_POSITION] = vec3(0, 0, 0);
		vec3s[VIRUS_DIMENSIONS] = vec3(1.0, 1.0, 1.0);

		others[CAMERA_MODE] = CAMERA_PLAYER;
	}

public:
	void setNS(ConfigFloat variableName, float value) {
		floats[variableName] = value;
	}

	void setNS(ConfigInt variableName, int value) {
		ints[variableName] = value;
	}

	void setNS(ConfigString variableName, string value) {
		strings[variableName] = value;
	}

	void setNS(ConfigBool variableName, bool value) {
		bools[variableName] = value;
	}

	void setNS(ConfigVec3 variableName, vec3 value) {
		vec3s[variableName] = value;
	}

	void setNS(int variableName, int value) {
		others[variableName] = value;
	}
	
	//

	float getNS(ConfigFloat variableName) {
		return floats[variableName];
	}

	int getNS(ConfigInt variableName) {
		return ints[variableName];
	}

	string getNS(ConfigString variableName) {
		return strings[variableName];
	}

	vec3 getNS(ConfigVec3 variableName) {
		return vec3s[variableName];
	}

	bool getNS(ConfigBool variableName) {
		return bools[variableName];
	}

	int getNS(int variableName) {
		return others[variableName];
	}

	//

	static void set(ConfigFloat variableName, float value) {
		config->setNS(variableName, value);
	}

	static void set(ConfigInt variableName, int value) {
		config->setNS(variableName, value);
	}

	static void set(ConfigString variableName, string value) {
		config->setNS(variableName, value);
	}

	static void set(ConfigCameraMode variableName, CameraMode value) {
		config->setNS(variableName, value);
	}

	static void set(ConfigBool variableName, bool value) {
		config->setNS(variableName, value);
	}

	static void set(ConfigVec3 variableName, vec3 value) {
		config->setNS(variableName, value);
	}

	static void set(int variableName, int value) {
		config->setNS(variableName, value);
	}
	//

	static float get(ConfigFloat variableName) {
		return config->getNS(variableName);
	}

	static int get(ConfigInt variableName) {
		return config->getNS(variableName);
	}

	static string get(ConfigString variableName) {
		return config->getNS(variableName);
	}

	static bool get(ConfigBool variableName) {
		return config->getNS(variableName);
	}

	static vec3 get(ConfigVec3 variableName) {
		return config->getNS(variableName);
	}

	static int get(int variableName) {
		return config->getNS(variableName);
	}
	 
	void toggleCameraModeNS() {
		others[CAMERA_MODE] == CAMERA_GLOBAL ? others[CAMERA_MODE] = CAMERA_PLAYER : others[CAMERA_MODE] = CAMERA_GLOBAL;
	}

	static void toggleCameraMode() {
		config->toggleCameraModeNS();
	}
};

Config* Config::config;