#pragma once
#include "ShaderResource.h"

class Shader {
	ShaderResource* mr;
	GLint id_prog;
	
public:
	void Load();
	Shader(ShaderResource* resursa);
	~Shader();
};

