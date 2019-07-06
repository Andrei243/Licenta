#pragma once
#include "Light.h"
#include "../Utilities/Math.h"
class DirectionalLight :
	public Light
{
public:
	DirectionalLight(Vector3 spec, Vector3 diff, int id, Vector3 _dir) :Light(spec, diff, id) { dir=_dir; tip = directional; };
	~DirectionalLight();
	

};

