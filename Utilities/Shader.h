#pragma once
#include "ShaderResource.h"

class Shader {
	ShaderResource* mr;
	GLint id_prog;
	GLint positionAttribute;
	GLint rotationUniform;
	GLint uvAttribute;


	GLint texUniform;
	
public:
	void Load();
	GLint getid();
	Shader(ShaderResource* resursa);
	~Shader();
	GLint getPosAtt();
	GLint getRotAtt();
	GLint getUvAtt();
	GLint getTexUn();
};

