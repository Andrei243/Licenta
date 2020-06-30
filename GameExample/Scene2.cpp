#pragma once
#include "Scene2.h"

void Scene2::Init() {
	resourceManager->addModel(1, ceutils::generateModelFromNFG("Resources/Models/fire.nfg"));

	resourceManager->addShader(1, new Shader("Resources/Shaders/Fire.vs", "Resources/Shaders/Fire.fs"));


	resourceManager->addTexture(1, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/fire3.tga"));
	resourceManager->addTexture(2, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/fire_mask.tga"));
	resourceManager->addTexture(3, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/DisplacementMap.tga"));

	setAmbientLight(Vector3(1, 1, 1), 0.5);
	numberOfFires = ExampleGame::GetExampleGame()->getBuses();
	currentNumberOfFires = 0;
	backgroundColor.x = backgroundColor.y = backgroundColor.z = 0.1f;
	addCamera(1, new Camera(Vector3(0, 0, 1), Vector3(0, 0, -1), Vector3(0, 1, 0), 500, 4, 45, 0.2, 100000, GameManager::getGameManager()->getWidth(), GameManager::getGameManager()->getHeight()));

	setActiveCamera(1);
}