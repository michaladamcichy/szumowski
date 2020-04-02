#pragma once

#include "stdafx.h"
#include "Keyboard.h"
#include "Mouse.h"

class InputHandler {
public:
	void handleInput(Keyboard& keyboard, Mouse& mouse);
};