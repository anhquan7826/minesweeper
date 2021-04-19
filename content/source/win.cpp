#include "win.hpp"
#include "controller_struct.hpp"

Controller win;

Text you_lose;
TextButton Continue;

void WIN_load(SDL_Renderer* gRenderer, TTF_Font* gFont_title, TTF_Font* gFont_button, int WINDOW_WIDTH, int WINDOW_HEIGHT) {
    you_lose.loadFromText(gRenderer, gFont_title, "YOU WIN!", {255, 255, 255});
    you_lose.setPosition(WINDOW_WIDTH/2-you_lose.getWidth()/2, 100);
    Continue.setText(gRenderer, gFont_button, "Continue", {255, 255, 255});
    Continue.setDimension(WINDOW_WIDTH/2-400/2, WINDOW_HEIGHT-150, 400, 40);
}

void WIN_handleEvent(SDL_Event* e, GameState state) {
    if (state == WIN) {
        Continue.handleEvent(e);
    }
}

GameState WIN_render(SDL_Renderer* gRenderer, int fadeSpeed) {
    GameState p = WIN;
    you_lose.render(gRenderer, fadeSpeed);
    Continue.render(gRenderer, fadeSpeed);
    if (Continue.isButtonPressed()) {
        win.next = true;
        you_lose.setFadeState(FADE_OUT);
        Continue.setFadeState(FADE_OUT);
    }
    if (win.next && !you_lose.isTextVisible()) {
        p = PLAY;
    }
    return p;
}