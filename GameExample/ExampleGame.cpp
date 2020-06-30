#pragma once

#include "ExampleGame.h"

ExampleGame::ExampleGame(int width,int height,std::string title) :GameManager(), mousePosition(0, 0) {
	this->width = width;
	this->height = height;
	this->title = title;
	mouseWasInScreen = false;
	addScene(new Scene1());
	addScene(new Scene2());
	numberOfBuses = 0;
}