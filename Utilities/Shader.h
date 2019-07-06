#pragma once
#include "ShaderResource.h"

class Shader {
	ShaderResource* mr;
	GLint id_prog;
	GLint positionAttribute;
	GLint rotationUniform;
	GLint uvAttribute;
	GLint normAttribute;
	GLint texUniform[6];
	GLint varUniform[6];
	GLint cubeUniform;
	GLint fogUniforms[3];
	GLint modelUniform;
	GLint camUniform;

	GLint ratioUniform;
	GLint ambColorUniform;

	GLint typeUniform[5];
	GLint specUniform[5];
	GLint diffUniform[5];
	GLint posUniform[5];
	GLint dirUniform[5];
	GLint deschidereUniform[5];
	
public:
	void Load();
	GLint getid();
	Shader(ShaderResource* resursa);
	~Shader();
	GLint getCubeUn();
	GLint getPosAtt();
	GLint getRotAtt();
	GLint getNormAtt() { return normAttribute; }
	GLint getUvAtt();
	GLint* getTexUn();
	GLint* getVarUn();
	GLint* getFogUn();
	GLint getModUn();
	GLint getCamUn();

	GLint getRatio();
	GLint getAmbColor();

	GLint* getTypes();
	GLint* getSpecs();
	GLint* getDiff();
	GLint* getPos();
	GLint* getDir();
	GLint* getDeschidere();
};

