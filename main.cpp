#include <stdio.h>
#include "include/Simulator/FallingSandGame.h"

#define TICK_INTERVAL    16

static Uint32 next_time;

Uint32 time_left(void)
{
	Uint32 now;

	now = SDL_GetTicks();
	if (next_time <= now)
		return 0;
	else
		return next_time - now;
}


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FRAMERATE_60 = 16;

int main(int argc, char* args[])
{
	FallingSandGame* game = new FallingSandGame();
	game->InitializeSDL("Game", SCREEN_WIDTH, SCREEN_HEIGHT);
	game->InitializeResources();
	game->InitializeGame();
	
	next_time = SDL_GetTicks() + TICK_INTERVAL;
	while (!game->quit) {
		game->Run(time_left());
		next_time += TICK_INTERVAL;
	}

	game->Destroy();
	game->Quit();

	return 0;
}