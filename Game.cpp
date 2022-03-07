#include "Game.h"
#include "ResourceLoader.h"
#include <iostream>


float scaleX = 1;
float scaleY = 1;
int xPos = 0;
int yPos = 0;
int mouseXPos;
int mouseYPos;

bool Game::Initialize(const std::string name, int screenWidth, int screenHeight)
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

	resourceLibrary = new ResourceLibrary();
	resourceLibrary->Add(ResourceLoader::LoadTextureAsResourceObject(renderer, "Assets/letsgo.png", "0", "lets go image"));



	quit = false;

	return true;
}

void Game::PrepareScene(void)
{
	Uint8 red = mouseXPos % 255;
	Uint8 green = mouseYPos % 255;
	Uint8 blue = (mouseXPos + mouseYPos) % 255;

	SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);


	ResourceObject* resObj = resourceLibrary->Get("0");
	int SHAPE_SIZE = 200;

	//SDL_Rect SrcR;
	//SDL_Rect DestR;

	//SrcR.x = 0;
	//SrcR.y = 0;
	//SrcR.w = SHAPE_SIZE;
	//SrcR.h = SHAPE_SIZE;

	//DestR.x = 640 / 2 - SHAPE_SIZE / 2;
	//DestR.y = 580 / 2 - SHAPE_SIZE / 2;
	//DestR.w = SHAPE_SIZE;
	//DestR.h = SHAPE_SIZE;

	SDL_Rect dest;
	dest.x = xPos;
	dest.y = yPos;

	// gets info of the texture
	SDL_QueryTexture(resObj->texture, NULL, NULL, &dest.w, &dest.h);
	dest.w /= scaleX;
	dest.h /= scaleY;
	SDL_RenderCopy(renderer, resObj->texture, NULL, &dest);
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


	SDL_GetMouseState(&mouseXPos, &mouseYPos);

	xPos = mouseXPos;
	yPos = mouseYPos;
	scaleX = mouseXPos / 100 + 1;
	scaleY = mouseYPos / 100 + 1;
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
