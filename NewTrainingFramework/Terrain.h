#pragma once
#include "stdafx.h"
#include "SceneObject.h"

class Terrain :public SceneObject {
	int nr_celule;
	int dimensiuneCelula;
	int heightr;
	int heightg;
	int heightb;
	int deplx;
	int deplz;
	
	Paralelipiped setBoundTag(Paralelipiped par);
public:
	Terrain(int _id, std::string _type, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>texturi, bool _depthTest,int nrCelule, int _dimensiuneCelula , int _offSetY, Vector3 height);
	void SpecificDraw(Matrix mat);
	void Update(float deltaTime);
	static Model* generateModel(int offsetY, int dimensiuneCelula, int nrCelule);

};