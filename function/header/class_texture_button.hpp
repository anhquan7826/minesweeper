#ifndef _CLASS_TEXTURE_BUTTON
#define _CLASS_TEXTURE_BUTTON

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "enum.hpp"

using namespace std;

class TextureButton {
    private:
        SDL_Texture* texture[4];
        Uint8 a[4];
        int x, y, w, h;
        ButtonState state;
    public:
        TextureButton();
        bool loadFromFile(SDL_Renderer* gRenderer, string path);
        void handleEvent(SDL_Event* e);
        void setPosition(int _x, int _y);
        void render(SDL_Renderer* gRenderer, int fadeSpeed);
};

#endif