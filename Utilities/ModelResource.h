#pragma once
#include <string>
#include "../Utilities/utilities.h"



class Model;
class ResourceManager;

class ModelResource {
	GLint id;
	std::string path;
	friend class Model;
	friend class ResourceManager;


};