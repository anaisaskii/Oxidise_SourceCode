#pragma once

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include <iostream>

class FontRenderer
{
public:
	FontRenderer(SDL_Renderer* sdlRenderer);
	void init();
	void render(std::string text, int colour, int x, int y); //to render text - takes in text to render/colour/and the co ordinates
	void clean();
private:
	SDL_Renderer* renderer;
	TTF_Font* font; //creates font
};

