#pragma once

#include "stdafx.h"
#include "Model.h"
#include <iostream>
#include <fstream>
#include "../NewTrainingFramework/ResourceManager.h"
#include "../NewTrainingFramework/Vertex.h"
#include <stdlib.h>


GLuint Model::getid() {
	return vbold;
}

GLuint Model::getindid() {
	return ibold;
}

GLint Model::getnrIndici() {
	return nrindici;
}


Model* generateModelFromNFG(std::string path) {
	int nrVertecsi;
	Vertex* verticesData;
	

	FILE* fisierModel = fopen(path.c_str(), "r");
	if (fisierModel == NULL)return 0;
	

	fscanf(fisierModel, "NrVertices: %d", &nrVertecsi);
	verticesData = new Vertex[nrVertecsi];
	int inutil;

	for (int i = 0; i < nrVertecsi; i++) {
		fscanf(fisierModel, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];", &inutil, &verticesData[i].pos.x, &verticesData[i].pos.y, &verticesData[i].pos.z, &verticesData[i].norm.x, &verticesData[i].norm.y, &verticesData[i].norm.z, &verticesData[i].binorm.x, &verticesData[i].binorm.y, &verticesData[i].binorm.z, &verticesData[i].tgt.x, &verticesData[i].tgt.y, &verticesData[i].tgt.z, &verticesData[i].uv.x, &verticesData[i].uv.y);
		
	}
	
	unsigned short* indici;
	int nrIndici;
	fscanf(fisierModel, "\nNrIndices: %d", &nrIndici);
	indici = (unsigned short*)malloc(nrIndici * sizeof(int));
	for (int i = 0; i < nrIndici / 3; i++) {
		fscanf(fisierModel, "%d. %d,%d,%d\n", &inutil, &indici[i * 3], &indici[i * 3 + 1], &indici[i * 3 + 2]);


	}


	fclose(fisierModel);
	return new Model(verticesData, nrVertecsi, indici, nrIndici);

}

Model::Model(std::vector<Vertex> vertices, std::vector<unsigned short> indices) :Model(&vertices[0], vertices.size(), &indices[0], indices.size()) {};

Model::Model(Vertex* verticesData, int nrVertexi, unsigned short* indici, int nrIndici) {
	for (int i = 0; i < nrVertexi; i++) {
		vertexi.push_back(verticesData[i]);
	}
	this->nrindici = nrIndici;
	glGenBuffers(1, &vbold);
	glBindBuffer(GL_ARRAY_BUFFER, vbold);
	glBufferData(GL_ARRAY_BUFFER, nrVertexi * sizeof(Vertex), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	boundingBox.maxx = boundingBox.minx = verticesData[0].pos.x;
	boundingBox.miny = boundingBox.maxy = verticesData[0].pos.y;
	boundingBox.maxz = boundingBox.minz = verticesData[0].pos.z;
	for (int i = 1; i < nrVertexi; i++) {
		Vector3 pos = verticesData[i].pos;
		if (boundingBox.minx > pos.x)boundingBox.minx = pos.x;
		if (boundingBox.maxx < pos.x)boundingBox.maxx = pos.x;
		if (boundingBox.miny > pos.y)boundingBox.miny = pos.y;
		if (boundingBox.maxy < pos.x)boundingBox.maxy = pos.y;
		if (boundingBox.minz > pos.z)boundingBox.minz = pos.z;
		if (boundingBox.maxz < pos.z)boundingBox.maxz = pos.z;
	}
	glGenBuffers(1, &ibold);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibold);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrindici * sizeof(unsigned short), indici, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

Paralelipiped Model::getBoundingBox(Vector3 rotation,Vector3 scale,Vector3 position) {
	
	return boundingBox.calculeazaParalelipiped(rotation,scale,position);
}

void Model::cleanUp() {
	glDeleteBuffers(1, &vbold);
	glDeleteBuffers(1, &ibold);
}