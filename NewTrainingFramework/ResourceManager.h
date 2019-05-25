#pragma once

#include "../Utilities/Model.h"
#include "../Utilities/Shader.h"
#include "../Utilities/Texture.h"
#include <map>
#include "../Utilities/fmod.h"
#include "../Utilities/fmod.hpp"




class ResourceManager {
private:
	static ResourceManager* resourceManager;
	FMOD::System* fmodSystem;
	ResourceManager() {};
	friend class Model;
	friend class Shader;
	friend class Texture;
	std::map<int, ShaderResource*> shaderresources;
	std::map<int, ModelResource*>modelresources;
	std::map<int, TextureResource*> textureresources;
	std::map<int, Model*>models;
	std::map<int, Shader*>shaders;
	std::map<int, Texture*>textures;
	std::map<int, Model*>modeleincarcate;
	std::map<int, Shader*>shadereincarcate;
	std::map<int, Texture*>texturiincarcate;
	std::map<int, std::string>suneteincarcate;

public:
	void Update();
	void playSound(int id);
	Shader* loadShader(GLint id);
	Model* loadModel(GLint id);
	Texture* loadTexture(GLint id);
	void Init(std::string xmlpath);
	static ResourceManager* getresourceManager();
};

