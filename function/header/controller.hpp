#ifndef _CONTROLLER
#define _CONTROLLER

#include <SDL.h>
#include "enum.hpp"

using namespace std;

struct AlphaControl {
    Uint8 alpha;
    FadeState querry;
    AlphaControl();
    void setFadeState(FadeState _querry);
    void fade(int fadeSpeed);
    void reset();
};

struct LineControl {
    int step;
    int line;
    bool next;
    LineControl();
    void reset();
    void handleLine(SDL_Event* e, const int lineCount);
};

#endif