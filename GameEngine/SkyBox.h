#pragma once
#include "SceneObject.h"

class SkyBox : public SceneObject
{
public:
	SkyBox(unsigned idSo, const Vector3& position, const Vector3& rotation, const Vector3& scale, Model* model,
		Shader* shader, const std::vector<Texture*>& textures, bool depthTest, bool isWired, bool isFollowingCamera, Vector3 followingCamera,FogResource fog,AmbientalLightResource alr);
	~SkyBox() override =default;

	void Update() override;
};