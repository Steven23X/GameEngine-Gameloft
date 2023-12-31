#pragma once
#include "SceneObject.h"

class Terrain : public SceneObject
{
	unsigned int nrCells;
	float dimCells, offsetY;
	Vector3 center;
	Vector3 cameraPosition;
	Vector3 heights;
	std::vector<Vertex> vertices;
	std::vector<GLushort> indices;
	Model* newModel;

public:
	void GenerateModel();
	void Update() override;

	Terrain(unsigned idSo, const Vector3& position, const Vector3& rotation, const Vector3& scale, Model* model,
		Shader* shader, const std::vector<Texture*>& textures, bool depthTest, bool isWired,bool isFollowingCamera,Vector3 followingCamera, int nrCells,
		float dimCells, float offsetY,Vector3 heights,Vector3 cameraPosition,FogResource fog,AmbientalLightResource alr);

	~Terrain();

	Vector3 GetHeights() const;
};


