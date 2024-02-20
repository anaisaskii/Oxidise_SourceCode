#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>

#include "TiledMap.h"
#include "HealthBar.h"

class Enemy
{
public:
	Enemy(SDL_Renderer* sdlRenderer, int _windowWidth, int _windowHeight, Player* _player);

	void init();
	void render();
	void updateLocation(); //teleports enemy to random location
	void clean();

	void move(SDL_FRect* playerpos); //handles enemy movement towards player
	void boxCollision(SDL_FRect* player); //checls if bullet collides with enemy
	void playerCollision(SDL_FRect* player); //checks if player collides with enemy
	void enemyAnimate(); //handles enemy animations

	int checkHighScore(); //checks the current highscore

	int returnHighScore(); //returns the current high score
	int returnScore(); //returns the current score
	int returnUpdates(); //returns the amount of times map has updates

private:
	SDL_FRect boundingBox;

	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;

	//screen dimensions
	int windowHeight = 1080;
	int windowWidth = 1920;

	//creates instance of tilemap, healthbar, and player
	TiledMap* tiledmap = new TiledMap(renderer, "assets/factoryTileMap.png");
	HealthBar* healthbar = new HealthBar(renderer, windowWidth, windowHeight);
	Player* playerObj = nullptr;

	//stores score and high score
	int score = 0;
	int highScore;

	//times maps have updated
	int updates = 0;

	//whether enemy should blink
	bool blink = false;
};