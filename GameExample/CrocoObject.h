#pragma once
#include "../NewTrainingFramework/SceneObject.h"

class Crocodil :public SceneObject {

public:
	Crocodil(int _id,  Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>textures, bool _depthTest) : SceneObject(_id, _position, _rotation, _scale, _model, _shader, textures, _depthTest) {}

	virtual void Key(unsigned char key) {

		switch (key) {
		case 'U':
		case 'u':
			position.z -= 20;
			break;

		case 'J':
		case 'j':
			position.z += 20;
			break;

		case 'H':
		case 'h':
			position.x += 20;
			break;

		case 'K':
		case 'k':
			position.x -= 20;
			break;

		}


	};

};