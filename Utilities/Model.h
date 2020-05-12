#pragma once
#include "../NewTrainingFramework/Vertex.h"
#include "../NewTrainingFramework/Paralelipiped.h"
#include <vector>


class Model {
	GLuint  ibold;
	GLuint vbold;
	GLint nrindici;
	Paralelipiped boundingBox;
	
public:
	GLuint getid();
	GLuint getindid();
	GLint getnrIndici();
	Paralelipiped getBoundingBox(Vector3 rotation,Vector3 scale,Vector3 position);

	Model(Vertex* vertexi, int nr_vertexi, unsigned short* indici, int nr_indici);
	Model(std::vector<Vertex> vertices, std::vector<unsigned short> indices);
	~Model() {};
	void cleanUp();
};
namespace ceutils {
	Model* generateModelFromNFG(std::string path);
	Model* generateSkyboxModel(float dim);
}
