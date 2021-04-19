#ifndef _WIN
#define _WIN

#include "class_text.hpp"
#include "class_text_button.hpp"
#include "game_state.hpp"

void WIN_load(SDL_Renderer* gRenderer, TTF_Font* gFont_title, TTF_Font* gFont_button, int WINDOW_WIDTH, int WINDOW_HEIGHT);
void WIN_handleEvent(SDL_Event* e, GameState state);
GameState WIN_render(SDL_Renderer* gRenderer, int fadeSpeed);

#endif