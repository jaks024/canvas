#include "Game.h"
#include "ResourceLoader.h"
#include <iostream>

bool Game::InitializeSDL(const std::string name, int screenWidth, int screenHeight)
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//Create window
	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// Create Renderer
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Renderer could not be created: %s", SDL_GetError());
		return false;
	}

	return true;
}

bool Game::InitializeResources()
{
	resourceLibrary = new ResourceLibrary();
	return true;
}

bool Game::InitializeGame(void)
{
	return true;
}

void Game::PrepareScene(void)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Game::PresentScene(void)
{
	SDL_RenderPresent(renderer);
}

void Game::ProcessInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;

			default:
				break;
		}
	}
}

// updates game logics
void Game::Update(void) {

}

void Game::Draw(void)
{
	PrepareScene();
	PresentScene();
}

void Game::Run(int framerate)
{
	if (quit) {
		return;
	}

	ProcessInput();
	Update();
	Draw();

	SDL_Delay(framerate);
}

void Game::Destroy(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	delete(resourceLibrary);
}

void Game::Quit(void) {
	SDL_Quit();
}
