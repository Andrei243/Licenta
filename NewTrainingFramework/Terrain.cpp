#pragma once
#include "stdafx.h"
#include "Terrain.h"
#include "Vertex.h"
#include "SceneManager.h"

#include <iostream>

Camera* camera = SceneManager::getsceneManager()->getActiveCamera();


Terrain::Terrain(int _id, std::string _type, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>texturi, bool _depthTest, int _nr_celule, int _dimensiuneCelula, int _offSetY, Vector3 height):SceneObject(_id, _type, _position, _rotation, _scale, _model, _shader, texturi, _depthTest) {
	position = SceneManager::getsceneManager()->getActiveCamera()->getposition();
	model = Terrain::generateModel(_offSetY, _dimensiuneCelula, _nr_celule);
	nr_celule = _nr_celule;
	dimensiuneCelula = _dimensiuneCelula;
	heightr = height.x;
	heightg = height.y;
	heightb = height.z;
	deplx = deplz = 0;
	
}

Model* Terrain::generateModel(int offsetY, int dimensiuneCelula,int nr_celule) {
	Vertex* vertexi;
	int nr_vertexi;
	nr_vertexi = (nr_celule + 1)*(nr_celule + 1);
	vertexi = new Vertex[nr_vertexi];

	for (int i = 0; i <= nr_celule; i++)
		for (int j = 0; j <= nr_celule; j++) {
			Vector3 poz;
			poz.x = (float)dimensiuneCelula * (i - nr_celule / 2);
			poz.z = (float)dimensiuneCelula * (j - nr_celule / 2);
			poz.y = offsetY;
			vertexi[i*nr_celule + j].pos = poz;
			vertexi[i*nr_celule + j].uv = Vector2(i /*/ (float)nr_celule*/, j /*/ (float)nr_celule*/);
		}


	int nrindiciter = 6 * nr_celule*nr_celule;
	unsigned short* indici = new unsigned short[nrindiciter];
	int indice_act = 0;
	for (int i = 0; i < nr_celule; i++) {
		for (int j = 0; j < nr_celule; j++) {
			indici[indice_act++] = i * nr_celule + j;
			indici[indice_act++] = (i + 1)*nr_celule + j;
			indici[indice_act++] = i * nr_celule + j + 1;

			indici[indice_act++] = (i + 1)*nr_celule + j;
			indici[indice_act++] = i * nr_celule + j + 1;
			indici[indice_act++] = (i + 1)*nr_celule + j + 1;
		}
	}



	return new Model(vertexi, nr_vertexi, indici, nrindiciter);

}

void Terrain::Draw() {
	Camera* camera = SceneManager::getsceneManager()->getActiveCamera();
	if (depthTest) { glEnable(GL_DEPTH_TEST); }
	glUseProgram(shader->getid());

	glUniform1i(shader->getVarUn()[0], nr_celule);
	glUniform1i(shader->getVarUn()[1], heightr);
	glUniform1i(shader->getVarUn()[2], heightg);
	glUniform1i(shader->getVarUn()[3], heightb);
	glUniform1i(shader->getVarUn()[4], deplx);
	glUniform1i(shader->getVarUn()[5], deplz);
	CommonDraw(camera);
	glDisable(GL_DEPTH_TEST);

}

void Terrain::Update(float deltaTime) {
	//std::cout << position.x << " " << position.y << " " << position.z << "\n";
	//std::cout << deplx << " " << deplz << "\n";
	if (position.x - SceneManager::getsceneManager()->getActiveCamera()->getposition().x > dimensiuneCelula) { 
		int nrSarituri = ((int)(position.x - SceneManager::getsceneManager()->getActiveCamera()->getposition().x)) / dimensiuneCelula;
		position.x -= nrSarituri*dimensiuneCelula; 
		deplx-=nrSarituri; 
	}
	else if (SceneManager::getsceneManager()->getActiveCamera()->getposition().x - position.x > dimensiuneCelula) { 
		int nrSarituri = ((int)(SceneManager::getsceneManager()->getActiveCamera()->getposition().x - position.x)) / dimensiuneCelula;
		position.x +=nrSarituri* dimensiuneCelula; 
		deplx+=nrSarituri; 
	}

	if (position.z - SceneManager::getsceneManager()->getActiveCamera()->getposition().z > dimensiuneCelula) {
		int nrSarituri = ((int)(position.z - SceneManager::getsceneManager()->getActiveCamera()->getposition().z)) / dimensiuneCelula;
		position.z -= nrSarituri * dimensiuneCelula;
		deplz -= nrSarituri;
	}
	else if (SceneManager::getsceneManager()->getActiveCamera()->getposition().z - position.z > dimensiuneCelula) {
		int nrSarituri = ((int)(SceneManager::getsceneManager()->getActiveCamera()->getposition().z - position.z)) / dimensiuneCelula;

		position.z += nrSarituri * dimensiuneCelula;
		deplz += nrSarituri;
	}
	/*if (position.y - SceneManager::getsceneManager()->getActiveCamera()->getposition().y > dimensiuneCelula)position.y -= dimensiuneCelula;
	else if (SceneManager::getsceneManager()->getActiveCamera()->getposition().y - position.y > dimensiuneCelula)position.y += dimensiuneCelula;*/

}

Paralelipiped Terrain::setBoundTag(Paralelipiped par) {
	par.tag = "terrain";
	return par;
}