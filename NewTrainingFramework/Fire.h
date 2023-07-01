#pragma once
#include "SceneObject.h"

class Fire : public SceneObject
{
	float dispMax;
	float currentTime = 0;
	float lastTime = 0;
	float time = 0;

public:
	void Update() override;

	Fire(unsigned idSo, const Vector3& position, const Vector3& rotation, const Vector3& scale, Model* model,
	     Shader* shader, const std::vector<Texture*>& textures, bool depthTest, bool isWired, bool isFollowingCamera,
	     const Vector3& followingCamera, const FogResource& fog, float dispMax);

	~Fire();

	float GetDispMax() const;
	float GetTime() const;
};
