#pragma once
#include "stdafx.h"
#include "GameManager.h"
#include <string>
#include "../Utilities/Vertex.h"
#include "../Utilities/utilities.h"
#include "../Utilities/Shader.h"
#include "../Utilities/Model.h"
#include "../Utilities/Texture.h"
#include <vector>
#include "SceneObject.h"

SceneObject::SceneObject(int _id,std::string _type, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*> _texturi, bool _depthTest) {
	id = _id;
	type = _type;
	position = _position;
	rotation = _rotation;
	scale = _scale;
	model = _model;
	shader = _shader;
	texturi = _texturi;
	depthTest = _depthTest;
	isDrawnBySceneManager = true;
}

int fromlighttyetoint(tip_lumina tip) {
	switch(tip) {
	case point:
		return 1;
	case directional:
		return 2;
	case spotlight:
		return 3;
	}
}

void SceneObject::setUndrawnBySceneManager() {
	isDrawnBySceneManager = false;
}

void SceneObject::setDrawnBySceneManager() {
	isDrawnBySceneManager = true;
}

bool SceneObject::getIsDrawnBySceneManager() {
	return isDrawnBySceneManager;
}

void SceneObject::Draw(Matrix mat) {
	Camera* camera = GameManager::getGameManager()->getCurrentScene()->getActiveCamera();
	if (depthTest) { glEnable(GL_DEPTH_TEST); }
	glUseProgram(shader->getid());
	SpecificDraw(mat);
	SceneManager* sceneManager = GameManager::getGameManager()->getCurrentScene();
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
	rotatie = rotatiex * rotatiey * rotatiez;
	matrice = scalare * rotatie * translatie;
	Matrix model = matrice * mat;
	matrice = matrice * camera->getmat();
	for (unsigned int i = 0; i < texturi.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texturi[i]->getid());
		if (shader->getTexUn()[i] != -1) {
			glUniform1i(shader->getTexUn()[i], i);
		}
	}

	if (shader->getModUn() != -1) {
		glUniformMatrix4fv(shader->getModUn(), 1, GL_FALSE, (GLfloat*)model.m);
	}

	if (shader->getPosAtt() != -1)
	{
		glEnableVertexAttribArray(shader->getPosAtt());
		glVertexAttribPointer(shader->getPosAtt(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}


	if (shader->getRotAtt() != -1) {
		glUniformMatrix4fv(shader->getRotAtt(), 1, GL_FALSE, (GLfloat*)matrice.m);

	}
	if (shader->getNormAtt() != -1) {
		glEnableVertexAttribArray(shader->getNormAtt());
		glVertexAttribPointer(shader->getNormAtt(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));

	}


	if (shader->getUvAtt() != -1) {
		glEnableVertexAttribArray(shader->getUvAtt());
		glVertexAttribPointer(shader->getUvAtt(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(4 * sizeof(Vector3)));
	}
	if (shader->getFogUn()[0] != -1) {
		glUniform1f(shader->getFogUn()[0], sceneManager->r);
	}
	if (shader->getFogUn()[1] != -1) {
		glUniform1f(shader->getFogUn()[1], sceneManager->R);
	}
	if (shader->getFogUn()[2] != -1) {
		glUniform3f(shader->getFogUn()[2], sceneManager->fogcol.x, sceneManager->fogcol.y, sceneManager->fogcol.z);
	}

	Vector3 camerapos = sceneManager->getActiveCamera()->getposition();
	if (shader->getCamUn() != -1) {
		glUniform3f(shader->getCamUn(), camerapos.x, camerapos.y, camerapos.z);
	}

	if (shader->getRatio() != -1) {
		glUniform1f(shader->getRatio(), sceneManager->ratio());
	}
	if (shader->getAmbColor() != -1) {
		glUniform3f(shader->getAmbColor(), sceneManager->ambientColor().x, sceneManager->ambientColor().y, sceneManager->ambientColor().z);

	}

	for (int i = 0; i < lights.size() && i < 5; i++) {
		Light* lumina = sceneManager->getLight(lights[i]);
		glUniform1i(shader->getTypes()[i], fromlighttyetoint(lumina->tip));
		glUniform3f(shader->getSpecs()[i], lumina->spec.x, lumina->spec.y, lumina->spec.z);
		glUniform3f(shader->getDiff()[i], lumina->diff.x, lumina->diff.y, lumina->diff.z);

		if (lumina->tip == point) {
			glUniform3f(shader->getPos()[i], lumina->pos.x, lumina->pos.y, lumina->pos.z);
		}
		if (lumina->tip == directional) {
			glUniform3f(shader->getPos()[1], lumina->dir.x, lumina->dir.y, lumina->dir.z);
		}
		if (lumina->tip == spotlight) {
			glUniform3f(shader->getPos()[i], lumina->pos.x, lumina->pos.y, lumina->pos.z);
			glUniform3f(shader->getPos()[1], lumina->dir.x, lumina->dir.y, lumina->dir.z);
			glUniform1f(shader->getDeschidere()[i], lumina->unghiDeschidere);

		}

	}
	for (int i = lights.size(); i < 5; i++) {
		glUniform1i(shader->getTypes()[i], 0);
	}
	
	glDrawElements(GL_TRIANGLES, nrIndici, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_TEXTURE_2D, 0);
	glDisable(GL_DEPTH_TEST);

}

void SceneObject::SpecificDraw(Matrix mat) {

}
Paralelipiped SceneObject::setBoundTag(Paralelipiped par) {
	par.tag = "Obiect";
	return par;
}

Paralelipiped SceneObject::getBoundingBox() {
	Paralelipiped paralelipiped = model->getBoundingBox(rotation,scale,position);

	paralelipiped=setBoundTag(paralelipiped);
	return paralelipiped;
}