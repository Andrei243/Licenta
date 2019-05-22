#pragma once
#include <iostream>

class Paralelipiped {
public:
	float minx, miny, minz, maxx, maxy, maxz;
	std::string tag;
	static bool verificaColiziune(Paralelipiped x1, Paralelipiped x2);

};