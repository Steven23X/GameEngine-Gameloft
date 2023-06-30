#include "stdafx.h"
#include "SceneManager.h"
#include <fstream>
#include <sstream>
#include "ResourceManager.h"
#include "CameraResource.h"
#include "FollowingCameraResource.h"
#include "ObjectResource.h"
#include "TerrainResource.h"
#include "Globals.h"
#include "SkyBox.h"
#include "Terrain.h"

SceneManager* SceneManager::spInstance = nullptr;
int Globals::screenWidth = 0;
int Globals::screenHeight = 0;
const char* Globals::gameName = "";

void SceneManager::LoadWindow()
{
	auto* doc = new xml_document<>();

	std::ifstream file("../Resources/XMLConfig/sceneManager.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc->parse<0>(&content[0]);

	const xml_node<>* sceneManager = doc->first_node();

	// retrieving game name
	const xml_node<>* gameName = sceneManager->first_node("gameName");
	wr.gameName = gameName->value();

	// retrieving window screen size
	const xml_node<>* defaultScreenSize = sceneManager->first_node("defaultScreenSize");
	const xml_node<>* width = defaultScreenSize->first_node("width");
	wr.width = std::stoi(width->value());
	const xml_node<>* height = defaultScreenSize->first_node("height");
	wr.height = std::stoi(height->value());

	// window background color
	const xml_node<>* backgroundColor = sceneManager->first_node("backgroundColor");
	const xml_node<>* r = backgroundColor->first_node("r");
	wr.r = std::stof(r->value());
	const xml_node<>* g = backgroundColor->first_node("g");
	wr.g = std::stof(g->value());
	const xml_node<>* b = backgroundColor->first_node("b");
	wr.b = std::stof(b->value());


	const auto pGameName = const_cast<char*>(wr.gameName.c_str());

	Globals::screenWidth = wr.width;
	Globals::screenHeight = wr.height;
	Globals::gameName = pGameName;

	delete doc;
}

void SceneManager::Controls(unsigned char key, bool bIsPressed)
{
	if (bIsPressed)
	{
		const auto it = cr.find(key);
		if (it != cr.end())
		{
			const std::string& action = it->second;
			if (action == "MOVE_CAMERA_POSITIVE_Z")
			{
				activeCamera->MoveOz(1);
			}
			else if (action == "MOVE_CAMERA_NEGATIVE_Z")
			{
				activeCamera->MoveOz(-1);
			}
			else if (action == "MOVE_CAMERA_NEGATIVE_X")
			{
				activeCamera->MoveOx(-1);
			}
			else if (action == "MOVE_CAMERA_POSITIVE_X")
			{
				activeCamera->MoveOx(1);
			}
			else if (action == "MOVE_CAMERA_POSITIVE_Y")
			{
				activeCamera->MoveOy(1);
			}
			else if (action == "MOVE_CAMERA_NEGATIVE_Y")
			{
				activeCamera->MoveOy(-1);
			}
			else if (action == "ROTATE_CAMERA_NEGATIVE_Y")
			{
				activeCamera->RotateOy(-1);
			}
			else if (action == "ROTATE_CAMERA_POSITIVE_Y")
			{
				activeCamera->RotateOy(1);
			}
		}
	}
}

void SceneManager::Init()
{
	// background color
	glClearColor(wr.r, wr.g, wr.b, 0.0f);

	// opening config file
	auto* doc = new xml_document<>();

	std::ifstream file("../Resources/XMLConfig/sceneManager.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc->parse<0>(&content[0]);

	xml_node<>* sceneManager = doc->first_node();

	// retrieving controls
	xml_node<>* controls = sceneManager->first_node("controls");
	InitControls(controls);


	// retrieving cameras
	xml_node<>* cameras = sceneManager->first_node("cameras");
	xml_node<>* activeCameraId = sceneManager->first_node("activeCamera");
	InitCameras(cameras, activeCameraId);

	//retrieving scene objects
	xml_node<>* objects = sceneManager->first_node("objects");
	InitObjects(objects);

	delete doc;
}

void SceneManager::InitControls(xml_node<>* controls)
{
	for (xml_node<>* x = controls->first_node("control"); x; x = x->next_sibling("control"))
	{
		xml_node<>* key = x->first_node("key");
		xml_node<>* action = x->first_node("action");

		ControlResource newControl;
		newControl.key = key->value()[0];
		newControl.action = action->value();

		cr[newControl.key] = newControl.action;
	}
}

void SceneManager::InitCameras(xml_node<>* cameras, xml_node<>* activeCameraId)
{
	for (xml_node<>* x = cameras->first_node("camera"); x; x = x->next_sibling("camera"))
	{
		xml_attribute<>* id = x->first_attribute("id");

		xml_node<>* type = x->first_node("type");
		xml_node<>* position = x->first_node("position");

		xml_node<>* positionX = position->first_node("x");
		xml_node<>* positionY = position->first_node("y");
		xml_node<>* positionZ = position->first_node("z");

		xml_node<>* target = x->first_node("target");

		xml_node<>* targetX = target->first_node("x");
		xml_node<>* targetY = target->first_node("y");
		xml_node<>* targetZ = target->first_node("z");

		xml_node<>* up = x->first_node("up");

		xml_node<>* upX = up->first_node("x");
		xml_node<>* upY = up->first_node("y");
		xml_node<>* upZ = up->first_node("z");

		xml_node<>* translationSpeed = x->first_node("translationSpeed");
		xml_node<>* rotationSpeed = x->first_node("rotationSpeed");
		xml_node<>* fovCamera = x->first_node("fov");
		xml_node<>* nearCamera = x->first_node("near");
		xml_node<>* farCamera = x->first_node("far");

		CameraResource cameraResource;
		cameraResource.type = type->value();
		cameraResource.posX = std::stof(positionX->value());
		cameraResource.posY = std::stof(positionY->value());
		cameraResource.posZ = std::stof(positionZ->value());

		cameraResource.targetX = std::stof(targetX->value());
		cameraResource.targetY = std::stof(targetY->value());
		cameraResource.targetZ = std::stof(targetZ->value());

		cameraResource.upX = std::stof(upX->value());
		cameraResource.upY = std::stof(upY->value());
		cameraResource.upZ = std::stof(upZ->value());

		cameraResource.translationSpeed = std::stof(translationSpeed->value());
		cameraResource.rotationSpeed = std::stof(rotationSpeed->value());
		cameraResource.fovCamera = std::stof(fovCamera->value());
		cameraResource.nearCamera = std::stof(nearCamera->value());
		cameraResource.farCamera = std::stof(farCamera->value());

		Vector3 v3Position(cameraResource.posX, cameraResource.posY, cameraResource.posZ);
		Vector3 v3Up(cameraResource.upX, cameraResource.upY, cameraResource.upZ);
		Vector3 v3Target(cameraResource.targetX, cameraResource.targetY, cameraResource.targetZ);

		auto newCamera = new Camera(v3Position, v3Target, v3Up, cameraResource.translationSpeed,
		                            cameraResource.rotationSpeed, cameraResource.nearCamera, cameraResource.farCamera,
		                            cameraResource.fovCamera);
		unsigned int idKey = std::stoi(id->value());

		camerasMap[idKey] = newCamera;
	}
	//retrieving active camera
	const unsigned int activeCameraIdValue = std::stoi(activeCameraId->value());

	activeCamera = camerasMap[activeCameraIdValue];
}

void SceneManager::InitObjects(xml_node<>* objects)
{
	for (xml_node<>* x = objects->first_node("object"); x; x = x->next_sibling("object"))
	{
		// General Attributes
		ObjectResource objectResource;
		TerrainResource terrainResource;

		xml_attribute<>* id = x->first_attribute("id");

		xml_node<>* model = x->first_node("model");
		std::string generated = "generated";
		bool hasModel = false;
		if (generated != model->value())
			objectResource.model = std::stoi(model->value()), hasModel = true;

		xml_node<>* shader = x->first_node("shader");
		objectResource.shader = std::stoi(shader->value());

		xml_node<>* type = x->first_node("type");
		objectResource.type = type->value();

		xml_node<>* name = x->first_node("name");
		objectResource.name = name->value();

		xml_node<>* textures = x->first_node("textures");
		if (textures)
		{
			for (xml_node<>* y = textures->first_node("texture"); y; y = y->next_sibling("texture"))
			{
				xml_attribute<>* idTexture = y->first_attribute("id");
				objectResource.textures.push_back(std::stoi(idTexture->value()));
			}
		}

		xml_node<>* position = x->first_node("position");
		if (position)
		{
			xml_node<>* positionX = position->first_node("x");
			xml_node<>* positionY = position->first_node("y");
			xml_node<>* positionZ = position->first_node("z");

			objectResource.posX = std::stof(positionX->value());
			objectResource.posY = std::stof(positionY->value());
			objectResource.posZ = std::stof(positionZ->value());
		}

		xml_node<>* rotation = x->first_node("rotation");
		if (rotation)
		{
			xml_node<>* rotationX = rotation->first_node("x");
			xml_node<>* rotationY = rotation->first_node("y");
			xml_node<>* rotationZ = rotation->first_node("z");

			objectResource.rotationX = std::stof(rotationX->value());
			objectResource.rotationY = std::stof(rotationY->value());
			objectResource.rotationZ = std::stof(rotationZ->value());
		}


		xml_node<>* scale = x->first_node("scale");
		if (scale)
		{
			xml_node<>* scaleX = scale->first_node("x");
			xml_node<>* scaleY = scale->first_node("y");
			xml_node<>* scaleZ = scale->first_node("z");

			objectResource.scaleX = std::stof(scaleX->value());
			objectResource.scaleY = std::stof(scaleY->value());
			objectResource.scaleZ = std::stof(scaleZ->value());
		}

		// object color
		const xml_node<>* objectColor = x->first_node("color");
		bool hasColor = false;
		if (objectColor)
		{
			const xml_node<>* r = objectColor->first_node("r");
			objectResource.r = std::stof(r->value());
			const xml_node<>* g = objectColor->first_node("g");
			objectResource.g = std::stof(g->value());
			const xml_node<>* b = objectColor->first_node("b");
			objectResource.b = std::stof(b->value());
			hasColor = true;
		}

		xml_node<>* wired = x->first_node("wired");
		if (wired)
			objectResource.isWired = true;
		else
			objectResource.isWired = false;

		Vector3 v3Position(objectResource.posX, objectResource.posY, objectResource.posZ);
		Vector3 v3Rotation(objectResource.rotationX, objectResource.rotationY, objectResource.rotationZ);
		Vector3 v3Scale(objectResource.scaleX, objectResource.scaleY, objectResource.scaleZ);
		unsigned int idKey = std::stoi(id->value());

		// terrain attributes
		if (objectResource.type == "terrain")
		{
			xml_node<>* heights = x->first_node("heights");

			xml_node<>* heightR = heights->first_node("r");
			xml_node<>* heightG = heights->first_node("g");
			xml_node<>* heightB = heights->first_node("b");
			terrainResource.heightR = std::stof(heightR->value());
			terrainResource.heightG = std::stof(heightG->value());
			terrainResource.heightB = std::stof(heightB->value());

			xml_node<>* cellNumber = x->first_node("cellNumber");
			terrainResource.cellNumber = std::stoi(cellNumber->value());

			xml_node<>* dimCell = x->first_node("dimCell");
			terrainResource.dimCell = std::stof(dimCell->value());

			xml_node<>* offsetY = x->first_node("offsetY");
			terrainResource.offsetY = std::stof(offsetY->value());
		}

		// following camera attributes
		FollowingCameraResource fcr;
		fcr.ox = fcr.oy = fcr.oz = 0.0f;
		xml_node<>* followingCameraNode = x->first_node("followingCamera");
		if(followingCameraNode)
		{
			fcr.isFollowing = true;
			xml_node<>* ox = followingCameraNode->first_node("ox");
			xml_node<>* oy = followingCameraNode->first_node("ox");
			xml_node<>* oz = followingCameraNode->first_node("ox");

			if (ox)
				fcr.ox = 1.0;
			if (oy)
				fcr.oy = 1.0;
			if (oz)
				fcr.oz = 1.0;
		}
		else
		{
			fcr.isFollowing = false;
		}
		Vector3 followingCamera(fcr.ox,fcr.oy,fcr.oz);


		//Texture Load
		std::vector<Texture*> pTextures ;
		if (objectResource.textures.empty() == false)
		{
			for (unsigned int& texture : objectResource.textures)
			{
				Texture* newTexture = ResourceManager::GetInstance()->LoadTexture(texture);
				pTextures.push_back(newTexture);
			}
		}

		//Model Load
		Model* pModel = nullptr;
		if (hasModel)
		{
			pModel = ResourceManager::GetInstance()->LoadModel(objectResource.model);
			if (hasColor)
			{
				pModel->SetColor(objectResource.r, objectResource.g, objectResource.b);
			}
			else
			{
				pModel->SetColor(0.0f, 0.0f, 0.0f);
			}
		}

		//Shader Load
		Shader* pShader;
		pShader = ResourceManager::GetInstance()->LoadShader(objectResource.shader);

		//Scene Object
		SceneObject* newSceneObject;
		if (objectResource.type == "normal")
			newSceneObject = new SceneObject(idKey, v3Position, v3Rotation, v3Scale, pModel, pShader, pTextures, true,
			                                 objectResource.isWired,fcr.isFollowing,followingCamera);
		else if (objectResource.type == "terrain")
		{
			newSceneObject = new Terrain(idKey, v3Position, v3Rotation, v3Scale, pModel, pShader, pTextures, true,
				objectResource.isWired, fcr.isFollowing, followingCamera, terrainResource.cellNumber,
				terrainResource.dimCell, terrainResource.offsetY,
				Vector3(terrainResource.heightR, terrainResource.heightG,
					terrainResource.heightB), activeCamera->GetPosition());
		}
		else if(objectResource.type =="skybox")
		{
			newSceneObject = new SkyBox(idKey, v3Position, v3Rotation, v3Scale, pModel, pShader, pTextures, true,
				objectResource.isWired,fcr.isFollowing, followingCamera);
		}
		sceneObjects.push_back(newSceneObject);
	}
}

void SceneManager::Draw()
{
	for (const auto& sceneObject : sceneObjects)
	{
		sceneObject->Draw();
	}
}

void SceneManager::Update()
{
	activeCamera->UpdateWorldView();
	for (const auto& sceneObject : sceneObjects)
	{
		sceneObject->Update();
	}
}

SceneManager* SceneManager::GetInstance()
{
	if (!spInstance)
	{
		spInstance = new SceneManager();
	}
	return spInstance;
}

void SceneManager::InstanceMethod()
{
}

void SceneManager::FreeResources()
{
	if (spInstance != nullptr)
	{
		// Delete ControlResources
		/*for (const ControlResource* controlResource : cr) {
			delete controlResource;
		}
		cr.clear();
		*/
		// Delete Cameras
		for (const auto& pair : camerasMap)
		{
			delete pair.second;
		}
		camerasMap.clear();

		// Delete SceneObjects
		for (const SceneObject* sceneObject : sceneObjects)
		{
			delete sceneObject;
		}
		sceneObjects.clear();

		delete spInstance;
		spInstance = nullptr;
	}
}

Camera* SceneManager::GetActiveCamera() const
{
	return activeCamera;
}

SceneManager::~SceneManager()
{
}
