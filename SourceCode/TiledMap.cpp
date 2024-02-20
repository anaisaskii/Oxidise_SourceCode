#include "TiledMap.h"

int map[mapHeight][mapWidth];
Sphere sphere = Sphere(0, 0, 0);

TiledMap::TiledMap(SDL_Renderer* sdlRenderer, std::string tiledMapFilename)
{
	renderer = sdlRenderer;
	filename = tiledMapFilename;
}

int TiledMap::init()
{
	//Loads image from given file name
	SDL_Surface* image = IMG_Load(filename.c_str());
	//create texture from the image
	texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image); //release image for memory management

	//calls loadtilemap with first mapt text file
	loadTileMap("assets/tilemap.txt");

	return 0;
}

void TiledMap::render()
{
	//for each row (set by map height)
	for (int i = 0; i < mapHeight; i++) {
		//for each column (set by map width)
		for (int j = 0; j < mapWidth; j++) {

			//Sets the dimensions for the parts of the image to be rendered
			SDL_Rect sourceRect;
			sourceRect.x = (map[i][j] % 8) * sourceTileSizePx;
			sourceRect.y = (map[i][j] / 8) * sourceTileSizePx;
			sourceRect.h = sourceTileSizePx;
			sourceRect.w = sourceTileSizePx;

			//sets the dimensions of where the image will be rendered
			SDL_Rect renderRect;
			renderRect.x = j * tileWidth;
			renderRect.y = i * tileHeight;
			renderRect.h = tileHeight;
			renderRect.w = tileWidth;

			SDL_RenderCopy(renderer, texture, &sourceRect, &renderRect);
		}
	}

}

void TiledMap::clean()
{
	//clean up texture for memory management
	SDL_DestroyTexture(texture);
}

void TiledMap::loadTileMap(std::string tiledmapname)
{
	//open tiledmap file
	std::ifstream tilemap_stream(tiledmapname); 

	if (!tilemap_stream.is_open()) {
		std::cout << "Failed to open tilemap.txt, check file is in project" << std::endl;

		return;
	}

	//for each row and column specified
	//get tile value from txt file and load in appropriate tile
	for (int rowIDx = 0; rowIDx < mapHeight; rowIDx++) {
		for (int colIDx = 0; colIDx < mapWidth; colIDx++) {
			std::string tileValue;

			tilemap_stream >> tileValue;

			int value = atoi(tileValue.c_str());

			map[rowIDx][colIDx] = value;
		}
	}

	//close file when no longer needed
	tilemap_stream.close();

}

void TiledMap::updateTileMap(std::string newfilename)
{
	//Increase number of map changes when the map is changed
	mapChanges += 1;

	//if on the second map, place the sphere collider
	if (mapChanges == 1)
	{
		sphere.setX(1000);
		sphere.setY(600);
		sphere.setRadius(60);
	}
	//if not on the second map don't have sphere
	else
	{
		sphere.setX(0);
		sphere.setY(0);
		sphere.setRadius(0);
	}

	//call load tilemap with the new filename
	loadTileMap(newfilename);
}

//Returns the sphere to check co ordinates
Sphere TiledMap::returnSphere()
{
	return sphere;
}

