#pragma once
#include "stdafx.h"
#include "../Utilities/rapidxml.hpp"
#include "ResourceManager.h"
#include "SceneManager.h"
#include <fstream>
#include <sstream>



SceneManager* SceneManager::sceneManager = NULL;

SceneManager* SceneManager::getsceneManager() {
	if (sceneManager == NULL) {
		sceneManager = new SceneManager();
	}
	return sceneManager;

}

void SceneManager::Init(std::string path) {
	
	rapidxml::xml_document<>doc;
	std::ifstream file(path.c_str());
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	rapidxml::xml_node<>* pcameras = doc.first_node()->first_node("cameras");
	backgroundColor.x = atoi(doc.first_node()->first_node("backgroundColor")->first_node("r")->value());
	backgroundColor.y = atoi(doc.first_node()->first_node("backgroundColor")->first_node("g")->value());
	backgroundColor.z = atoi(doc.first_node()->first_node("backgroundColor")->first_node("b")->value());

	//pentru camere

	for (rapidxml::xml_node<>*itercameras = pcameras->first_node("camera");itercameras; itercameras = itercameras->next_sibling()) {
		int id = atoi(itercameras->first_attribute("id")->value());

		rapidxml::xml_node<>* pos = itercameras->first_node("position");
		GLfloat posx = atof(pos->first_node("x")->value());
		GLfloat posy = atof(pos->first_node("y")->value());
		GLfloat posz = atof(pos->first_node("z")->value());
		Vector3 position(posx, posy, posz);

		rapidxml::xml_node<>* target = itercameras->first_node("target");
		GLfloat tarx = atof(target->first_node("x")->value());
		GLfloat tary = atof(target->first_node("y")->value());
		GLfloat tarz = atof(target->first_node("z")->value());
		Vector3 targ(tarx, tary, tarz);

		rapidxml::xml_node<>* ups = itercameras->first_node("up");
		GLfloat upx = atof(ups->first_node("x")->value());
		GLfloat upy = atof(ups->first_node("y")->value());
		GLfloat upz = atof(ups->first_node("z")->value());
		Vector3 up(upx, upy, upz);


		GLfloat translationSpeed = atof(itercameras->first_node("translationSpeed")->value());

		GLfloat rotationSpeed = atof(itercameras->first_node("rotationSpeed")->value());

		GLfloat fov = atof(itercameras->first_node("fov")->value());
		GLfloat nears = atof(itercameras->first_node("near")->value());
		GLfloat fars = atof(itercameras->first_node("far")->value());
		camere.insert(std::make_pair(id, new Camera(position, targ, up, translationSpeed, rotationSpeed, fov, nears, fars)));


	}
	camera_actuala = atoi(doc.first_node()->first_node("activeCamera")->value());
	rapidxml::xml_node<>* pobjects = doc.first_node()->first_node("objects");
	for (rapidxml::xml_node<>*iterobjects = pobjects->first_node("object"); iterobjects; iterobjects = iterobjects->next_sibling()) {
		int id = atoi(iterobjects->first_attribute("id")->value());
		Model* model = ResourceManager::getresourceManager()->loadModel(atoi(iterobjects->first_node("model")->value()));
		Shader* shader = ResourceManager::getresourceManager()->loadShader(atoi(iterobjects->first_node("shader")->value()));
		std::vector<Texture*> texturi;
		for (rapidxml::xml_node<>*itertex = iterobjects->first_node("textures")->first_node("texture"); itertex; itertex = itertex->next_sibling()) {
			texturi.push_back(ResourceManager::getresourceManager()->loadTexture(atoi(itertex->first_attribute("id")->value())));
		}
		printf("am citit texturi\n");
		Vector3 pos;
		pos.x = atoi(iterobjects->first_node("position")->first_node("x")->value());
		pos.y = atoi(iterobjects->first_node("position")->first_node("y")->value());
		pos.z = atoi(iterobjects->first_node("position")->first_node("z")->value());

		Vector3 rotation;
		rotation.x = atoi(iterobjects->first_node("rotation")->first_node("x")->value());
		rotation.y = atoi(iterobjects->first_node("rotation")->first_node("y")->value());
		rotation.z = atoi(iterobjects->first_node("rotation")->first_node("z")->value());

		Vector3 scale;
		scale.x = atoi(iterobjects->first_node("scale")->first_node("x")->value());
		scale.y = atoi(iterobjects->first_node("scale")->first_node("y")->value());
		scale.z = atoi(iterobjects->first_node("scale")->first_node("z")->value());

		bool depth_test = iterobjects->first_node("blend")->value() == "true" ? true : false;
		std::string tip = iterobjects->first_node("type")->value();
		if (tip == "normal") {
			obiecte.push_back(new SceneObject(tip, pos, rotation, scale, model, shader, texturi, depth_test));

		}
		printf("Am incarcat un obiect \n");
	}


}

Camera* SceneManager::getActiveCamera() {
	return camere[camera_actuala];
}

void SceneManager::Draw(ESContext* escontext) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 0.0f);

	for (auto obiect : obiecte) {
		obiect->Draw();
	}
	eglSwapBuffers(escontext->eglDisplay, escontext->eglSurface);
}