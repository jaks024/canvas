#pragma once
#include <vector>
#include "PixelBehaviorEvaluator.h"
#include <SDL.h>
#include <map>
#include "ResourceObject.h"
using std::vector;
using std::pair;
using std::map;
class PixelChunk
{
	private: 
		PixelBehaviorEvaluator* evaluator;
		map<pair<int, int>, PixelChunk*> neighbours;
		PixelChunk* CanSetInNeighbour(int y, int x, pair<int, int> neighbourIndex);
		int ConvertToNeighbourIndex(int val, int limit);

	public:
		const static short INVALID = -1;
		const static short NOTHING = 0;
		const static short SAND = 1;
		vector<vector<short>> grid;
		pair<int, int> chunkIndex;	// (y, x)
		int originX = 0;
		int originY = 0;
		int chunkWidth = 0;
		int chunkHeight = 0;

		PixelChunk(int width, int height, pair<int, int> chunkIndex, short initialValue = 0);
		~PixelChunk(void);
		void SetPosition(int x, int y);
		bool IsIndexValid(int y, int x);
		bool IsLocationEmpty(int y, int x, bool neighbourConvert = false);
		bool IsLocationCorner(int y, int x);
		PixelChunk* IsNeighbourAvailableForSet(int y, int x);
		void Clear(void);
		void Advance(int neighbourIndexOffset);
		bool Set(int y, int x, short value);	
		void AddNeighbour(PixelChunk* newNeighbour);
		void Print(void);
		void Draw(SDL_Renderer* renderer, ResourceObject* textureObj, int pixelSize);
};

