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
	this->window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// Create Renderer
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Renderer could not be created: %s", SDL_GetError());
		return false;
	}

	return true;
}

bool Game::InitializeResources(void)
{
	this->resourceLibrary = new ResourceLibrary();
	return true;
}

bool Game::InitializeGame(void)
{
	this->inputKeybindManager = new InputKeybindManager();
	this->inputEventManager = new InputEventManager(this->inputKeybindManager, std::bind(&Game::OnQuitEvent, this));
	return true;
}

void Game::OnQuitEvent(void)
{
	quit = true;
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
	this->inputEventManager->ProcessInput();
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
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	delete(this->resourceLibrary);
	delete(this->inputKeybindManager);
	delete(this->inputEventManager);
}

void Game::Quit(void) {
	SDL_Quit();
}
