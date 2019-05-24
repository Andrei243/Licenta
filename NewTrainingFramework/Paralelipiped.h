#pragma once
#include <iostream>
#include "Vertex.h"

class Paralelipiped {
public:
	float minx, miny, minz, maxx, maxy, maxz;
	std::string tag;
	static bool verificaColiziune(Paralelipiped x1, Paralelipiped x2);
	Paralelipiped calculeazaParalelipiped(Vector3 rotatie, Vector3 scale,Vector3 pozitie);
};