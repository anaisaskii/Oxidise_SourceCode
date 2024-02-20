#include  "GameLoop.h"

//initialises everything for the game
int GameLoop::init()
{
	//error message for is SDL does not initialise
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "could not initialize SDL2!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}
	
	//creates the window
	window = SDL_CreateWindow(
		"oxidise", //name of the window
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		1920, 1080, //dimsenions of window
		SDL_WINDOW_BORDERLESS //runs as borderless windowed
	);

	//error message for if window cannot initialise
	if (window == NULL) {
		std::cout << "could not initialise window!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	//creates renderer
	//error message for if renderer does not initialise
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cout << "could not initialise renderer!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	//gets window surface
	screenSurface = SDL_GetWindowSurface(window);

	SDL_UpdateWindowSurface(window);

	//creates instances of and calls init functions for all files used
	tiledMap = new TiledMap(renderer, "assets/factoryTileMap.png");
	tiledMap->init();

	player = new Player(renderer, screenWidth, screenHeight);
	player->init(tiledMap);

	healthbar = std::unique_ptr<HealthBar>(new HealthBar(renderer, screenWidth, screenHeight));
	healthbar->init();

	enemy = new Enemy(renderer, screenWidth, screenHeight, player);
	enemy->init();

	fontRenderer = std::unique_ptr<FontRenderer>(new FontRenderer(renderer));
	fontRenderer->init();

	audio = new Audio();
	audio->PlaySound();

	bm = new BulletManager(this->renderer, this->player, this->audio);
	bm->init();

	enemy->checkHighScore(); //checks the current highscore so it can be displayed
	highScore = enemy->returnHighScore();

	return 0;
}

//Checks for all game input
bool GameLoop::handleInput(SDL_Scancode) {
	const Uint8* keyState = SDL_GetKeyboardState(nullptr);

	//checks which key is pressed and calls appropriate functino to move player
	if (keyState[SDL_SCANCODE_D]) {
		player->moveRight();
	}
	if (keyState[SDL_SCANCODE_A]) {
		player->moveLeft();
	}
	if (keyState[SDL_SCANCODE_W]) {
		player->moveUp();
	}
	if (keyState[SDL_SCANCODE_S]) {
		player->moveDown();
	}

	SDL_FRect playerPos = player->ReturnPosition(); //gets current player position
	bm->processInput(keyDown, playerPos.x, playerPos.y, &playerPos); //processes input for shooting mechanic

	return 0; 
}

//Whilst this function runs - game runs
//if false is returned, game will end
bool GameLoop::keepalive() {
	SDL_Event userInput;

	while (SDL_PollEvent(&userInput)) {
		if (userInput.type == SDL_QUIT) //if user presses 'x' on window - end game
		{
			return false;
		}

		if (userInput.type == SDL_KEYDOWN)
		{
			keyDown[userInput.key.keysym.scancode] = true;

			handleInput(userInput.key.keysym.scancode);

			switch (userInput.key.keysym.scancode) { //if user presses escape - end game
				case SDL_SCANCODE_ESCAPE:
					return false;
					break;
			}
			
		}

		if (userInput.type == SDL_KEYUP) {
			keyDown[userInput.key.keysym.scancode] = false;
		}
	}

	if (enemy->returnUpdates() >= 3) //if the map has changed 3 times (player has been hit 3 times) end the game!
	{
		return false;
	}

	return true;
}	

void GameLoop::update()
{
	bm->update(); //updates bullets (moves them)

	enemy->enemyAnimate(); //enemy animations

	handleInput(SDL_SCANCODE_UNKNOWN); //calls the handleinput function each frame
}

//renders everything on screen so user can see it
void GameLoop::render()
{
	SDL_RenderClear(renderer); //clears the screen if anything is on it

	//returns the current bullet and player position
	SDL_FRect returnBulletPosition = bm->returnPosition();
	SDL_FRect returnPlayerPosition = player->ReturnPosition();

	//stores the current score so it can be displayed
	int score = enemy->returnScore();

	//checks if enemy is colliding with bullet or player
	enemy->boxCollision(&returnBulletPosition);
	enemy->playerCollision(&returnPlayerPosition);

	//renders tilemap, player, enemy, and healthbar
	tiledMap->render();
	player->render();
	enemy->render();
	healthbar->render();

	//renders on screen font (score and highscore)
	fontRenderer->render("Score:" + to_string(score), 1, 30, 10);
	fontRenderer->render("High Score:" + to_string(highScore), 2, 1380, 10);

	//renders bullets
	bm->render();

	//update the screen with all the rendered objects
	SDL_RenderPresent(renderer);

}

//cleans up all assets (called when game ends)
void GameLoop::clean()
{
	SAFERELEASE(audio);

	fontRenderer->clean();
	bm->clean();
	tiledMap->clean();
	enemy->clean();

	healthbar->clean();

	delete player;

	SDL_DestroyWindow(window);
	SDL_Quit();
}
