#include "FallingSandGame.h"

bool FallingSandGame::InitializeResources(void)
{
	if (Game::InitializeResources())
	{
		resourceLibrary->Add(ResourceLoader::LoadTextureAsResourceObject(renderer, "Assets/square.png", "square", "white_square"));
		defaultSquare = resourceLibrary->Get("square");
		return true;
	}
	return false;
}

bool FallingSandGame::InitializeGame(void)
{

	vector<PixelChunk*> chunkRow;
	PixelChunk* chunk = new PixelChunk(CHUNK_SIZE, CHUNK_SIZE);
	chunkRow.push_back(chunk);
	chunkGrid.push_back(chunkRow);
	currentChunk = chunk;

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

	for (size_t y = 0; y < chunkGrid.size(); y++)
	{
		for (size_t x = 0; x < chunkGrid[y].size(); x++)
		{
			delete(chunkGrid[y][x]);
		}
	}
}

void FallingSandGame::PrepareScene(void)
{
	// Clears the screen
	Game::PrepareScene(); 

	// draw pixels
	int offset = 100;
	vector<vector<short>>* pixelGrid = &chunkGrid[0][0]->grid;
	for (size_t y = 0; y < (*pixelGrid).size(); y++)
	{
		for (size_t x = 0; x < (*pixelGrid)[y].size(); x++)
		{
			if ((*pixelGrid)[y][x] > 0) {
				SDL_Rect dest;
				dest.w = PIXEL_SIZE;
				dest.h = PIXEL_SIZE;
				dest.x = offset + (x * dest.w);
				dest.y = offset + (y * dest.h);

				SDL_RenderCopy(renderer, defaultSquare->texture, NULL, &dest);
			}
		}
	}

}

void FallingSandGame::Update(void)
{
	int mouseXPos;
	int mouseYPos; 
	SDL_GetMouseState(&mouseXPos, &mouseYPos);

	int setY = (mouseYPos - 100) / 5;
	int setX = (mouseXPos - 100) / 5;
	currentChunk->Set(setY - 1, setX, 1);
	currentChunk->Set(setY, setX, 1);
	currentChunk->Set(setY, setX - 1, 1);
	currentChunk->Set(setY + 1, setX, 1);
	currentChunk->Set(setY, setX + 1, 1);

	currentChunk->Advance();
	//printf("mouse pos: {%d, %d}", mouseXPos, mouseYPos);
}


