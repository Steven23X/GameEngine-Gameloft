#pragma once
#include "../Utilities/rapidxml.hpp"
#include "ModelResource.h"
#include "ShaderResource.h"
#include "TextureResource.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include <map>
using namespace rapidxml;

// Singleton Class
class ResourceManager
{
	// Resource Manager Instance
	static ResourceManager* spInstance;

	ResourceManager() = default;

	// Maps for Resources
	std::map<unsigned int, ModelResource*> mapModelResource;
	std::map<unsigned int, TextureResource*> mapTextureResource;
	std::map<unsigned int, ShaderResource*> mapShaderResource;

	// Maps for M T S
	std::map<unsigned int, Model*> models;
	std::map<unsigned int, Texture*> textures;
	std::map<unsigned int, Shader*> shaders;

	void LoadXml();

public:
	ResourceManager(const ResourceManager&) = delete; // Disable copy constructor
	ResourceManager& operator=(const ResourceManager&) = delete; // Disable assignment operator

	// Uses LoadXml()
	void Init();

	// Load M T S
	Model* LoadModel(const unsigned& resourceId);
	Texture* LoadTexture(const unsigned int& resourceId);
	Shader* LoadShader(const unsigned int& resourceId);

	// Singleton
	static ResourceManager* GetInstance();
	void InstanceMethod();

	// Destructors
	void FreeResources();
	~ResourceManager();
};
