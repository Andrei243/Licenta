#pragma once

#include "stdafx.h"
#include "Texture.h"
#include <iostream>

GLuint Texture::getid() {
	return id;
}

void inversare_vector(char* vec, int lungime) {
	for (int i = 0; i < lungime / 2; i++) {
		char aux = vec[i];
		vec[i] = vec[lungime - i];
		vec[lungime - i] - aux;
	}


}

GLint procesare_stringuri(std::string nume) {
	if (nume == "NEAREST")return GL_NEAREST;
	else if (nume == "LINEAR")return GL_LINEAR;
	else if (nume == "NEAREST_MIPMAP_NEAREST")return GL_NEAREST_MIPMAP_NEAREST;
	else if (nume == "LINEAR_MIPMAP_NEAREST")return GL_LINEAR_MIPMAP_NEAREST;
	else if (nume == "NEAREST_MIPMAP_LINEAR")return GL_NEAREST_MIPMAP_LINEAR;
	else if (nume == "LINEAR_MIPMAP_LINEAR")return GL_LINEAR_MIPMAP_LINEAR;
	else if (nume == "CLAMP_TO_EDGE")return GL_CLAMP_TO_EDGE;
	else if (nume == "MIRRORED_REPEAT")return GL_MIRRORED_REPEAT;
	else if (nume == "REPEAT")return GL_REPEAT;
	else return -1;


}

Texture::Texture(TextureResource* tr) {
	this->tr = tr;
}
Texture* Texture::generareSkybox(std::string path,
	std::string type,
	std::string min_filter,
	std::string mag_filter,
	std::string wrap_s,
	std::string wrap_t) {
	std::cout << "Generare skybox" << "\n";
	Texture* texture = new Texture();
	int width, height, bpp;
	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture->id);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, procesare_stringuri(min_filter));
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, procesare_stringuri(mag_filter));
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, procesare_stringuri(wrap_s));
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, procesare_stringuri(wrap_t));
	int tip;
	GLvoid* tga = (GLvoid*)LoadTGA(path.c_str(), &width, &height, &bpp);
	char* text = (char*)tga;
	//for (int i = 0; i < height*width*bpp / 8; i++)std::cout << text[i];
	int nr_oct;
	if (bpp == 32) {
		tip = GL_RGBA;
		nr_oct = 4;

	}
	else if (bpp == 24) {
		tip = GL_RGB;
		nr_oct = 3;
	}
	//char* minitga1 = new char[(width / 4) * (height / 3)*nr_oct];
	//for (int i = 0; i < height / 3; i++) {
		//for (int j = 0; j < width / 4; j++) {
			//for(int k=0;k<nr_oct;k++)
			//minitga1[i*width * nr_oct/4 + j * nr_oct+k] = text[i*width * nr_oct + width / 4 + j * nr_oct+k];

		//}
	//}

	//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, tip, width/4, height/3, 0, tip, GL_UNSIGNED_BYTE, minitga1);
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, tip, width/4, height/3, 0, tip, GL_UNSIGNED_BYTE, minitga1);
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, tip, width/4, height/3, 0, tip, GL_UNSIGNED_BYTE, minitga1);
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, tip, width/4, height/3, 0, tip, GL_UNSIGNED_BYTE, minitga1);
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, tip, width/4, height/3, 0, tip, GL_UNSIGNED_BYTE, minitga1);
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, tip, width/4, height/3, 0, tip, GL_UNSIGNED_BYTE, minitga1);
	//delete minitga1;
	char** minitga = new char*[6];
	for (int idx = 0; idx < 6; idx++) {
		minitga[idx] = new char[(width / 4) * (height / 3) * nr_oct];
	}

	for (int i = 0; i < height / 3; i++) {
		for (int j = 0; j < width / 4; j++) {
			for (int k = 0; k < nr_oct; k++) {
				minitga[2][i*width * nr_oct / 4 + j * nr_oct + k] = text[i*width * nr_oct + width / 4 * nr_oct + j * nr_oct + k]; // 2
				minitga[3][i*width * nr_oct / 4 + j * nr_oct + k] = text[i*width * nr_oct + height / 3 * 2 * width * nr_oct + width / 4 * nr_oct + j * nr_oct + k];  // 3
				minitga[1][i*width * nr_oct / 4 + j * nr_oct + k] = text[i*width * nr_oct + height / 3 * width * nr_oct + j * nr_oct + k];
				minitga[4][i*width * nr_oct / 4 + j * nr_oct + k] = text[i*width * nr_oct + height / 3 * width * nr_oct + width / 4 * nr_oct + j * nr_oct + k];
				minitga[0][i*width * nr_oct / 4 + j * nr_oct + k] = text[i*width * nr_oct + height / 3 * width * nr_oct + 2 * width / 4 * nr_oct + j * nr_oct + k];
				minitga[5][i*width * nr_oct / 4 + j * nr_oct + k] = text[i*width * nr_oct + height / 3 * width * nr_oct + 3 * width / 4 * nr_oct + j * nr_oct + k];

			}
		}
	}
	

	for (int idx = 0; idx < 6; idx++) {
		//inversare_vector(minitga[idx], (width / 4) * (height / 3) * nr_oct);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + idx, 0, tip, width / 4, height / 3, 0, tip, GL_UNSIGNED_BYTE, minitga[idx]);
	}


	return texture;
}

void Texture::Load() {
	std::string path = tr->path;
	std::string type = tr->type;
	std::string min_filter = tr->min_filter;
	std::string mag_filter = tr->mag_filter;
	std::string wrap_s = tr->wrap_s;
	std::string wrap_t = tr->wrap_t;
	int width, height,bpp;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, procesare_stringuri(min_filter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, procesare_stringuri(mag_filter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, procesare_stringuri(wrap_s));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, procesare_stringuri(wrap_t));

	GLvoid* tga = (GLvoid*)LoadTGA(path.c_str(), &width, &height, &bpp);
	if (bpp == 32) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tga);
	}
	else if (bpp == 24) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tga);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	
}