#pragma once
#include "Light.h"
#include "../Utilities/Math.h"

class SpotLight : public Light {

public:
	SpotLight(Vector3 spec, Vector3 diff, int id, double _openingAngle, Vector3 _pos, Vector3 _dir) :
		Light(spec, diff, id) {
		openingAngle = _openingAngle;
		pos = _pos;
		dir = _dir;
		tip = spotlight;
	};


};