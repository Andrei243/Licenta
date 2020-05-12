#pragma once

#include "../NewTrainingFramework/GameManager.h"
#include "Scene1.h"

class ExampleGame :public GameManager {
	GLfloat deltaTime;
public:
	ExampleGame(int width, int height, std::string title) :GameManager() {
		this->width = width;
		this->height = height;
		this->title = title;
		addScene(new Scene1());
	}
	void Update(ESContext* escontext, float deltaTime) {
		this->deltaTime = deltaTime;
	}

	void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
	{

		if (bIsPressed) {
			getCurrentScene()->Key(key);

			switch (key) {
			case 97:
			case 65: {
				getCurrentScene()->getActiveCamera()->MoveOx(-1, deltaTime);
				break;

			}

			case 115:
			case 83: {
				getCurrentScene()->getActiveCamera()->MoveOz(1, deltaTime);
				break;
			}

			case 100:
			case 68: {
				getCurrentScene()->getActiveCamera()->MoveOx(1, deltaTime);
				break;
			}

			case 113:
			case 81: {
				getCurrentScene()->getActiveCamera()->MoveOy(1, deltaTime);
				break;
			}

			case 119:
			case 87: {
				getCurrentScene()->getActiveCamera()->MoveOz(-1, deltaTime);
				break;
			}

			case 101:
			case 69: {
				getCurrentScene()->getActiveCamera()->MoveOy(-1, deltaTime);
				break;
			}

			case VK_UP: {
				getCurrentScene()->getActiveCamera()->rotateOx(1, deltaTime);
				break;
			}
			case VK_DOWN: {
				getCurrentScene()->getActiveCamera()->rotateOx(-1, deltaTime);
				break;
			}

			case VK_LEFT: {
				getCurrentScene()->getActiveCamera()->rotateOy(1, deltaTime);
				break;
			}

			case VK_RIGHT: {
				getCurrentScene()->getActiveCamera()->rotateOy(-1, deltaTime);
				break;
			}

			case 111:
			case 79: {
				getCurrentScene()->getActiveCamera()->rotateOz(-1, deltaTime);
				break;
			}

			case 112:
			case 80: {
				getCurrentScene()->getActiveCamera()->rotateOz(1, deltaTime);
				break;
			}






			}

		}


	}
	void Mouse(Vector2 position, MouseButton button, bool isPressed) {}
};