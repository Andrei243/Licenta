#pragma once

#include "stdafx.h"
#include "ResourceManager.h"
#include "../Utilities/Model.h"
#include "../Utilities/Shader.h"
#include "../Utilities/Texture.h"
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <iostream>
#include "../Utilities/fmod.h"
#include "../Utilities/fmod.hpp"


void ResourceManager::playSound(int id) {
	FMOD::Sound* sound = sounds[id];

	if (fmodSystem->playSound(sound, 0, false, 0)!=FMOD_OK) 
	{std::cout<<"Ceva e gresit\n" ; }
}
void ResourceManager::Update() {
	fmodSystem->update();
}

void ResourceManager::addModel(int id, Model* model) {
	if (models.find(id) != models.end()) {
		delete models[id];
	}
	models.insert(std::make_pair(id, model));
}
void ResourceManager::addShader(int id, Shader* shader) {
	if (shaders.find(id) != shaders.end()) {
		delete shaders[id];
	}
	shaders.insert(std::make_pair(id, shader));
}
void ResourceManager::addTexture(int id, Texture* texture) {
	if (textures.find(id) != textures.end()) {
		delete textures[id];
	}
	textures.insert(std::make_pair(id, texture));
}

void ResourceManager::cleanUp() {
	for (auto model : models) {
		delete model.second;
	}
	models.clear();
	for (auto texture : textures) {
		delete texture.second;
	}
	textures.clear();
	for (auto shader:shaders) {
		delete shader.second;
	}
	shaders.clear();
}

ResourceManager::~ResourceManager() {
	cleanUp();
	fmodSystem->close();
}

void ResourceManager::releaseModel(int id) {
	if (models.find(id) == models.end())return;
	delete models[id];
	models.erase(id);
}
void ResourceManager::releaseShader(int id) {
	if (shaders.find(id) != shaders.end())return;
	delete shaders[id];
	shaders.erase(id);
}
void ResourceManager::releaseTexture(int id) {
	if (textures.find(id) != textures.end())return;
	delete textures[id];
	textures.erase(id);
}
void ResourceManager::releaseSound(int id) {
	delete sounds[id];
	sounds.erase(id);
}

void ResourceManager::addSound(int id, std::string path,FMOD_MODE mode) {
	FMOD::Sound* sound;
	fmodSystem->createSound(path.c_str(), mode, 0,&sound);
	if (sounds.find(id) != sounds.end()) {
		delete sounds[id];
	}
	sounds.insert(std::make_pair(id, sound));
}

Model* ResourceManager::getModel(int id) {
	Model* model = models[id];
	if (model == NULL) {
		throw std::string("Model with id ") + std::to_string(id) + std::string(" could not be found");
	}
	return model;
}

Texture* ResourceManager::getTexture(int id) {
	Texture* texture = textures[id];
	if (texture == NULL) {
		throw std::string("Model with id ") + std::to_string(id) + std::string(" could not be found");
	}
	return texture;
}

Shader* ResourceManager::getShader(int id) {
	Shader* shader = shaders[id];
	if (shader == NULL) {
		throw std::string("Model with id ") + std::to_string(id) + std::string(" could not be found");
	}
	return shader;
}

ResourceManager::ResourceManager() {
	if (FMOD::System_Create(&fmodSystem) != FMOD_OK) {
		std::cout << "Sounds can't be loaded\n";
	}
	else {
		int driverCount = 0;
		fmodSystem->getNumDrivers(&driverCount);
		if (driverCount == 0) {
			std::cout << "Ceva e in neregula cu sunetul\n";
		}

		fmodSystem->init(36, FMOD_INIT_NORMAL, NULL);
	}
}