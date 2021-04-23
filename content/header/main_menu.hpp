#ifndef _MAIN_MENU
#define _MAIN_MENU

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "enum.hpp"

using namespace std;

bool MAIN_MENU_load(SDL_Renderer* gRenderer);
void MAIN_MENU_handleEvent(SDL_Event* e, GameState state);
GameState MAIN_MENU_render(SDL_Renderer* gRenderer, int fadeSpeed, Level& lv);

#endif