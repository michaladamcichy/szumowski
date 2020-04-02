#pragma once

#include "stdafx.h"
#include "Keyboard.h"
#include "Mouse.h"

class InputHandler {
public:
	virtual void handleInput(Mouse& mouse, Keyboard& keyboard) {}
};