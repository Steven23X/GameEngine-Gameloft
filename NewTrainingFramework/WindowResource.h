#pragma once

#include "../Utilities/utilities.h"
#include <string>

struct WindowResource {
	// game name
	std::string gameName;

	// screen size
	int width;
	int height;

	// backgroundColor
	GLfloat r;
	GLfloat g;
	GLfloat b;
};