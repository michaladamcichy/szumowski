#pragma once

#include "stdafx.h"

class TimeManager {
private:
	double static lastEntry;
	double static frameDuration;

public:
	static void handleTime() {
		double time = glfwGetTime();
		frameDuration = time - lastEntry;
		lastEntry = time;
	}

	static double getFrameDuration() {
		return frameDuration;
	}

};

double TimeManager::lastEntry;
double TimeManager::frameDuration;
