#ifndef _MAIN_MENU
#define _MAIN_MENU

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "game_state.hpp"
#include "level.hpp"

using namespace std;

bool MAIN_MENU_load(SDL_Renderer* gRenderer, TTF_Font* gFont_title, TTF_Font* gFont_button, int WINDOW_WIDTH, int WINDOW_HEIGHT);
void MAIN_MENU_handleEvent(SDL_Event* e, GameState state);
GameState MAIN_MENU_render(SDL_Renderer* gRenderer, int fadeSpeed, Level& lv);

#endif