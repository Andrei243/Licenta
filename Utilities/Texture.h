#pragma once
#include "TextureResource.h"

class Texture {
	TextureResource* tr;
	GLuint id;

	
public:
	static Texture* generareSkybox(std::string path,
		std::string type,
		std::string min_filter,
		std::string mag_filter,
		std::string wrap_s,
		std::string wrap_t);
	void Load();
	GLuint getid();
	Texture() {};
	Texture(TextureResource* tr);
	~Texture() {};
};

