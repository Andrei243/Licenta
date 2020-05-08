#pragma once
#include "stdafx.h"
#include "../Utilities/rapidxml.hpp"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Terrain.h"
#include "SkyBox.h"
#include "Bus.h"
#include "Fire.h"
#include "Croco.h"
#include <fstream>
#include <sstream>


//void SceneManager::Init(std::string path) {
//	
//	rapidxml::xml_document<>doc;
//	std::ifstream file(path.c_str());
//	std::stringstream buffer;
//	buffer << file.rdbuf();
//	file.close();
//	std::string content(buffer.str());
//	doc.parse<0>(&content[0]);
//
//	rapidxml::xml_node<>* pcameras = doc.first_node()->first_node("cameras");
//	backgroundColor.x = atoi(doc.first_node()->first_node("backgroundColor")->first_node("r")->value());
//	backgroundColor.y = atoi(doc.first_node()->first_node("backgroundColor")->first_node("g")->value());
//	backgroundColor.z = atoi(doc.first_node()->first_node("backgroundColor")->first_node("b")->value());
//
//	r = atof(doc.first_node()->first_node("fog")->first_node("r")->value());
//	R = atof(doc.first_node()->first_node("fog")->first_node("R")->value());
//	fogcol.x = atof(doc.first_node()->first_node("fog")->first_node("color")->first_node("r")->value());
//	fogcol.y = atof(doc.first_node()->first_node("fog")->first_node("color")->first_node("g")->value());
//	fogcol.z = atof(doc.first_node()->first_node("fog")->first_node("color")->first_node("b")->value());
//
//
//	//pentru camere
//
//	for (rapidxml::xml_node<>*itercameras = pcameras->first_node("camera");itercameras; itercameras = itercameras->next_sibling()) {
//		int id = atoi(itercameras->first_attribute("id")->value());
//
//		rapidxml::xml_node<>* pos = itercameras->first_node("position");
//		GLfloat posx = atof(pos->first_node("x")->value());
//		GLfloat posy = atof(pos->first_node("y")->value());
//		GLfloat posz = atof(pos->first_node("z")->value());
//		Vector3 position(posx, posy, posz);
//
//		rapidxml::xml_node<>* target = itercameras->first_node("target");
//		GLfloat tarx = atof(target->first_node("x")->value());
//		GLfloat tary = atof(target->first_node("y")->value());
//		GLfloat tarz = atof(target->first_node("z")->value());
//		Vector3 targ(tarx, tary, tarz);
//
//		rapidxml::xml_node<>* ups = itercameras->first_node("up");
//		GLfloat upx = atof(ups->first_node("x")->value());
//		GLfloat upy = atof(ups->first_node("y")->value());
//		GLfloat upz = atof(ups->first_node("z")->value());
//		Vector3 up(upx, upy, upz);
//
//
//		GLfloat translationSpeed = atof(itercameras->first_node("translationSpeed")->value());
//
//		GLfloat rotationSpeed = atof(itercameras->first_node("rotationSpeed")->value());
//
//		GLfloat fov = atof(itercameras->first_node("fov")->value());
//		GLfloat nears = atof(itercameras->first_node("near")->value());
//		GLfloat fars = atof(itercameras->first_node("far")->value());
//		camere.insert(std::make_pair(id, new Camera(position, targ, up, translationSpeed, rotationSpeed, fov, nears, fars)));
//
//
//	}
//
//	rapidxml::xml_node<>* plights = doc.first_node()->first_node("lights");
//	for (rapidxml::xml_node<>* iterlights = plights->first_node("light"); iterlights; iterlights = iterlights->next_sibling()) {
//		int id = atoi(iterlights->first_attribute("id")->value());
//		Vector3 diff;
//		diff.x = atof(iterlights->first_node("diffuseColor")->first_node("r")->value());
//		diff.y = atof(iterlights->first_node("diffuseColor")->first_node("g")->value());
//		diff.z = atof(iterlights->first_node("diffuseColor")->first_node("b")->value());
//
//		Vector3 spec;
//		spec.x = atof(iterlights->first_node("specularColor")->first_node("r")->value());
//		spec.y = atof(iterlights->first_node("specularColor")->first_node("g")->value());
//		spec.z = atof(iterlights->first_node("specularColor")->first_node("b")->value());
//
//		std::string tip = iterlights->first_node("type")->value();
//
//		if (tip == "point") {
//			Vector3 pos;
//			pos.x = atof(iterlights->first_node("position")->first_node("x")->value());
//			pos.y = atof(iterlights->first_node("position")->first_node("y")->value());
//			pos.z = atof(iterlights->first_node("position")->first_node("z")->value());
//			lights.insert(std::make_pair(id, new PointLight(spec, diff, id, pos)));
//		}
//		else if (tip == "directional") {
//			Vector3 dir;
//			dir.x = atof(iterlights->first_node("direction")->first_node("x")->value());
//			dir.y = atof(iterlights->first_node("direction")->first_node("y")->value());
//			dir.z = atof(iterlights->first_node("direction")->first_node("z")->value());
//			lights.insert(std::make_pair(id, new DirectionalLight(spec, diff, id, dir)));
//		}
//		else if (tip == "spotlight") {
//			Vector3 pos;
//			pos.x = atof(iterlights->first_node("position")->first_node("x")->value());
//			pos.y = atof(iterlights->first_node("position")->first_node("y")->value());
//			pos.z = atof(iterlights->first_node("position")->first_node("z")->value());
//
//			Vector3 dir;
//			dir.x = atof(iterlights->first_node("direction")->first_node("x")->value());
//			dir.y = atof(iterlights->first_node("direction")->first_node("y")->value());
//			dir.z = atof(iterlights->first_node("direction")->first_node("z")->value());
//
//			float unghiDeschidere = atof(iterlights->first_node("unghiDeschidere")->value());
//
//			lights.insert(std::make_pair(id, new SpotLight(spec, diff, id, unghiDeschidere, pos, dir)));
//		}
//
//	}
//	ambientLight = new AmbientLight();
//	ambientLight->diff.x = atof(doc.first_node()->first_node("ambientalLight")->first_node("color")->first_node("r")->value());
//	ambientLight->diff.y = atof(doc.first_node()->first_node("ambientalLight")->first_node("color")->first_node("g")->value());
//	ambientLight->diff.z = atof(doc.first_node()->first_node("ambientalLight")->first_node("color")->first_node("b")->value());
//	ambientLight->spec = ambientLight->diff;
//	ambientLight->ratio = atof(doc.first_node()->first_node("ambientalLight")->first_node("ratio")->value());
//
//
//	currentCamera = atoi(doc.first_node()->first_node("activeCamera")->value());
//	rapidxml::xml_node<>* pobjects = doc.first_node()->first_node("objects");
//	int count = 0;
//	for (rapidxml::xml_node<>*iterobjects = pobjects->first_node("object"); iterobjects; iterobjects = iterobjects->next_sibling()) {
//		int id = atoi(iterobjects->first_attribute("id")->value());
//		Model* model;
//		{std::string mod = iterobjects->first_node("model")->value();
//		if (mod == "generated")model = NULL;
//		else model = ResourceManager::getresourceManager()->loadModel(atoi(iterobjects->first_node("model")->value()));
//		}
//		Shader* shader = ResourceManager::getresourceManager()->loadShader(atoi(iterobjects->first_node("shader")->value()));
//		std::vector<Texture*> texturi;
//		for (rapidxml::xml_node<>*itertex = iterobjects->first_node("textures")->first_node("texture"); itertex; itertex = itertex->next_sibling()) {
//			texturi.push_back(ResourceManager::getresourceManager()->loadTexture(atoi(itertex->first_attribute("id")->value())));
//		}
//		Vector3 pos;
//		pos.x = atof(iterobjects->first_node("position")->first_node("x")->value());
//		pos.y = atof(iterobjects->first_node("position")->first_node("y")->value());
//		pos.z = atof(iterobjects->first_node("position")->first_node("z")->value());
//
//		Vector3 rotation;
//		rotation.x = atof(iterobjects->first_node("rotation")->first_node("x")->value());
//		rotation.y = atof(iterobjects->first_node("rotation")->first_node("y")->value());
//		rotation.z = atof(iterobjects->first_node("rotation")->first_node("z")->value());
//
//		Vector3 scale;
//		scale.x = atof(iterobjects->first_node("scale")->first_node("x")->value());
//		scale.y = atof(iterobjects->first_node("scale")->first_node("y")->value());
//		scale.z = atof(iterobjects->first_node("scale")->first_node("z")->value());
//
//		
//		std::string blend = iterobjects->first_node("blend")->value();
//		bool depthTest;
//		if (blend == "true") {
//			depthTest = true;
//		}
//		else {
//			depthTest = false;
//		}
//		std::string tip = iterobjects->first_node("type")->value();
//		if (tip == "skybox") {
//			int offSet = atoi(iterobjects->first_node("offSetY")->value());
//			objects.insert(std::make_pair(id,new SkyBox(id, tip, pos, rotation, scale, model, shader, texturi,depthTest, offSet)));
//		}
//		else if (tip == "terrain") {
//			int nr_celule, dimensiuneCelula, offSetY;
//			nr_celule = atoi(iterobjects->first_node("nrCelule")->value());
//			dimensiuneCelula = atoi(iterobjects->first_node("dimensiuneCelula")->value());
//			offSetY = atoi(iterobjects->first_node("offSetY")->value());
//			Vector3 height;
//			height.x = atoi(iterobjects->first_node("inaltimi")->first_node("r")->value());
//			height.y = atoi(iterobjects->first_node("inaltimi")->first_node("g")->value());
//			height.z = atoi(iterobjects->first_node("inaltimi")->first_node("b")->value());
//
//			objects.insert(std::make_pair(id,new Terrain(id,tip,pos,rotation,scale,model,shader,texturi,depthTest,nr_celule,dimensiuneCelula,offSetY,height)));
//		}
//		else if (tip == "croco") {
//			objects.insert(std::make_pair(id,new Crocodil(id, tip, pos, rotation, scale, model, shader, texturi, depthTest)));
//		}
//		else if (tip == "bus") {
//			objects.insert(std::make_pair(id,new Bus(id, tip, pos, rotation, scale, model, shader, texturi, depthTest)));
//
//		}
//		else if (tip == "fire") {
//			float dismax = atof(iterobjects->first_node("displ_max")->value());
//			objects.insert(std::make_pair(id,new Fire(id, tip, pos, rotation, scale, model, shader, texturi, depthTest,dismax)));
//
//		}
//		else if (tip == "normal") {
//			objects.insert(std::make_pair(id,new SceneObject(id,tip, pos, rotation, scale, model, shader, texturi, depthTest)));
//
//		}
//		if (iterobjects->first_node("lights") != 0) {
//			for (rapidxml::xml_node<>* iterlumini = iterobjects->first_node("lights")->first_node("light"); iterlumini; iterlumini = iterlumini->next_sibling()) {
//				objects[count++]->adaugaLumina(atoi(iterlumini->value()));
//
//			}
//		}
//	}
//
//
//
//}

