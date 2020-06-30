#pragma once
#include "Scene1.h"
#include "ExampleGame.h"
#include "../NewTrainingFramework/CollisionExecutor.h"

class Scene1;

class BusCrocoCollider :public CollisionExecutor {
public:
	void OnCollisionEnter();
};