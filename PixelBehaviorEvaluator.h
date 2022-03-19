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

		const pair<short, short> TOP_LEFT = { -1, -1 };		// {x , y}
		const pair<short, short> TOP = { 0, -1 };
		const pair<short, short> TOP_RIGHT = { 1, -1 };
		const pair<short, short> LEFT = { -1, 0 };
		const pair<short, short> STILL = { 0, 0 };
		const pair<short, short> RIGHT = { 1, 0 };
		const pair<short, short> BOT_LEFT = { -1, 1 };
		const pair<short, short> BOT = { 0, 1 };
		const pair<short, short> BOT_RIGHT = { 1, 1 };

		const pair<pair<short, short>, PixelChunk*> Evaluate(PixelChunk* chunk, int centerY = 1, int centerX = 1);	// returns direction to go


};