Camera* SceneManager::getActiveCamera() {
	return camere[currentCamera];
}

void SceneManager::Draw(ESContext* escontext) {
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 0.0f);

	for (auto obiect : objects) {
		obiect.second->Draw();
	}


}

void SceneManager::Update(float deltaTime) {
	for (auto obiect : objects) {
		obiect.second->Update(deltaTime);
	}
	resourceManager->Update();


}

void SceneManager::Key(unsigned char key) {

	for (auto obiect : objects) {
		obiect.second->Key(key);
	}
	
}

void SceneManager::verifyCollisions() {
	
	for (auto collision : collisions) {
		bool colizionat = Paralelipiped::verificaColiziune(objects[collision.first.first]->getBoundingBox(), objects[collision.first.second]->getBoundingBox());
		if (colizionat) {
			if (isCollided.find(collision.first) != isCollided.end()) {
				for (auto collisionExecutor : collision.second) {
					collisionExecutor.OnCollisionContinuing();
				}
			}
			else {
				isCollided.insert(collision.first);
				for (auto collisionExecutor : collision.second) {
					collisionExecutor.OnCollisionEnter();
				}

			}
		}
		else {
			if (isCollided.find(collision.first) != isCollided.end()) {
				isCollided.erase(collision.first);
				for (auto collisionExecutor : collision.second) {
					collisionExecutor.OnCollisionExit();
				}
			}
		}
	}
}

