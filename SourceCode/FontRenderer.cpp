#include "FontRenderer.h"

FontRenderer::FontRenderer(SDL_Renderer* sdlRenderer)
{
	renderer = sdlRenderer; //creates instance of renderer
}

void FontRenderer::init()
{
	int init = TTF_Init();

	if (init != 0) {
		std::cout << SDL_GetError() << std::endl;
	}
	font = TTF_OpenFont("assets/PixeloidSans.ttf", 70); //sets font and font size

	if (font == NULL) {
		std::cout << SDL_GetError() << std::endl;
	}
}

void FontRenderer::clean()
{
	TTF_CloseFont(font); //closes font when not needed anymore
}

void FontRenderer::render(std::string text, int colour, int x, int y)
{
	SDL_Color Colour = SDL_Color();

	//checks which colour has been inputted
	switch (colour) {
	case 1: //RED
		Colour.r = 240;
		Colour.g = 105;
		Colour.b = 100;
		Colour.a = 255;
		break;

	case 2: //BLUE
		Colour.r = 66;
		Colour.g = 135;
		Colour.b = 245;
		Colour.a = 255;
		break;
	}

	//creates surface with the text to be rendered on
	SDL_Surface* textImage = TTF_RenderText_Solid(font, text.c_str(), Colour);
	//creates texture from the textImage so it can be rendered
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textImage);
	//created rect to hold text so it doesn't fill screen
	SDL_Rect textRect = { x, y, textImage->w, textImage->h };

	SDL_RenderCopy(renderer, texture, NULL, &textRect); //renders text

	//frees up resources
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(textImage);
}