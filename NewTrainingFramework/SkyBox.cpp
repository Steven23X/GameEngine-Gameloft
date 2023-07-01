#include "stdafx.h"
#include "SkyBox.h"

SkyBox::SkyBox(unsigned idSo, const Vector3& position, const Vector3& rotation, const Vector3& scale, Model* model,
               Shader* shader, const std::vector<Texture*>& textures, bool depthTest, bool isWired, bool isFollowingCamera, Vector3 followingCamera, FogResource fog)
	: SceneObject(idSo, position, rotation, scale, model, shader, textures, depthTest, isWired, isFollowingCamera, followingCamera,fog)
{
	offset = Vector3(position.x, position.y, position.z);
}

void SkyBox::Update()
{
	SceneObject::Update();
}
