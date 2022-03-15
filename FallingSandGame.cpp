#include "FallingSandGame.h"

bool FallingSandGame::InitializeResources(void)
{
	if (Game::InitializeResources())
	{
		resourceLibrary->Add(ResourceLoader::LoadTextureAsResourceObject(renderer, "Assets/square.png", "square", "white_square"));
		defaultSquare = resourceLibrary->Get("square");
		printf("Loading Resource Complete\n");
		return true;
	}
	return false;
}

bool FallingSandGame::InitializeGame(void)
{
	Game::InitializeGame();

	pixelGrid = new PixelGrid(10, 10, CHUNK_SIZE, CHUNK_SIZE, PIXEL_SIZE, 100, 100);
	currentChunk = pixelGrid->Get(0);

	BindKeys();

	// randomize pixels
	//for (int i = 0; i < CHUNK_SIZE; i++)
	//{
	//	for (int j = 0; j < CHUNK_SIZE; j++)
	//	{
	//		currentChunk->Set(i, j, rand() % 2 ? 1 : 0);
	//	}
	//}


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

	pixelGrid->Advance();
	//printf("mouse pos: {%d, %d}", mouseXPos, mouseYPos);
}

void FallingSandGame::Paint(void)
{
	int mouseXPos;
	int mouseYPos;
	SDL_GetMouseState(&mouseXPos, &mouseYPos);

	Brush(mouseXPos, mouseYPos, 1);
}

void FallingSandGame::Clear(void)
{
	int mouseXPos;
	int mouseYPos;
	SDL_GetMouseState(&mouseXPos, &mouseYPos);

	Brush(mouseXPos, mouseYPos, 0);
}

void FallingSandGame::BindKeys()
{
	inputKeybindManager->Add(SDLK_a, SDLK_a);
	inputKeybindManager->Add(SDLK_d, SDLK_d);
	inputKeybindManager->Add(SDLK_s, SDLK_s);
	inputEventManager->BindBehaviorToKey(SDLK_a, std::bind(&PixelChunk::Advance, currentChunk));
	inputEventManager->BindBehaviorToKey(SDLK_s, std::bind(&FallingSandGame::Paint, this));
	inputEventManager->BindBehaviorToKey(SDLK_d, std::bind(&FallingSandGame::Clear, this));

}

void FallingSandGame::Brush(int mouseXPos, int mouseYPos, int value)
{
	pixelGrid->Set(mouseXPos, mouseYPos - PIXEL_SIZE, value);
	pixelGrid->Set(mouseXPos, mouseYPos, value);
	pixelGrid->Set(mouseXPos - PIXEL_SIZE, mouseYPos, value);
	pixelGrid->Set(mouseXPos, mouseYPos + PIXEL_SIZE, value);
	pixelGrid->Set(mouseXPos + PIXEL_SIZE, mouseYPos, value);
}
