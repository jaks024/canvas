#pragma once
#include "Component.h"

namespace Framework::UI {

    class Background : public Component
    {
    protected:
        SDL_Color tintColor = {255, 255, 255};
    public:
        Background(unsigned int id, string name, SDL_Color tintColor, ResourceObject* textureObj, int width, int height);
        void SetTintColor(SDL_Color color);
        virtual void Draw(SDL_Renderer* renderer) override;
    };
}
