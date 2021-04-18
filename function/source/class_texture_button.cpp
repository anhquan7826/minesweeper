#include "class_texture_button.hpp"

#include "class_texture.hpp"
#include <sstream>
#include <iostream>

using namespace std;

TextureButton::TextureButton() {
    for (int i=0; i<4; i++) {
        texture[i] = NULL;
        a[i] = 0;
    }
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

bool TextureButton::loadFromFile(SDL_Renderer* gRenderer, string path) {
    SDL_Surface* loadedSurface[4];
    for (int i=0; i<4; i++) {
        stringstream input;
        input << path << '/' << i << ".png";
        loadedSurface[i] = IMG_Load(input.str().c_str());
        if (loadedSurface[i] == NULL) {
            cout << "Cannot load: " << input.str() << endl;
            return false;
        }
        else {
            texture[i] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface[i]);
            w = loadedSurface[i]->w;
            h = loadedSurface[i]->h;
            SDL_FreeSurface(loadedSurface[i]);
        }
    }
    return true;
}

void TextureButton::setPosition(int _x, int _y) {
    x = _x;
    y = _y;
}

void TextureButton::handleEvent(SDL_Event* e) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    bool inside = true;
    if ((mouseX < x) || (mouseX > x+w)) {
        inside = false;
    }
    if ((mouseY < y) || (mouseY > y+h)) {
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
                state = BUTTON_MOUSE_DOWN;
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                state = BUTTON_MOUSE_UP;
                break;
            }
        }
    }
}

void TextureButton::render(SDL_Renderer* gRenderer, int fadeSpeed) {
    SDL_Rect renderPos = {x, y, w, h};
    switch (state) {
        case BUTTON_MOUSE_OUT:
            if (a[BUTTON_MOUSE_OUT] < 255) {
                a[BUTTON_MOUSE_OUT] += fadeSpeed;
            }
            if (a[BUTTON_MOUSE_HOVER] > 0) {
                a[BUTTON_MOUSE_HOVER] -= fadeSpeed;
            }
            a[BUTTON_MOUSE_DOWN] = 0;
            SDL_SetTextureAlphaMod(texture[BUTTON_MOUSE_OUT], a[BUTTON_MOUSE_OUT]);
            SDL_SetTextureAlphaMod(texture[BUTTON_MOUSE_HOVER], a[BUTTON_MOUSE_HOVER]);
            SDL_RenderCopy(gRenderer, texture[BUTTON_MOUSE_OUT], NULL, &renderPos);
            SDL_RenderCopy(gRenderer, texture[BUTTON_MOUSE_HOVER], NULL, &renderPos);
            break;
        case BUTTON_MOUSE_HOVER:
            if (a[BUTTON_MOUSE_HOVER] < 255) {
                a[BUTTON_MOUSE_HOVER] += fadeSpeed;
            }
            if (a[BUTTON_MOUSE_OUT] > 0) {
                a[BUTTON_MOUSE_OUT] -= fadeSpeed;
            }
            SDL_SetTextureAlphaMod(texture[BUTTON_MOUSE_OUT], a[BUTTON_MOUSE_OUT]);
            SDL_SetTextureAlphaMod(texture[BUTTON_MOUSE_HOVER], a[BUTTON_MOUSE_HOVER]);
            SDL_RenderCopy(gRenderer, texture[BUTTON_MOUSE_OUT], NULL, &renderPos);
            SDL_RenderCopy(gRenderer, texture[BUTTON_MOUSE_HOVER], NULL, &renderPos);
            break;
        case BUTTON_MOUSE_DOWN:
            a[BUTTON_MOUSE_DOWN] = 255;
            SDL_SetTextureAlphaMod(texture[BUTTON_MOUSE_DOWN], a[BUTTON_MOUSE_DOWN]);
            SDL_RenderCopy(gRenderer, texture[BUTTON_MOUSE_DOWN], NULL, &renderPos);
            break;
        case BUTTON_MOUSE_UP:
            if (a[BUTTON_MOUSE_HOVER] < 255) {
                a[BUTTON_MOUSE_HOVER] += fadeSpeed;
            }
            if (a[BUTTON_MOUSE_OUT] > 0) {
                a[BUTTON_MOUSE_OUT] -= fadeSpeed;
            }
            SDL_SetTextureAlphaMod(texture[BUTTON_MOUSE_OUT], a[BUTTON_MOUSE_OUT]);
            SDL_SetTextureAlphaMod(texture[BUTTON_MOUSE_HOVER], a[BUTTON_MOUSE_HOVER]);
            SDL_RenderCopy(gRenderer, texture[BUTTON_MOUSE_OUT], NULL, &renderPos);
            SDL_RenderCopy(gRenderer, texture[BUTTON_MOUSE_HOVER], NULL, &renderPos);
            break;
    }
}