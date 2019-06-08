#include "stdafx.h"
#include "Fire.h"
#include <time.h>
#include "SceneManager.h"

void Fire::Draw() {
	Camera* camera = SceneManager::getsceneManager()->getActiveCamera();
	if (depthTest) { 
		glEnable(GL_DEPTH_TEST); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	GLuint vboId, indBuff, idTextura;
	GLint nrIndici;
	nrIndici = model->getnrIndici();
	vboId = model->getid();
	indBuff = model->getindid();
	glUseProgram(shader->getid());
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBuff);
	Matrix matrice;
	Matrix translatie, rotatie, rotatiex, rotatiey, rotatiez, scalare;
	translatie.SetTranslation(position);
	rotatiex.SetRotationX(rotation.x);
	rotatiey.SetRotationY(rotation.y);
	rotatiez.SetRotationZ(rotation.z);
	scalare.SetScale(scale);
	rotatie = rotatiex * rotatiey*rotatiez;
	matrice = scalare * rotatie*translatie;
	Matrix model = matrice;
	matrice = matrice * camera->getmat();
	if (shader->getVarUn()[0] != -1) {
		glUniform1f(shader->getVarUn()[0], time);
	}
	if (shader->getVarUn()[1] != -1) {
		glUniform1f(shader->getVarUn()[1], displmax);
	}

	for (unsigned int i = 0; i < texturi.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texturi[i]->getid());
		if (shader->getTexUn()[i] != -1) {
			glUniform1i(shader->getTexUn()[i], i);
		}
	}

	if (shader->getModUn() != -1) {
		glUniformMatrix4fv(shader->getModUn(), 1, GL_FALSE, (GLfloat*)model.m);
	}

	if (shader->getPosAtt() != -1)
	{
		glEnableVertexAttribArray(shader->getPosAtt());
		glVertexAttribPointer(shader->getPosAtt(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}


	if (shader->getRotAtt() != -1) {
		glUniformMatrix4fv(shader->getRotAtt(), 1, GL_FALSE, (GLfloat*)matrice.m);

	}

	if (shader->getUvAtt() != -1) {
		glEnableVertexAttribArray(shader->getUvAtt());
		glVertexAttribPointer(shader->getUvAtt(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(4 * sizeof(Vector3)));
	}
	/*if (shader->getFogUn()[0] != -1) {
		glUniform1f(shader->getFogUn()[0], SceneManager::getsceneManager()->r);
	}
	if (shader->getFogUn()[1] != -1) {
		glUniform1f(shader->getFogUn()[1], SceneManager::getsceneManager()->R);
	}
	if (shader->getFogUn()[2] != -1) {
		glUniform3f(shader->getFogUn()[2], SceneManager::getsceneManager()->fogcol.x, SceneManager::getsceneManager()->fogcol.y, SceneManager::getsceneManager()->fogcol.z);
	}*/

	//Vector3 camerapos = SceneManager::getsceneManager()->getActiveCamera()->getposition();
	/*if (shader->getCamUn() != -1) {
		glUniform3f(shader->getCamUn(), camerapos.x, camerapos.y, camerapos.z);
	}*/

	glDrawElements(GL_TRIANGLES, nrIndici, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_TEXTURE_2D, 0);

}


void Fire::Update(float deltaTime) {
	time += deltaTime;
	if (time >= 1) {
		time -= 1;
	}
}
