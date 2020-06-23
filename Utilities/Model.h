#pragma once
#include "Vertex.h"
#include "BoundingBox.h"
#include <vector>


class Model {
	GLuint  ibold;
	GLuint vbold;
	GLint nrindici;
	BoundingBox boundingBox;
	
public:
	GLuint getid();
	GLuint getindid();
	GLint getnrIndici();
	BoundingBox getBoundingBox(Vector3 rotation,Vector3 scale,Vector3 position);

	Model(Vertex* vertexi, int nr_vertexi, unsigned short* indici, int nr_indici);
	Model(std::vector<Vertex> vertices, std::vector<unsigned short> indices);
	~Model() {};
	void cleanUp();
};
namespace ceutils {
	Model* generateModelFromNFG(std::string path);
	Model* generateSkyboxModel(float dim);
	Model* generateModelFromObj(std::string path);
	Model* generateTerrain(int offsetY, int cellDimension, int nrCells);
}
