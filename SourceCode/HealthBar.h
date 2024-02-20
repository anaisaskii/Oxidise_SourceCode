#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Player.h"

class HealthBar
{
public:
	HealthBar(SDL_Renderer* sdlRenderer, int _windowWidth, int _windowHeight);

	void init();
	void render(); //renders healthbar
	void update();
	void clean();
	void updateHealthBar(); //updates health in healthbar

private:
	//creates instance of renderer and texture and player
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	Player* player = nullptr;

	int windowHeight = 1080;
	int windowWidth = 1920;
};
