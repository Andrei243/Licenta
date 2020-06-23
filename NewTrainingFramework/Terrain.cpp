#pragma once
#include "stdafx.h"
#include "Terrain.h"
#include "../Utilities/Vertex.h"
#include "GameManager.h"

#include <iostream>



Terrain::Terrain(int _id,  Vector3 _rotation, Vector3 _scale,  Shader* _shader, std::vector<Texture*>textures, bool _depthTest,int _nrCells,  int _cellDimension, int _offSetY, Vector3 height):
	SceneObject(_id,  GameManager::getGameManager()->getCurrentScene()->getActiveCamera()->getposition(), _rotation, _scale,ceutils::generateTerrain(_offSetY,_cellDimension,_nrCells) , _shader, textures, _depthTest) {
	nrCells = _nrCells;
	cellDimension = _cellDimension;
	heightr = height.x;
	heightg = height.y;
	heightb = height.z;
	deplx = deplz = 0;
	
}
void Terrain::SpecificDraw(Matrix mat) {
	glUniform1i(shader->getVarUn()[0], nrCells);
	glUniform1i(shader->getVarUn()[1], heightr);
	glUniform1i(shader->getVarUn()[2], heightg);
	glUniform1i(shader->getVarUn()[3], heightb);
	glUniform1i(shader->getVarUn()[4], deplx);
	glUniform1i(shader->getVarUn()[5], deplz);
}


void Terrain::Update(float deltaTime) {
	Camera* activeCamera = GameManager::getGameManager()->getCurrentScene()->getActiveCamera();
	if (position.x - activeCamera->getposition().x > cellDimension) {
		int nrSarituri = ((int)(position.x - activeCamera->getposition().x)) / cellDimension;
		position.x -= nrSarituri*cellDimension; 
		deplx-=nrSarituri; 
	}
	else if (activeCamera->getposition().x - position.x > cellDimension) {
		int nrSarituri = ((int)(activeCamera->getposition().x - position.x)) / cellDimension;
		position.x +=nrSarituri* cellDimension; 
		deplx+=nrSarituri; 
	}

	if (position.z - activeCamera->getposition().z > cellDimension) {
		int nrSarituri = ((int)(position.z - activeCamera->getposition().z)) / cellDimension;
		position.z -= nrSarituri * cellDimension;
		deplz -= nrSarituri;
	}
	else if (activeCamera->getposition().z - position.z > cellDimension) {
		int nrSarituri = ((int)(activeCamera->getposition().z - position.z)) / cellDimension;

		position.z += nrSarituri * cellDimension;
		deplz += nrSarituri;
	}

}
