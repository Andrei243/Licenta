#pragma once
#include "Light.h"
#include "../Utilities/Math.h"


class AmbientLight :public Light {
	AmbientLight() :Light(Vector3(0, 0, 0), Vector3(0, 0, 0), 0) {};
	double ratio;
	friend class SceneManager;

};

