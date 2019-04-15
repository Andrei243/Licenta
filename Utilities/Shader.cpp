#pragma once 

#include "stdafx.h"
#include "Shader.h"
#include "ShaderResource.h"

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

}

Shader::Shader(ShaderResource* resursa) {
	this->mr = resursa;
	this->Load();

}