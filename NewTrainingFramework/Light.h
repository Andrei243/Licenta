#pragma once
#include"../Utilities/Math.h"

enum tip_lumina { null, point, directional, spotlight };

class Light
{
public:
	Light(Vector3 _spec, Vector3 _diff,int _id) :spec(_spec), diff(_diff),id(_id) {};
	~Light() {};

	tip_lumina tip;
	Vector3 spec;
	Vector3 diff;
	int id;
	

};

