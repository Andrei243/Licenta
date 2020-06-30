#pragma once
#include "ExampleGame.h"
#include "../NewTrainingFramework/SceneManager.h"


class Scene2 : public SceneManager {
	int numberOfFires;
	int currentNumberOfFires;
	float secondsPerFire = 1.0f;
	float secondsUntilNextFire = 1.0f;
	float sizeOfFire = 1.0f;
public:
	void Init();
	void Update(float deltaTime) {
		secondsUntilNextFire -= deltaTime;
		for (auto obiect : objects) {
			obiect.second->Update(deltaTime);
		}
		resourceManager->Update();
		if (numberOfFires == currentNumberOfFires) {
			return;
		}
		if (secondsUntilNextFire <= 0) {
			float x = 0.5 - (currentNumberOfFires % 4 -2) * sizeOfFire;
			float y = 0.5 - ((currentNumberOfFires/4) % 4 -2 ) * sizeOfFire;

			addObject(currentNumberOfFires, new Fire(currentNumberOfFires, Vector3(x*60, y*60, -600), Vector3(0, 0, 0), Vector3(5, 5, 5), resourceManager->getModel(1), resourceManager->getShader(1), std::vector<Texture*>{resourceManager->getTexture(2), resourceManager->getTexture(1), resourceManager->getTexture(3)}, true, 0.1));

			currentNumberOfFires++;
			secondsUntilNextFire = 1.0f;
		}

	}

	void Key(unsigned char key) {

		if (key == ' ') {
			GameManager::getGameManager()->setCurrentScene(0);
		}
	}
};