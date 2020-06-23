#pragma once
#include "stdafx.h"
#include "SceneObject.h"

class Terrain :public SceneObject {
protected:
	int nrCells;
	int cellDimension;
	int heightr;
	int heightg;
	int heightb;
	int deplx;
	int deplz;
	
public:
	Terrain(int _id, Vector3 _rotation, Vector3 _scale, Shader* _shader, std::vector<Texture*>textures, bool _depthTest,int nrCelule, int _cellDimension , int _offSetY, Vector3 height);
	void SpecificDraw(Matrix mat);
	void Update(float deltaTime);

};