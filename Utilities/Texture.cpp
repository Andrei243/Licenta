#pragma once

#include "stdafx.h"
#include "Texture.h"

GLuint Texture::getid() {
	return id;
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
	Texture* texture = new Texture();
	int width, height, bpp;
	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture->id);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, procesare_stringuri(min_filter));
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, procesare_stringuri(mag_filter));
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, procesare_stringuri(wrap_s));
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, procesare_stringuri(wrap_t));

	GLvoid* tga = (GLvoid*)LoadTGA(path.c_str(), &width, &height, &bpp);
	if (bpp == 32) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tga);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tga);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tga);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tga);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tga);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tga);

	}
	else if (bpp == 24) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tga);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tga);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tga);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tga);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tga);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tga);

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