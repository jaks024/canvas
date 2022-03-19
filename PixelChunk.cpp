#include "PixelChunk.h"
#include <iostream>
bool PixelChunk::IsIndexValid(int y, int x)
{
	bool yInRange = 0 <= y && y < chunkHeight;
	bool xInRange = 0 <= x && x < chunkWidth;
	return yInRange && xInRange;
}

PixelChunk* PixelChunk::CanSetInNeighbour(int y, int x, pair<int, int> neighbourIndex)
{
	auto result = neighbours.find(neighbourIndex);
	if (result != neighbours.end() && result->second->chunkIndex == neighbourIndex &&
		result->second->IsIndexValid(y, x) && result->second->IsLocationEmpty(y, x))
	{
		return result->second;
	}
	return nullptr;
}

int PixelChunk::ConvertToNeighbourIndex(int val, int limit)
{
	if (val >= limit) {
		return 0;
	}
	else if (val < 0) {
		return limit - 1;
	}
	return val;
}

bool PixelChunk::IsLocationEmpty(int y, int x, bool neighbourConvert)
{
	if (neighbourConvert) {
		//printf("before convert %d %d at %d %d\n", chunkIndex.first, chunkIndex.second, y, x);
		//printf("checking after convert %d %d at %d %d\n", chunkIndex.first, chunkIndex.second, ConvertToNeighbourIndex(y, chunkHeight), ConvertToNeighbourIndex(x, chunkWidth));
		return grid[ConvertToNeighbourIndex(y, chunkHeight)][ConvertToNeighbourIndex(x, chunkWidth)] == NOTHING;
	}
	return grid[y][x] == NOTHING;
}

PixelChunk::PixelChunk(int width, int height, pair<int, int> chunkIndex, short initialValue)
{
	this->chunkIndex = chunkIndex;
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

void PixelChunk::Advance(int neighbourIndexOffset)
{
	for (int y = chunkHeight - 1; y >= 0; --y)
	{
		for (int x = 0; x < chunkWidth; ++x)
		{
			if (IsLocationEmpty(y, x)) {
				continue;
			}


			//printf("evalauted: %d %d\n", evaluation->second, evaluation->first);
//printf("current: %d %d\n", y, x);

			const pair<pair<short, short>, PixelChunk*> evaluation = evaluator->Evaluate(this, y, x);
			if (evaluation.first.first == y && evaluation.first.second == x && evaluation.second == nullptr) {
				continue;
			}
			if (evaluation.second == nullptr)
			{
				grid[evaluation.first.first][evaluation.first.second] = grid[y][x];
				grid[y][x] = NOTHING;
			}
			else 
			{
				int convertedY = ConvertToNeighbourIndex(evaluation.first.first, chunkHeight);
				int convertedX = ConvertToNeighbourIndex(evaluation.first.second, chunkWidth);
				//printf("in %d %d setting %d %d\n", chunkIndex.first, chunkIndex.second, convertedY, convertedX);
				if (evaluation.second->Set(convertedY, convertedX, grid[y][x])) {
					grid[y][x] = NOTHING;
				}

				//newY = ConvertToNeighbourIndex(newY, chunkHeight);
				//newX = ConvertToNeighbourIndex(newX, chunkWidth);
				////printf("new coord: %d %d\n", newY, newX);
				////printf("neightbour: %d %d\n", chunkIndex.first + evaluation->second, chunkIndex.second + evaluation->first);
				//if (neighbour != nullptr && neighbour->IsLocationEmpty(newY, newX))
				//{
				//	//printf("to neighbour index: %d %d\n", neighbour->chunkIndex.second, neighbour->chunkIndex.first);
				//	neighbour->Set(newY, newX, grid[y][x]);
				//	grid[y][x] = NOTHING;
				//}
			}
		}
	}
}

bool PixelChunk::IsLocationCorner(int y, int x)
{
	return (y == 0 && x == 0) || (y == 0 && x == chunkWidth - 1) || 
		(y == chunkHeight - 1 && x == 0) || (y == chunkHeight - 1 && x == chunkWidth - 1);
}

PixelChunk* PixelChunk::IsNeighbourAvailableForSet(int y, int x)
{
	bool yInRange = 0 <= y && y < chunkHeight;
	bool xInRange = 0 <= x && x < chunkWidth;

	// check neighbouring grid
	int xInd = chunkIndex.second;
	int yInd = chunkIndex.first;
	if (y < 0 && xInRange)	// top
	{
		--yInd;
	}
	else if (y >= chunkHeight && xInRange)	// bottom 
	{
		++yInd;
	}
	else if (x < 0 && yInRange)	// left
	{
		--xInd;
	}
	else if (x >= chunkWidth && yInRange)	// right
	{
		++xInd;
	}
	else if (x < 0 && y < 0)	// top left
	{
		--yInd;
		--xInd;
	}
	else if (x >= chunkWidth && y < 0)	// top right
	{
		--yInd;
		++xInd;
	}
	else if (x >= chunkWidth && y >= chunkHeight)	// bottom right 
	{
		++yInd;
		++xInd;
	}
	else if (x < 0 && y >= chunkHeight)	// bottom left
	{
		++yInd;
		--xInd;
	}
	//printf("validating: %d %d\n", y, x);
	//printf("checking neighbour: %d %d\n", yInd, xInd);
	//for (auto& n : neighbours)
	//{
	//	printf("neighbouring %d %d\n", n.second->chunkIndex.first, n.second->chunkIndex.second);
	//}

	auto result = neighbours.find(std::make_pair(yInd, xInd));
	if (result != neighbours.end())
	{
		//printf("found neighbour %d %d\n", result->second->chunkIndex.first, result->second->chunkIndex.second);
		return result->second;
	}
	return  nullptr;
}

bool PixelChunk::Set(int y, int x, short value)
{
	if (IsIndexValid(y, x)) {
		grid[y][x] = value;
		//printf("Set {%d, %d}", y, x);
		return true;
	}
	return false;
}

void PixelChunk::Print(void)
{
	//std::cout << "\x1B[2J\x1B[H";
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
	neighbours.emplace(newNeighbour->chunkIndex, newNeighbour);
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