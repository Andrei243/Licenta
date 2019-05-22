#pragma once
#include "ModelResource.h"
#include "../NewTrainingFramework/Vertex.h"
#include "../NewTrainingFramework/Paralelipiped.h"


class Model {
	ModelResource* mr;
	GLuint  ibold;
	GLuint wiredIbold;
	GLuint vbold;
	GLint nrindici, nrindiciWired;
	Paralelipiped boundingBox;
	
public:
	GLuint getid();
	GLuint getwiredid();
	GLuint getindid();
	GLint getnrIndici();
	GLint getnrIndiciWired();
	Paralelipiped getBoundingBox();

	void Load();
	Model(Vertex* vertexi, int nr_vertexi, unsigned short* indici, int nr_indici);
	Model(ModelResource* resursa);
	~Model() {};
};


