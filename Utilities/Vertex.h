#pragma once
#include "../Utilities/Math.h"

struct Vertex 
{
	Vector3 pos;
	Vector3 norm;
	Vector3 binorm;
	Vector3 tgt;
	Vector2 uv;
	Vertex(){}
	Vertex(const Vertex &v):pos(v.pos),norm(v.norm),binorm(v.binorm),tgt(v.tgt),uv(v.uv){}
};