#pragma once 

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Shader.h"
#include "ShaderResource.h"

GLint Shader::getid() {
	return id_prog;
}

void Shader::Load() {
	std::string vs = mr->vs;
	std::string fs = mr->fs;
	
	GLuint vertexShader, fragmentShader;
	char vsf[360];
	strcpy(vsf, vs.c_str());
	char fsf[360];
	strcpy(fsf, fs.c_str());

	vertexShader = esLoadShader(GL_VERTEX_SHADER, vsf);
	if (vertexShader == 0) return;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fsf);
	if (fragmentShader == 0) {
		glDeleteShader(vertexShader);
		return;
	}
	id_prog = esLoadProgram(vertexShader, fragmentShader);

	 positionAttribute = glGetAttribLocation(id_prog, "a_posL");
	 rotationUniform = glGetUniformLocation(id_prog, "u_rotation");
	 normAttribute = glGetAttribLocation(id_prog, "a_norm");
	 uvAttribute = glGetAttribLocation(id_prog, "a_uv");


	texUniform[0] = glGetUniformLocation(id_prog, "u_texture0");
	texUniform[1] = glGetUniformLocation(id_prog, "u_texture1");
	texUniform[2] = glGetUniformLocation(id_prog, "u_texture2");
	texUniform[3] = glGetUniformLocation(id_prog, "u_texture3");
	texUniform[4] = glGetUniformLocation(id_prog, "u_texture4");
	texUniform[5] = glGetUniformLocation(id_prog, "u_texture5");

	varUniform[0] = glGetUniformLocation(id_prog, "u_var0");
	varUniform[1] = glGetUniformLocation(id_prog, "u_var1");
	varUniform[2] = glGetUniformLocation(id_prog, "u_var2");
	varUniform[3] = glGetUniformLocation(id_prog, "u_var3");
	varUniform[4] = glGetUniformLocation(id_prog, "u_var4");
	varUniform[5] = glGetUniformLocation(id_prog, "u_var5");

	fogUniforms[0] = glGetUniformLocation(id_prog, "r");
	fogUniforms[1] = glGetUniformLocation(id_prog, "R");
	fogUniforms[2] = glGetUniformLocation(id_prog, "fogcol");

	cubeUniform = glGetUniformLocation(id_prog, "u_cube_texture");

	modelUniform = glGetUniformLocation(id_prog, "model");

	camUniform = glGetUniformLocation(id_prog, "camera");

	ratioUniform = glGetUniformLocation(id_prog, "ratio");
	ambColorUniform = glGetUniformLocation(id_prog, "ambColor");

	typeUniform[0] = glGetUniformLocation(id_prog, "tip0");
	typeUniform[1] = glGetUniformLocation(id_prog, "tip1");
	typeUniform[2] = glGetUniformLocation(id_prog, "tip2");
	typeUniform[3] = glGetUniformLocation(id_prog, "tip3");
	typeUniform[4] = glGetUniformLocation(id_prog, "tip4");

	specUniform[0] = glGetUniformLocation(id_prog, "spec0");
	specUniform[1] = glGetUniformLocation(id_prog, "spec1");
	specUniform[2] = glGetUniformLocation(id_prog, "spec2");
	specUniform[3] = glGetUniformLocation(id_prog, "spec3");
	specUniform[4] = glGetUniformLocation(id_prog, "spec4");

	diffUniform[0] = glGetUniformLocation(id_prog, "diff0");
	diffUniform[1] = glGetUniformLocation(id_prog, "diff1");
	diffUniform[2] = glGetUniformLocation(id_prog, "diff2");
	diffUniform[3] = glGetUniformLocation(id_prog, "diff3");
	diffUniform[4] = glGetUniformLocation(id_prog, "diff4");

	posUniform[0] = glGetUniformLocation(id_prog, "pos0");
	posUniform[1] = glGetUniformLocation(id_prog, "pos1");
	posUniform[2] = glGetUniformLocation(id_prog, "pos2");
	posUniform[3] = glGetUniformLocation(id_prog, "pos3");
	posUniform[4] = glGetUniformLocation(id_prog, "pos4");

	dirUniform[0] = glGetUniformLocation(id_prog, "dir0");
	dirUniform[1] = glGetUniformLocation(id_prog, "dir1");
	dirUniform[2] = glGetUniformLocation(id_prog, "dir2");
	dirUniform[3] = glGetUniformLocation(id_prog, "dir3");
	dirUniform[4] = glGetUniformLocation(id_prog, "dir4");

	deschidereUniform[0] = glGetUniformLocation(id_prog, "deschidere0");
	deschidereUniform[1] = glGetUniformLocation(id_prog, "deschidere1");
	deschidereUniform[2] = glGetUniformLocation(id_prog, "deschidere2");
	deschidereUniform[3] = glGetUniformLocation(id_prog, "deschidere3");
	deschidereUniform[4] = glGetUniformLocation(id_prog, "deschidere4");
}

Shader::Shader(ShaderResource* resursa) {
	this->mr = resursa;
	this->Load();

}
GLint Shader::getPosAtt() {
	return positionAttribute;
}
GLint Shader::getRotAtt() {
	return rotationUniform;
}
GLint Shader::getUvAtt() {
	return uvAttribute;
}
GLint* Shader::getTexUn() {
	return texUniform;
}
GLint* Shader::getVarUn() {
	return varUniform;
}
GLint Shader::getCubeUn() {
	return cubeUniform;
}
Shader::~Shader() {
	delete mr;
}

GLint* Shader::getFogUn() {
	return fogUniforms;
}

GLint Shader::getModUn() {
	return modelUniform;
}

GLint Shader::getCamUn() {
	return camUniform;
}

GLint Shader::getRatio() {
	return ratioUniform;
}

GLint Shader::getAmbColor() {
	return ambColorUniform;
}

GLint* Shader::getTypes() {
	return typeUniform;
}

GLint* Shader::getSpecs() {
	return specUniform;
}

GLint* Shader::getDiff() {
	return diffUniform;
}

GLint* Shader::getPos() {
	return posUniform;
}

GLint* Shader::getDir() {
	return dirUniform;
}

GLint* Shader::getDeschidere() {
	return deschidereUniform;
}