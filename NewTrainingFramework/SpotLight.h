#pragma once
#include "Light.h"
#include "../Utilities/Math.h"

class SpotLight : public Light {
	double unghiDeschidere;
	Vector3 pos;
	Vector3 dir;
public:
	SpotLight(Vector3 spec, Vector3 diff, int id, double _unghiDeschidere, Vector3 _pos, Vector3 _dir) :
		Light(spec, diff, id), unghiDeschidere(_unghiDeschidere), pos(_pos), dir(_dir) {
		tip = spotlight;
	};


};