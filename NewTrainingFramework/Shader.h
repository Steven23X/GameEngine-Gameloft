#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "ShaderResource.h"

class Shader {

	// Pointer to Shader Resource
	ShaderResource* sr;

	// Shader attributes
	GLuint sId, vertexShader, fragmentShader;

	GLint positionAttribute;
	GLint colorAttribute;
	GLint uvAttribute;

	GLint modelmatrixUniform;
	GLint viewmatrixUniform;
	GLint projectionmatrixUniform;

	GLint textureUniform;

public:

	// Constructors
	Shader();
	explicit Shader(ShaderResource* sr);

	// Shader Load
	int Load();

	// Getters
	ShaderResource* GetSr() const;
	GLuint GetSId() const;
	GLuint GetVertexShader() const;
	GLuint GetFragmentShader() const;
	GLint GetPositionAttribute() const;
	GLint GetColorAttribute() const;
	GLint GetUvAttribute() const;
	GLint GetModelmatrixUniform() const;
	GLint GetViewmatrixUniform() const;
	GLint GetProjectionmatrixUniform() const;
	GLint GetTextureUniform() const;

	// Destructor
	~Shader();
};