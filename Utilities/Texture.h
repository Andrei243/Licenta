#pragma once
#include "utilities.h"
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

namespace ceutils {
	Texture* generateFromTGA( ::std::string min_filter, ::std::string mag_filter, ::std::string wrap_s, ::std::string wrap_t, ::std::string path);
	Texture* generateSkyboxFromTGA(::std::string path, ::std::string min_filter, ::std::string mag_filter, ::std::string wrap_s, ::std::string wrap_t);
	Texture* generateFromPhoto(::std::string min_filter, ::std::string mag_filter, ::std::string wrap_s, ::std::string wrap_t, ::std::string path);
}

