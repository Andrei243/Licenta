#pragma once
#include "stdafx.h"
#include "../Utilities/rapidxml.hpp"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Terrain.h"
#include "SkyBox.h"
#include "Fire.h"
#include <fstream>
#include <sstream>


Camera* SceneManager::getActiveCamera() {
	return camere[currentCamera];
}

void SceneManager::Draw(ESContext* escontext) {
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 0.0f);

	for (auto obiect : objects) {
		if (obiect.second->getIsDrawnBySceneManager()) {
			obiect.second->Draw();
		}
	}


}

void SceneManager::Update(float deltaTime) {
	for (auto obiect : objects) {
		obiect.second->Update(deltaTime);
	}
	resourceManager->Update();


}

void SceneManager::Key(unsigned char key) {

	for (auto obiect : objects) {
		obiect.second->Key(key);
	}
	
}

void SceneManager::verifyCollisions() {
	
	for (auto collision : collisions) {
		bool colizionat = Paralelipiped::verificaColiziune(objects[collision.first.first]->getBoundingBox(), objects[collision.first.second]->getBoundingBox());
		if (colizionat) {
			if (isCollided.find(collision.first) != isCollided.end()) {
				for (auto collisionExecutor : collision.second) {
					collisionExecutor.OnCollisionContinuing();
				}
			}
			else {
				isCollided.insert(collision.first);
				for (auto collisionExecutor : collision.second) {
					collisionExecutor.OnCollisionEnter();
				}

			}
		}
		else {
			if (isCollided.find(collision.first) != isCollided.end()) {
				isCollided.erase(collision.first);
				for (auto collisionExecutor : collision.second) {
					collisionExecutor.OnCollisionExit();
				}
			}
		}
	}
}

ResourceManager* SceneManager::getResourceManager() {
	return this->resourceManager;
}
void SceneManager::setBackgroundColor(Vector3 color) {
	backgroundColor = color;
}

void SceneManager::setFogColor(Vector3 color) {
	fogcol = color;
}

void SceneManager::addCamera(int id, Camera* camera) {
	camere.insert(std::make_pair(id, camera));
}

void SceneManager::setActiveCamera(int id) {
	currentCamera = id;
}

void SceneManager::addLight(int id, Light* light) {
	lights.insert(std::make_pair(id, light));
}

void SceneManager::addObject(int id, SceneObject* object) {
	objects.insert(std::make_pair(id, object));
}

void SceneManager::setAmbientLight( Vector3 diff, double ratio) {
	ambientLight = new AmbientLight();
	ambientLight->diff = diff;
	ambientLight->spec = ambientLight->diff;
	ambientLight->ratio = ratio;
}

SceneManager::SceneManager() {
	resourceManager = new ResourceManager();
}

void SceneManager::cleanUp() {
	resourceManager->cleanUp();
}

void SceneManager::deleteObject(int id) {
	delete objects[id];
	objects.erase(id);
	for (auto it = collisions.begin();; it != collisions.end()) {
		if (it->first.first == id || it->first.second == id) {
			it = collisions.erase(it);
		}
		else {
			++it;
		}
	}
}