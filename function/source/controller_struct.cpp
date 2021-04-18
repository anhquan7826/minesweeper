#include "controller_struct.hpp"

#include <SDL.h>

Controller::Controller() {
    step = 0;
    line = 0;
    next = false;
}

void Controller::reset() {
    step = 0;
    line = 0;
    next = false;
}

void Controller::handleLine(SDL_Event* e, const int lineCount) {
    if (e->type == SDL_MOUSEBUTTONUP) {
        step++;
        if (step < lineCount) {
            line++;
        }
    }
}