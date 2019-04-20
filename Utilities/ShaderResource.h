#pragma once
#include <string>
#include "../Utilities/utilities.h"


class Shader;
class ResourceManager;

class ShaderResource {
	GLint id;
	std::string vs;
	std::string fs;
	friend class Shader;
	friend class ResourceManager;

};