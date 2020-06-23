#pragma once

#include "stdafx.h"
#include "Model.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Vertex.h"
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

Model* ceutils::generateTerrain(int offsetY, int cellDimension, int nrCells) {
	Vertex* vertexi;
	int nr_vertexi;
	nr_vertexi = (nrCells + 1) * (nrCells + 1);
	vertexi = new Vertex[nr_vertexi];

	for (int i = 0; i <= nrCells; i++)
		for (int j = 0; j <= nrCells; j++) {
			Vector3 poz;
			poz.x = (float)cellDimension * (i - nrCells / 2);
			poz.z = (float)cellDimension * (j - nrCells / 2);
			poz.y = offsetY;
			vertexi[i * nrCells + j].pos = poz;
			vertexi[i * nrCells + j].uv = Vector2(i /*/ (float)nrCells*/, j /*/ (float)nrCells*/);
		}


	int nrindiciter = 6 * nrCells * nrCells;
	unsigned short* indici = new unsigned short[nrindiciter];
	int indice_act = 0;
	for (int i = 0; i < nrCells; i++) {
		for (int j = 0; j < nrCells; j++) {
			indici[indice_act++] = i * nrCells + j;
			indici[indice_act++] = (i + 1) * nrCells + j;
			indici[indice_act++] = i * nrCells + j + 1;

			indici[indice_act++] = (i + 1) * nrCells + j;
			indici[indice_act++] = i * nrCells + j + 1;
			indici[indice_act++] = (i + 1) * nrCells + j + 1;
		}
	}



	return new Model(vertexi, nr_vertexi, indici, nrindiciter);
}

Model* ceutils::generateModelFromObj(std::string path) {
	int noVertexes;
	std::stringstream ss;
	std::vector<Vertex> verticesData;
	std::vector<unsigned short> indices;
	std::vector<Vector3> positions;
	std::vector<Vector2>uvs;
	std::vector<Vector3>normals;
	std::ifstream file(path);
	if (!file.is_open()) {
		throw "File " + path + " could not be found";
	}
	std::string line;
	while (std::getline(file,line)) {
		if (file.eof()) {
			break;
		}
		std::string lineHeader;
		ss.clear();
		ss.str(line);
		ss >> lineHeader;
		if (lineHeader == "v") {
			Vector3 position;
			ss >> position.x >> position.y >> position.z;
			positions.push_back(position);
		}
		else if(lineHeader== "vt") {
			Vector2 uv;
			ss >> uv.x >> uv.y;
			uvs.push_back(uv);
		}
		else if (lineHeader == "vn") {
			Vector3 normal;
			ss >> normal.x >> normal.y >> normal.z;
			normals.push_back(normal);
		}
		else if (lineHeader== "f") {
			std::string vertex;
			while (ss >> vertex) {
				std::stringstream vertexReader;
				Vertex vert;
				vertexReader.str(vertex);
				int pos, norm, uv;
				vertexReader >> pos;
				vert.pos = positions[pos - 1];
				vertexReader.ignore(1, '/');
				vertexReader >> uv;
				vert.uv = uvs[uv - 1];
				if (!vertexReader.eof()) {
					vertexReader.ignore(1, '/');
					vertexReader >> norm;
					vert.norm = normals[norm-1];
				}
				verticesData.push_back(vert);
				indices.push_back(indices.size());

			}
			
		}
	}
	file.close();
	return new Model(verticesData, indices);
}


Model* ceutils::generateModelFromNFG(std::string path) {
	int noVertexes;
	Vertex* verticesData;
	

	FILE* fisierModel = fopen(path.c_str(), "r");
	if (fisierModel == NULL) {
		throw "File " + path + " could not be found";
	}
	

	fscanf(fisierModel, "NrVertices: %d", &noVertexes);
	verticesData = new Vertex[noVertexes];
	int inutil;

	for (int i = 0; i < noVertexes; i++) {
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
	return new Model(verticesData, noVertexes, indici, nrIndici);

}

Model::Model(std::vector<Vertex> vertices, std::vector<unsigned short> indices) :Model(&vertices[0], vertices.size(), &indices[0], indices.size()) {};

Model::Model(Vertex* verticesData, int nrVertexi, unsigned short* indici, int nrIndici) {
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

BoundingBox Model::getBoundingBox(Vector3 rotation,Vector3 scale,Vector3 position) {
	
	return boundingBox.calculateBoundingBox(rotation,scale,position);
}

void Model::cleanUp() {
	glDeleteBuffers(1, &vbold);
	glDeleteBuffers(1, &ibold);
}
Model* ceutils::generateSkyboxModel(float dim) {
	Vertex* vertexi = new Vertex[8];
	unsigned short indici[36] = { 0,1,2,1,2,3,    //fata de sus
							  0,1,4,1,4,5,    //fata din fata
							  1,3,5,3,5,7,    //fata din dreapta
							  0,2,4,2,4,6,    //fata din stanga
							  2,3,6,6,3,7,    //fata din spate
							  4,6,5,6,5,7 };   //fata de jos


	vertexi[0].pos = Vector3(dim, dim, dim);
	vertexi[1].pos = Vector3(-dim, dim, dim);
	vertexi[2].pos = Vector3(dim, dim, -dim);
	vertexi[3].pos = Vector3(-dim, dim, -dim);
	vertexi[4].pos = Vector3(dim, -dim, dim);
	vertexi[5].pos = Vector3(-dim, -dim, dim);
	vertexi[6].pos = Vector3(dim, -dim, -dim);
	vertexi[7].pos = Vector3(-dim, -dim, -dim);

	return new Model(vertexi, 8, indici, 36);
}