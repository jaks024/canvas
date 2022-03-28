#include "../../include/Simulator/FallingSandGame.h"
#include "../../include/Simulator/Pixel/PixelPropertyLookupTable.h"
#include <format>
using Framework::Resource::ResourceLoader;

bool FallingSandGame::InitializeResources(void)
{
	if (Game::InitializeResources())
	{
		resourceLibrary->Add(ResourceLoader::LoadTextureAsResourceObject(renderer, "square.png", "square"));
		defaultSquare = resourceLibrary->Get(0);
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


	PixelTypeProperty* airProperty = new PixelTypeProperty();
	airProperty->r = 0;
	airProperty->g = 0;
	airProperty->b = 0;

	PixelTypeProperty* sandProperty = new PixelTypeProperty();
	sandProperty->r = 255;
	sandProperty->g = 250;
	sandProperty->b = 205;

	PixelTypeProperty* dirtProperty = new PixelTypeProperty();
	dirtProperty->r = 193;
	dirtProperty->g = 154;
	dirtProperty->b = 107;

	propertyTable = new PixelPropertyLookupTable();
	propertyTable->AddProperty(PixelType::AIR, airProperty);
	propertyTable->AddProperty(PixelType::SAND, sandProperty);
	propertyTable->AddProperty(PixelType::DIRT, dirtProperty);

	BindKeys();

	uiComponent = new Text(0, "test_message", "roboto.ttf");
	Background* bg = new Background(1, "bg", { 55, 55, 55 }, defaultSquare, 200, 50);
	bg->SetPosition(-50, -10);
	uiComponent->AddChild(bg);

	return true;
}

void FallingSandGame::Destroy(void)
{
	Game::Destroy();

	delete(pixelGrid);
	delete(propertyTable);
}

void FallingSandGame::PrepareScene(void)
{
	// Clears the screen
	Game::PrepareScene(); 

	// draw pixels
	pixelGrid->Draw(renderer, defaultSquare, propertyTable);

	// draw UI
	uiComponent->Draw(renderer);
}

void FallingSandGame::Update(void)
{
	Game::Update();

	if (autoAdvance) 
	{
		pixelGrid->Advance();
	}

	int mouseXPos;
	int mouseYPos;
	SDL_GetMouseState(&mouseXPos, &mouseYPos);
	uiComponent->SetPosition(mouseXPos, mouseYPos);
	uiComponent->SetText(std::format("[{},{}]", mouseXPos, mouseYPos));

}

void FallingSandGame::Paint(PixelType type)
{
	int mouseXPos;
	int mouseYPos;
	SDL_GetMouseState(&mouseXPos, &mouseYPos);

	Brush(mouseXPos, mouseYPos, type);
}

void FallingSandGame::Clear(void)
{
	int mouseXPos;
	int mouseYPos;
	SDL_GetMouseState(&mouseXPos, &mouseYPos);

	Brush(mouseXPos, mouseYPos, PixelType::AIR);
}

void FallingSandGame::BindKeys()
{
	inputKeybindManager->Add(SDLK_a, SDLK_a);
	inputKeybindManager->Add(SDLK_d, SDLK_d);
	inputKeybindManager->Add(SDLK_1, SDLK_1);
	inputKeybindManager->Add(SDLK_2, SDLK_2);
	inputKeybindManager->Add(SDLK_f, SDLK_f);
	inputEventManager->BindBehaviorToKey(SDLK_a, std::bind(&PixelGrid::Advance, pixelGrid));
	inputEventManager->BindBehaviorToKey(SDLK_1, std::bind(&FallingSandGame::Paint, this, PixelType::SAND));
	inputEventManager->BindBehaviorToKey(SDLK_2, std::bind(&FallingSandGame::Paint, this, PixelType::DIRT));
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
