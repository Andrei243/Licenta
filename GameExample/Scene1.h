#pragma once
#include "../NewTrainingFramework/SceneManager.h"
#include "../NewTrainingFramework/Terrain.h"
#include "../NewTrainingFramework/SkyBox.h"
#include "CrocoObject.h"

class Scene1 :public SceneManager {

	void Init() {
		resourceManager = new ResourceManager();
		resourceManager->addModel(1, ceutils::generateModelFromNFG("Resources/Models/croco.nfg"));
		resourceManager->addModel(2, ceutils::generateModelFromNFG("Resources/Models/bus.nfg"));
		resourceManager->addModel(3, ceutils::generateModelFromNFG("Resources/Models/fire.nfg"));
		resourceManager->addModel(4, ceutils::generateSkyboxModel(500));
		resourceManager->addModel(5, Terrain::generateModel(-50, 500, 10));

		resourceManager->addShader(1, new Shader("Resources/Shaders/TriangleShaderVS.vs", "Resources/Shaders/TriangleShaderFS.fs"));
		resourceManager->addShader(2, new Shader("Resources/Shaders/Fire.vs", "Resources/Shaders/Fire.fs"));
		resourceManager->addShader(3, new Shader("Resources/Shaders/TerrainShaderVS.vs", "Resources/Shaders/TerrainShaderFS.fs"));
		resourceManager->addShader(4, new Shader("Resources/Shaders/SkyboxShaderVS.vs", "Resources/Shaders/SkyboxShaderFS.fs"));

		resourceManager->addTexture(1, ceutils::generateFromTGA("LINEAR", "LINEAR", "CLAMP_TO_EDGE", "CLAMP_TO_EDGE", "Resources/Textures/croco.tga"));
		resourceManager->addTexture(2, ceutils::generateFromTGA("LINEAR", "LINEAR", "CLAMP_TO_EDGE", "CLAMP_TO_EDGE", "Resources/Textures/bus.tga"));
		resourceManager->addTexture(3, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/fire3.tga"));
		resourceManager->addTexture(4, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/fire_mask.tga"));
		resourceManager->addTexture(5, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/DisplacementMap.tga"));
		resourceManager->addTexture(6, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/dirt.tga"));
		resourceManager->addTexture(7, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/rock.tga"));
		resourceManager->addTexture(8, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/Grass.tga"));
		resourceManager->addTexture(9, ceutils::generateFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/Terrain_blend_map.tga"));
		resourceManager->addTexture(10, ceutils::generateSkyboxFromTGA("LINEAR", "LINEAR", "GL_REPEAT", "GL_REPEAT", "Resources/Textures/envMap.tga"));

		resourceManager->addSound(1, "Resources/Sounds/hapciu.wav", FMOD_LOOP_OFF);

		r = 2000;
		R = 5000;
		setFogColor(Vector3(0.3f, 0, 0.4f));

		backgroundColor.x = backgroundColor.y = backgroundColor.z = 1;
		addCamera(1, new Camera(Vector3(0, 0, 1), Vector3(0, 0, -1), Vector3(0, 1, 0), 500, 4, 45, 0.2, 100000));
		setActiveCamera(1);
		setAmbientLight(Vector3(1, 1, 1), 0.5);
		addObject(1, new Crocodil(1, "normal", Vector3(20, 20, -800), Vector3(0, 3.14f, 0), Vector3(1, 1, 1), resourceManager->getModel(1), resourceManager->getShader(1), std::vector<Texture*>(1, resourceManager->getTexture(1)), true));
		addObject(2, new Terrain(2, "terrain", Vector3(0, 0, 0), Vector3(1, 1, 1), resourceManager->getModel(5), resourceManager->getShader(3), std::vector<Texture*>{resourceManager->getTexture(6), resourceManager->getTexture(7), resourceManager->getTexture(8), resourceManager->getTexture(9)}, true, 10, 500, -100, Vector3(50, -20, 30)));
		addObject(3, new SkyBox(3, "skybox", Vector3(0, 0, 0), Vector3(180, 0, 0), Vector3(5, 5, 5), resourceManager->getModel(4), resourceManager->getShader(4), std::vector<Texture*>{resourceManager->getTexture(10)}, true));
	}

};