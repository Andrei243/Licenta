#pragma once
#include "../Utilities/utilities.h"
#include <string>

class Texture {
	GLuint id;
	
public:
	
	GLuint getid();
	Texture(std::string type,std::string min_filter,std::string mag_filter,std::string wrap_s,std::string wrap_t,GLvoid* data,int width,int height,int pixelType);
	Texture(GLuint id);
	~Texture() {};
	void cleanUp();
};

