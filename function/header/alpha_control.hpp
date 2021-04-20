#ifndef _ALPHA_CONTROL
#define _ALPHA_CONTROL

#include <SDL.h>

using namespace std;

struct AlphaControl {
    Uint8 alpha;
    int querry;
    AlphaControl();
    void setFade(int _querry);
    void fade(int fadeSpeed);
    void reset();
};

#endif