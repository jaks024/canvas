#include "PixelBehaviorEvaluator.h"
#include <tuple>
using std::get;

bool PixelBehaviorEvaluator::IsIndexValid(vector<vector<short>>* grid, int y, int x)
{
	if (0 <= y && y < (*grid).size()) {
		if (0 <= x && x < (*grid)[y].size()) {
			return true;
		}
	}
	return false;
}

const tuple<short, short>* PixelBehaviorEvaluator::Evaluate(vector<vector<short>>* fragment, int centerY, int centerX)
{
	int newY = centerY + get<1>(BOT);
	int newX = centerX + get<0>(BOT);
	if (IsIndexValid(fragment, newY, newX) && (*fragment)[newY][newX] == 0) {
		return &BOT;
	}
	bool left = rand() % 2 == 0 ? true : false;
	newY = centerY + get<1>(BOT_LEFT);
	newX = centerX + get<0>(BOT_LEFT);
	if (left && IsIndexValid(fragment, newY, newX) && (*fragment)[newY][newX] == 0)
	{
		return &BOT_LEFT;
	}
	newY = centerY + get<1>(BOT_RIGHT);
	newX = centerX + get<0>(BOT_RIGHT);
	if (IsIndexValid(fragment, newY, newX) && (*fragment)[newY][newX] == 0)
	{
		return &BOT_RIGHT;
	}
	return &STILL;
}
