#pragma once
#include <iostream>
#include "Vertex.h"
#include <vector>

class BoundingBox {
public:
	float minx, miny, minz, maxx, maxy, maxz;
	std::string tag;
	static bool verifyCollision(BoundingBox x1, BoundingBox x2);
	BoundingBox calculateBoundingBox(Vector3 rotatie, Vector3 scale,Vector3 pozitie);
	BoundingBox() {};
	BoundingBox(std::vector<Vertex> vertexi);
};