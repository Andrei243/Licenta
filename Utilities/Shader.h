#pragma once
#include "ShaderResource.h"

class Shader {
	ShaderResource* mr;
	GLint id_prog;
	
public:
	void Load();
	GLint getid();
	Shader(ShaderResource* resursa);
	~Shader();
};

