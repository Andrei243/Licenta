#pragma once

#include "stdafx.h"
#include "Model.h"
#include <iostream>
#include <fstream>
#include "../NewTrainingFramework/ResourceManager.h"
#include "../NewTrainingFramework/Vertex.h"
#include <stdlib.h>

ResourceManager* manager = ResourceManager::getresourceManager();

GLuint Model::getid() {
	return vbold;
}

GLuint Model::getindid() {
	return ibold;
}

GLint Model::getnrIndici() {
	return nrindici;
}
GLint Model::getnrIndiciWired() {
	return nrindiciWired;
}

GLuint Model::getwiredid() {
	return wiredIbold;
}

void Model::Load() {
	int id = mr->id;
	std::string path = mr->path;
	int nrVertecsi;
	Vertex* verticesData;
	

	FILE* fisierModel = fopen(path.c_str(), "r");
	if (fisierModel == NULL)return;


	fscanf(fisierModel, "NrVertices: %d", &nrVertecsi);
	verticesData = new Vertex[nrVertecsi];
	int inutil;
	for (int i = 0; i < nrVertecsi; i++) {
		fscanf(fisierModel, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];", &inutil, &verticesData[i].pos.x, &verticesData[i].pos.y, &verticesData[i].pos.z, &verticesData[i].norm.x, &verticesData[i].norm.y, &verticesData[i].norm.z, &verticesData[i].binorm.x, &verticesData[i].binorm.y, &verticesData[i].binorm.z, &verticesData[i].tgt.x, &verticesData[i].tgt.y, &verticesData[i].tgt.z, &verticesData[i].uv.x, &verticesData[i].uv.y);

	}

	//buffer object
	glGenBuffers(1, &vbold);
	glBindBuffer(GL_ARRAY_BUFFER, vbold);
	glBufferData(GL_ARRAY_BUFFER, nrVertecsi * sizeof(Vertex), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	unsigned short* indici;
	fscanf(fisierModel, "\nNrIndices: %d", &nrindici);
	indici = (unsigned short*)malloc(nrindici * sizeof(int));
	for (int i = 0; i < nrindici / 3; i++) {
		fscanf(fisierModel, "%d. %d,%d,%d\n", &inutil, &indici[i * 3], &indici[i * 3 + 1], &indici[i * 3 + 2]);


	}


	glGenBuffers(1, &ibold);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibold);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrindici * sizeof(unsigned short), indici, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	fclose(fisierModel);

}

Model::Model(ModelResource* resursa) {
	this->mr = resursa;
	this->Load();
}