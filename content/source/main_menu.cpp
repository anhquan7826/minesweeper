#include "main_menu.hpp"

#include "class_text.hpp"
#include "class_text_button.hpp"
#include "controller_struct.hpp"

using namespace std;

Controller main_menu;

Text menu_title;
TextButton menu_start;

void MAIN_MENU_load(SDL_Renderer* gRenderer, TTF_Font* gFont_title, TTF_Font* gFont_button, int WINDOW_WIDTH, int WINDOW_HEIGHT) {
    menu_title.loadFromText(gRenderer, gFont_title, "MINESWEEPER", {255, 255, 255});
    menu_title.setPosition(WINDOW_WIDTH/2-menu_title.getWidth()/2, 100);
    menu_start.setText(gRenderer, gFont_button, "START", {255, 255, 255});
    menu_start.setDimension(WINDOW_WIDTH/2-400/2, WINDOW_HEIGHT-150, 400, 40);
}

void MAIN_MENU_handleEvent(SDL_Event* e, GameState state) {
    if (state == MAIN_MENU) {
        menu_start.handleEvent(e);
    }
}

GameState MAIN_MENU_render(SDL_Renderer* gRenderer, int fadeSpeed) {
    GameState p = MAIN_MENU;
    menu_title.render(gRenderer, fadeSpeed);
    menu_start.render(gRenderer, fadeSpeed);

    if (menu_start.isButtonPressed()) {
        main_menu.next = true;
        menu_title.setFadeState(FADE_OUT);
        menu_start.setFadeState(FADE_OUT);
    }
    if (main_menu.next && !menu_title.isTextVisible()) {
        p = PLAY;
        main_menu.next = false;
    }
    return p;
}