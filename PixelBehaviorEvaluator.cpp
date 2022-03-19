#include "PixelBehaviorEvaluator.h"
#include "PixelChunk.h"

const pair<pair<short, short>, PixelChunk*> PixelBehaviorEvaluator::Evaluate(PixelChunk* chunk, int centerY, int centerX)
{
	int newY = centerY + BOT.second;
	int newX = centerX + BOT.first;
	//printf("pixel %d %d to %d %d\n", centerY, centerX, newY, newX);
	if (chunk->IsIndexValid(newY, newX)) 
	{
		if (chunk->IsLocationEmpty(newY, newX)) 
		{
			return { {newY, newX}, nullptr };
		}
	}
	else
	{
		PixelChunk* neighbour = chunk->IsNeighbourAvailableForSet(newY, newX);
		if (neighbour != nullptr)
		{
			if (neighbour->IsLocationEmpty(newY, newX, true))
			{
		//		printf("bot location avaliable %d %d", newY, newX);
				return { {newY, newX}, neighbour };
			}
		}
	}

	//printf("not bot\n");
	bool left = rand() % 2 == 0 ? true : false;
	newY = centerY + BOT_LEFT.second;
	newX = centerX + BOT_LEFT.first;
	if (left)
	{
		if (chunk->IsIndexValid(newY, newX))
		{
			if (chunk->IsLocationEmpty(newY, newX))
			{
				return { {newY, newX}, nullptr };
			}
		}
		else
		{
			if (chunk->IsLocationCorner(centerY, centerX))
			{
				PixelChunk* neighbour = chunk->IsNeighbourAvailableForSet(newY, newX);
				if (neighbour != nullptr)
				{
					if (neighbour->IsLocationEmpty(newY, newX, true))
					{
						return { {newY, newX}, neighbour };
					}
				}
			}
			else
			{
		//		printf("looking for %d %d neighbour\n", centerY, newX);
				PixelChunk* neighbour = chunk->IsNeighbourAvailableForSet(centerY, newX);
				if (neighbour != nullptr)
				{
			//		printf("found neighbour: %d %d\n", neighbour->chunkIndex.first, neighbour->chunkIndex.second);
					if (neighbour->IsLocationEmpty(newY, newX, true))
					{
				//		printf("location avaliable %d %d\n", newY, newX);
						return { {newY, newX}, neighbour };
					}
				}
				neighbour = chunk->IsNeighbourAvailableForSet(newY, newX);
				if (neighbour != nullptr)
				{
					//printf("found neighbour: %d %d\n", neighbour->chunkIndex.first, neighbour->chunkIndex.second);
					if (neighbour->IsLocationEmpty(newY, newX, true))
					{
						//printf("location avaliable %d %d\n", newY, newX);
						return { {newY, newX}, neighbour };
					}
				}
			}
		}
	}
	//printf("not left\n");
	newY = centerY + BOT_RIGHT.second;
	newX = centerX + BOT_RIGHT.first;
	if (chunk->IsIndexValid(newY, newX))
	{
		if (chunk->IsLocationEmpty(newY, newX))
		{
			return { {newY, newX}, nullptr };
		}
	}
	else
	{
		if (chunk->IsLocationCorner(centerY, centerX))
		{
			PixelChunk* neighbour = chunk->IsNeighbourAvailableForSet(newY, newX);
			if (neighbour != nullptr)
			{
				if (neighbour->IsLocationEmpty(newY, newX, true))
				{
					return { {newY, newX}, neighbour };
				}
			}
		}
		else
		{
			//printf("looking for %d %d neighbour\n", centerY, newX);
			PixelChunk* neighbour = chunk->IsNeighbourAvailableForSet(centerY, newX);
			if (neighbour != nullptr)
			{
				//printf("found neighbour: %d %d\n", neighbour->chunkIndex.first, neighbour->chunkIndex.second);
				if (neighbour->IsLocationEmpty(newY, newX, true))
				{
				//	printf("location avaliable %d %d\n", newY, newX);
					return { {newY, newX}, neighbour };
				}
			}
			neighbour = chunk->IsNeighbourAvailableForSet(newY, newX);
			if (neighbour != nullptr)
			{
			//	printf("found neighbour: %d %d\n", neighbour->chunkIndex.first, neighbour->chunkIndex.second);
				if (neighbour->IsLocationEmpty(newY, newX, true))
				{
		//			printf("location avaliable %d %d\n", newY, newX);
					return { {newY, newX}, neighbour };
				}
			}
		}
	}
	//printf("not right\n");

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
