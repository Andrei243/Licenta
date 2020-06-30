#pragma once

#include "Scene1.h"
#include "ExpiringFire.h"

void Scene1::setBusOnFire() {
	Vector3 position = dynamic_cast<Bus*>(objects[numberOfObjects])->getPosition();
	deleteObject(numberOfObjects);
	numberOfObjects++;
	addObject(numberOfObjects, new ExpiringFire(numberOfObjects,Vector3(position.x,position.y,position.z), Vector3(0, 0, 0), Vector3(10, 10, 10), resourceManager->getModel(3), resourceManager->getShader(2), std::vector<Texture*>{resourceManager->getTexture(4), resourceManager->getTexture(3), resourceManager->getTexture(5)}, true, 0.1,2.0f));
	thereIsABus = false;
	ExampleGame::GetExampleGame()->addABus();
}
void Scene1::Init() {
	resourceManager->addModel(1, ceutils::generateModelFromNFG("Resources/Models/Croco.nfg"));
	resourceManager->addModel(2, ceutils::generateModelFromNFG("Resources/Models/bus.nfg"));
	resourceManager->addModel(3, ceutils::generateModelFromNFG("Resources/Models/fire.nfg"));
	resourceManager->addModel(4, ceutils::generateSkyboxModel(500));

	resourceManager->addShader(1, new Shader("Resources/Shaders/TriangleShaderVS.vs", "Resources/Shaders/TriangleShaderFS.fs"));
	resourceManager->addShader(2, new Shader("Resources/Shaders/Fire.vs", "Resources/Shaders/Fire.fs"));
	resourceManager->addShader(3, new Shader("Resources/Shaders/TerrainShaderVS.vs", "Resources/Shaders/TerrainShaderFS.fs"));
	resourceManager->addShader(4, new Shader("Resources/Shaders/SkyboxShaderVS.vs", "Resources/Shaders/SkyboxShaderFS.fs"));

	resourceManager->addTexture(1, ceutils::generateFromPhoto("LINEAR", "LINEAR", "CLAMP_TO_EDGE", "CLAMP_TO_EDGE", "Resources/Textures/Croco.tga"));
	resourceManager->addTexture(2, ceutils::generateFromTGA("LINEAR", "LINEAR", "CLAMP_TO_EDGE", "CLAMP_TO_EDGE", "Resources/Textures/bus.tga"));
	resourceManager->addTexture(3, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/fire3.tga"));
	resourceManager->addTexture(4, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/fire_mask.tga"));
	resourceManager->addTexture(5, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/DisplacementMap.tga"));
	resourceManager->addTexture(6, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/dirt.tga"));
	resourceManager->addTexture(7, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/rock.tga"));
	resourceManager->addTexture(8, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/Grass.tga"));
	resourceManager->addTexture(9, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/Terrain_blend_map.tga"));
	resourceManager->addTexture(10, ceutils::generateSkyboxFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/envMap.tga"));

	resourceManager->addSound(1, "Resources/Sounds/crash.mp3", FMOD_LOOP_OFF);

	r = 2000;
	R = 5000;
	setFogColor(Vector3(0.3f, 0, 0.4f));

	backgroundColor.x = backgroundColor.y = backgroundColor.z = 1;
	addCamera(1, new Camera(Vector3(0, 0, 1), Vector3(0, 0, -1), Vector3(0, 1, 0), 500, 4, 45, 0.2, 100000, GameManager::getGameManager()->getWidth(), GameManager::getGameManager()->getHeight()));
	setActiveCamera(1);
	setAmbientLight(Vector3(1, 1, 1), 0.5);
	addObject(1, new Crocodil(1, Vector3(20, 20, -800), Vector3(0, 0, 0), Vector3(1, 1, 1), resourceManager->getModel(1), resourceManager->getShader(1), std::vector<Texture*>(1, resourceManager->getTexture(1)), true));
	addObject(2, new Terrain(2, Vector3(0, 0, 0), Vector3(1, 1, 1), resourceManager->getShader(3), std::vector<Texture*>{resourceManager->getTexture(6), resourceManager->getTexture(7), resourceManager->getTexture(8), resourceManager->getTexture(9)}, true, 10, 500, -100, Vector3(50, -20, 30)));
	addObject(3, new SkyBox(3, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(50, 50, 50), resourceManager->getModel(4), resourceManager->getShader(4), std::vector<Texture*>{resourceManager->getTexture(10)}, true));

	ExampleGame::GetExampleGame()->resetBuses();
	totalTimeOfPlay = 30.0;
}

void Scene1::addBus() {
	numberOfObjects++;
	addObject(numberOfObjects, new Bus(1, Vector3(20, 20, -800), Vector3(0, 0, 0), Vector3(1, 1, 1), resourceManager->getModel(2), resourceManager->getShader(1), std::vector<Texture*>(1, resourceManager->getTexture(2)), true));
	addCollisionBetween(1, numberOfObjects, new BusCrocoCollider());
	timeFromLastBus = 3.0f;
	thereIsABus = true;
}