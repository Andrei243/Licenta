#pragma once
#include "stdafx.h"
#include "SkyBox.h"
#include <iostream>
#include "SceneManager.h"

SkyBox::SkyBox(int _id, std::string _type, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>texturi, bool _depthTest, GLint _offsetY) :SceneObject(_id, _type, _position, _rotation, _scale, _model, _shader, texturi, _depthTest) {
	offsetY = _offsetY;
	model = SkyBox::generateModel();

}


void SkyBox::Draw() {
	Camera* camera = SceneManager::getsceneManager()->getActiveCamera();
	if (depthTest) { glEnable(GL_DEPTH_TEST); }

	glActiveTexture(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texturi[0]->getid());
	CommonDraw(camera);
	glBindBuffer(GL_TEXTURE_CUBE_MAP, 0);
	glDisable(GL_DEPTH_TEST);


}

Model* SkyBox::generateModel() {
	Vertex* vertexi = new Vertex[8];
	unsigned short indici[36] = {0,1,2,1,2,3,    //fata de sus
							  0,1,4,1,4,5,    //fata din fata
							  1,3,5,3,5,7,    //fata din dreapta
							  0,2,4,2,4,6,    //fata din stanga
							  2,3,6,6,3,7,    //fata din spate
							  4,6,5,6,5,7};   //fata de jos

	float dimensiune = 1000.0f;
	vertexi[0].pos = Vector3(1000, 1000, 1000);
	vertexi[1].pos = Vector3(-1000, 1000, 1000);
	vertexi[2].pos = Vector3(1000, 1000, -1000);
	vertexi[3].pos = Vector3(-1000, 1000, -1000);
	vertexi[4].pos = Vector3(1000, -1000, 1000);
	vertexi[5].pos = Vector3(-1000, -1000, 1000);
	vertexi[6].pos = Vector3(1000, -1000, -1000);
	vertexi[7].pos = Vector3(-1000, -1000, -1000);
	
	return new Model(vertexi, 8, indici, 36);
}