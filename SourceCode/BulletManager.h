#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <math.h>
#include <algorithm>

#include "Player.h"
#include "Audio.h" //to play shooting sound effect

#define PI 3.14159265

using namespace std;

//used when creating bullets
struct Bullet {
	float x, y, rotation, distance;
	SDL_Rect sourceRect;
	Uint32 lastAnimationTime;
	int animationOffset;
};

class BulletManager {
public:

	BulletManager(SDL_Renderer* renderer, Player* player, Audio* audio) : renderer(renderer), player(player), audio(audio), lastShot(0) {}

	//initialises bullet
	void init() {
		SDL_Surface* surface = IMG_Load("assets/lazer.png"); //Only loads image once, even if multiple instances of bullet struct
		this->bulletTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
		SDL_FreeSurface(surface); //frees the memory used by the image

		//sets the size of the image to render
		sourceRect.w = 200;
		sourceRect.h = 200;
	}

	//checks if player presses the left mouse button and shoots
	void processInput(bool* keyDown, float X, float Y, SDL_FRect* player) {
		Uint32 currentTime = SDL_GetTicks();

		//if left mouse if being clicked
		if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT) && (currentTime - lastShot > SHOOT_TIMER_MS)) {
			audio->PlaySoundEffect(); //plays shooting sound effect

			//get the mouse's x and y and store them as mouseX and mouseY
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			//get the player x andy and add an offset so that the bullet shoots from the center of the player
			float playerX = player->x + 150;
			float playerY = player->y + 200;

			//calculates the angle to shoot on based on the mouse x and y
			float angle = atan2(mouseY - playerY, mouseX - playerX);

			angle = angle * (180 / PI);

			//creates bullet and adds it to Bullet vector
			bullets.push_back(Bullet{ playerX, playerY, angle + 85, 0 });

			//sets the current time to the last shot so it can be calculated again
			lastShot = currentTime;
		}

	}

	void update()
	{
		//for each bullet
		for (auto& b : bullets)
		{
			//updates x and y in current rotation
			b.x += sin(b.rotation * PI / 180.0f) * BULLET_VELOCITY;
			b.y -= cos(b.rotation * PI / 180.0f) * BULLET_VELOCITY;
			b.distance += BULLET_VELOCITY;
		}

		//if the bullet's distance is greater than the max distance, delete it
		auto remove = std::remove_if(bullets.begin(), bullets.end(), [this](const Bullet& b) { return b.distance > MAX_BULLET_DISTANCE; });
		bullets.erase(remove, bullets.end()); //removes the bullet
	}

	void render()
	{
		SDL_FPoint center = { 5, 5 };
		for (auto& b : bullets)
		{
			dest = { b.x, b.y, 100, 100 }; // BULLET SIZE !
		

			SDL_RenderCopyExF(renderer, bulletTexture, &sourceRect, &dest, b.rotation, &center, SDL_FLIP_NONE);
		}

	}

	void clean()
	{
		SDL_DestroyTexture(this->bulletTexture); //destroying textures
	}

	//returns the position of the bullet
	SDL_FRect returnPosition()
	{
		return dest;
	}


private:
	SDL_Renderer* renderer;
	SDL_Texture* bulletTexture;
	vector<Bullet> bullets; //to store list of bullets

	//instances of player and audio
	Player* player;
	Audio* audio;

	SDL_FRect dest;
	SDL_Rect sourceRect;

	const int SHOOT_TIMER_MS = 150; //how often bullets can fire
	const int BULLET_VELOCITY = 1; //how quickly the bullets fire (number of pixels per frame)
	unsigned int lastShot = 0;
	const float MAX_BULLET_DISTANCE = 2000.0f; //how far the bullet can move before being destroyed
};