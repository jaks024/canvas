#pragma once
#include <vector>
using std::vector;
using std::tuple;

class PixelBehaviorEvaluator
{
	public:

		//		0	1	2
		//	0	x	x	x
		//	1	x	o	x
		//	2	x	x	x
		//
		// o = {1, 1}

		const tuple<short, short> TOP_LEFT = { -1, -1 };
		const tuple<short, short> TOP = { 0, -1 };
		const tuple<short, short> TOP_RIGHT = { 1, -1 };
		const tuple<short, short> LEFT = { -1, 0 };
		const tuple<short, short> STILL = { 0, 0 };
		const tuple<short, short> RIGHT = { 1, 0 };
		const tuple<short, short> BOT_LEFT = { -1, 1 };
		const tuple<short, short> BOT = { 0, 1 };
		const tuple<short, short> BOT_RIGHT = { 1, 1 };

		bool IsIndexValid(vector<vector<short>>* grid, int y, int x);
		const tuple<short, short>* Evaluate(vector<vector<short>>* fragment, int centerY = 1, int centerX = 1);	// returns direction to go


};

