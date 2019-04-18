#pragma once
#include <string>
#include "../Utilities/utilities.h"
#include "../Utilities/Shader.h"
#include "../Utilities/Model.h"
#include "../Utilities/Texture.h"
#include "Camera.h"
#include <vector>

class SceneObject {
private:
	std::string type;
	int id;
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Model* model;
	Shader* shader;
	std::vector<Texture*> texturi;
	bool depthTest;

public:
	SceneObject(std::string _type, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>texturi, bool _depthTest);
	virtual void Draw(ESContext* escontext,Camera* camera);

};