#include "main_menu.hpp"

#include "class_text.hpp"
#include "class_text_button.hpp"
#include "controller_struct.hpp"
#include "class_static_texture_button.hpp"

using namespace std;

Controller main_menu;

Text menu_title;
Text menu_level;

STxButton menu_start;
STxButton menu_easy;
STxButton menu_hard;
STxButton menu_expert;

enum menu_state {
    _begin, _choose
};
menu_state m = _begin;

bool MAIN_MENU_load(SDL_Renderer* gRenderer, TTF_Font* gFont_title, TTF_Font* gFont_button, int WINDOW_WIDTH, int WINDOW_HEIGHT) {
    menu_title.loadFromText(gRenderer, gFont_title, "MINESWEEPER", {255, 255, 255});
    menu_title.setPosition(WINDOW_WIDTH/2-menu_title.getWidth()/2, 100);
    menu_level.loadFromText(gRenderer, gFont_button, "Choose Level...", {255, 255, 255});
    menu_level.setPosition(WINDOW_WIDTH/2-menu_title.getWidth()/2, 100);
    if (!menu_start.load(gRenderer, "assets/button/play.png")) {return false;}
    menu_start.setDimension(WINDOW_WIDTH/2-125/2, WINDOW_HEIGHT-200, 125, 125);
    if (!menu_easy.load(gRenderer, "assets/button/9x9.png")) {return false;}
    menu_easy.setDimension(300, WINDOW_HEIGHT-200, 120, 120);
    if (!menu_hard.load(gRenderer, "assets/button/16x16.png")) {return false;}
    menu_hard.setDimension(440, WINDOW_HEIGHT-200, 120, 120);
    if (!menu_expert.load(gRenderer, "assets/button/30x30.png")) {return false;}
    menu_expert.setDimension(580, WINDOW_HEIGHT-200, 120, 120);
    return true;
}

void MAIN_MENU_handleEvent(SDL_Event* e, GameState state) {
    if (state == MAIN_MENU) {
        switch (m) {
            case _begin: {
                menu_start.handleEvent(e);
                break;
            }
            case _choose: {
                menu_easy.handleEvent(e);
                menu_hard.handleEvent(e);
                menu_expert.handleEvent(e);
                break;
            }
        }
    }
}

GameState MAIN_MENU_render(SDL_Renderer* gRenderer, int fadeSpeed, Level& lv) {
    GameState p = MAIN_MENU;
    switch (m) {
        case _begin: {
            menu_title.render(gRenderer, fadeSpeed);
            menu_start.render(gRenderer, fadeSpeed);

            if (menu_start.isButtonPressed()) {
                main_menu.next = true;
                menu_title.setFadeState(FADE_OUT);
                menu_start.setFade(0);
            }
            if (main_menu.next && !menu_title.isTextVisible()) {
                m = _choose;
                main_menu.reset();
                menu_title.reset();
                menu_start.reset();
            }
            break;
        }
        case _choose: {
            menu_level.render(gRenderer, fadeSpeed);
            menu_easy.render(gRenderer, fadeSpeed);
            menu_hard.render(gRenderer, fadeSpeed);
            menu_expert.render(gRenderer, fadeSpeed);
            if (menu_easy.isButtonPressed() || menu_hard.isButtonPressed() || menu_expert.isButtonPressed()) {
                menu_easy.setFade(0);
                menu_hard.setFade(0);
                menu_expert.setFade(0);
                menu_level.setFadeState(FADE_OUT);
                main_menu.next = true;
            }
            if (main_menu.next && !menu_level.isTextVisible()) {
                if (menu_easy.isButtonPressed()) {lv = easy;}
                else if (menu_hard.isButtonPressed()) {lv = hard;}
                else if (menu_expert.isButtonPressed()) {lv = expert;}
                main_menu.reset();
                menu_level.reset();
                menu_easy.reset();
                menu_hard.reset();
                menu_expert.reset();
                p = PLAY;
            }
            break;
        }
    }
    return p;
}