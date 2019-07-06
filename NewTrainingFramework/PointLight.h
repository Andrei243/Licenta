#pragma once
#include "Light.h"
#include "../Utilities/Math.h"
class PointLight :
	public Light
{
public:
	PointLight(Vector3 spec, Vector3 diff, int id, Vector3 _pos) : Light(spec, diff, id), pos(_pos) { tip = point; };
	~PointLight();
	Vector3 pos;
	
};

