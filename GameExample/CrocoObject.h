#pragma once
#include "../NewTrainingFramework/SceneObject.h"

class Crocodil :public SceneObject {

public:
	Crocodil(int _id,  Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>textures, bool _depthTest) : SceneObject(_id, _position, _rotation, _scale, _model, _shader, textures, _depthTest) {}

	virtual void Key(unsigned char key) {
		Camera* camera = GameManager::getGameManager()->getCurrentScene()->getActiveCamera();
		Vector3 movementForward = camera->gettarget(); //- camera->getposition();
		Vector3 position = camera->getposition();
		movementForward -= position;
		Vector3 moveForward = Vector3(movementForward.x, 0.0f, movementForward.z);
		moveForward.Normalize();
		Vector4 movement = Vector4(moveForward, 1.0f);
		Matrix matRot;
		matRot.SetRotationY(PI / 2);
		Vector4 movementSide = movement * matRot;
		Vector3 moveSide = Vector3(movementSide.x, movementSide.y, movementSide.z);
		moveSide.Normalize();
		moveSide *= 20;
		moveForward *= 20;

		switch (key) {
		case 'U':
		case 'u':
			this->position += moveForward;
			break;

		case 'J':
		case 'j':
			this->position -= moveForward;
			break;

		case 'H':
		case 'h':
			this->position -= moveSide;
			break;

		case 'K':
		case 'k':
			this->position += moveSide;
			break;

		}


	};

};