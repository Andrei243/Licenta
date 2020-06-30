#pragma once
#include <vector>
#include "SceneManager.h"

enum MouseButton { LeftClick, RightClick };

class GameManager {
	static GameManager* gameManager;
	std::vector<SceneManager*> scenes;
	ESContext context;
	static void setGameManager(GameManager* manager);
protected:

	int sceneNumber;
	int width, height;
	std::string title;
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
	int getWidth();
	int getHeight();
	void addScene(SceneManager* scene);
	void Play();
	static GameManager* getGameManager();
	~GameManager();
};