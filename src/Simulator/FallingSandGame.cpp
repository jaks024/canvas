#include "../../include/Simulator/FallingSandGame.h"
using Framework::Resource::ResourceLoader;

bool FallingSandGame::InitializeResources(void)
{
	if (Game::InitializeResources())
	{
		resourceLibrary->Add(ResourceLoader::LoadTextureAsResourceObject(renderer, "square.png", "square", "white_square"));
		defaultSquare = resourceLibrary->Get("square");
		printf("Loading Resource Complete\n");
		return true;
	}
	return false;
}

bool FallingSandGame::InitializeGame(void)
{
	Game::InitializeGame();

	pixelGrid = new PixelGrid(GRID_WIDTH, GRID_HEIGHT, CHUNK_SIZE, CHUNK_SIZE, PIXEL_SIZE, 100, 100);
	currentChunk = pixelGrid->Get({0, 0});

	BindKeys();

	return true;
}

void FallingSandGame::Destroy(void)
{
	Game::Destroy();

	delete(pixelGrid);
}

void FallingSandGame::PrepareScene(void)
{
	// Clears the screen
	Game::PrepareScene(); 

	// draw pixels
	pixelGrid->Draw(renderer, defaultSquare);

}

void FallingSandGame::Update(void)
{
	Game::Update();

	if (autoAdvance) 
	{
		pixelGrid->Advance();
	}
}

void FallingSandGame::Paint(void)
{
	int mouseXPos;
	int mouseYPos;
	SDL_GetMouseState(&mouseXPos, &mouseYPos);

	Brush(mouseXPos, mouseYPos, PixelType::SAND);
}

void FallingSandGame::Clear(void)
{
	int mouseXPos;
	int mouseYPos;
	SDL_GetMouseState(&mouseXPos, &mouseYPos);

	Brush(mouseXPos, mouseYPos, PixelType::NOTHING);
}

void FallingSandGame::BindKeys()
{
	inputKeybindManager->Add(SDLK_a, SDLK_a);
	inputKeybindManager->Add(SDLK_d, SDLK_d);
	inputKeybindManager->Add(SDLK_s, SDLK_s);
	inputKeybindManager->Add(SDLK_f, SDLK_f);
	inputEventManager->BindBehaviorToKey(SDLK_a, std::bind(&PixelGrid::Advance, pixelGrid));
	inputEventManager->BindBehaviorToKey(SDLK_s, std::bind(&FallingSandGame::Paint, this));
	inputEventManager->BindBehaviorToKey(SDLK_d, std::bind(&FallingSandGame::Clear, this));
	inputEventManager->BindBehaviorToKey(SDLK_f, std::bind(&FallingSandGame::ToggleAutoAdvance, this));

}

void FallingSandGame::Brush(int mouseXPos, int mouseYPos, PixelType value)
{
	pixelGrid->Set(mouseXPos, mouseYPos - PIXEL_SIZE, value);
	pixelGrid->Set(mouseXPos, mouseYPos, value);
	pixelGrid->Set(mouseXPos - PIXEL_SIZE, mouseYPos, value);
	pixelGrid->Set(mouseXPos, mouseYPos + PIXEL_SIZE, value);
	pixelGrid->Set(mouseXPos + PIXEL_SIZE, mouseYPos, value);
}

void FallingSandGame::ToggleAutoAdvance(void)
{
	autoAdvance = !autoAdvance;
}
