#pragma once
#include "SceneObject.h"

class SkyBox :public SceneObject {
protected:
	Paralelipiped setBoundTag(Paralelipiped par);
public:
	SkyBox(int _id, std::string _type, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>texturi, bool _depthTest);
	
	void Draw();
	void Update(float deltaTime);


};