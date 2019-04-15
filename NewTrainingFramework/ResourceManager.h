#pragma once

#include "../Utilities/Model.h"
#include "../Utilities/Shader.h"
#include "../Utilities/Texture.h"
#include <map>



class ResourceManager {
private:
	static ResourceManager* resourceManager;
	//ResourceManager() {};


public:
	void Init(std::string xmlpath);
	static ResourceManager* getresourceManager();
	//static void freeResources();
	//ModelResource* mr;
	//ShaderResource* sr;
	//TextureResource* tr;
	//Model* modele;
	//Shader* shadere;
	//Texture* texturi;
	std::map<int, ShaderResource*> shaderresources;
	std::map<int, ModelResource*>modelresources;
	std::map<int, TextureResource*> textureresources;
	std::map<int, Model*>models;
	std::map<int, Shader*>shaders;
	std::map<int, Texture*>textures;
	std::map<int, Model*>modeleincarcate;
	std::map<int, Shader*>shadereincarcate;
	std::map<int, Texture*>texturiincarcate;

	Shader* loadShader(GLint id);
	Model* loadModel(GLint id);
	Texture* loadTexture(GLint id);

};

