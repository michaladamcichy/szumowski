#pragma once

#include "stdafx.h"

class Log {
private:
	static bool enabled;
public:
	static void enable() {
		enabled = true;
	}

	static void disable() {
		enabled = false;
	}

	static void print(string message) {
		if (enabled == true) {
			cout << message << '\n';
		}
	}

	static void print(string message1, string message2) {
		if (enabled == true) {
			cout << message1 << " " << message2 << '\n';
		}
	}

	template <class X, class Y> static void print(pair<X, Y> keyValue) {
		if (enabled == true) {
			cout << keyValue.first << " -> " << keyValue.second << '\n';
		}
	}
};

bool Log::enabled = true;