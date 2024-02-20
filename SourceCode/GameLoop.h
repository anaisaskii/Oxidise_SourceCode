#pragma once

#include <iostream>
#define SDL_MAIN_HANDLED
#define SAFERELEASE(x) { if (x) { delete x; x = NULL;} } //to safely delete objects
//includes files so that other parts of code can be used
#include <SDL.h>
#include "Player.h"
#include "FontRenderer.h"
#include "TiledMap.h"
#include "BulletManager.h"
#include "Enemy.h"
#include "Audio.h"
#include "HealthBar.h"

//sets screenwidth and height
const int screenWidth = 1920;
const int screenHeight = 1080;

class GameLoop
{
public:
	int init();
	void update();
	void render();
	bool handleInput(SDL_Scancode);
	bool keepalive();
	void clean();

private:
	//creates empty window/renderer/screensurface to be initialised in gameloop.cpp
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* screenSurface = nullptr;

	//scripts to be initialised
	std::unique_ptr<FontRenderer> fontRenderer;
	TiledMap* tiledMap = nullptr;
	std::unique_ptr<HealthBar> healthbar;
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	BulletManager* bm;
	Audio* audio;

	bool keyDown[512];
	bool keysPressed[SDL_NUM_SCANCODES];
	
	int highScore; //to store highscore
};