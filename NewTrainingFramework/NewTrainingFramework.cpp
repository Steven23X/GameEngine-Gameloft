// Entry point for the console application.

#include "stdafx.h"
#include "../Utilities/utilities.h"
#include <conio.h>
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Globals.h"

int Init(ESContext* esContext)
{
	// Init for Resource
	ResourceManager::GetInstance()->Init();

	// Init for Scene
	SceneManager::GetInstance()->Init();
	return 0;
}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Scene Draw
	SceneManager::GetInstance()->Draw();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{
	// Scene Update
	SceneManager::GetInstance()->Update();
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	// Keyboard Controls
	SceneManager::GetInstance()->Controls(key,bIsPressed);
}

void CleanUp()
{
	// Delete memory on heap

	ResourceManager::GetInstance()->FreeResources();
	SceneManager::GetInstance()->FreeResources();
}

int _tmain(int argc, _TCHAR* argv[])
{
	//memory leaks detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ESContext esContext;
	esInitContext(&esContext);

	// Window Setup
	SceneManager::GetInstance()->LoadWindow();
	esCreateWindow(&esContext, Globals::gameName, Globals::screenWidth, Globals::screenHeight,
		ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);

	esMainLoop(&esContext);

	CleanUp();

	return 0;
}
