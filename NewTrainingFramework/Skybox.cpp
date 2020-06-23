#pragma once
#include "stdafx.h"
#include "SkyBox.h"
#include <iostream>
#include "GameManager.h"



SkyBox::SkyBox(int _id,  Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>textures, bool _depthTest) :SceneObject(_id, _position, _rotation, _scale, _model, _shader, textures, _depthTest) {
	
}
void SkyBox::SpecificDraw(Matrix mat) {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textures[0]->getid());
	glUniform1i(shader->getCubeUn(), 0);
}


void SkyBox::Update(float deltaTime) {
	float y = position.y;
	position = GameManager::getGameManager()->getCurrentScene()->getActiveCamera()->getposition();
	position.y = y;
}

