#pragma once
#include "ShaderResource.h"

class Shader {
	ShaderResource* mr;
	GLint id_prog;
	GLint positionAttribute;
	GLint rotationUniform;
	GLint uvAttribute;
	GLint texUniform[6];
	GLint varUniform[6];
	GLint cubeUniform;
	GLint fogUniforms[3];
	GLint modelUniform;
	GLint camUniform;
	
public:
	void Load();
	GLint getid();
	Shader(ShaderResource* resursa);
	~Shader();
	GLint getCubeUn();
	GLint getPosAtt();
	GLint getRotAtt();
	GLint getUvAtt();
	GLint* getTexUn();
	GLint* getVarUn();
	GLint* getFogUn();
	GLint getModUn();
	GLint getCamUn();
};

