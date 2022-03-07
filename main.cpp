#include <stdio.h>
#include "Game.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FRAMERATE_60 = 16;

int main(int argc, char* args[])
{
	Game* game = new Game();
	game->Initialize("Game", SCREEN_WIDTH, SCREEN_HEIGHT);
	
	while (!game->quit) {
		game->Run(FRAMERATE_60);
	}
	game->Destroy();
	game->Quit();

	return 0;
}