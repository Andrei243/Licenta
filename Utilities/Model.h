#pragma once
#include "ModelResource.h"


class Model {
	ModelResource* mr;
	GLuint  ibold;
	GLuint wiredIbold;
	GLuint vbold;
	GLint nrindici, nrindiciWired;
	
public:
	GLuint getid();
	GLuint getwiredid();
	GLuint getindid();
	GLint getnrIndici();
	GLint getnrIndiciWired();

	void Load();
	Model(ModelResource* resursa);
	~Model() {};
};


