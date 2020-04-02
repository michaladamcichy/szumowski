#pragma once

#include "stdafx.h"
#include "Light.h"
#include "Camera.h"

class Drawable {
public:
	virtual void draw(Camera& camera, vector <Light> lights) {}
};