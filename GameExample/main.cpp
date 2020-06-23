#include "ExampleGame.h"


int main() {
	ExampleGame* game = new ExampleGame(1920,1090,"Example");
	game->Play();
	delete game;
	return 0;
}