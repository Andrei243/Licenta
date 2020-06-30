#pragma once

#include "../NewTrainingFramework/Fire.h"
#include "../NewTrainingFramework/GameManager.h"

class ExpiringFire : public Fire {
	float expiringTime;
public:
	ExpiringFire(int _id, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>textures, bool _depthTest, float _displmax, float _expTime) :Fire(_id, _position,  _rotation,  _scale,  _model,  _shader, textures,  _depthTest,  _displmax) {
		this->expiringTime = _expTime;
	}

	void Update(float deltaTime) {
		Fire::Update(deltaTime);
		expiringTime -= deltaTime;
		if (expiringTime < 0) {
			GameManager::getGameManager()->getCurrentScene()->deleteObject(this->id);
		}
	}
};