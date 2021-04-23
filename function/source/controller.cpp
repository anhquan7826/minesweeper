#include "controller.hpp"

AlphaControl::AlphaControl() {
    querry = FADE_IN;
    alpha = 0;
}

void AlphaControl::setFadeState(FadeState _querry) {
    querry = _querry;
}

void AlphaControl::fade(int fadeSpeed) {
    switch (querry) {
        case FADE_OUT: {
            if (alpha > 0) {
                if (alpha >= fadeSpeed) {
                    alpha -= fadeSpeed;
                } else {
                    alpha = 0;
                }
            }
            if (alpha == 0) {
                querry = STATIC;
            }
            break;
        }
        case FADE_IN: {
            if (alpha < 255) {
                if (255-alpha >= fadeSpeed) {
                    alpha += fadeSpeed;
                } else {
                    alpha = 255;
                }
            }
            if (alpha == 255) {
                querry = STATIC;
            }
            break;
        }
    }
}

void AlphaControl::reset() {
    querry = FADE_IN;
    alpha = 0;
}

LineControl::LineControl() {
    step = 0;
    line = 0;
    next = false;
}

void LineControl::reset() {
    step = 0;
    line = 0;
    next = false;
}

void LineControl::handleLine(SDL_Event* e, const int lineCount) {
    if (e->type == SDL_MOUSEBUTTONUP) {
        step++;
        if (step < lineCount) {
            line++;
        }
    }
}