#pragma once
#include <vector>
#include "SceneManager.h"

enum MouseButton { LeftClick, RightClick };

class GameManager {
	static GameManager* gameManager;
	std::vector<SceneManager*> scenes;
	int sceneNumber;
	int width, height;
	std::string title;
	ESContext context;
protected:
	GameManager();
public:
	SceneManager* getCurrentScene();
	void setCurrentScene(int id);
	ResourceManager* getCurrentResourceManager();
	virtual void Draw(ESContext* esContext);
	virtual void Update(ESContext* esContext, float deltaTime);
	virtual void Key(ESContext* esContext, unsigned char key, bool bIsPressed) = 0;
	virtual void Init(ESContext* esContext);
	virtual void Mouse(Vector2 position,MouseButton button, bool isPressed) = 0;
	void addScene(SceneManager* scene);
	void Play();
	static GameManager* getGameManager();
	static void setGameManager(GameManager* manager);

};