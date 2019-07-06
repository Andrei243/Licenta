#pragma once
#include <map>
#include "Camera.h"
#include "SceneObject.h"
#include <vector>
#include "Lights.h"

class SceneManager {
	static SceneManager* sceneManager;
	std::map<int,Camera*> camere;
	int camera_actuala;
	Vector3 backgroundColor;
	std::vector<SceneObject*>obiecte;
	std::vector<std::vector<bool> > coliziune;
	std::map<int, Light*> lumini;
	AmbientLight* ambientLight;
	

public:
	float r, R;
	Vector3 fogcol;
	void verificaColiziuni();
	static SceneManager* getsceneManager();
	void Init(std::string path);
	Camera* getActiveCamera();
	void Draw(ESContext * escontext);
	void Key(unsigned char key);
	void Update(float deltaTime);
	Vector3 ambientColor() { return ambientLight->diff; };
	double ratio() { return ambientLight->ratio; }
};