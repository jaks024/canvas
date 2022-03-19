#include "PixelGrid.h"

bool PixelGrid::IsIndexValid(int y, int x)
{
	return y >= 0 && y < height && x >= 0 && x < width;
}

PixelGrid::PixelGrid(int gridWidth, int gridHeight, int chunkWidth, int chunkHeight, int pixelSize, int originX, int originY)
{
	this->originX = originX;
	this->originY = originY;
	this->width = gridWidth;
	this->height = gridHeight;
	this->chunkWidth = chunkWidth;
	this->chunkHeight = chunkHeight;
	this->pixelSize = pixelSize;

	int totalChunks = gridWidth * gridHeight;
	for (int y = 0; y < gridHeight; ++y) 
	{
		vector<PixelChunk*> row;
		for (int x = 0; x < gridWidth; ++x) 
		{
			PixelChunk* chunk = new PixelChunk(chunkWidth, chunkHeight, {y, x});
			chunk->SetPosition(originX + chunkWidth * x * pixelSize, originY + chunkHeight * y * pixelSize);
			row.push_back(chunk);
		}
		grid.push_back(row);
	}

	// adding neighbours
	for (auto& row : grid)
	{
		for (auto& chunk : row)
		{
			int currentY = chunk->chunkIndex.first;
			int currentX = chunk->chunkIndex.second;
			pair<int, int> neighbourIds[8] = {
				{currentY - 1, currentX - 1},
				{currentY - 1, currentX},
				{currentY - 1, currentX + 1},
				{currentY, currentX - 1},
				{currentY, currentX + 1},
				{currentY + 1, currentX - 1},
				{currentY + 1, currentX},
				{currentY + 1, currentX + 1}

			};
			for (auto& index : neighbourIds)
			{
				if (IsIndexValid(index.first, index.second)) 
				{
					chunk->AddNeighbour(grid[index.first][index.second]);
					printf("added: (%d, %d) to (%d, %d)\n", currentY, currentX, index.first, index.second);
				}
			}
		}
	}
}

PixelGrid::~PixelGrid(void)
{
	for (auto& chunkRow : grid)
	{
		for (auto& chunk : chunkRow)
		{
			delete(chunk);
		}
	}
}

void PixelGrid::Advance(void)
{
	for (int i = height - 1; i >= 0; --i)
	{
		for (auto& chunk : grid[i])
		{
			chunk->Advance(width);
		}
	}
}

PixelChunk* PixelGrid::Get(pair<int, int> chunkIndex)
{
	for (auto& row : grid)
	{
		for (auto& chunk : row)
		{
			if (chunk->chunkIndex == chunkIndex)
			{
				return chunk;
			}
		}
	}
	return nullptr;
}

void PixelGrid::Draw(SDL_Renderer* renderer, ResourceObject* textureObj)
{
	for (auto& row : grid)
	{
		for (auto& chunk : row)
		{
			chunk->Draw(renderer, textureObj, pixelSize);
		}
	}
}

void PixelGrid::Set(int mousePosX, int mousePosY, short value)
{
	int correctedX = (mousePosX - originX) / pixelSize;
	int correctedY = (mousePosY - originY) / pixelSize;
	int xIndex = correctedX / chunkWidth;
	int yIndex = correctedY / chunkHeight;
	//printf("grid: [%d][%d]\n", yIndex, xIndex);
	if (xIndex < width && yIndex < height && xIndex >= 0 && yIndex >= 0) 
	{
		//printf("setting: [%d][%d]\n", correctedY - yIndex * chunkHeight, correctedX - xIndex * chunkWidth);
		grid[yIndex][xIndex]->Set(correctedY - yIndex * chunkHeight, correctedX - xIndex * chunkWidth, value);
	}
}

