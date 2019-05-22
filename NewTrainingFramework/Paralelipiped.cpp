#pragma once
#include "stdafx.h"
#include "Paralelipiped.h"

bool Paralelipiped::verificaColiziune(Paralelipiped o1, Paralelipiped o2) {
	bool x, y, z;
	x = y = z = false;
	if (o1.minx <= o2.maxx&&o1.maxx >= o2.minx)x = true;
	if (o1.miny <= o2.maxy && o1.maxy >= o2.miny)y = true;
	if (o1.minz <= o2.maxz && o1.maxz >= o2.minz)z = true;
	return x && y&&z;
}