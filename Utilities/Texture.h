#pragma once
#include "TextureResource.h"

class Texture {
	TextureResource* tr;
	GLuint id;

	
public:
	void Load();
	Texture(TextureResource* tr);
	~Texture() {};
};

