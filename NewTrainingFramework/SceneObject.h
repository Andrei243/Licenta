#pragma once
#include <string>
#include "../Utilities/Shader.h"
#include "../Utilities/Model.h"
#include "../Utilities/Texture.h"
#include "Camera.h"
#include <vector>
#include "../Utilities/utilities.h"


class SceneObject {
private:
protected:
	std::string type;
	int id;
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Model* model;
	Shader* shader;
	std::vector<Texture*> texturi;
	bool depthTest;
	virtual Paralelipiped setBoundTag(Paralelipiped par);
	std::vector<int> lumini;

public:
	SceneObject(int _id,std::string _type, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>texturi, bool _depthTest);
	void CommonDraw(Camera* camera);
	virtual void Draw();
	virtual void Update(float deltaTime) {};
	virtual void Key(unsigned char key) {};
	Paralelipiped getParalelipiped();
	void adaugaLumina(int id) { lumini.push_back(id); }

};