#pragma once
#include "Game.h"
#include "PixelGrid.h"
using std::vector;
class FallingSandGame :
    public Game
{
    private:
        const int PIXEL_SIZE = 3;
        const int CHUNK_SIZE = 25;
        PixelGrid* pixelGrid; 
        PixelChunk* currentChunk;
        ResourceObject* defaultSquare;
        void PrepareScene(void) override;
        void Update(void) override;
        void Paint(void);
        void Clear(void);
        void BindKeys();
        void Brush(int mouseXPos, int mouseYPos, int value);

    public:
        bool InitializeResources(void) override;
        bool InitializeGame(void) override;
        void Destroy(void) override;
};

