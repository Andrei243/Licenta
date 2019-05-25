#pragma once
#include "stdafx.h"
#include "SceneManager.h"
#include <string>
#include "Vertex.h"
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

}

void SceneObject::Draw() {
	Camera* camera = SceneManager::getsceneManager()->getActiveCamera();
	if (depthTest) { glEnable(GL_DEPTH_TEST); }
	CommonDraw(camera);
	glDisable(GL_DEPTH_TEST);

}

void SceneObject::CommonDraw(Camera* camera) {
	
	GLuint vboId, indBuff, idTextura;
	GLint nrIndici;
	nrIndici = model->getnrIndici();
	vboId = model->getid();
	indBuff = model->getindid();
	glUseProgram(shader->getid());
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
	for (unsigned int i = 0; i < texturi.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texturi[i]->getid());
		if (shader->getTexUn()[i] != -1) {
			glUniform1i(shader->getTexUn()[i], i);
		}
	}

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

}
Paralelipiped SceneObject::setBoundTag(Paralelipiped par) {
	par.tag = "Obiect";
	return par;
}

Paralelipiped SceneObject::getParalelipiped() {
	Paralelipiped paralelipiped = model->getBoundingBox(rotation,scale,position);

	paralelipiped=setBoundTag(paralelipiped);
	//std::cout << paralelipiped.tag << " " << paralelipiped.minx << " " << paralelipiped.maxx << " " << paralelipiped.miny << " " << paralelipiped.maxy << " " << paralelipiped.minz << " " << paralelipiped.maxz << "\n";
	return paralelipiped;
}