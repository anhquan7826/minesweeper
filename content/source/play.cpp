#include "play.hpp"
#include "class_tile.hpp" 
#include "class_timer.hpp"
#include "class_static_texture_button.hpp"

Tile Minefield[3];
Timer timeCount;

STxButton test;

bool PLAY_load(SDL_Renderer* gRenderer) {
    for (int i=0; i<3; i++) {
        if (!Minefield[i].load(gRenderer, "assets/tiles")) {return false;}
    }
    Minefield[0].setup(9, 9, 10, 476, 116, 40, 40, 6);
    Minefield[1].setup(16, 16, 40, 395, 35, 30, 30, 6); 
    Minefield[2].setup(30, 30, 99, 382, 22, 16, 16, 4);
    return true;
}

void PLAY_handleEvent(SDL_Event* e, GameState state, Level lv) {
    if (state == PLAY) {
        Minefield[lv].handleEvent(e);
    }
}

GameState PLAY_render(SDL_Renderer* gRenderer, int fadeSpeed, Level lv) {
    GameState p = PLAY;
    switch (Minefield[lv].render(gRenderer, fadeSpeed)) {
        case WIN: {
            
            break;
        }
        case LOSE: {

            break;
        }
    }
    return p;
}