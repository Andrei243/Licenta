#pragma once
#include "stdafx.h"
#include "SceneObject.h"

class Terrain :public SceneObject {
	int nr_celule;
	int offSetY;
	int dimensiuneCelula;
	GLuint  iboldter;
	GLuint wiredIboldter;
	GLuint vboldter;
	GLint nrindiciter, nrindiciWiredter;
public:
	Terrain(int _id, std::string _type, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>texturi, bool _depthTest, int _nr_celule,int _dimensiuneCelula , int _offSetY);
	void Draw();
	void Update(float deltaTime);

};