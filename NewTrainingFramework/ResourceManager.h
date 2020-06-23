#pragma once

#include "../Utilities/Model.h"
#include "../Utilities/Shader.h"
#include "../Utilities/Texture.h"
#include <map>
#include "../Utilities/fmod.h"
#include "../Utilities/fmod.hpp"




class ResourceManager {
private:
	FMOD::System* fmodSystem;
	
	std::map<int, Model*>models;
	std::map<int, Shader*>shaders;
	std::map<int, Texture*>textures;
	std::map<int, FMOD::Sound*>sounds;

public:
	ResourceManager();
	void Update();
	void playSound(int id);
	void addModel(int id, Model* model);
	void addShader(int id, Shader* shader);
	void addTexture(int id, Texture* texture);
	void addSound(int id, std::string path, FMOD_MODE mode);
	void releaseModel(int id);
	void releaseShader(int id);
	void releaseTexture(int id);
	void releaseSound(int id);
	Model* getModel(int id);
	Shader* getShader(int id);
	Texture* getTexture(int id);
	~ResourceManager();
	void cleanUp();
};

