#ifndef _PLAY
#define _PLAY

#include "enum.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

bool PLAY_load(SDL_Renderer* gRenderer);
void PLAY_handleEvent(SDL_Event* e, GameState state, Level lv);
GameState PLAY_render(SDL_Renderer* gRenderer, int fadeSpeed, Level lv);

#endif