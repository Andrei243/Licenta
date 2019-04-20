#pragma once
#include <string>
#include "../Utilities/utilities.h"


class Texture;
class ResourceManager;

class TextureResource {
	friend class Texture;
	friend class ResourceManager;
	GLint id;
	std::string type;
	std::string path;
	std::string min_filter;
	std::string mag_filter;
	std::string wrap_s;
	std::string wrap_t;


};