#pragma once
#include"../Utilities/Math.h"

enum typeLight { null, point, directional, spotlight };

class Light
{
public:
	Light(Vector3 _spec, Vector3 _diff,int _id) :spec(_spec), diff(_diff),id(_id) {};
	~Light() {};
	Vector3 dir;
	float openingAngle;

	Vector3 pos;
	typeLight tip;
	Vector3 spec;
	Vector3 diff;
	int id;
	

};

