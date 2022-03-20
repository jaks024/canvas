#pragma once
#include <vector>
#include "PixelBehaviorEvaluator.h"
#include <SDL.h>
#include <map>
#include "../../Framework/Resource/ResourceObject.h"
#include "PixelState.h"
#include "PixelType.h"
using std::vector;
using std::pair;
using std::map;
using Framework::Resource::ResourceObject;

class PixelChunk
{
	private: 
		PixelBehaviorEvaluator* evaluator;
		map<pair<int, int>, PixelChunk*> neighbours;
		PixelChunk* CanSetInNeighbour(int y, int x, pair<int, int> neighbourIndex);
		int ConvertToNeighbourIndex(int val, int limit);
		bool IsSlowUpdateFrame = false;
		int slowUpdateTimer = 0;
		const int SLOW_UPDATE_TIME = 30;
		void UpdateSlowUpdateTimer(void);
		void UpdateState(int y, int x);

	public:
		vector<vector<PixelType>> grid;
		vector<vector<PixelState>> states;
		pair<int, int> chunkIndex;	// (y, x)
		int originX = 0;
		int originY = 0;
		int chunkWidth = 0;
		int chunkHeight = 0;

		PixelChunk(int width, int height, pair<int, int> chunkIndex, PixelType initialValue = PixelType::NOTHING);
		~PixelChunk(void);
		void SetPosition(int x, int y);
		bool IsIndexValid(int y, int x);
		bool IsLocationEmpty(int y, int x, bool neighbourConvert = false);
		bool IsLocationCorner(int y, int x);
		PixelChunk* IsNeighbourAvailableForSet(int y, int x);
		void Clear(void);
		void Advance(int neighbourIndexOffset);
		bool Set(int y, int x, PixelType value);	
		void Set_NoValidation(int y, int x, PixelType type);
		void AddNeighbour(PixelChunk* newNeighbour);
		void Print(void);
		void Draw(SDL_Renderer* renderer, ResourceObject* textureObj, int pixelSize);
};

