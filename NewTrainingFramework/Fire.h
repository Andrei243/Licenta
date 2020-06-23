#pragma once
#include "SceneObject.h"
class Fire :
	public SceneObject
{
public:
	Fire(int _id,  Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>textures, bool _depthTest, float _displmax) : SceneObject(_id, _position, _rotation, _scale, _model, _shader, textures, _depthTest) { displmax = _displmax; time = 0; };
	void SpecificDraw(Matrix mat=Matrix().SetIdentity());
	void Update(float deltaTime);

private:
	double time;
	float displmax;

};

