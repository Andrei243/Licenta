#pragma once
#include "stdafx.h"
#include "Terrain.h"
#include "Vertex.h"
#include "GameManager.h"

#include <iostream>



Terrain::Terrain(int _id, std::string _type, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>texturi, bool _depthTest,int _nrCelule,  int _dimensiuneCelula, int _offSetY, Vector3 height):
	SceneObject(_id, _type, GameManager::getGameManager()->getCurrentScene()->getActiveCamera()->getposition(), _rotation, _scale, _model, _shader, texturi, _depthTest) {
	nr_celule = _nrCelule;
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
void Terrain::SpecificDraw(Matrix mat) {
	glUseProgram(shader->getid());
	glUniform1i(shader->getVarUn()[0], nr_celule);
	glUniform1i(shader->getVarUn()[1], heightr);
	glUniform1i(shader->getVarUn()[2], heightg);
	glUniform1i(shader->getVarUn()[3], heightb);
	glUniform1i(shader->getVarUn()[4], deplx);
	glUniform1i(shader->getVarUn()[5], deplz);
}


void Terrain::Update(float deltaTime) {
	Camera* activeCamera = GameManager::getGameManager()->getCurrentScene()->getActiveCamera();
	if (position.x - activeCamera->getposition().x > dimensiuneCelula) {
		int nrSarituri = ((int)(position.x - activeCamera->getposition().x)) / dimensiuneCelula;
		position.x -= nrSarituri*dimensiuneCelula; 
		deplx-=nrSarituri; 
	}
	else if (activeCamera->getposition().x - position.x > dimensiuneCelula) {
		int nrSarituri = ((int)(activeCamera->getposition().x - position.x)) / dimensiuneCelula;
		position.x +=nrSarituri* dimensiuneCelula; 
		deplx+=nrSarituri; 
	}

	if (position.z - activeCamera->getposition().z > dimensiuneCelula) {
		int nrSarituri = ((int)(position.z - activeCamera->getposition().z)) / dimensiuneCelula;
		position.z -= nrSarituri * dimensiuneCelula;
		deplz -= nrSarituri;
	}
	else if (activeCamera->getposition().z - position.z > dimensiuneCelula) {
		int nrSarituri = ((int)(activeCamera->getposition().z - position.z)) / dimensiuneCelula;

		position.z += nrSarituri * dimensiuneCelula;
		deplz += nrSarituri;
	}

}

Paralelipiped Terrain::setBoundTag(Paralelipiped par) {
	par.tag = "terrain";
	return par;
}