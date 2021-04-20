#include "alpha_control.hpp"

AlphaControl::AlphaControl() {
    querry = 1;
    alpha = 0;
}

void AlphaControl::setFade(int _querry) {
    querry = _querry;
}

void AlphaControl::fade(int fadeSpeed) {
    switch (querry) {
        case 0: {
            if (alpha > 0) {
                alpha -= fadeSpeed;
            }
            if (alpha == 0) {
                querry = -1;
            }
            break;
        }
        case 1: {
            if (alpha < 255) {
                alpha += fadeSpeed;
            }
            if (alpha == 255) {
                querry = -1;
            }
            break;
        }
    }
}

void AlphaControl::reset() {
    querry = 1;
    alpha = 0;
}