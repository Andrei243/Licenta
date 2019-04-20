#pragma once 

#include "stdafx.h"
#include <iostream>
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
	std::cout << vs;
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
	 uvAttribute = glGetAttribLocation(id_prog, "a_uv");


	texUniform = glGetUniformLocation(id_prog, "u_texture");

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
GLint Shader::getTexUn() {
	return texUniform;
}