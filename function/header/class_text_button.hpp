#ifndef TEXT_BUTTON
#define TEXT_BUTTON

#include <SDL.h>
#include "class_text.hpp"
#include "enum_ButtonState.hpp"

using namespace std;

class TextButton {
    private:
        SDL_Rect rect;
        ButtonState state; 
        Text text;
        Uint8 alpha;
    public:
        TextButton();
        void setText(SDL_Renderer* gRenderer, TTF_Font* gFont, string _text, SDL_Color color);
        void setDimension(int _x, int _y, int _w, int _h);
        void handleEvent(SDL_Event* e);
        void render(SDL_Renderer* gRenderer, int speedvalue);
        ButtonState getState();
        void setFadeState(FadeState state);
        bool isButtonVisible();
        void reset();
        bool isButtonPressed();
};

#endif
