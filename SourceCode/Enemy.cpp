#include "Enemy.h"

SDL_Rect sourceRectEnemy;

//creates instances of player and renderer
Enemy::Enemy(SDL_Renderer* sdlRenderer, int _windowWidth, int _windowHeight, Player* _player) {
	renderer = sdlRenderer;
	playerObj = _player;
}

void Enemy::init()
{
	//width of enemy
	float enemyWidth = 0.12f * (float)windowWidth;

	//sets dimensions for bounding box
	boundingBox.w = (int)enemyWidth / 2;
	boundingBox.h = (int)enemyWidth;
	boundingBox.x = boundingBox.y = rand() % (2000 - 500 + 1) + 500;

	//creates image from image file and creates texture from it
	SDL_Surface* image = IMG_Load("assets/enemies.png");
	if (image == nullptr) {
		std::cout << "Could not load image!!" << std::endl;
		return;
	}
	texture = SDL_CreateTextureFromSurface(renderer, image);

	//sets initial dimensions for enemy (height and width)
	sourceRectEnemy.w = 260;
	sourceRectEnemy.h = 540;
}

void Enemy::render()
{
	SDL_RenderCopyF(renderer, texture, &sourceRectEnemy, &boundingBox);
}

//teleports enemy to a random location 
void Enemy::updateLocation()
{
	boundingBox.x = rand() % 2000; //random number 1-2000
	boundingBox.y = rand() % 1000; //random number 1-1000
}

//moves enemy towards player
void Enemy::move(SDL_FRect* playerpos)
{
	//stores the player's current x and y to x and y
	float x = playerpos->x - boundingBox.x;
	float y = playerpos->y - boundingBox.y;
	//uses pythagoras' theorem to get distance to player
	//x squared + y squared gives the distance squared
	float distance = std::sqrt(x * x + y * y);

	//if there is a distance between the enemy and player, divide the x and y by the distance
	if (distance > 0) 
	{
		x /= distance;
		y /= distance;
	}

	//actually moves the enemy towards character
	boundingBox.x += x * 0.08;
	boundingBox.y += y * 0.08;
}

//animates enemy
void Enemy::enemyAnimate()
{
	//gets the current time (time since SDL initialises)
	Uint32 currentTime = SDL_GetTicks();
	//creates int time
	static int time;

	//if one second has passed
	if (currentTime - time > 1000)
	{
		//set the amount of time passed to be time in order to calculate when another second passes
		time = currentTime;
		//if enemy is blinking, stop it from blinking or vice versa
		blink = !blink;
	}

	//if the enemy should blink/not blink, change the source rect to fit the apropriate flame
	if (blink)
	{
		sourceRectEnemy.x = 280;
	}
	else
	{
		sourceRectEnemy.x = 10;
	}
}

void Enemy::clean()
{
	SDL_DestroyTexture(texture); //destroys textures
}

//if enemy intersects bullet
void Enemy::boxCollision(SDL_FRect* bullet) {
	if (SDL_HasIntersectionF(&boundingBox, bullet) == true) {
		updateLocation(); //change to random location
		score += 1; //increases score as enemy is hit
		checkHighScore(); //check if the high score needs to be updated
	}
}

//if enemy intersects player
void Enemy::playerCollision(SDL_FRect* player)
{
	if (SDL_HasIntersectionF(&boundingBox, player) == true) {
		updateLocation(); //new location
		if (updates == 0)
		{	
			//if the player is in the co ordinates of where the sphere collider will be
			if ((player->x <= 1000 && player->x > 700) && (player->y <= 600 && player->y >= 400))
			{
				playerObj->updatePosition(); //change the player position to 0, 0
			}
		
			tiledmap->updateTileMap("assets/tilemap2.txt"); //change to map 2
			updates += 1; // increase map updates
		}
		else if (updates == 1)
		{
			tiledmap->updateTileMap("assets/tilemap3.txt"); //change to map 3
			updates += 1; // increase map updates
		}
		else
		{
			updates += 1;
		}
		healthbar->updateHealthBar(); //update healthbar as player has been hit
	}
	else
	{
		move(player); //move enemy towards player
	}
}
//returns current score
int Enemy::returnScore() {
	return score;
}
//returns current amount of map updates
int Enemy::returnUpdates()
{
	return updates;
}

int Enemy::checkHighScore() {
	std::ifstream scoreFileIn("assets/score.txt", std::ios::binary); // Reads high score

	scoreFileIn.read(reinterpret_cast<char*>(&highScore), sizeof(int)); // Reads high score as highScore

	if (score > highScore) { // If the player's current score is higher than highScore
		std::ofstream scoreFileOut("assets/score.txt", std::ios::binary); // Opens score.txt in write mode

		scoreFileOut.write(reinterpret_cast<const char*>(&score), sizeof(int)); // Writes the score to the file
		scoreFileOut.close();
	}

	scoreFileIn.close();

	return 0;
}

int Enemy::returnHighScore() {
	return highScore;
}
