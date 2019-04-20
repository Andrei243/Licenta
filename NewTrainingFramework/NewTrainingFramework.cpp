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
GLuint indBuff;
Shaders myShaders;
GLfloat alpha = 0.0f;
Matrix matrice;
Camera camera;
GLfloat vitrot = 0.0f;
HWND fereastra;
int nrVertecsi;
int nrIndici;
GLushort* indici;
Vertex *verticesData;
GLuint idTextura;
int width;
int height;
int bpp;


int Init ( ESContext *esContext )
{
	/*glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );


	//triangle data (heap)

	FILE* fisierModel = fopen("../Resources/Modele/Woman2.nfg", "r");
	if (fisierModel == NULL)return 0;


	fscanf(fisierModel, "NrVertices: %d", &nrVertecsi);
    verticesData = new Vertex[nrVertecsi];
	int inutil;
	for (int i = 0; i < nrVertecsi; i++) {
		fscanf(fisierModel, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];", &inutil, &verticesData[i].pos.x, &verticesData[i].pos.y, &verticesData[i].pos.z, &verticesData[i].norm.x, &verticesData[i].norm.y, &verticesData[i].norm.z, &verticesData[i].binorm.x, &verticesData[i].binorm.y, &verticesData[i].binorm.z,&verticesData[i].tgt.x, &verticesData[i].tgt.y, &verticesData[i].tgt.z, &verticesData[i].uv.x, &verticesData[i].uv.y);

	}
	
	//buffer object
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, nrVertecsi*sizeof(Vertex), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	fscanf(fisierModel, "\nNrIndices: %d", &nrIndici);
	indici = (unsigned short*)malloc(nrIndici * sizeof(int));
	for (int i = 0; i < nrIndici / 3; i++) {
		fscanf(fisierModel, "%d. %d,%d,%d\n", &inutil, &indici[i * 3], &indici[i * 3 + 1], &indici[i * 3 + 2]);


	}


	glGenBuffers(1, &indBuff);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBuff);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndici * sizeof(unsigned short), indici, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	fclose(fisierModel);
	
	glEnable(GL_DEPTH_TEST);
	glGenTextures(1, &idTextura);
	glBindTexture(GL_TEXTURE_2D, idTextura);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE0, idTextura);

	GLvoid* tga =(GLvoid*) LoadTGA("../Resources/Texturi/Woman2.tga",&width,&height,&bpp);

	if (bpp == 32) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tga);
	}
	else if (bpp == 24) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tga);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	//creation of shaders and program */

	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	
}

void Draw ( ESContext *esContext )
{
	/*glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	

	glUseProgram(myShaders.program);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBuff);

	//xml_document<> doc;

	
	if(myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}


	if (myShaders.rotationUniform != -1) {
		glUniformMatrix4fv(myShaders.rotationUniform, 1, GL_FALSE, (GLfloat*)matrice.m);

	}

	if (myShaders.uvAttribute != -1) {
		glEnableVertexAttribArray(myShaders.uvAttribute);
		glVertexAttribPointer(myShaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(4 * sizeof(Vector3)));
	}

	if (myShaders.TexUniform != -1) {
		glUniform1i(myShaders.TexUniform, 0);
	}
	glBindTexture(GL_TEXTURE_2D, idTextura);

	glDrawElements(GL_TRIANGLES, nrIndici, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindTexture(GL_TEXTURE_2D, 0);


	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );*/
	SceneManager::getsceneManager()->Draw(esContext);
}

void Update ( ESContext *esContext, float deltaTime )
{
	/*static float contor = 0;
	static float lim = 0.05;
	contor += deltaTime;
	if (GetKeyState(VK_LBUTTON) & 0x100 || GetKeyState(VK_LBUTTON) & 0x80) {
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
	}
	if (contor >= lim) {
		camera.setDeltaTime(deltaTime);
		camera.rotateOy(vitrot);
		matrice = camera.getmat();

	

		contor -= lim;
	}
	*/
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	/*if (bIsPressed) {
		switch (key) {
		case 97:
		case 65: {
			camera.MoveOx(-1);
			break;

		}

		case 115:
		case 83: {
			camera.MoveOz(1);
			break;
		}

		case 100:
		case 68: {
			camera.MoveOx(1);
			break;
		}

		case 113:
		case 81: {
			camera.MoveOy(1);
			break;
		}

		case 119:
		case 87: {
			camera.MoveOz(-1);
			break;
		}

		case 101:
		case 69: {
			camera.MoveOy(-1);
			break;
		}

		case VK_UP: {
			camera.rotateOx(1);
			break;
		}
		case VK_DOWN: {
			camera.rotateOx(-1);
			break;
		}

		case VK_LEFT: {
			camera.rotateOy(1);
			break;
		}

		case VK_RIGHT: {
			camera.rotateOy(-1);
			break;
		}

		case 111:
		case 79: {
			camera.rotateOz(-1);
			break;
		}

		case 112:
		case 80: {
			camera.rotateOz(1);
			break;
		}




		case VK_RBUTTON: {
			vitrot = 0;
			break;
		}
		
		
		}

	}


	
	*/
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
}

int _tmain(int argc, _TCHAR* argv[])
{

	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 
	ResourceManager::getresourceManager()->Init("../Resources/XML/resourceManager.xml");
	SceneManager::getsceneManager()->Init("../Resources/XML/sceneManager.xml");

	/*camera = Camera(Vector3(0, 0, -1), Vector3(0, 0, 0));

	matrice = camera.getmat();

	*/ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Nightmare", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	//if ( Init ( &esContext ) != 0 )
		//return 0;
	//fereastra = FindWindow(NULL, "Hello Square");
	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	printf("\n");
	printf("Press any key...\n");
	_getch();
	/*glDeleteBuffers(1, &indBuff);
	glDeleteBuffers(1, &vboId);
	free(indici);
	delete[]verticesData;*/

	std::cout << myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

	return 0;
}

