#include "class_text_button.hpp"
#include "class_text.hpp"

#include <SDL.h>
#include <iostream>

using namespace std;

TextButton::TextButton() {
    rect = {0, 0, 0, 0};
    alpha = 0;
}

void TextButton::setText(SDL_Renderer* gRenderer, TTF_Font* gFont, string _text, SDL_Color color) {
    text.loadFromText(gRenderer, gFont, _text, color);
}

void TextButton::setDimension(int _x, int _y, int _w, int _h) {
    rect = {_x, _y, _w, _h};
    text.setPosition(_x+rect.w/2-text.getWidth()/2, _y+rect.h/2-text.getHeight()/2);
}

void TextButton::handleEvent(SDL_Event* e) {
    if (text.getFadeState() == STATIC) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        bool inside = true;
        if ((mouseX < rect.x) || (mouseX > rect.x+rect.w)) {
            inside = false;
        }
        if ((mouseY < rect.y) || (mouseY > rect.y+rect.h)) {
            inside = false;
        }
        if (!inside) {
            state = BUTTON_MOUSE_OUT;
        } else {
            switch (e->type) {
                case SDL_MOUSEMOTION: {
                    state = BUTTON_MOUSE_HOVER;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    state = BUTTON_MOUSELEFT_DOWN;
                    break;
                }
                case SDL_MOUSEBUTTONUP: {
                    state = BUTTON_MOUSELEFT_UP;
                    break;
                }
            }
        }
    }
}

ButtonState TextButton::getState() {
    return state;
}

void TextButton::render(SDL_Renderer* gRenderer, int speedvalue) {
    switch (state) {
        case BUTTON_MOUSE_OUT:
            if (alpha > 0) {
                alpha -= speedvalue;
            }
            SDL_SetRenderDrawColor(gRenderer, alpha, alpha, alpha, 255);
            SDL_RenderDrawRect(gRenderer, &rect);
            text.render(gRenderer, speedvalue);
            break;
        case BUTTON_MOUSE_HOVER:
            if (alpha < 255) {
                alpha += speedvalue;
            }
            SDL_SetRenderDrawColor(gRenderer, alpha, alpha, alpha, 255);
            SDL_RenderDrawRect(gRenderer, &rect);
            text.render(gRenderer, speedvalue);
            break;
        case BUTTON_MOUSELEFT_DOWN:
            alpha = 255;
            SDL_SetRenderDrawColor(gRenderer, alpha, alpha, alpha, 255);
            SDL_RenderDrawRect(gRenderer, &rect);
            text.render(gRenderer, speedvalue);
            break;
        case BUTTON_MOUSELEFT_UP:
            if (text.getFadeState() != FADE_OUT) {
                if (alpha < 255) {
                    alpha += speedvalue;
                }
            } else {
                if (alpha > 0) {
                    alpha -= speedvalue;
                }
            }
            SDL_SetRenderDrawColor(gRenderer, alpha, alpha, alpha, 255);
            SDL_RenderDrawRect(gRenderer, &rect);
            text.render(gRenderer, speedvalue);
            break;
    }
}

void TextButton::setFadeState(FadeState state) {
    text.setFadeState(state);
}

void TextButton::reset() {
    alpha = 0;
    state = BUTTON_MOUSE_OUT;
    text.reset();
}

bool TextButton::isButtonVisible() {
    return text.isTextVisible();
}

bool TextButton::isButtonPressed() {
    if (state == BUTTON_MOUSELEFT_UP) {
        return true;
    }
    return false;
}