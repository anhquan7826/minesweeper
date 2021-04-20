#ifndef CLASS_TEXT
#define CLASS_TEXT

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

enum FadeState {
    FADE_IN, FADE_OUT, STATIC
};

class Text {
    private:
        SDL_Texture* texture;
        int x, y;
        int w, h;
        Uint8 a;
        FadeState fadeState;
        bool isVisible;
    public:
        Text();
        void free();
        int getWidth();
        int getHeight();
        void setPosition(int _x, int _y);
        void loadFromText(SDL_Renderer* gRenderer, TTF_Font* gFont, string text, SDL_Color color);
        void render(SDL_Renderer* gRenderer, int speedvalue);
        void setFadeState(FadeState state);
        bool isTextVisible();
        void reset();
        int getFadeState();
};

#endif