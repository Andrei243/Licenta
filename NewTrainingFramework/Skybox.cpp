#pragma once
#include "stdafx.h"
#include "SkyBox.h"
#include <iostream>
#include "GameManager.h"



SkyBox::SkyBox(int _id, std::string _type, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>texturi, bool _depthTest) :SceneObject(_id, _type, _position, _rotation, _scale, _model, _shader, texturi, _depthTest) {
	
}


void SkyBox::Draw() {
	Camera* camera = GameManager::getGameManager()->getCurrentScene()->getActiveCamera();
	if (depthTest) { glEnable(GL_DEPTH_TEST); }
	glUseProgram(shader->getid());




	GLuint vboId, indBuff, idTextura;
	GLint nrIndici;
	nrIndici = model->getnrIndici();
	vboId = model->getid();
	indBuff = model->getindid();
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBuff);
	Matrix matrice;
	Matrix translatie, rotatie, rotatiex, rotatiey, rotatiez, scalare;
	translatie.SetTranslation(position);
	rotatiex.SetRotationX(rotation.x);
	rotatiey.SetRotationY(rotation.y);
	rotatiez.SetRotationZ(rotation.z);
	scalare.SetScale(scale);
	rotatie = rotatiex * rotatiey*rotatiez;
	matrice = scalare * rotatie*translatie;
	matrice = matrice * camera->getmat();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texturi[0]->getid());
	glUniform1i(shader->getCubeUn(), 0);

	if (shader->getPosAtt() != -1)
	{
		glEnableVertexAttribArray(shader->getPosAtt());
		glVertexAttribPointer(shader->getPosAtt(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}


	if (shader->getRotAtt() != -1) {
		glUniformMatrix4fv(shader->getRotAtt(), 1, GL_FALSE, (GLfloat*)matrice.m);

	}

	if (shader->getUvAtt() != -1) {
		glEnableVertexAttribArray(shader->getUvAtt());
		glVertexAttribPointer(shader->getUvAtt(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(4 * sizeof(Vector3)));
	}


	glDrawElements(GL_TRIANGLES, nrIndici, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_TEXTURE_2D, 0);

	glBindBuffer(GL_TEXTURE_CUBE_MAP, 0);
	glDisable(GL_DEPTH_TEST);


}

void SkyBox::Update(float deltaTime) {
	float y = position.y;
	position = GameManager::getGameManager()->getCurrentScene()->getActiveCamera()->getposition();
	position.y = y;
}


Paralelipiped SkyBox::setBoundTag(Paralelipiped par) {
	par.tag = "skybox";
	return par;
}