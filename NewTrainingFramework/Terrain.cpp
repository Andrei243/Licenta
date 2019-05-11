#pragma once
#include "stdafx.h"
#include "Terrain.h"
#include "Vertex.h"
#include "SceneManager.h"

Camera* camera = SceneManager::getsceneManager()->getActiveCamera();

Terrain::Terrain(int _id, std::string _type, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>texturi, bool _depthTest, int _nr_celule, int _dimensiuneCelula, int _offSetY):SceneObject(_id, _type, _position, _rotation, _scale, _model, _shader, texturi, _depthTest) {
	nr_celule = _nr_celule;
	offSetY = _offSetY;
	dimensiuneCelula = _dimensiuneCelula;
	position = Vector3(0.0f, 0.0f, 0.0f);

	Vertex* vertexi;
	int nr_vertexi;
	nr_vertexi = (nr_celule + 1)*(nr_celule + 1);
	vertexi = new Vertex[nr_vertexi];
	
		for(int i=0;i<=nr_celule;i++)
			for (int j = 0; j <= nr_celule; j++) {
				Vector3 poz;
				poz.x = (GLfloat)dimensiuneCelula + (i - nr_celule / 2);
				poz.y = (GLfloat)dimensiuneCelula + (i - nr_celule / 2);
				poz.y = offSetY;
				vertexi[i*nr_celule + j].pos = poz;
				vertexi[i*nr_celule + j].uv = Vector2(i / (GLfloat)nr_celule, j / (GLfloat)nr_celule);
			}
	nrindiciter = 6 * nr_celule*nr_celule;
	unsigned short* indici = new unsigned short[nrindiciter];
	int indice_act = 0;
		for (int i = 0; i < nr_celule; i++) {
			for (int j = 0; j < nr_celule; j++) {
				indici[nrindiciter++] = i * nr_celule + j;
				indici[nrindiciter++] = (i + 1)*nr_celule + j;
				indici[nrindiciter++] = i * nr_celule + j + 1;
				
				indici[nrindiciter++] = (i + 1)*nr_celule + j;
				indici[nrindiciter++] = i * nr_celule + j + 1;
				indici[nrindiciter++] = (i + 1)*nr_celule + j + 1;
			}
	}
	
		glGenBuffers(1, &vboldter);
		glBindBuffer(GL_ARRAY_BUFFER, vboldter);
		glBufferData(GL_ARRAY_BUFFER, nr_vertexi * sizeof(Vertex), vertexi, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &iboldter);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboldter);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrindiciter * sizeof(unsigned short), indici, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
	
}

void Terrain::Draw() {
	/*Camera* camera = SceneManager::getsceneManager()->getActiveCamera();
	if (depthTest) { glEnable(GL_DEPTH_TEST); }
	GLuint vboId, indBuff, idTextura;
	GLint nrIndici;
	nrIndici = nrindiciter;
	vboId = vboldter;
	indBuff = iboldter;
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
	glDisable(GL_DEPTH_TEST);
	*/
}

void Terrain::Update(float deltaTime) {



}