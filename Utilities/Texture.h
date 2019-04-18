#pragma once
#include "TextureResource.h"

class Texture {
	TextureResource* tr;
	GLuint id;

	
public:
	void Load();
	GLuint getid();
	Texture(TextureResource* tr);
	~Texture() {};
};

