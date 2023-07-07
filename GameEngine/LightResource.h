#pragma once
#include "../Utilities/utilities.h"

struct LightResource
{
	int associatedObject;
	GLfloat directionX, directionY, directionZ;
	GLfloat diffuseColorR, diffuseColorG, diffuseColorB;
	GLfloat specularColorR, specularColorG, specularColorB;
	GLfloat specPower;
};