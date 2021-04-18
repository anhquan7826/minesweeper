#ifndef _PLAY
#define _PLAY

#include "game_state.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

void PLAY_load(SDL_Renderer* gRenderer);
void PLAY_handleEvent(SDL_Event* e, GameState state);
GameState PLAY_render(SDL_Renderer* gRenderer);

#endif