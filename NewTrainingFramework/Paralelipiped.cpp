#pragma once
#include "stdafx.h"
#include <vector>
#include "Paralelipiped.h"
#include "Vertex.h"

bool Paralelipiped::verificaColiziune(Paralelipiped o1, Paralelipiped o2) {
	bool x, y, z;
	x = y = z = false;
	if (o1.minx <= o2.maxx&&o1.maxx >= o2.minx)x = true;
	if (o1.miny <= o2.maxy && o1.maxy >= o2.miny)y = true;
	if (o1.minz <= o2.maxz && o1.maxz >= o2.minz)z = true;
	return x && y&&z;
}

Paralelipiped Paralelipiped::calculeazaParalelipiped(Vector3 rotatie, Vector3 scale,Vector3 pos) {
	std::vector<Vector3> pozitii;
	pozitii.push_back(Vector3(maxx, maxy, maxz));
	pozitii.push_back(Vector3(maxx, maxy, minz));
	pozitii.push_back(Vector3(maxx, miny, maxz));
	pozitii.push_back(Vector3(maxx, miny, minz));
	pozitii.push_back(Vector3(minx, maxy, maxz));
	pozitii.push_back(Vector3(minx, maxy, minz));
	pozitii.push_back(Vector3(minx, miny, maxz));
	pozitii.push_back(Vector3(minx, miny, minz));
	Matrix rotatiex, rotatiey, rotatiez, matrotatie,scalare,pozitie;
	rotatiex.SetRotationX(rotatie.x);
	rotatiey.SetRotationY(rotatie.y);
	rotatiez.SetRotationZ(rotatie.z);
	scalare.SetScale(scale);
	pozitie.SetTranslation(pos);
	matrotatie = scalare* rotatiex * rotatiey*rotatiez*pozitie;
	
	for (auto element : pozitii) {
		Vector4 aux = Vector4(element, 1.0f);
		aux = matrotatie * aux;
		element = Vector3(aux.x,aux.y,aux.z);
	}
	Paralelipiped nou;
	nou.minx = nou.maxx = pozitii[0].x;
	nou.miny = nou.maxy = pozitii[0].y;
	nou.minz = nou.maxz = pozitii[0].z;

	for (auto pos : pozitii) {
		if (pos.x < nou.minx)nou.minx = pos.x;
		if (pos.x > nou.maxx)nou.maxx = pos.x;
		if (pos.y < nou.miny)nou.miny = pos.y;
		if (pos.y > nou.maxy)nou.maxy = pos.y;
		if (pos.z < nou.minz)nou.minz = pos.z;
		if (pos.z > nou.maxz)nou.maxz = pos.z;

	}
	return nou;




}

Paralelipiped::Paralelipiped(std::vector<Vertex>vertexi) {
	minx = maxx = vertexi[0].pos.x;
	miny = maxy = vertexi[0].pos.y;
	minz = maxz = vertexi[0].pos.z;

	for (auto vert : vertexi) {
		if (vert.pos.x < minx)minx = vert.pos.x;
		if (vert.pos.x > maxx)maxx = vert.pos.x;
		if (vert.pos.y < miny)miny = vert.pos.y;
		if (vert.pos.y > maxy)maxy = vert.pos.y;
		if (vert.pos.z < minz)minz = vert.pos.z;
		if (vert.pos.z > maxz)maxz = vert.pos.z;

	}

}