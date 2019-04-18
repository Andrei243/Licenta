#pragma once
#include "stdafx.h"
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

void SceneObject::Draw(ESContext* escontext,Camera* camera) {

	GLuint vboId, indBuff, idTextura;
	GLint program,nrIndici;
	program = shader->getid();
	nrIndici = model->getnrIndici();
	vboId = model->getid();
	indBuff = model->getindid();
	idTextura = texturi[0]->getid();
	GLint positionAttribute = glGetAttribLocation(program, "a_posL");
	GLint rotationUniform = glGetUniformLocation(program, "u_rotation");
	GLint uvAttribute = glGetAttribLocation(program, "a_uv");
	GLint TexUniform = glGetUniformLocation(program, "u_texture");
	glUseProgram(program);
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

	if (positionAttribute != -1)
	{
		glEnableVertexAttribArray(positionAttribute);
		glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}


	if (rotationUniform != -1) {
		glUniformMatrix4fv(rotationUniform, 1, GL_FALSE, (GLfloat*)matrice.m);

	}

	if (uvAttribute != -1) {
		glEnableVertexAttribArray(uvAttribute);
		glVertexAttribPointer(uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(4 * sizeof(Vector3)));
	}

	if (TexUniform != -1) {
		glUniform1i(TexUniform, 0);
	}

	glBindTexture(GL_TEXTURE_2D, idTextura);
	glDrawElements(GL_TRIANGLES, nrIndici, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_TEXTURE_2D, 0);

}