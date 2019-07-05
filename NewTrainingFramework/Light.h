#pragma once
#include"../Utilities/Math.h"
class Light
{
public:
	Light(Vector3 _spec, Vector3 _diff,int _id) :spec(_spec), diff(_diff),id(_id) {};
	~Light();

	virtual double calculeazaComponentaSpeculara() = 0;
	virtual double calculeazaComponentaDifuza() = 0;
	Vector3 spec;
	Vector3 diff;
	int id;
	

};

