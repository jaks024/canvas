#pragma once
#include "Game.h"
#include "PixelGrid.h"
using std::vector;
class FallingSandGame :
    public Game
{
    private:
        const int PIXEL_SIZE = 5;
        const int CHUNK_SIZE = 40;
        const int GRID_WIDTH = 5;
        const int GRID_HEIGHT = 3;
        PixelGrid* pixelGrid; 
        PixelChunk* currentChunk;
        ResourceObject* defaultSquare;
        bool autoAdvance = false;
        void PrepareScene(void) override;
        void Update(void) override;
        void Paint(void);
        void Clear(void);
        void BindKeys();
        void Brush(int mouseXPos, int mouseYPos, PixelType value);
        void ToggleAutoAdvance(void);

    public:
        bool InitializeResources(void) override;
        bool InitializeGame(void) override;
        void Destroy(void) override;
};

