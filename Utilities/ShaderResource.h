#pragma once
#include "../Utilities/rapidxml.hpp"
#include "../Utilities/utilities.h"
#include <string>

class Shader;
class ResourceManager;

class ShaderResource {
	GLint id;
	std::string vs;
	std::string fs;
	friend class Shader;
	friend class ResourceManager;

};