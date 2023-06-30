#pragma once

#include "../Utilities/utilities.h"
#include <string>

struct CameraResource {
	std::string type;

	GLfloat posX;
	GLfloat posY;
	GLfloat posZ;

	GLfloat targetX;
	GLfloat targetY;
	GLfloat targetZ;

	GLfloat upX;
	GLfloat upY;
	GLfloat upZ;

	GLfloat translationSpeed;
	GLfloat rotationSpeed;

	GLfloat fovCamera;
	GLfloat nearCamera;
	GLfloat farCamera;
};