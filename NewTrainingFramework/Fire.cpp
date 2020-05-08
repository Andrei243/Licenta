#include "stdafx.h"
#include "Fire.h"
#include <time.h>
#include "GameManager.h"

void Fire::SpecificDraw(Matrix mat) {
	
	if (shader->getVarUn()[0] != -1) {
		glUniform1f(shader->getVarUn()[0], time);
	}
	if (shader->getVarUn()[1] != -1) {
		glUniform1f(shader->getVarUn()[1], displmax);
	}

}


void Fire::Update(float deltaTime) {
	time_t cl = clock();

	time = (double)cl/5000;
	time = (double)time - (int)time;
}
