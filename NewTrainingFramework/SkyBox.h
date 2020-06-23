#pragma once
#include "SceneObject.h"

class SkyBox :public SceneObject {
public:
	SkyBox(int _id, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>textures, bool _depthTest);
	
	void Update(float deltaTime);
	void SpecificDraw(Matrix mat = Matrix().SetIdentity());

};