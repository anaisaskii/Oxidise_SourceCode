// cplusplus_programming_for_games.cpp : This file contains the 'main' function. Program execution begins and ends there
#include "GameLoop.h"

int main()
{

	GameLoop gameLoop = GameLoop();
	if (gameLoop.init() < 0) return 1;

	//game can end if keepAlive is false
	while (gameLoop.keepalive()) {
		gameLoop.update();
		gameLoop.render();
	}

	gameLoop.clean();
    return 0;
}