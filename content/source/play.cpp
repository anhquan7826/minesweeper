#include "play.hpp"
#include "class_tile.hpp" 
#include "class_timer.hpp"

Tile Minefield(16, 16, 255, 383, 10, 37, 37, 1);
Timer timeCount;

void PLAY_load(SDL_Renderer* gRenderer) {
    Minefield.load(gRenderer, "assets/tiles");
}

void PLAY_handleEvent(SDL_Event* e, GameState state) {
    if (state == PLAY) {
        Minefield.handleEvent(e);
    }
}

GameState PLAY_render(SDL_Renderer* gRenderer) {
    GameState p = PLAY;
    switch (Minefield.render(gRenderer)) {
        case WIN: {
            
            break;
        }
        case LOSE: {

            break;
        }
    }
    return p;
}