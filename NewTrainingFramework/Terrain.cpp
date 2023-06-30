#include "stdafx.h"
#include "Terrain.h"
#include "SceneManager.h"

Terrain::Terrain(unsigned idSo, const Vector3& position, const Vector3& rotation, const Vector3& scale, Model* model,
                 Shader* shader, const std::vector<Texture*>& textures, bool depthTest, bool isWired, int nrCells, float dimCells,
                 float offsetY, Vector3 heights, Vector3 cameraPosition) : SceneObject(idSo, position, rotation, scale, model,
                                                                                       shader, textures, depthTest, isWired),
                                                                           nrCells(nrCells),
                                                                           dimCells(dimCells),
                                                                           offsetY(offsetY),
                                                                           cameraPosition(cameraPosition),
                                                                           heights(heights)
{
	GenerateModel();
}


Terrain::~Terrain()
{
	delete newModel;
}

Vector3 Terrain::GetHeights() const
{
	return heights;
}

void Terrain::GenerateModel()
{
	Vector3 currentPos;

	center.x = cameraPosition.x;
	center.y = offsetY;
	center.z = cameraPosition.z;


	std::vector<std::vector<unsigned short>> indicesCount(nrCells + 1, std::vector<unsigned short>(nrCells + 1));
	unsigned short k = 0;


	for (unsigned int i = 0; i < nrCells + 1; i++)
	{
		currentPos.z = center.z + nrCells / 2 * dimCells - i * dimCells;

		for (unsigned int j = 0; j < nrCells + 1; j++)
		{
			currentPos.x = center.x - nrCells / 2 * dimCells + j * dimCells;

			Vertex newVertex;
			newVertex.pos.x = currentPos.x;
			newVertex.pos.y = center.y;
			newVertex.pos.z = currentPos.z;
			newVertex.norm.x = 0;
			newVertex.norm.y = 1;
			newVertex.norm.z = 0;
			newVertex.binorm.x = 0;
			newVertex.binorm.y = 1;
			newVertex.binorm.z = 0;
			newVertex.tgt.x = 0;
			newVertex.tgt.y = 1;
			newVertex.tgt.z = 0;
			newVertex.uv.x = static_cast<float>(i);
			newVertex.uv.y = static_cast<float>(j);

			//uv Blend
			newVertex.uv2.x = static_cast<float>(i) / static_cast<float>(nrCells);
			newVertex.uv2.y = static_cast<float>(j) / static_cast<float>(nrCells);
			vertices.push_back(newVertex);

			indicesCount[i][j] = k++;

		}
	}

	for (unsigned int i = 0; i < nrCells; i++)
	{
		for (unsigned int j = 0; j < nrCells; j++)
		{

			indices.push_back(indicesCount[i][j]);
			indices.push_back(indicesCount[i][j + 1]);
			indices.push_back(indicesCount[i + 1][j]);

			indices.push_back(indicesCount[i][j + 1]);
			indices.push_back(indicesCount[i + 1][j]);
			indices.push_back(indicesCount[i + 1][j + 1]);

		}
	}

	GLuint vboId, iboId;
	newModel = new Model();
	glGenBuffers(1, &vboId);
	newModel->SetVboId(vboId);
	newModel->SetVertexBuffer(vertices);
	glBindBuffer(GL_ARRAY_BUFFER, newModel->GetVboId());
	glBufferData(GL_ARRAY_BUFFER, newModel->GetVertexBuffer().size() * sizeof(Vertex), newModel->GetVertexBuffer().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	newModel->SetIboId(iboId);
	newModel->SetIndexBuffer(indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newModel->GetIboId());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, newModel->GetIndexBuffer().size() * sizeof(GLushort), newModel->GetIndexBuffer().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	newModel->SetNrIndex(indices.size());
	newModel->SetColor(0.0, 0.0, 1.0);
	model = newModel;
}

void Terrain::Update()
{

	int i;
	cameraPosition = SceneManager::GetInstance()->GetActiveCamera()->GetPosition();

	if (abs(cameraPosition.x - center.x) > dimCells)
	{
		if (cameraPosition.x > center.x)
		{
			for (i = 0; i < vertices.size(); i++)
			{
				vertices[i].pos.x += dimCells;
				vertices[i].uv2.y += 1 / (float)nrCells;
			}

			center.x += dimCells;
		}
		else
		{
			for (i = 0; i < vertices.size(); i++)
			{
				vertices[i].pos.x -= dimCells;
				vertices[i].uv2.y -= 1 / (float)nrCells;
			}

			center.x -= dimCells;
		}
	}

	if (abs(cameraPosition.z - center.z) > dimCells)
	{
		if (cameraPosition.z > center.z)
		{
			for (i = 0; i < vertices.size(); i++)
			{
				vertices[i].pos.z += dimCells;
				vertices[i].uv2.x -= 1 / (float)nrCells;
			}

			center.z += dimCells;
		}
		else
		{
			for (i = 0; i < vertices.size(); i++)
			{
				vertices[i].pos.z -= dimCells;
				vertices[i].uv2.x += 1 / (float)nrCells;
			}

			center.z -= dimCells;
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, model->GetVboId());
	glBufferData(GL_ARRAY_BUFFER, model->GetVertexBuffer().size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
