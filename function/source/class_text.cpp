#include "class_text.hpp"
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

Text::Text() {
    texture = NULL;
    x = 0;
    y = 0;
    w = 0;
    h = 0;
    isVisible = true;
}

Text::~Text() {
    free();
}

void Text::free() {
    SDL_DestroyTexture(texture);
    texture = NULL;
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

int Text::getWidth() {
    return w;
}

int Text::getHeight() {
    return h;
}

void Text::setPosition(int _x, int _y) {
    x = _x;
    y = _y;
}

void Text::setFadeState(FadeState state) {
    mAlpha.setFadeState(state);
}

void Text::loadFromText(SDL_Renderer* gRenderer, TTF_Font* gFont, string text, SDL_Color color) {
    free();
    SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    w = textSurface->w;
    h = textSurface->h;
    SDL_FreeSurface(textSurface);
}

void Text::render(SDL_Renderer* gRenderer, int speedvalue) {
    mAlpha.fade(speedvalue);
    SDL_SetTextureAlphaMod(texture, mAlpha.alpha);
    SDL_Rect renderPos = {x, y, w, h};
    SDL_RenderCopy(gRenderer, texture, NULL, &renderPos);
}

void Text::reset() {
    mAlpha.reset();
    isVisible = true;
}

bool Text::isTextVisible() {
    if (mAlpha.alpha == 0) {
        return false;
    }
    else {
        return true;
    }
}
