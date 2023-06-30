#include "stdafx.h"
#include "ResourceManager.h"
#include <fstream>
#include <sstream>

ResourceManager* ResourceManager::spInstance = nullptr;

void ResourceManager::LoadXml()
{
	//opening file
	auto* doc = new xml_document<>();
	std::ifstream file("../Resources/XMLConfig/resourceManager.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc->parse<0>(&content[0]);

	xml_node<>* resourceManager = doc->first_node();
	xml_node<>* models = resourceManager->first_node("models");
	xml_node<>* shaders = resourceManager->first_node("shaders");
	xml_node<>* textures = resourceManager->first_node("textures");

	// retrieving models
	for (xml_node<>* x = models->first_node("folder"); x; x = x->next_sibling("folder"))
	{
		xml_attribute<>* path = x->first_attribute("path");

		for (xml_node<>* y = x->first_node("model"); y; y = y->next_sibling("model"))
		{
			xml_attribute<>* id = y->first_attribute("id");
			xml_node<>* modelFile = y->first_node("file");

			auto model = new ModelResource();
			unsigned int idKey;
			model->path = path->value();
			model->file = modelFile->value();
			idKey = std::stoi(id->value());

			mapModelResource[idKey] = model;
		}
	}

	for (xml_node<>* x = shaders->first_node("folder"); x; x = x->next_sibling("folder"))
	{
		xml_attribute<>* path = x->first_attribute("path");

		// retrieving shaders
		for (xml_node<>* y = x->first_node("shader"); y; y = y->next_sibling("shader"))
		{
			xml_attribute<>* id = y->first_attribute("id");
			xml_node<>* vs = y->first_node("vs");
			xml_node<>* fs = y->first_node("fs");

			auto shader = new ShaderResource();
			unsigned int idKey;

			shader->path = path->value();
			shader->vs = vs->value();
			shader->fs = fs->value();
			idKey = std::stoi(id->value());

			mapShaderResource[idKey] = shader;
		}
	}

	for (xml_node<>* x = textures->first_node("folder"); x; x = x->next_sibling("folder"))
	{
		xml_attribute<>* path = x->first_attribute("path");

		//retrieving texture
		for (xml_node<>* y = x->first_node("texture"); y; y = y->next_sibling("texture"))
		{
			xml_attribute<>* id = y->first_attribute("id");
			xml_attribute<>* type = y->first_attribute("type");
			xml_node<>* textureFile = y->first_node("file");
			xml_node<>* minFilter = y->first_node("min_filter");
			xml_node<>* magFilter = y->first_node("mag_filter");
			xml_node<>* wrapS = y->first_node("wrap_s");
			xml_node<>* wrapT = y->first_node("wrap_t");

			auto texture = new TextureResource();
			unsigned int idKey;

			texture->path = path->value();
			texture->type = type->value();
			texture->file = textureFile->value();
			texture->minFilter = minFilter->value();
			texture->magFilter = magFilter->value();
			texture->wrapS = wrapS->value();
			texture->wrapT = wrapT->value();

			idKey = std::stoi(id->value());

			mapTextureResource[idKey] = texture;
		}
	}
	delete doc;
}

void ResourceManager::Init()
{
	LoadXml();
}

ResourceManager* ResourceManager::GetInstance()
{
	if (!spInstance)
	{
		spInstance = new ResourceManager();
	}
	return spInstance;
}

void ResourceManager::InstanceMethod()
{
}

Model* ResourceManager::LoadModel(const unsigned int& resourceId)
{
	if (models.find(resourceId) == models.end())
	{
		auto newModel = new Model(mapModelResource[resourceId]);
		newModel->Load();
		models[resourceId] = newModel;
	}

	return models.at(resourceId);
}

Texture* ResourceManager::LoadTexture(const unsigned int& resourceId)
{
	if (textures.find(resourceId) == textures.end())
	{
		auto newTexture = new Texture(mapTextureResource[resourceId]);
		newTexture->Load();
		textures[resourceId] = newTexture;
	}

	return textures.at(resourceId);
}

Shader* ResourceManager::LoadShader(const unsigned int& resourceId)
{
	if (shaders.find(resourceId) == shaders.end())
	{
		auto newShader = new Shader(mapShaderResource[resourceId]);
		newShader->Load();
		shaders[resourceId] = newShader;
	}

	return shaders.at(resourceId);
}

void ResourceManager::FreeResources()
{
	if (spInstance != nullptr)
	{
		for (const auto& pair : mapModelResource)
		{
			delete pair.second;
		}
		mapModelResource.clear();

		// Free TextureResources
		for (const auto& pair : mapTextureResource)
		{
			delete pair.second;
		}
		mapTextureResource.clear();

		// Free ShaderResources
		for (const auto& pair : mapShaderResource)
		{
			delete pair.second;
		}
		mapShaderResource.clear();

		// Clear models
		for (const auto& pair : models)
		{
			delete pair.second;
		}
		models.clear();

		// Clear textures
		for (const auto& pair : textures)
		{
			delete pair.second;
		}
		textures.clear();

		// Clear shaders
		for (const auto& pair : shaders)
		{
			delete pair.second;
		}
		shaders.clear();

		delete spInstance;
		spInstance = nullptr;
	}
}

ResourceManager::~ResourceManager()
= default;
