#pragma once
#include "../NewTrainingFramework/SceneObject.h"
#include "../NewTrainingFramework/GameManager.h"

class Bus :public SceneObject {

public:
	Bus(int _id, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>textures, bool _depthTest) : SceneObject(_id, _position, _rotation, _scale, _model, _shader, textures, _depthTest) {}

	Vector3 getPosition() {
		return position;
	}

	virtual void Key(unsigned char key) {
		


	};

};