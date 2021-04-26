#include "play.hpp"

#include "tile.hpp" 
#include "class_text.hpp"
#include "class_timer.hpp"
#include "class_static_texture_button.hpp"
#include "sound.hpp"

Tile Minefield[3];
TTF_Font* timer_font;
TTF_Font* prompt_font;
Text you_lose;
Text you_win;
Timer timeCount;
Text timer;
int timer_y = 700/2-30/2;
STxButton replay;
STxButton goback;
STxButton goback_sub;

bool PLAY_load(SDL_Renderer* gRenderer) {
    for (int i=0; i<3; i++) {
        if (!Minefield[i].load(gRenderer, "assets/tiles")) {return false;}
    }
    Minefield[0].setup(9, 9, 10, 602, 18, 72, 72, 8);
    Minefield[1].setup(16, 16, 40, 602, 23, 40, 40, 6); 
    Minefield[2].setup(30, 30, 99, 600, 21, 21, 21, 4);
    timer_font = TTF_OpenFont("assets/font/whitrabt.ttf", 30);
    if (timer_font == NULL) {return false;}
    prompt_font = TTF_OpenFont("assets/font/whitrabt.ttf", 40);
    you_lose.loadFromText(gRenderer, prompt_font, "YOU LOSE!", {255, 255, 255});
    you_win.loadFromText(gRenderer, prompt_font, "YOU WIN!", {255, 255, 255});
    if (!replay.load(gRenderer, "assets/button/replay.png")) {return false;}
    if (!goback.load(gRenderer, "assets/button/back.png")) {return false;}
    if (!goback_sub.load(gRenderer, "assets/button/back.png")) {return false;}
    goback_sub.setDimension(10, 10, 30, 30);
    return true;
}

void PLAY_handleEvent(SDL_Event* e, GameState state, Level lv) {
    if (state == PLAY) {
        Minefield[lv].handleEvent(e);
        goback.handleEvent(e);
        replay.handleEvent(e);
        goback_sub.handleEvent(e);
    }
}

GameState PLAY_render(SDL_Renderer* gRenderer, int fadeSpeed, Level lv) {
    GameState p = PLAY;
    switch (Minefield[lv].render(gRenderer, fadeSpeed)) {
        case PLAY: {
            goback_sub.render(gRenderer, fadeSpeed);
            timeCount.start();
            if (timer_y < 700/2-timer.getHeight()/2) {
                timer_y += 20;
            }
            break;
        }
        case WIN: {
            goback_sub.setFadeState(FADE_OUT);
            goback_sub.render(gRenderer, fadeSpeed);
            playWin();
            timeCount.pause();
            if (timer_y > 150) {
                timer_y -= 10;
            } else {
                replay.setDimension(Minefield[lv].getX()/2-110, 450, 100, 100);
                goback.setDimension(Minefield[lv].getX()/2+10, 450, 100, 100);
                you_win.setPosition(Minefield[lv].getX()/2-you_win.getWidth()/2, 320);
                replay.render(gRenderer, fadeSpeed);
                goback.render(gRenderer, fadeSpeed);
                you_win.render(gRenderer, fadeSpeed);
            }
            break;
        }
        case LOSE: {
            goback_sub.setFadeState(FADE_OUT);
            goback_sub.render(gRenderer, fadeSpeed);
            playLose();
            timeCount.pause();
            if (timer_y > 100) {
                timer_y -= 10;
            } else {
                replay.setDimension(Minefield[lv].getX()/2-110, 450, 100, 100);
                goback.setDimension(Minefield[lv].getX()/2+10, 450, 100, 100);
                you_lose.setPosition(Minefield[lv].getX()/2-you_lose.getWidth()/2, 320);
                replay.render(gRenderer, fadeSpeed);
                goback.render(gRenderer, fadeSpeed);
                you_lose.render(gRenderer, fadeSpeed);
            }
            break;
        }
    }
    if (replay.isButtonPressed()) {
        replay.setFadeState(FADE_OUT);
        goback.setFadeState(FADE_OUT);
        you_lose.setFadeState(FADE_OUT);
        you_win.setFadeState(FADE_OUT);
        Minefield[lv].FadeOut();
        if (replay.isButtonPressed() && !replay.isButtonVisible()) {
            replay.reset();
            goback.reset();
            you_lose.reset();
            you_win.reset();
            Minefield[lv].reset();
            timeCount.stop();
            goback_sub.reset();
        }
    }
    if (goback.isButtonPressed()) {
        replay.setFadeState(FADE_OUT);
        goback.setFadeState(FADE_OUT);
        you_lose.setFadeState(FADE_OUT);
        you_win.setFadeState(FADE_OUT);
        Minefield[lv].FadeOut();
        timer.setFadeState(FADE_OUT);
        goback_sub.setFadeState(FADE_OUT);
        if (!goback.isButtonVisible()) {
            replay.reset();
            goback.reset();
            you_lose.reset();
            you_win.reset();
            Minefield[lv].reset();
            timeCount.stop();
            timer.reset();
            timer_y = 700/2-30/2;
            p = MAIN_MENU;
            goback_sub.reset();
        }
    }
    if (goback_sub.isButtonPressed()) {
        replay.setFadeState(FADE_OUT);
        goback.setFadeState(FADE_OUT);
        you_lose.setFadeState(FADE_OUT);
        you_win.setFadeState(FADE_OUT);
        Minefield[lv].FadeOut();
        timer.setFadeState(FADE_OUT);
        goback_sub.setFadeState(FADE_OUT);
        if (!goback_sub.isButtonVisible()) {
            replay.reset();
            goback.reset();
            you_lose.reset();
            you_win.reset();
            Minefield[lv].reset();
            timeCount.stop();
            timer.reset();
            timer_y = 700/2-30/2;
            p = MAIN_MENU;
            goback_sub.reset();
        }
    }
    timer.loadFromText(gRenderer, timer_font, timeCount.getClockCount(), {255, 255, 255});
    timer.setPosition(Minefield[lv].getX()/2-timer.getWidth()/2, timer_y);
    timer.render(gRenderer, fadeSpeed);
    return p;
}