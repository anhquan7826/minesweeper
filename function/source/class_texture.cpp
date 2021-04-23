#include "class_texture.hpp"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

Texture::Texture() {
    texture == NULL;
    w = 0;
    h = 0;
    a = 0;
}

void Texture::free() {
    texture = NULL;
    w = 0;
    h = 0;
    a = 0;
}

int Texture::getWidth() {
    return w;
}

int Texture::getHeight() {
    return h;
}

void Texture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::setDimension(int _x, int _y, int _w, int _h) {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

bool Texture::loadFromFile(SDL_Renderer* gRenderer, string path) {
    free();
    SDL_Surface* loadedSurface = NULL;
    loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        return false;
    } else {
        texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }
    return true;
}

void Texture::render(SDL_Renderer* gRenderer) {
    SDL_Rect renderPos = {x, y, w, h};
    SDL_RenderCopy(gRenderer, texture, NULL, &renderPos);
}

bool Texture::isTextureNULL() {
    return (texture != NULL);
}