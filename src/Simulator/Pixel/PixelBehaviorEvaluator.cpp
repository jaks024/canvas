#include "../../../include/Simulator/Pixel/PixelBehaviorEvaluator.h"
#include "../../../include/Simulator/Pixel/PixelChunk.h"

const pair<pair<short, short>, PixelChunk*> PixelBehaviorEvaluator::Evaluate(PixelType type, PixelChunk* chunk, int centerY, int centerX)
{
	if (type != PixelType::SAND) {
		return { {centerY, centerX}, nullptr };
	}

	PixelChunk* neighbour = nullptr;
	int newY = centerY + BOT.first;
	int newX = centerX + BOT.second;

	if (chunk->IsIndexValid(newY, newX))
	{
		if (chunk->IsLocationEmpty(newY, newX)) 
		{
			return { {newY, newX}, nullptr };
		}
	}
	else if (CanSetNeighbour(chunk, BOT, centerY, centerX, newY, newX, neighbour))
	{
		return { {newY, newX}, neighbour };
	}

	bool left = rand() % 2 == 0 ? true : false;
	newY = centerY + BOT_LEFT.first;
	newX = centerX + BOT_LEFT.second;
	if (left)
	{
		if (chunk->IsIndexValid(newY, newX))
		{
			if (chunk->IsLocationEmpty(newY, newX)) 
			{
				return { {newY, newX}, nullptr };
			}
		}
		else if (chunk->IsLocationCorner(centerY, centerX)) 
		{
			if (CanSetNeighbour(chunk, BOT_LEFT, centerY, centerX, newY, newX, neighbour)) 
			{
				return { {newY, newX}, neighbour };
			}
		} 
		else if (CanSetNeighbour(chunk, LEFT, centerY, centerX, newY, newX, neighbour)
			|| CanSetNeighbour(chunk, BOT_LEFT, centerY, centerX, newY, newX, neighbour))
		{
			return { {newY, newX}, neighbour };
		}
	}

	newY = centerY + BOT_RIGHT.first;
	newX = centerX + BOT_RIGHT.second;
	if (chunk->IsIndexValid(newY, newX))
	{
		if (chunk->IsLocationEmpty(newY, newX))
		{
			return { {newY, newX}, nullptr };
		}
	}
	else if (chunk->IsLocationCorner(centerY, centerX))
	{
		if (CanSetNeighbour(chunk, BOT_RIGHT, centerY, centerX, newY, newX, neighbour))
		{
			return { {newY, newX}, neighbour };
		}
	}
	else if (CanSetNeighbour(chunk, RIGHT, centerY, centerX, newY, newX, neighbour)
		|| CanSetNeighbour(chunk, BOT_RIGHT, centerY, centerX, newY, newX, neighbour))
	{
		return { {newY, newX}, neighbour };
	}


	return { {centerY, centerX}, nullptr };
	/*
		priorties: go down, then bot left or bot right
		check going bot
			if it is valid 
				if location is empty
					go bot and signify no neighbour
					end
			else if it is not valid 
				if there's a neighbour right below chunk 
					if the location is empty
						go bot and signify bot neighbour
						end
		check going bot left
			if it is valid
				is location is empty
					go bot left and signify no neighbour
			else if it is not valid
				if current location is a corner location
					if there is a neighbour to the bot left
						if the location is empty
							go bot left and signify bot left neighbour
							end
				else if current location is not a corner location
					if there is a neighbour to the left
						if the location is empty
							go bot left and signify left neighbour
				
		check going bot right
			...
		
			stay still 
			end
	
	*/
}

PixelChunk* PixelBehaviorEvaluator::CheckNeighbour(PixelChunk* chunk, int nY, int nX, int setY, int setX)
{
	PixelChunk* neighbour = chunk->IsNeighbourAvailableForSet(nY, nX);
	if (neighbour != nullptr)
	{
		if (neighbour->IsLocationEmpty(setY, setX, true))
		{
			//		printf("bot location avaliable %d %d", newY, newX);
			return neighbour;
		}
	}
	return nullptr;
}

bool PixelBehaviorEvaluator::CanSetNeighbour(PixelChunk* chunk, const pair<int, int> neighbourDirection, 
	int centerY, int centerX, int setY, int setX, PixelChunk*& neighbour)
{
	neighbour = CheckNeighbour(chunk, centerY + neighbourDirection.first, centerX + neighbourDirection.second, setY, setX);
	return neighbour != nullptr;
}
