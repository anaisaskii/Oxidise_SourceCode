#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "TiledMap.h"

class Player
{
public:
	Player(SDL_Renderer* sdlRenderer, int _windowWidth, int _windowHeight);

	void init(TiledMap* tiledMapGet);
	void render();
	void update();
	void clean();

	//moves player
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

	//returns the player's current position
	SDL_FRect ReturnPosition() {
		return portion;
	}

	void updatePosition();

private:
	//bounds for player
	SDL_FRect portion;
	//creates instances of renderer, texture and tilemap
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	TiledMap* tiledmap = nullptr;

	//sets the speed for the player to move
	float speed = 0.2;

	int windowHeight = 1080;
	int windowWidth = 1920;
};

 