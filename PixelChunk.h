#pragma once
#include <vector>
#include "PixelBehaviorEvaluator.h"
#include <SDL.h>
#include "ResourceObject.h"
using std::vector;
class PixelChunk
{
	private: 
		PixelBehaviorEvaluator* evaluator;
		bool IsIndexValid(int y, int x);
		vector<PixelChunk*> neighbours;

	public:
		const static short INVALID = -1;
		const static short NOTHING = 0;
		const static short SAND = 1;
		vector<vector<short>> grid;
		int chunkId;
		int originX = 0;
		int originY = 0;
		int chunkWidth = 0;
		int chunkHeight = 0;

		PixelChunk(int width, int height, int chunkId, short initialValue = 0);
		~PixelChunk(void);
		void SetPosition(int x, int y);
		void Clear(void);
		void Advance(void);
		void Set(int y, int x, short value);	
		void AddNeighbour(PixelChunk* newNeighbour);
		void Print(void);
		void Draw(SDL_Renderer* renderer, ResourceObject* textureObj, int pixelSize);
};

