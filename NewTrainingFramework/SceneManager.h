#pragma once
#include <map>
#include "Camera.h"
#include "SceneObject.h"
#include <vector>
#include "Lights.h"
#include <utility>
#include "CollisionExecutor.h"
#include <set>
#include "ResourceManager.h"

class SceneManager {
	std::map<int,Camera*> camere;
	int currentCamera;
	Vector3 backgroundColor;
	std::map<int,SceneObject*>objects;
	std::set<std::pair<int,int> > isCollided;
	std::map<int, Light*> lights;
	AmbientLight* ambientLight;
	ResourceManager* resourceManager;
	std::map<std::pair<int, int>, std::vector<CollisionExecutor> > collisions;

public:
	float r, R;
	Vector3 fogcol;
	void verifyCollisions();
	ResourceManager* getResourceManager();
	void setBackgroundColor(Vector3 color);
	void setFogColor(Vector3 color);
	void addCamera(int id, Camera* camera);
	void setActiveCamera(int id);
	void addLight(int id, Light* light);
	void addObject(int id, SceneObject* sceneObject);
	void setAmbientLight( Vector3 diff, double ratio);
	Camera* getActiveCamera();
	virtual void Draw(ESContext * escontext);
	virtual void Key(unsigned char key);
	virtual void Update(float deltaTime);
	virtual void Init() = 0;
	void deleteObject(int id);
	void cleanUp();
	Vector3 ambientColor() { return ambientLight->diff; };
	double ratio() { return ambientLight->ratio; }
	Light* getLight(int id) { return lights.at(id); }
	SceneManager();
};