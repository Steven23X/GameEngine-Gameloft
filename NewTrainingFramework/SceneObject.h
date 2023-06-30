#pragma once

#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include <vector>

class SceneObject
{
protected:
	unsigned int idSo;
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Model* model;
	Shader* shader;
	std::vector<Texture*> textures;
	bool depthTest;
	bool isWired;

public:
	// Constructor
	SceneObject(unsigned idSo, const Vector3& position, const Vector3& rotation, const Vector3& scale, Model* model, Shader* shader, const std::vector<Texture*>& textures, bool depthTest, bool isWired);

	// Getters
	Matrix GetModelMatrix() const;

	// Draw Simple Objects
	void Draw() const;

	// Virtual Methods
	virtual void Update() {};
	// Virtual Destructor
	virtual ~SceneObject() = default;
};

