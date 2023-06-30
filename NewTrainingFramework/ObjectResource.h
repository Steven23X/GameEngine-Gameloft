#pragma once
#include "../Utilities/utilities.h"
#include <string>
#include <vector>
struct ObjectResource
{
	unsigned int model;
	unsigned int shader;
	std::string type;
	std::string name;
	std::vector<unsigned int> textures;

	GLfloat posX;
	GLfloat posY;
	GLfloat posZ;

	GLfloat rotationX;
	GLfloat rotationY;
	GLfloat rotationZ;

	GLfloat scaleX;
	GLfloat scaleY;
	GLfloat scaleZ;

	GLfloat r;
	GLfloat g;
	GLfloat b;

	bool isWired;
};
