#include "Player.h"

Player::Player(SDL_Renderer* sdlRenderer, int _windowWidth, int _windowHeight) {
	renderer = sdlRenderer;
}

void Player::init(TiledMap* tiledMapGet)
{
	tiledmap = tiledMapGet; //creates instance of tilemap

	SDL_Surface* image = IMG_Load("assets/blue.png"); //loads png image of character
	if (image == nullptr) {
		std::cout << "Could not load image!!" << std::endl;
		return;
	}
	texture = SDL_CreateTextureFromSurface(renderer, image); //creates texture from image
}

//renders player
void Player::render()
{
	//sets dimensions of player and renders it
	float playerWidth = 0.1f * (float)windowWidth;
	portion.w = (int)playerWidth;
	portion.h = (int)playerWidth;

	SDL_RenderCopyF(renderer, texture, NULL, &portion); //SDL_RenderCopy(renderer, texture, NULL, &portion); to fill screen
}

void Player::update()
{

}


void Player::clean()
{

}

//if called, moves the player specified direction by increasing/decreasing x/y
//if touching sphere collider, will also move in opposite direction so directions cancel out and player doesn't move
void Player::moveDown()
{
	portion.y += speed;
	if (portion.y + portion.h >= windowHeight) {
		portion.y = windowHeight - portion.h;
	}
	else if (tiledmap->returnSphere().CollisionWithRect(portion))
	{
		portion.y -= speed;
	}
}

void Player::moveUp()
{
	portion.y -= speed;
	if (portion.y <= 0) {
		portion.y = 0;
	}
	else if (tiledmap->returnSphere().CollisionWithRect(portion))
	{
		portion.y += speed;
	}
}

void Player::moveLeft()
{
	portion.x -= speed;
	if (portion.x <= 0) {
		portion.x = 0;
	}
	else if (tiledmap->returnSphere().CollisionWithRect(portion))
	{
		portion.x += speed;
	}
}

void Player::moveRight()
{
	portion.x += speed;
	if (portion.x + portion.w >= windowWidth) {
		portion.x = windowWidth - portion.w;
	}
	else if (tiledmap->returnSphere().CollisionWithRect(portion))
	{
		portion.x -= speed;
	}
}

//if called will set player to original position of 0,0
void Player::updatePosition()
{
	portion.x = 0;
	portion.y = 0;

}