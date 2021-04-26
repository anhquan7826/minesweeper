#include "main_menu.hpp"

#include "class_text.hpp"
#include "controller.hpp"
#include "class_static_texture_button.hpp"

using namespace std;

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 700;

LineControl main_menu;

Text menu_title;
Text menu_level;

STxButton menu_start;
STxButton menu_quit;

STxButton menu_easy;
STxButton menu_hard;
STxButton menu_expert;

TTF_Font* gFont_title = NULL;
TTF_Font* gFont_text = NULL;

const int title_size = 50;
const int text_size = 35;

enum menu_state {
    _begin, _choose
};
menu_state m = _begin;

bool MAIN_MENU_load(SDL_Renderer* gRenderer) {
    gFont_title = TTF_OpenFont("assets/font/whitrabt.ttf", title_size);
    if (gFont_title == NULL) {
        cout << "Cannot load font for MAIN_MENU" << endl;
        return false;
    }
    gFont_text = TTF_OpenFont("assets/font/whitrabt.ttf", text_size);

    menu_title.loadFromText(gRenderer, gFont_title, "MINESWEEPER", {255, 255, 255});
    menu_title.setPosition(WINDOW_WIDTH/2-menu_title.getWidth()/2, 200);
    menu_level.loadFromText(gRenderer, gFont_text, "Choose Level...", {255, 255, 255});
    menu_level.setPosition(WINDOW_WIDTH/2-menu_title.getWidth()/2, 200);

    if (!menu_start.load(gRenderer, "assets/button/play.png")) {return false;}
    menu_start.setDimension(WINDOW_WIDTH/2-125-10, WINDOW_HEIGHT-200, 125, 125);
    if (!menu_quit.load(gRenderer, "assets/button/quit.png")) {return false;}
    menu_quit.setDimension(WINDOW_WIDTH/2+10, WINDOW_HEIGHT-200, 125, 125);

    if (!menu_easy.load(gRenderer, "assets/button/9x9.png")) {return false;}
    menu_easy.setDimension(WINDOW_WIDTH/2-60-20-120, WINDOW_HEIGHT-200, 120, 120);
    if (!menu_hard.load(gRenderer, "assets/button/16x16.png")) {return false;}
    menu_hard.setDimension(WINDOW_WIDTH/2-60, WINDOW_HEIGHT-200, 120, 120);
    if (!menu_expert.load(gRenderer, "assets/button/30x30.png")) {return false;}
    menu_expert.setDimension(WINDOW_WIDTH/2+60+20, WINDOW_HEIGHT-200, 120, 120);
    return true;
}

void MAIN_MENU_handleEvent(SDL_Event* e, GameState state) {
    if (state == MAIN_MENU) {
        switch (m) {
            case _begin: {
                menu_start.handleEvent(e);
                menu_quit.handleEvent(e);
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
            menu_quit.render(gRenderer, fadeSpeed);

            if (menu_start.isButtonPressed() || menu_quit.isButtonPressed()) {
                main_menu.next = true;
                menu_title.setFadeState(FADE_OUT);
                menu_start.setFadeState(FADE_OUT);
                menu_quit.setFadeState(FADE_OUT);
            }
            if (main_menu.next && !menu_start.isButtonVisible() && menu_start.isButtonPressed()) {
                m = _choose;
                main_menu.reset();
                menu_title.reset();
                menu_start.reset();
                menu_quit.reset();
            }
            if (main_menu.next && menu_quit.isButtonPressed() && !menu_quit.isButtonVisible()) {
                p = QUIT;
            }
            break;
        }
        case _choose: {
            menu_level.render(gRenderer, fadeSpeed);
            menu_easy.render(gRenderer, fadeSpeed);
            menu_hard.render(gRenderer, fadeSpeed);
            menu_expert.render(gRenderer, fadeSpeed);
            if (menu_easy.isButtonPressed() || menu_hard.isButtonPressed() || menu_expert.isButtonPressed()) {
                menu_easy.setFadeState(FADE_OUT);
                menu_hard.setFadeState(FADE_OUT);
                menu_expert.setFadeState(FADE_OUT);
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
                m = _begin;
                p = PLAY;
            }
            break;
        }
    }
    return p;
}