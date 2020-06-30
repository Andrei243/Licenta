#pragma once
#include "../NewTrainingFramework/GameManager.h"
#include "../NewTrainingFramework/SceneManager.h"
#include "../NewTrainingFramework/Terrain.h"
#include "../NewTrainingFramework/SkyBox.h"
#include "../NewTrainingFramework/Fire.h"
#include "CrocoObject.h"
#include "Bus.h"
#include "BusCrocoCollider.h"

class BusCrocoCollider;

class Scene1 :public SceneManager {
	int numberOfObjects = 3;
	bool thereIsABus = false;
	float timeFromLastBus = 2.0f;
	float totalTimeOfPlay;
public:
	void Init();

	void Update(float deltaTime) {
		totalTimeOfPlay -= deltaTime;
		

		for (auto obiect : objects) {
			obiect.second->Update(deltaTime);
		}
		resourceManager->Update();
		this->verifyCollisions();
		if (!thereIsABus) {
			timeFromLastBus -= deltaTime;
			if (timeFromLastBus < 0) {
				addBus();
			}
		}
		deleteObjects();
		if (totalTimeOfPlay <= 0) {
			GameManager::getGameManager()->setCurrentScene(1);
		}
	}

	void addBus();

	void setBusOnFire();

};