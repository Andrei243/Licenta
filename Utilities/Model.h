#pragma once
#include "ModelResource.h"


class Model {
	ModelResource* mr;
	GLuint  ibold;
	GLuint wiredIbold;
	GLuint vbold;
	GLint nrindici, nrindiciWired;
	
public:
	void Load();
	Model(ModelResource* resursa);
	~Model() {};
};


