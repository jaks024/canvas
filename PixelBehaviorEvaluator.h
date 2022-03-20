#pragma once
#include <vector>
using std::vector;
using std::pair;

class PixelChunk;

class PixelBehaviorEvaluator
{
	public:

		//		0	1	2
		//	0	x	x	x
		//	1	x	o	x
		//	2	x	x	x
		//
		// o = {1, 1}

		const pair<short, short> TOP_LEFT = { -1, -1 };		// { , y}
		const pair<short, short> TOP = { -1, 0 };
		const pair<short, short> TOP_RIGHT = { -1, 1 };
		const pair<short, short> LEFT = { 0, -1 };
		const pair<short, short> STILL = { 0, 0 };
		const pair<short, short> RIGHT = { 0, 1 };
		const pair<short, short> BOT_LEFT = { 1, -1 };
		const pair<short, short> BOT = { 1, 0 };
		const pair<short, short> BOT_RIGHT = { 1, 1 };

		const pair<pair<short, short>, PixelChunk*> Evaluate(PixelChunk* chunk, int centerY = 1, int centerX = 1);	// returns direction to go
		PixelChunk* CheckNeighbour(PixelChunk* chunk, int nY, int nX, int setY, int setX);
		bool CanSetNeighbour(PixelChunk* chunk, const pair<int, int> neighbourDirection, 
			int centerY, int centerX, int setY, int setX, PixelChunk*& neighbour);




};

