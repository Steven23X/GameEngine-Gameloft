#include "stdafx.h"
#include "Texture.h"

Texture::Texture()
= default;

Texture::Texture(TextureResource* tr) : tId(0)
{
	this->tr = tr;
}

Texture::~Texture()
= default;

// Texture Load
void Texture::Load()
{
	int width;
	int height;
	int bpp;
	GLint format, type = 0;

	// Set Type
	if (tr->type == "2d")
	{
		type = GL_TEXTURE_2D;
	}
	else if (tr->type == "cube")
		type = GL_TEXTURE_CUBE_MAP;

	glGenTextures(1, &tId);
	glBindTexture(type, tId);

	// Set TexParameteri
	if (tr->minFilter == "LINEAR")
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if (tr->minFilter == "NEAREST")
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	if (tr->magFilter == "LINEAR")
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (tr->magFilter == "NEAREST")
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	if (tr->wrapS == "REPEAT")
		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	if (tr->wrapS == "CLAMP_TO_EDGE")
		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	if (tr->wrapS == "MIRRORED_REPEAT")
		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	if (tr->wrapT == "REPEAT")
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (tr->wrapT == "CLAMP_TO_EDGE")
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	if (tr->wrapT == "MIRRORED_REPEAT")
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// TGA Load
	std::string filename;
	filename = tr->path + tr->file;
	const auto pfilename = const_cast<char*>(filename.c_str());
	const char* pixelArray = LoadTGA(pfilename, &width, &height, &bpp);

	// Set Format
	if (bpp == 24)
		format = GL_RGB;
	else
		format = GL_RGBA;


	if (tr->type == "2d")
	{
		glTexImage2D(type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixelArray);
		//glActiveTexture(GL_TEXTURE0);
		glEnable(GL_DEPTH_TEST);
	}
	else if (tr->type == "cube")
	{
		const int totalTexture = (width / 4) * (bpp / 8);
		auto buff = new char[totalTexture * height / 3];
		int i, j;

		for (i = 0; i < height / 3; i++)
			for (j = 0; j < totalTexture; j++)
				buff[i * totalTexture + j] = pixelArray[i * width * bpp / 8 + (j + totalTexture)];

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE,
		             (GLvoid*)buff);

		for (i = 0; i < height / 3; i++)
			for (j = 0; j < totalTexture; j++)
				buff[i * totalTexture + j] = pixelArray[(i + height / 3) * width * bpp / 8 + j];

		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE,
		             (GLvoid*)buff);

		for (i = 0; i < height / 3; i++)
			for (j = 0; j < totalTexture; j++)
				buff[i * totalTexture + j] = pixelArray[(i + height / 3) * width * bpp / 8 + (j + totalTexture)];

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE,
		             (GLvoid*)buff);

		for (i = 0; i < height / 3; i++)
			for (j = 0; j < totalTexture; j++)
				buff[i * totalTexture + j] = pixelArray[(i + height / 3) * width * bpp / 8 + (j + 2 * totalTexture)];

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE,
		             (GLvoid*)buff);

		for (i = 0; i < height / 3; i++)
			for (j = 0; j < totalTexture; j++)
				buff[i * totalTexture + j] = pixelArray[(i + height / 3) * width * bpp / 8 + (j + 3 * totalTexture)];

		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE,
		             (GLvoid*)buff);

		for (i = 0; i < height / 3; i++)
			for (j = 0; j < totalTexture; j++)
				buff[i * totalTexture + j] = pixelArray[(i + 2 * height / 3) * width * bpp / 8 + (j + totalTexture)];

		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE,
		             (GLvoid*)buff);
		delete[] buff;

	}

	glBindTexture(type, 0);
	delete[] pixelArray;
}

// Getters
TextureResource* Texture::GetTr() const
{
	return tr;
}

GLuint Texture::GetTId() const
{
	return tId;
}
