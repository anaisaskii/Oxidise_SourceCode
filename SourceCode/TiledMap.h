#pragma once
#include <SDL.h>
#include <SDL_image.h>
#define SDL_MAIN_HANDLED
#include <iostream>
#include <fstream>

//the height and width of the map
//used for when loading map in
const int mapWidth = 20;
const int mapHeight = 11;

//Sphere (or technically circle) collider
//Returns CollisionWithRect to check if an SDL_Rect collides with the Sphere
struct Sphere {
public:
	//the location and size of the sphere
	Sphere(int x, int y, int radius) : x(x), y(y), radius(radius) {}

	bool CollisionWithRect(const SDL_FRect& rect) const {
		float closestX = std::max(rect.x, std::min(static_cast<float>(x), rect.x + rect.w));
		float closestY = std::max(rect.y, std::min(static_cast<float>(y), rect.y + rect.h));
		float distance = std::sqrt(std::pow(x - closestX, 2) + std::pow(y - closestY, 2));
		return distance <= radius; //is distance between rect and sphere smaller than radius (if yes then colliding)
	}

	//used to set Sphere's X and Y radius easily
	void setX(int X)
	{
		x = X;
	}
	void setY(int Y)
	{
		y = Y;
	}
	void setRadius(int Radius)
	{
		radius = Radius;
	}

private:
	int x, y;
	int radius;
};


class TiledMap
{
public:
	TiledMap(SDL_Renderer* sdlRenderer, std::string tiledMapFilename);

	int init();
	void render();
	void clean();
	void loadTileMap(std::string); //loads in the tilemap
	void updateTileMap(std::string); //updates the tilemap
	int returnMapChanges()
	{
		return mapChanges; //returns the number of map changes
	}

	Sphere returnSphere();

private:
	std::string filename;
	SDL_Renderer* renderer;
	SDL_Texture* texture;

	//dimensions of each tile on the tilemap
	const int sourceTileSizePx = 32;
	const int tileWidth = 98;
	const int tileHeight = 98;
	
	//the number of times the map has changed
	int mapChanges = 0;

	std::string tilemapName = "assets/tilemap.txt";
};