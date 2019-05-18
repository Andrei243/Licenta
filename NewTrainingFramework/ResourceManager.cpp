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



ResourceManager* ResourceManager::resourceManager = NULL;



ResourceManager* ResourceManager::getresourceManager() {

	if (!resourceManager) {
		resourceManager = new ResourceManager();
	}
	return resourceManager;

}


Model* ResourceManager::loadModel(GLint id) {
	if (getresourceManager()->modeleincarcate.find(id) != getresourceManager()->modeleincarcate.end()) {
		return getresourceManager()->modeleincarcate.at(id);
	}
	else {
		Model* modelact = new Model ( getresourceManager()->modelresources.at(id));
		modelact->Load();
		getresourceManager()->modeleincarcate.insert(std::make_pair(id, modelact));
		return modelact;


	}

}

Texture* ResourceManager::loadTexture(GLint id) {
	if (getresourceManager()->texturiincarcate.find(id) != getresourceManager()->texturiincarcate.end()) {
		return getresourceManager()->texturiincarcate.at(id);
	}
	else {
		Texture* texact = new Texture(getresourceManager()->textureresources.at(id));
		texact->Load();
		getresourceManager()->texturiincarcate.insert(std::make_pair(id, texact));
		return texact;
	}

}

Shader* ResourceManager::loadShader(GLint id) {
	if (getresourceManager()->shadereincarcate.find(id) != getresourceManager()->shadereincarcate.end()) {
		return getresourceManager()->shadereincarcate[id];
	}
	else {
		Shader* shaderact = new Shader(getresourceManager()->shaderresources.at(id));
		shaderact->Load();
		getresourceManager()->shadereincarcate.insert(std::make_pair(id, shaderact));
		return shaderact;


	}


}


void ResourceManager::Init(std::string xmlpath) {

	rapidxml::xml_document<>doc;
	std::ifstream file(xmlpath.c_str());
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	rapidxml::xml_node<>* pmodel = doc.first_node()->first_node("models");
	rapidxml::xml_node<>*pshader = doc.first_node()->first_node("shaders");
	rapidxml::xml_node<>*ptextures = doc.first_node()->first_node("textures");


	//pentru modele

	for (rapidxml::xml_node<>*itermodele = pmodel->first_node("model"); itermodele; itermodele = itermodele->next_sibling()) {
		int id = atoi(itermodele->first_attribute("id")->value());
		std::string path = itermodele->first_node("path")->value();
		ModelResource* mr = new ModelResource();
		mr->path = path;
		mr->id = id;
		modelresources.insert(std::make_pair(id, mr));

	}

	//pentru shadere
	for (rapidxml::xml_node<>*itershadere = pshader->first_node("shader"); itershadere; itershadere = itershadere->next_sibling()) {
		int id = atoi(itershadere->first_attribute("id")->value());
		std::string vs = itershadere->first_node("vs")->value();
		std::string fs = itershadere->first_node("fs")->value();
		ShaderResource* sr = new ShaderResource();
		sr->fs = fs;
		sr->id = id;
		sr->vs = vs;
		shaderresources.insert(std::make_pair(id, sr));
	}

	//pentru texturi

	for (rapidxml::xml_node<>*itertexturi = ptextures->first_node("texture"); itertexturi; itertexturi = itertexturi->next_sibling()) {
		int id = atoi(itertexturi->first_attribute("id")->value());
		std::string path = itertexturi->first_node("path")->value();
		std::string min_filter = itertexturi->first_node("min_filter")->value();
		std::string mag_filter = itertexturi->first_node("mag_filter")->value();
		std::string wrap_s = itertexturi->first_node("wrap_s")->value();
		std::string wrap_t = itertexturi->first_node("wrap_t")->value();
		TextureResource* tr = new TextureResource();
		tr->id = id;
		tr->path = path;
		tr->mag_filter = mag_filter;
		tr->min_filter = min_filter;
		tr->wrap_s = wrap_s;
		tr->wrap_t = wrap_t;
		textureresources.insert(std::make_pair(id, tr));
	}

}

