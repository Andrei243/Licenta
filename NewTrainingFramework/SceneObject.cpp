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

SceneObject::SceneObject(std::string _type, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*> _texturi, bool _depthTest) {
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
	if (depthTest)glEnable(GL_DEPTH_TEST);
	GLuint vboId, indBuff, idTextura;
	GLint nrIndici;
	nrIndici = model->getnrIndici();
	vboId = model->getid();
	indBuff = model->getindid();
	idTextura = texturi[0]->getid();
	std::vector<GLuint>id_texturi;
	for (unsigned int i = 0; i < texturi.size(); i++) {
		id_texturi.push_back(texturi[i]->getid());
	}



	glUseProgram(shader->getid());
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBuff);
	Matrix matrice;
	Matrix translatie,rotatie, rotatiex,rotatiey,rotatiez, scalare;
	translatie.SetTranslation(position);
	rotatiex.SetRotationX(rotation.x);
	rotatiey.SetRotationY(rotation.y);
	rotatiez.SetRotationZ(rotation.z);
	scalare.SetScale(scale);
	rotatie = rotatiex * rotatiey*rotatiez;
	matrice = scalare * rotatie*translatie;
	matrice = matrice * camera->getmat();

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

	if (shader->getTexUn() != -1) {
		glUniform1i(shader->getTexUn(), 0);
	}

	glBindTexture(GL_TEXTURE_2D, idTextura);
	glDrawElements(GL_TRIANGLES, nrIndici, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_TEXTURE_2D, 0);
	glDisable(GL_DEPTH_TEST);

}