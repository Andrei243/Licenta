#pragma once

#include "stdafx.h"
#include "GameManager.h"

GameManager* GameManager::gameManager = NULL;



void GameManager::Init(ESContext* context) {
	sceneNumber = 0;
	scenes[sceneNumber]->Init();
}

void GameManager::Draw(ESContext* context) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	scenes[sceneNumber]->Draw(context);
	eglSwapBuffers(context->eglDisplay, context->eglSurface);
}

void GameManager::Update(ESContext* esContext, float deltaTime) {
	scenes[sceneNumber]->Update(deltaTime);
	scenes[sceneNumber]->verifyCollisions();
}

SceneManager* GameManager::getCurrentScene() {
	return scenes[sceneNumber];
}

void GameManager::setCurrentScene(int id) {
	sceneNumber = id;
}

ResourceManager* GameManager::getCurrentResourceManager() {
	return scenes[sceneNumber]->getResourceManager();
}

GameManager* GameManager::getGameManager() {
	return gameManager;
}

void GameManager::setGameManager(GameManager* manager) {
	GameManager::gameManager = manager;
}

void GameManager::addScene(SceneManager* scene) {
	scenes.push_back(scene);
}


GameManager::GameManager() {
	sceneNumber = 0;
}
void Draw(ESContext* context) {
	GameManager::getGameManager()->Draw(context);
}

void Update(ESContext* context, float deltaTime) {
	POINT a;
	GetCursorPos(&a);
	ScreenToClient(context->hWnd, &a);
	GameManager::getGameManager()->Mouse(Vector2(a.x, a.y), LeftClick, GetKeyState(VK_LBUTTON) & 0x100 || GetKeyState(VK_LBUTTON) & 0x80);
	GameManager::getGameManager()->Mouse(Vector2(a.x, a.y), RightClick, GetKeyState(VK_RBUTTON) & 0x100 || GetKeyState(VK_RBUTTON) & 0x80);
	GameManager::getGameManager()->Update(context, deltaTime);
}

void Key(ESContext* context, unsigned char key, bool bIsPressed) {
	GameManager::getGameManager()->Key(context, key, bIsPressed);
}

void GameManager::Play() {
	esInitContext(&context);
	esCreateWindow(&context, title.c_str(), width, height, ES_WINDOW_RGB| ES_WINDOW_DEPTH);
	Init(&context);
	esRegisterDrawFunc(&context, ::Draw);
	esRegisterUpdateFunc(&context, ::Update);
	esRegisterKeyFunc(&context, ::Key);
	esMainLoop(&context);

	for (SceneManager* sceneManager:scenes) {
		delete sceneManager;
	}
}