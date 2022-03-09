#pragma once
#include "Game.h"
#include "PixelChunk.h"
using std::vector;
class FallingSandGame :
    public Game
{
    private:
        const int PIXEL_SIZE = 5;
        const int CHUNK_SIZE = 100;
        vector<vector<PixelChunk*>> chunkGrid;
        PixelChunk* currentChunk;
        ResourceObject* defaultSquare;
        void PrepareScene(void) override;
        void Update(void) override;
        void Paint(void);
        void Clear(void);

    public:
        bool InitializeResources(void) override;
        bool InitializeGame(void) override;
        void Destroy(void) override;
};

