#include "stdafx.h"
#include "Model.h"
#include "Vertex.h"
#include <sstream>
#include <fstream>

Model::Model(ModelResource* mr) : iboId(0), vboId(0), wiredIboId(0), nrIndex(0), nrIndiciWired(0)
{
	this->mr = mr;
}

Model::Model(): mr(nullptr), iboId(0), vboId(0), wiredIboId(0), nrIndex(0), nrIndiciWired(0)
{
}

Model::~Model()
= default;

// NFG Parser
std::vector<std::string> Model::Split(const std::string& s, const char delimiter) const
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

void Model::Load()
{
	std::ifstream file;
	std::string filename = mr->path + mr->file;
	file.open(filename);
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		auto tokens = Split(line, ':');
		int nVertex = std::stoi(tokens[1]);

		for (int i = 0; i < nVertex; i++)
		{
			Vertex v;
			std::getline(file, line);
			auto strings = Split(line, ';');
			int ok = 1;
			for (const auto& token : strings)
			{
				auto values = Split(token, ':');
				std::string position;
				auto coordsStr = values[1].substr(1, values[1].size() - 2);
				auto coords = Split(coordsStr, ',');
				if (ok)
				{
					position = values[0].substr(6, values[0].size());
					ok = 0;
				}
				if (position == "pos")
				{

					v.pos.x = std::stof(coords[0]);
					v.pos.y = std::stof(coords[1]);
					v.pos.z = std::stof(coords[2]);
				}
				else
					if (values[0] == " norm")
					{

						v.norm.x = std::stof(coords[0]);
						v.norm.y = std::stof(coords[1]);
						v.norm.z = std::stof(coords[2]);
					}
					else
						if (values[0] == " binorm")
						{

							v.binorm.x = std::stof(coords[0]);
							v.binorm.y = std::stof(coords[1]);
							v.binorm.z = std::stof(coords[2]);
						}
						else
							if (values[0] == " tgt")
							{

								v.tgt.x = std::stof(coords[0]);
								v.tgt.y = std::stof(coords[1]);
								v.tgt.z = std::stof(coords[2]);
							}
							else
							{

								v.uv.x = std::stof(coords[0]);
								v.uv.y = std::stof(coords[1]);
							}

			}
			vertexBuffer.push_back(v);
		}

		std::getline(file, line);
		auto tokens1 = Split(line, ':');
		nrIndex = std::stoi(tokens1[1]);

		for (unsigned int i = 0; i < nrIndex / 3; i++)
		{
			std::getline(file, line);
			auto tokensIndex = Split(line, '.');
			auto values = Split(tokensIndex[1], ',');
			indexBuffer.push_back(static_cast<unsigned short>(std::stoi(values[0])));
			indexBuffer.push_back(static_cast<unsigned short>(std::stoi(values[1])));
			indexBuffer.push_back(static_cast<unsigned short>(std::stoi(values[2])));
		}

		for (unsigned int i = 0; i < indexBuffer.size(); i += 3)
		{
			wiredBuffer.push_back(indexBuffer[i]);
			wiredBuffer.push_back(indexBuffer[i + 1]);
			wiredBuffer.push_back(indexBuffer[i + 1]);
			wiredBuffer.push_back(indexBuffer[i + 2]);
			wiredBuffer.push_back(indexBuffer[i + 2]);
			wiredBuffer.push_back(indexBuffer[i]);
		}

		nrIndiciWired = wiredBuffer.size();

	}
}

// Getters
ModelResource* Model::GetMr() const
{
	return mr;
}

GLuint Model::GetIboId() const
{
	return iboId;
}

GLuint Model::GetVboId() const
{
	return vboId;
}

GLuint Model::GetWiredIboId() const
{
	return wiredIboId;
}

GLuint Model::GetNrIndex() const
{
	return nrIndex;
}

GLuint Model::GetNrIndiciWired() const
{
	return nrIndiciWired;
}

std::vector<Vertex> Model::GetVertexBuffer() const
{
	return vertexBuffer;
}

std::vector<GLushort> Model::GetIndexBuffer() const
{
	return indexBuffer;
}

std::vector<GLushort> Model::GetWiredBuffer() const
{
	return wiredBuffer;
}

//Setters
void Model::SetColor(GLfloat r, GLfloat g, GLfloat b)
{
	for (unsigned int i = 0; i < vertexBuffer.size(); i++)
	{
		vertexBuffer[i].color.x = r;
		vertexBuffer[i].color.y = g;
		vertexBuffer[i].color.z = b;
	}
	// creating buffers for vertex, wired and index
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(Vertex), vertexBuffer.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &wiredIboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wiredIboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, wiredBuffer.size() * sizeof(GLushort), wiredBuffer.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(GLushort), indexBuffer.data(), GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::SetIboId(GLuint iboId)
{
	this->iboId = iboId;
}

void Model::SetVboId(GLuint vboId)
{
	this->vboId = vboId;
}

void Model::SetWiredIboId(GLuint wiredIboId)
{
	this->wiredIboId = wiredIboId;
}

void Model::SetNrIndex(GLuint nrIndex)
{
	this->nrIndex = nrIndex;
}

void Model::SetNrIndiciWired(GLuint nrIndiciWired)
{
	this->nrIndiciWired = nrIndiciWired;
}

void Model::SetVertexBuffer(const std::vector<Vertex>& vertexBuffer)
{
	this->vertexBuffer = vertexBuffer;
}

void Model::SetIndexBuffer(const std::vector<GLushort>& indexBuffer)
{
	this->indexBuffer = indexBuffer;
}

void Model::SetWiredBuffer(const std::vector<GLushort>& wiredBuffer)
{
	this->wiredBuffer = wiredBuffer;
}

