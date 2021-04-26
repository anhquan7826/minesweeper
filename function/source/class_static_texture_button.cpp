#include "class_static_texture_button.hpp"
#include "sound.hpp"

STxButton::STxButton() {
    org_x = 0; org_y = 0; org_w = 0; org_h = 0;
    x = 0;     y = 0;     w = 0;     h = 0;
    texture = NULL;
    state = BUTTON_MOUSE_OUT;
    isDimensionSet = false;
    isPressed = false;
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
    if (!isDimensionSet) {
        x = _x;     y = _y;     w = _w;     h = _h;
        isDimensionSet = true;
    }
    effectSize = org_w/10;
    if (effectSize < 2) {effectSpeed = 1;} else {effectSpeed = 2;}
}

void STxButton::handleEvent(SDL_Event* e) {
    if (mAlpha.alpha == 255) {
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
                    playButton();
                    isPressed = true;
                    break;
                }
            }
        }
    }
}

void STxButton::render(SDL_Renderer* gRenderer, int fadeSpeed) {
    mAlpha.fade(fadeSpeed);
    switch (state) {
        case BUTTON_MOUSE_OUT: {
            if (x < org_x && y < org_y) {
                x += effectSpeed;
                y += effectSpeed;
            }
            if (w > org_w && h > org_h) {
                w -= effectSpeed*2;
                h -= effectSpeed*2;
            }
            if (x > org_x && y > org_y) {
                x -= effectSpeed;
                y -= effectSpeed;
            }
            if (w < org_w && h < org_h) {
                w += effectSpeed*2;
                h += effectSpeed*2;
            }
            break;
        }
        case BUTTON_MOUSE_HOVER: {
            if (x > org_x-effectSize && y > org_y-effectSize) {
                x -= effectSpeed;
                y -= effectSpeed;
            }
            if (w < org_w+effectSize*2 && h < org_h+effectSize*2) {
                w += effectSpeed*2;
                h += effectSpeed*2;
            }
            break;
        }
        case BUTTON_MOUSELEFT_DOWN: {
            if (x < org_x+effectSize && y < org_y+effectSize) {
                x += effectSpeed;
                y += effectSpeed;
            }
            if (w > org_w-effectSize*2 && h > org_h-effectSize*2) {
                w -= effectSpeed*2;
                h -= effectSpeed*2;
            }
            break;
        }
        case BUTTON_MOUSELEFT_UP: {
            if (x > org_x-effectSize && y > org_y-effectSize) {
                x -= effectSpeed;
                y -= effectSpeed;
            }
            if (w < org_w+effectSize*2 && h < org_h+effectSize*2) {
                w += effectSpeed*2;
                h += effectSpeed*2;
            }
            break;
        }
    }
    SDL_SetTextureAlphaMod(texture, mAlpha.alpha);
    SDL_Rect renderPos = {x, y, w, h};
    SDL_RenderCopy(gRenderer, texture, NULL, &renderPos);
}

void STxButton::setFadeState(FadeState fade) {
    mAlpha.setFadeState(fade);
}

bool STxButton::isButtonPressed() {
    if (isPressed) {
        return true;
    }
    return false;
}

bool STxButton::isButtonVisible() {
    if (mAlpha.alpha == 0) {
        return false;
    } else {return true;}
}

void STxButton::reset() {
    isPressed = false;
    mAlpha.alpha = 0;
    mAlpha.setFadeState(FADE_IN);
    state = BUTTON_MOUSE_OUT;
    x = org_x; y = org_y; w = org_w; h = org_h;
}