ResourceManager* SceneManager::getResourceManager() {
	return this->resourceManager;
}
void SceneManager::setBackgroundColor(Vector3 color) {
	backgroundColor = color;
}

void SceneManager::setFogColor(Vector3 color) {
	fogcol = color;
}

void SceneManager::addCamera(int id, Camera* camera) {
	camere.insert(std::make_pair(id, camera));
}

void SceneManager::setActiveCamera(int id) {
	currentCamera = id;
}

void SceneManager::addLight(int id, Light* light) {
	lights.insert(std::make_pair(id, light));
}

void SceneManager::addObject(int id, SceneObject* object) {
	objects.insert(std::make_pair(id, object));
}

void SceneManager::setAmbientLight( Vector3 diff, double ratio) {
	ambientLight = new AmbientLight();
	ambientLight->diff = diff;
	ambientLight->spec = ambientLight->diff;
	ambientLight->ratio = ratio;
}

SceneManager::SceneManager() {
	resourceManager = new ResourceManager();
}

void SceneManager::cleanUp() {
	resourceManager->cleanUp();
}

void SceneManager::deleteObject(int id) {
	delete objects[id];
	objects.erase(id);
	for (auto it = collisions.begin();; it != collisions.end()) {
		if (it->first.first == id || it->first.second == id) {
			it = collisions.erase(it);
		}
		else {
			++it;
		}
	}
}