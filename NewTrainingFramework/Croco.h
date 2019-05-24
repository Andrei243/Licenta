#pragma once
#include "stdafx.h"
#include "SceneObject.h"

class Crocodil :public SceneObject {
protected:
	Paralelipiped setBoundTag(Paralelipiped par) {
		par.tag = "croco";
		return par;
	}

public:
	Crocodil(int _id, std::string _type, Vector3 _position, Vector3 _rotation, Vector3 _scale, Model* _model, Shader* _shader, std::vector<Texture*>texturi, bool _depthTest): SceneObject(_id, _type, _position, _rotation, _scale, _model, _shader,texturi, _depthTest){}


public:
	virtual void Key(unsigned char key) {
		
			switch (key) {
			case 'U':
			case 'u':
				position.z += 20;
			
		}

	};

};

