#pragma once

#include "BusCrocoCollider.h"

void BusCrocoCollider::OnCollisionEnter() {

	Scene1* scene = dynamic_cast<Scene1*>(GameManager::getGameManager()->getCurrentScene());
	scene->getResourceManager()->playSound(1);
	scene->setBusOnFire();
}