#pragma once
#include "stdafx.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Terrain.h"
#include "SkyBox.h"
#include "Fire.h"
#include <fstream>
#include <sstream>


Camera* SceneManager::getActiveCamera() {
	return cameras[currentCamera];
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
	verifyCollisions();

}

void SceneManager::Key(unsigned char key) {

	for (auto obiect : objects) {
		obiect.second->Key(key);
	}
	
}

void SceneManager::verifyCollisions() {
	
	for (auto collision : collisions) {
		bool colizionat = BoundingBox::verifyCollision(objects[collision.first.first]->getBoundingBox(), objects[collision.first.second]->getBoundingBox());
		if (colizionat) {
			if (isCollided.find(collision.first) != isCollided.end()) {
				for (auto collisionExecutor : collision.second) {
					collisionExecutor->OnCollisionContinuing();
				}
			}
			else {
				isCollided.insert(collision.first);
				for (auto collisionExecutor : collision.second) {
					collisionExecutor->OnCollisionEnter();
				}

			}
		}
		else {
			if (isCollided.find(collision.first) != isCollided.end()) {
				isCollided.erase(collision.first);
				for (auto collisionExecutor : collision.second) {
					collisionExecutor->OnCollisionExit();
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
	cameras.insert(std::make_pair(id, camera));
}

void SceneManager::setActiveCamera(int id) {
	currentCamera = id;
}

void SceneManager::addLight(int id, Light* light) {
	lights.insert(std::make_pair(id, light));
}

void SceneManager::addObject(int id, SceneObject* object) {
	if (objects.find(id) != objects.end()) {
		delete objects[id];
		objects.erase(id);
	}
	objects.insert(std::make_pair(id, object));
}

void SceneManager::setAmbientLight( Vector3 diff, double ratio) {
	ambientLight = new AmbientLight();
	ambientLight->diff = diff;
	ambientLight->spec = ambientLight->diff;
	ambientLight->ratio = ratio;
}
void SceneManager::addCollisionBetween(int object1, int object2, CollisionExecutor* executor) {
	for (auto it = collisions.begin();; it != collisions.end()) {
		if ((it->first.first == object1 && it->first.second == object2) || (it->first.first == object2 && it->first.second == object1)) {
			it->second.push_back(executor);
			return;
		}
	}

	collisions.insert(std::make_pair(std::make_pair(object1, object2), std::vector<CollisionExecutor*>{ executor }));
}

SceneManager::SceneManager() {
	resourceManager = new ResourceManager();
}

void SceneManager::cleanUp() {
	resourceManager->cleanUp();
}

void SceneManager::deleteObject(int id) {
	objectsToBeDeleted.push_back(id);
}

void SceneManager::deleteObjectInternal(int id) {
	delete objects[id];
	objects.erase(id);
	for (auto it = collisions.begin();; it != collisions.end()) {
		if (it->first.first == id || it->first.second == id) {
			for (auto collision : it->second) {
				delete collision;
			}
			it->second.clear();
			it = collisions.erase(it);
		}
		else {
			++it;
		}
	}
}

void SceneManager::deleteObjects() {
	for (auto i : objectsToBeDeleted) {
		deleteObjectInternal(i);
	}
	objectsToBeDeleted.clear();
}

SceneManager::~SceneManager() {
	delete resourceManager;
	deleteObjects();
	for (auto light : lights) {
		delete light.second;
	}
	lights.clear();

	for (auto camera : cameras) {
		delete camera.second;
	}
	cameras.clear();
}