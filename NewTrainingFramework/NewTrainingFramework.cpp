// NewTrainingFramework.cpp : Defines the entry point for the console application.
//
// irina.ciocan@gmail.com

#include "stdafx.h"
#include <string>
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include "Camera.h"
#include <iostream>
#include "ResourceManager.h"
#include "SceneManager.h"

#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include



GLuint vboId;
//GLuint indBuff;
Shaders myShaders;
GLfloat alpha = 0.0f;
//Matrix matrice;
//Camera camera;
GLfloat vitrot = 0.0f;
HWND fereastra;
//int nrVertecsi;
//int nrIndici;
//GLushort* indici;
//Vertex *verticesData;
//GLuint idTextura;
int width;
int height;
int bpp;


int Init ( ESContext *esContext )
{
	ResourceManager::getresourceManager()->Init("../Resources/XML/resourceManager.xml");
	SceneManager::getsceneManager()->Init("../Resources/XML/sceneManager.xml");

	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	
}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SceneManager::getsceneManager()->Draw(esContext);
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);

}

void Update ( ESContext *esContext, float deltaTime )
{
	SceneManager::getsceneManager()->Update(deltaTime);
	SceneManager::getsceneManager()->verificaColiziuni();
	static float contor=0;
	contor += deltaTime;
	static float lim = 0.05f;
	/*if (GetKeyState(VK_LBUTTON) & 0x100 || GetKeyState(VK_LBUTTON) & 0x80) {
		POINT a;
		GetCursorPos(&a);
		ScreenToClient(fereastra, &a);
		if (a.y<0 || a.y>Globals::screenHeight)return;
		if (a.x > 640)vitrot -= 0.5f;
		if (a.x < 640)vitrot += 0.5f;
	}
	if (GetKeyState(VK_RBUTTON) & 0x100 || GetKeyState(VK_RBUTTON) & 0x80) {
		POINT a;
		GetCursorPos(&a);
		ScreenToClient(fereastra, &a);
		if (a.x > 0 && a.x < Globals::screenWidth&&a.y>0 && a.y < Globals::screenHeight)vitrot = 0;
	}*/
	{
	if (contor > lim) {
			SceneManager::getsceneManager()->getActiveCamera()->setDeltaTime(contor);
			SceneManager::getsceneManager()->getActiveCamera()->rotateOy(vitrot);

			contor-=lim;
		}
	}
	

	
	
	
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed) {
		SceneManager::getsceneManager()->Key(key);

		switch (key) {
		case 97:
		case 65: {
			SceneManager::getsceneManager()->getActiveCamera()->MoveOx(-1);
			break;

		}

		case 115:
		case 83: {
			SceneManager::getsceneManager()->getActiveCamera()->MoveOz(1);
			break;
		}

		case 100:
		case 68: {
			SceneManager::getsceneManager()->getActiveCamera()->MoveOx(1);
			break;
		}

		case 113:
		case 81: {
			SceneManager::getsceneManager()->getActiveCamera()->MoveOy(1);
			break;
		}

		case 119:
		case 87: {
			SceneManager::getsceneManager()->getActiveCamera()->MoveOz(-1);
			break;
		}

		case 101:
		case 69: {
			SceneManager::getsceneManager()->getActiveCamera()->MoveOy(-1);
			break;
		}

		case VK_UP: {
			SceneManager::getsceneManager()->getActiveCamera()->rotateOx(1);
			break;
		}
		case VK_DOWN: {
			SceneManager::getsceneManager()->getActiveCamera()->rotateOx(-1);
			break;
		}

		case VK_LEFT: {
			SceneManager::getsceneManager()->getActiveCamera()->rotateOy(1);
			break;
		}

		case VK_RIGHT: {
			SceneManager::getsceneManager()->getActiveCamera()->rotateOy(-1);
			break;
		}

		case 111:
		case 79: {
			SceneManager::getsceneManager()->getActiveCamera()->rotateOz(-1);
			break;
		}

		case 112:
		case 80: {
			SceneManager::getsceneManager()->getActiveCamera()->rotateOz(1);
			break;
		}




		case VK_RBUTTON: {
			vitrot = 0;
			break;
		}
		
		
		}

	}


	
	
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
}

int _tmain(int argc, _TCHAR* argv[])
{

	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 
	
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Nightmare", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	Init(&esContext);
		//return 0;
	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	printf("\n");
	printf("Press any key...\n");
	_getch();

	delete ResourceManager::getresourceManager();
	delete SceneManager::getsceneManager();

	return 0;
}

