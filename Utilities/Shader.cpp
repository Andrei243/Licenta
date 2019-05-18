#pragma once 

#include "stdafx.h"
#include <iostream>
#include <fstream>
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

Shader::~Shader() {
	delete mr;
}