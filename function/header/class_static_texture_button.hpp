#ifndef _CLASS_STATIC_TEXTURE_BUTTON
#define _CLASS_STATIC_TEXTURE_BUTTON

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

#include "enum.hpp"
#include "controller.hpp"

using namespace std;

class STxButton {
    private:
        AlphaControl mAlpha;
        int org_x, org_y, org_w, org_h;
        int x, y, w, h;
        int effectSize;
        int effectSpeed;
        SDL_Texture* texture;
        ButtonState state;
        bool isDimensionSet;
        bool isPressed;
    public:
        STxButton();
        bool load(SDL_Renderer* gRenderer, string path);
        void setDimension(int _x, int _y, int _w, int _h);
        void handleEvent(SDL_Event* e);
        void render(SDL_Renderer* gRenderer, int fadeSpeed);
        void setFadeState(FadeState fade);
        bool isButtonPressed();
        bool isButtonVisible();
        void reset();
};

#endif