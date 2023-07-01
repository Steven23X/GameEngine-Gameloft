#include "stdafx.h"
#include "Fire.h"
#include <ctime>

Fire::Fire(unsigned idSo, const Vector3& position, const Vector3& rotation, const Vector3& scale, Model* model,
	Shader* shader, const std::vector<Texture*>& textures, bool depthTest, bool isWired, bool isFollowingCamera,
	const Vector3& followingCamera, const FogResource& fog, float dispMax) : SceneObject(
		idSo, position, rotation, scale, model, shader, textures, depthTest, isWired, isFollowingCamera,
		followingCamera, fog),
	dispMax(dispMax)
{}

Fire::~Fire()
= default;

void Fire::Update()
{
	currentTime = static_cast<float>(clock()) / CLOCKS_PER_SEC / 2;
	time += (currentTime - lastTime);
	lastTime = currentTime;
	if (time > 1)
	{
		time -= 1;
	}
}

float Fire::GetDispMax() const
{
	return dispMax;
}

float Fire::GetTime() const
{
	return time;
}