#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "TextureResource.h"

class Texture
{
	//Pointer to Texture Resource
	TextureResource* tr;

	// Texture attributes
	GLuint tId;

public:
	// Constructors
	Texture();
	explicit Texture(TextureResource* tr);

	// Texture Load
	void Load();

	// Getters
	TextureResource* GetTr() const;
	GLuint GetTId() const;

	// Destructor
	~Texture();
};
