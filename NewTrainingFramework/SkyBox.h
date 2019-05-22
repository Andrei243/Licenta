#pragma once
#include "SceneObject.h"

class SkyBox :public SceneObject {
protected:
	GLint offsetY;


	static Model* generateModel();
	Paralelipiped setBoundTag(Paralelipiped par);
public:
	SkyBox(int _id, std::string _type, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>texturi, bool _depthTest,GLint offsetY);
	
	void Draw();
	void Update();


};