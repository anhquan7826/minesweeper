#include "play.hpp"
#include "class_tile.hpp" 

Tile Minefield(16, 16, 255, 383, 10, 37, 37, 1);

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
    p = Minefield.render(gRenderer);
    return p;
}