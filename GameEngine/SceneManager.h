#pragma once
#include "../Utilities/rapidxml.hpp"
#include "WindowResource.h"
#include "ControlResource.h"
#include "Camera.h"
#include "SceneObject.h"
#include <vector>
#include <map>

#include "AmbientalLightResource.h"
#include "FogResource.h"
#include "LightResource.h"
using namespace rapidxml;

class SceneManager {

	static SceneManager* spInstance;
	SceneManager() = default;

	WindowResource wr;
	std::map<char,std::string> cr;
	std::map<unsigned int, Camera*> camerasMap;

	Camera* activeCamera;

	std::vector<SceneObject*> sceneObjects;

	FogResource fg;
	AmbientalLightResource alr;
	LightResource lr;
public:

	SceneManager(const SceneManager&) = delete; // Disable copy constructor
	SceneManager& operator=(const SceneManager&) = delete; // Disable assignment operator

	void LoadWindow();
	void Controls(unsigned char key, bool bIsPressed);

	void Init();
	void InitFog(xml_node<>* fog);
	void InitAmbientalLight(xml_node<>* ambientalLight);
	void InitLight(xml_node<>* light);
	void InitControls(xml_node<>* controls);
	void InitCameras(xml_node<>* cameras, xml_node<>* activeCameraId);
	void InitObjects(xml_node<>* objects);

	void Draw();
	void Update();

	static SceneManager* GetInstance();
	void InstanceMethod();
	void FreeResources();

	Camera* GetActiveCamera() const;
	LightResource GetLr() const;
	~SceneManager();
};