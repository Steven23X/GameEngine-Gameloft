#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "ModelResource.h"
#include <vector>
#include "Vertex.h"

class Model
{
	// Pointer to resource
	ModelResource* mr;

	// Model attributes
	GLuint iboId;
	GLuint vboId;
	GLuint wiredIboId;
	GLuint nrIndex;
	GLuint nrIndiciWired;

	std::vector<Vertex> vertexBuffer;
	std::vector<GLushort> indexBuffer;
	std::vector<GLushort> wiredBuffer;

public:
	// Constructors
	explicit Model(ModelResource* mr);
	Model();

	// NFG Load
	std::vector<std::string> Split(const std::string& s, char delimiter) const;
	void Load();

	// Getters
	ModelResource* GetMr() const;
	GLuint GetIboId() const;
	GLuint GetVboId() const;
	GLuint GetWiredIboId() const;
	GLuint GetNrIndex() const;
	GLuint GetNrIndiciWired() const;
	std::vector<Vertex> GetVertexBuffer() const;
	std::vector<GLushort> GetIndexBuffer() const;
	std::vector<GLushort> GetWiredBuffer() const;

	// Setters
	void SetColor(GLfloat r, GLfloat g, GLfloat b);
	void SetIboId(GLuint iboId);
	void SetVboId(GLuint vboId);
	void SetWiredIboId(GLuint wiredIboId);
	void SetNrIndex(GLuint nrIndex);
	void SetNrIndiciWired(GLuint nrIndiciWired);
	void SetVertexBuffer(const std::vector<Vertex>& vertexBuffer);
	void SetIndexBuffer(const std::vector<GLushort>& indexBuffer);
	void SetWiredBuffer(const std::vector<GLushort>& wiredBuffer);
	// Destructor
	~Model();
};
