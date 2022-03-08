#pragma once
#include <vector>
#include "PixelBehaviorEvaluator.h"
using std::vector;

class PixelChunk
{
	private: 
		PixelBehaviorEvaluator* evaluator;
		bool IsIndexValid(int y, int x);

	public:
		const static short INVALID = -1;
		const static short NOTHING = 0;
		const static short SAND = 1;
		vector<vector<short>> grid;

		PixelChunk(int width, int height, short initialValue = 0);
		~PixelChunk(void);
		void Clear(void);
		void Advance(void);
		void Set(int y, int x, short value);
		void Print(void);
};

