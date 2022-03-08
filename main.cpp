#include <stdio.h>
#include "FallingSandGame.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FRAMERATE_60 = 16;

int main(int argc, char* args[])
{
	FallingSandGame* game = new FallingSandGame();
	game->InitializeSDL("Game", SCREEN_WIDTH, SCREEN_HEIGHT);
	game->InitializeResources();
	game->InitializeGame();
	
	while (!game->quit) {
		game->Run(FRAMERATE_60);
	}
	game->Destroy();
	game->Quit();

	return 0;
}