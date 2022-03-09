#include "PixelBehaviorEvaluator.h"
using std::pair;

bool PixelBehaviorEvaluator::IsIndexValid(vector<vector<short>>* grid, int y, int x)
{
	if (0 <= y && y < (*grid).size()) {
		if (0 <= x && x < (*grid)[y].size()) {
			return true;
		}
	}
	return false;
}

const pair<short, short>* PixelBehaviorEvaluator::Evaluate(vector<vector<short>>* fragment, int centerY, int centerX)
{
	int newY = centerY + BOT.second;
	int newX = centerX + BOT.first;
	if (IsIndexValid(fragment, newY, newX) && (*fragment)[newY][newX] == 0) {
		return &BOT;
	}
	bool left = rand() % 2 == 0 ? true : false;
	newY = centerY + BOT_LEFT.second;
	newX = centerX + BOT_LEFT.first;
	if (left && IsIndexValid(fragment, newY, newX) && (*fragment)[newY][newX] == 0)
	{
		return &BOT_LEFT;
	}
	newY = centerY + BOT_RIGHT.second;
	newX = centerX + BOT_RIGHT.first;
	if (IsIndexValid(fragment, newY, newX) && (*fragment)[newY][newX] == 0)
	{
		return &BOT_RIGHT;
	}
	return &STILL;
}
