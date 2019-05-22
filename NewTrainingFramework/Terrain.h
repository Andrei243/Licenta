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
	static Model* generateModel(int offsetY, int dimensiuneCelula,int nrCelule);
	Paralelipiped setBoundTag(Paralelipiped par);
public:
	Terrain(int _id, std::string _type, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>texturi, bool _depthTest, int _nr_celule,int _dimensiuneCelula , int _offSetY, Vector3 height);
	void Draw();
	void Update(float deltaTime);


};