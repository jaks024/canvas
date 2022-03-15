#include "PixelChunk.h"
#include <iostream>
bool PixelChunk::IsIndexValid(int y, int x)
{
	if (0 <= y && y < grid.size()) {
		if (0 <= x && x < grid[y].size()) {
			return true;
		}
	}
	return false;
}

PixelChunk::PixelChunk(int width, int height, int chunkId, short initialValue)
{
	this->chunkId = chunkId;
	this->chunkWidth = width;
	this->chunkHeight = height;
	evaluator = new PixelBehaviorEvaluator();
	for (int i = 0; i < height; i++)
	{
		vector<short> row;
		for (int h = 0; h < width; h++)
		{
			row.push_back(initialValue);
		}
		grid.push_back(row);
	}
}

PixelChunk::~PixelChunk(void)
{
	delete(evaluator);
}

void PixelChunk::SetPosition(int x, int y)
{
	this->originX = x;
	this->originY = y;
}

void PixelChunk::Clear(void)
{
	for (int i = 0; i < chunkHeight; i++)
	{
		for (int j = 0; j < chunkWidth; j++)
		{
			grid[i][j] = NOTHING;
		}
	}
}

void PixelChunk::Advance(void)
{
	for (int y = chunkHeight - 1; y >= 0; --y)
	{
		for (int x = 0; x < chunkWidth; ++x)
		{
			if (grid[y][x] == 0) {
				continue;
			}

			const pair<short, short>* evaluation = evaluator->Evaluate(&grid, y, x);
			int newY = y + (*evaluation).second;
			int newX = x + (*evaluation).first;
			if (IsIndexValid(newY, newX) && grid[newY][newX] == 0)
			{
				grid[newY][newX] = grid[y][x];
				grid[y][x] = NOTHING;
			}
		}
	}
}

void PixelChunk::Set(int y, int x, short value)
{
	if (IsIndexValid(y, x)) {
		grid[y][x] = value;
		//printf("Set {%d, %d}", y, x);
	}
}

void PixelChunk::Print(void)
{
	std::cout << "\x1B[2J\x1B[H";
	for (int y = 0; y < chunkHeight; y++)
	{
		for (int x = 0; x < chunkWidth; x++)
		{
			printf("%d ", grid[y][x]);
		}
		printf("\n");
	}
}


void PixelChunk::AddNeighbour(PixelChunk* newNeighbour)
{
	neighbours.push_back(newNeighbour);
}

void PixelChunk::Draw(SDL_Renderer* renderer, ResourceObject* textureObj, int pixelSize) 
{
	for (size_t y = 0; y < chunkHeight; y++)
	{
		for (size_t x = 0; x < chunkWidth; x++)
		{
			if (grid[y][x] > 0) {
				SDL_Rect dest;
				dest.w = pixelSize;
				dest.h = pixelSize;
				dest.x = this->originX + (x * dest.w);
				dest.y = this->originY + (y * dest.h);

				SDL_RenderCopy(renderer, textureObj->texture, NULL, &dest);
			}
		}
	}
}