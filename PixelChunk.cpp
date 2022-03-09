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

PixelChunk::PixelChunk(int width, int height, short initialValue)
{
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

void PixelChunk::Clear(void)
{
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			grid[i][j] = NOTHING;
		}
	}
}

void PixelChunk::Advance(void)
{
	for (int y = grid.size() - 1; y >= 0; --y)
	{
		for (int x = 0; x < grid[y].size(); ++x)
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
	for (int y = 0; y < grid.size(); y++)
	{
		for (int x = 0; x < grid[y].size(); x++)
		{
			printf("%d ", grid[y][x]);
		}
		printf("\n");
	}
}
