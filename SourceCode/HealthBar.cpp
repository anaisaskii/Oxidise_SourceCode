#include "HealthBar.h"
#include <string>

//which part of the image to render
SDL_Rect renderRect;
//where to render it on screen
SDL_Rect sourceRect;

HealthBar::HealthBar(SDL_Renderer* sdlRenderer, int _windowWidth, int _windowHeight) {
	renderer = sdlRenderer; //creates instance of renderer
}

void HealthBar::init()
{
	//laods image for healthbar and creates texture
	SDL_Surface* image = IMG_Load("assets/healthbars.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

}

//sets the dimensions for what part of the image to render
//sets dimensions of where to render the image on the screen
void HealthBar::render()
{
	sourceRect.w = 26;
	sourceRect.h = 9;

	renderRect.x =750;
	renderRect.y = 0;
	renderRect.h = 90 * 1;
	renderRect.w = 260 * 1;

	SDL_RenderCopy(renderer, texture, &sourceRect, &renderRect);
}

//when called, will remove one bar of health (moves part of image rendered 25 pixels across to render next frame)
void HealthBar::updateHealthBar()
{
	sourceRect.x += 25;
}

void HealthBar::update()
{

}

void HealthBar::clean()
{

}
