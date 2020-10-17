#pragma once

#include "stdafx.h"

class TimeManager {
private:
	double static lastEntry;
	double static frameDuration;

	double static rendering;
	double static finalRendering;
	double static gpu;
	double static finalGpu;
	double static cpu;
	double static finalCpu;

	int static frameCounter;

public:
	static void handleTime() {
		double time = glfwGetTime();
		frameDuration = time - lastEntry;
		lastEntry = time;

		if (frameCounter++ == Config::get(TIME_MEASUREMENT_FREQUENCY)+1) {
			frameCounter = 0;
		}
	}

	static double getFrameDuration() {
		return frameDuration;
	}

	static void startRendering() {
		rendering = glfwGetTime();
	}
	
	static void stopRendering() {
		finalRendering += glfwGetTime() - rendering;

		if (frameCounter == Config::get(TIME_MEASUREMENT_FREQUENCY)) {
			Log::print(pair<string, double> ("RND", finalRendering/Config::get(TIME_MEASUREMENT_FREQUENCY)));
			finalRendering = 0;
		}
	}
	
	static void startGpu() {
		gpu = glfwGetTime();
	}
	
	static void stopGpu() {
		finalGpu += glfwGetTime() - gpu;
		
		if (frameCounter == Config::get(TIME_MEASUREMENT_FREQUENCY)) {
			Log::print(pair<string, double> ("GPU", finalGpu/Config::get(TIME_MEASUREMENT_FREQUENCY)));
			finalGpu = 0;
		}
	}
	static void startCpu() {
		cpu = glfwGetTime();
	}
	
	static void stopCpu() {
		finalCpu += glfwGetTime() - rendering;

		if (frameCounter == Config::get(TIME_MEASUREMENT_FREQUENCY)) {
			Log::print(pair<string, double> ("CPU", finalCpu/Config::get(TIME_MEASUREMENT_FREQUENCY)));
			finalCpu = 0;
		}
	}
};

double TimeManager::lastEntry;
double TimeManager::frameDuration;

double TimeManager::rendering;
double TimeManager::finalRendering;

double TimeManager::gpu;
double TimeManager::finalGpu;

double TimeManager::cpu;
double TimeManager::finalCpu;

int TimeManager::frameCounter = 0;

