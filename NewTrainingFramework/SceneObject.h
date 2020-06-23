#pragma once
#include <string>
#include "../Utilities/Shader.h"
#include "../Utilities/Model.h"
#include "../Utilities/Texture.h"
#include "Camera.h"
#include <vector>
#include "../Utilities/utilities.h"


class SceneObject {
protected:
	int id;
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Model* model;
	Shader* shader;
	std::vector<Texture*> textures;
	bool depthTest;
	std::vector<int> lights;
	bool isDrawnBySceneManager;

public:
	SceneObject(int _id, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>textures, bool _depthTest);
	virtual void SpecificDraw(Matrix mat=Matrix().SetIdentity());
	virtual void Draw(Matrix mat = Matrix().SetIdentity());
	virtual void Update(float deltaTime) {};
	virtual void Key(unsigned char key) {};
	BoundingBox getBoundingBox();
	void addLight(int id) { lights.push_back(id); }
	void setUndrawnBySceneManager();
	void setDrawnBySceneManager();
	bool getIsDrawnBySceneManager();

};