#pragma once

#include "stdafx.h"
#include "../Utilities/rapidxml.hpp"
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
	models.insert(std::make_pair(id, model));
}
void ResourceManager::addShader(int id, Shader* shader) {
	shaders.insert(std::make_pair(id, shader));
}
void ResourceManager::addTexture(int id, Texture* texture) {
	textures.insert(std::make_pair(id, texture));
}

void ResourceManager::cleanUp() {
	for (auto model : models) {
		delete model.second;
	}
	for (auto texture : textures) {
		delete texture.second;
	}
	for (auto shader:shaders) {
		delete shader.second;
	}
}

ResourceManager::~ResourceManager() {
	cleanUp();
	fmodSystem->close();
	delete fmodSystem;
}

void ResourceManager::addSound(int id, std::string path,FMOD_MODE mode) {
	FMOD::Sound* sound;
	fmodSystem->createSound(path.c_str(), mode, 0,&sound);
	sounds.insert(std::make_pair(id, sound));
}

Model* ResourceManager::getModel(int id) {
	return models[id];
}

Texture* ResourceManager::getTexture(int id) {
	return textures[id];
}

Shader* ResourceManager::getShader(int id) {
	return shaders[id];
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