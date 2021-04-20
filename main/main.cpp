#define SDL_MAIN_HANDLED
// Standard C++ libraries
#include <iostream>
#include <vector>
#include <ctime>

// SDL
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

// Custom headers
#include "game_state.hpp"
#include "level.hpp"
#include "class_texture.hpp"

#include "main_menu.hpp"
#include "play.hpp"
#include "win.hpp"

using namespace std;

// Global variables
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 640;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

TTF_Font* gFont_title = NULL;
TTF_Font* gFont_text = NULL;
TTF_Font* gFont_button = NULL;

const int title_size = 50;
const int text_size = 20;
const int button_size = 16;

int fadeSpeed = 15;

// Files directory
string dir_font = "assets/font/whitrabt.ttf";

// Contents
GameState currentState = MAIN_MENU;
Texture background;
Level lv = unknown;

// Initiate
bool initiate() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << SDL_GetError() << endl;
        return false;
    }
    else if (!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) {
        cout << SDL_GetError() << endl;
        return false;
    }
    else if (TTF_Init() == -1) {
        cout << SDL_GetError() << endl;
        return false;
    }
    else if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << SDL_GetError() << endl;
        return false;
    }
    else {
        gWindow = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            cout << "gWindow NULL" << endl;
            cout << SDL_GetError() << endl;
            return false;
        } else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                cout << "gRenderer NULL" << endl;
                cout << SDL_GetError() << endl;
                return false;
            }
        }
    }
    return true;
}

// Shutdown
void close() {
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    TTF_CloseFont(gFont_title);
    TTF_CloseFont(gFont_text);
    TTF_CloseFont(gFont_button);
    gFont_title = NULL;
    gFont_text = NULL;
    gFont_button = NULL;
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

// Load
bool load() {
    gFont_title = TTF_OpenFont(dir_font.c_str(), title_size);
    if (gFont_title == NULL) {
        cout << "Cannot find " << dir_font << endl;
        return false;
    }
    gFont_text = TTF_OpenFont(dir_font.c_str(), text_size);
    gFont_button = TTF_OpenFont(dir_font.c_str(), button_size);

    if (!background.loadFromFile(gRenderer, "assets/background/background.png")) {
        return false;
    }
    background.setDimension(0, 0, 1000, 640);

    if (!MAIN_MENU_load(gRenderer, gFont_title, gFont_button, WINDOW_WIDTH, WINDOW_HEIGHT)) {return false;}
    if (!PLAY_load(gRenderer)) {return false;}
    WIN_load(gRenderer, gFont_title, gFont_button, WINDOW_WIDTH, WINDOW_HEIGHT);

    return true;
}

int main(int argc, char* argv[]) {
    srand(time(0));
    if (!initiate()) {
        cout << "Cannot initiate!" << endl;
    }
    else if (!load()) {
        cout << "Cannot load!" << endl;
    }
    else {
        bool quit = false;
        SDL_Event e;
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                MAIN_MENU_handleEvent(&e, currentState);
                PLAY_handleEvent(&e, currentState, lv);
                WIN_handleEvent(&e, currentState);
            }

            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
            SDL_RenderClear(gRenderer);

            background.render(gRenderer);

            switch(currentState) {
                case MAIN_MENU: {
                    currentState = MAIN_MENU_render(gRenderer, fadeSpeed, lv);
                    break;
                }
                case PLAY: {
                    currentState = PLAY_render(gRenderer, fadeSpeed, lv);
                    break;
                }
            }

            SDL_RenderPresent(gRenderer);
        }
    }
    close();
    return 0;
}