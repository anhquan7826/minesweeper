#include "class_static_texture_button.hpp"

STxButton::STxButton() {
    org_x = 0; org_y = 0; org_w = 0; org_h = 0;
    x = 0;     y = 0;     w = 0;     h = 0;
    texture = NULL;
    state = BUTTON_MOUSE_OUT;
}

bool STxButton::load(SDL_Renderer* gRenderer, string path) {
    SDL_Surface* loadedSurface;
    loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        cout << "Cannot load: " << path << endl;
        return false;
    }
    else {
        texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        w = loadedSurface->w;
        h = loadedSurface->h;
        SDL_FreeSurface(loadedSurface);
    }
    return true;
}

void STxButton::setDimension(int _x, int _y, int _w, int _h) {
    org_x = _x; org_y = _y; org_w = _w; org_h = _h;
    x = _x;     y = _y;     w = _w;     h = _h;
}

void STxButton::handleEvent(SDL_Event* e) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    bool inside = true;
    if ((mouseX < org_x) || (mouseX > org_x+org_w)) {
        inside = false;
    }
    if ((mouseY < org_y) || (mouseY > org_y+org_h)) {
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

void STxButton::render(SDL_Renderer* gRenderer, int fadeSpeed) {
    mAlpha.fade(fadeSpeed);
    switch (state) {
        case BUTTON_MOUSE_OUT: {
            if (x < org_x && y < org_y) {
                x += 1;
                y += 1;
            }
            if (w > org_w && h > org_h) {
                w -= 2;
                h -= 2;
            }
            break;
        }
        case BUTTON_MOUSE_HOVER: {
            if (x > org_x-4 && y > org_y-4) {
                x -= 1;
                y -= 1;
            }
            if (w < org_w+8 && h < org_h+8) {
                w += 2;
                h += 2;
            }
            break;
        }
        case BUTTON_MOUSELEFT_DOWN: {
            if (x < org_x+4 && y < org_y+4) {
                x += 2;
                y += 2;
            }
            if (w > org_w-8 && h > org_h-8) {
                w -= 4;
                h -= 4;
            }
            break;
        }
        case BUTTON_MOUSELEFT_UP: {
            if (x > org_x-4 && y > org_y-4) {
                x -= 1;
                y -= 1;
            }
            if (w < org_w+8 && h < org_h+8) {
                w += 2;
                h += 2;
            }
            break;
        }
    }
    SDL_SetTextureAlphaMod(texture, mAlpha.alpha);
    SDL_Rect renderPos = {x, y, w, h};
    SDL_RenderCopy(gRenderer, texture, NULL, &renderPos);
}

void STxButton::setFade(int fade) {
    mAlpha.setFade(fade);
}

bool STxButton::isButtonPressed() {
    if (state == BUTTON_MOUSELEFT_UP) {
        return true;
    }
    return false;
}

void STxButton::reset() {
    mAlpha.alpha = 0;
    mAlpha.setFade(1);
    state = BUTTON_MOUSE_OUT;
}