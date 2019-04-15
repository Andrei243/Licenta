#pragma once
#include "../Utilities/rapidxml.hpp"
#include "../Utilities/utilities.h"
#include <string>


class Model;
class ResourceManager;

class ModelResource {
	GLint id;
	std::string path;
	friend class Model;
	friend class ResourceManager;


};