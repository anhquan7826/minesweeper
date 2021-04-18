#ifndef _CONTROLLER_STRUCT
#define _CONTROLLER_STRUCT

#include <SDL.h>

struct Controller {
    int step;
    int line;
    bool next;
    Controller();
    void reset();
    void handleLine(SDL_Event* e, const int lineCount);
};

#endif