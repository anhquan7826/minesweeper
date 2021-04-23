#ifndef _CLASS_TILE
#define _CLASS_TILE

#include "enum.hpp"
#include "controller.hpp"

#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class Tile {
    private:
        vector<vector<ButtonState>> state;
        SDL_Texture* tx[12];
        int m, n, k;
        int x, y;
        int w, h, g;
        AlphaControl mAlpha;
        vector<vector<int>> tile_x;
        vector<vector<int>> tile_y;
        vector<vector<int>> tile_w;
        vector<vector<int>> tile_h;

        vector<vector<TileState>> tile;
        vector<vector<TileState>> mine;

        bool isUserPressed = false;
    public:
        void setup(int _m, int _n, int _k, int _x, int _y, int _w, int _h, int _g);
        bool load(SDL_Renderer* gRenderer, string path);
        void generate();
        void handleEvent(SDL_Event* e);
        GameState render(SDL_Renderer* gRenderer, int fadeSpeed);
        void revealTile(int x, int y);
        void revealAll();
        bool checkWin();
        void reset();
        int getX();
        void FadeOut();
};

#endif