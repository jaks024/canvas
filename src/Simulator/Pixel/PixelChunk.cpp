#include "../../../include/Simulator/Pixel/PixelChunk.h"
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

void PixelChunk::UpdateSlowUpdateTimer(void)
{
	if (IsSlowUpdateFrame) {
		IsSlowUpdateFrame = false;
		return;
	}

	++slowUpdateTimer;
	if (slowUpdateTimer == SLOW_UPDATE_TIME) {
		slowUpdateTimer = 0;
		IsSlowUpdateFrame = true;
	}
}

void PixelChunk::UpdateState(int y, int x)
{
	switch (states[y][x])
	{
	case PixelState::LAST_MOVED:
		states[y][x] = PixelState::LAST_STILL;
		break;
	case PixelState::LAST_STILL:
		states[y][x] = PixelState::LAST_STILL_TWO_FRAME;
		break;
	case PixelState::LAST_STILL_TWO_FRAME:
		states[y][x] = PixelState::LAST_STILL_THREE_FRAME;
		break;
	case PixelState::LAST_STILL_THREE_FRAME:
		states[y][x] = PixelState::SLOW_UDPATE;
		break;
	}
}

bool PixelChunk::IsLocationEmpty(int y, int x, bool neighbourConvert)
{
	if (neighbourConvert) {
		return grid[ConvertToNeighbourIndex(y, chunkHeight)][ConvertToNeighbourIndex(x, chunkWidth)] == PixelType::NOTHING;
	}
	return grid[y][x] == PixelType::NOTHING;
}

PixelChunk::PixelChunk(int width, int height, pair<int, int> chunkIndex, PixelType initialValue)
{
	this->chunkIndex = chunkIndex;
	this->chunkWidth = width;
	this->chunkHeight = height;
	evaluator = new PixelBehaviorEvaluator();
	for (int i = 0; i < height; i++)
	{
		vector<PixelType> gridRow;
		vector<PixelState> stateRow;
		for (int h = 0; h < width; h++)
		{
			gridRow.push_back(initialValue);
			stateRow.push_back(PixelState::LAST_STILL);
		}
		grid.push_back(gridRow);
		states.push_back(stateRow);
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
			grid[i][j] = PixelType::NOTHING;
		}
	}
}

void PixelChunk::Advance(int neighbourIndexOffset)
{
	for (int y = chunkHeight - 1; y >= 0; --y)
	{
		for (int x = 0; x < chunkWidth; ++x)
		{
			if (IsLocationEmpty(y, x) || (!IsSlowUpdateFrame && states[y][x] == PixelState::SLOW_UPDATE)) {
				continue;
			}

			const pair<pair<short, short>, PixelChunk*> evaluation = evaluator->Evaluate(this, y, x);

			// evaluated to stay still
			if (evaluation.first.first == y && evaluation.first.second == x && evaluation.second == nullptr) {
				UpdateState(y, x);
				continue;
			}
			// evaluated to be able to move
			if (evaluation.second == nullptr)
			{
				Set_NoValidation(evaluation.first.first, evaluation.first.second, grid[y][x]);
				Set_NoValidation(y, x, PixelType::NOTHING);
			}
			else 
			{
				int convertedY = ConvertToNeighbourIndex(evaluation.first.first, chunkHeight);
				int convertedX = ConvertToNeighbourIndex(evaluation.first.second, chunkWidth);
				if (evaluation.second->Set(convertedY, convertedX, grid[y][x])) {
					Set_NoValidation(y, x, PixelType::NOTHING);
				}
			}
		}
	}

	UpdateSlowUpdateTimer();
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

	auto result = neighbours.find(std::make_pair(yInd, xInd));
	if (result != neighbours.end())
	{
		return result->second;
	}
	return  nullptr;
}

bool PixelChunk::Set(int y, int x, PixelType type)
{
	if (IsIndexValid(y, x)) {
		Set_NoValidation(y, x, type);
		return true;
	}
	return false;
}

void PixelChunk::Set_NoValidation(int y, int x, PixelType type)
{
	states[y][x] = type == grid[y][x] ? PixelState::LAST_STILL : PixelState::LAST_MOVED;
	grid[y][x] = type;
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
	for (int y = 0; y < chunkHeight; y++)
	{
		for (int x = 0; x < chunkWidth; x++)
		{
			if (grid[y][x] != PixelType::NOTHING) {
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