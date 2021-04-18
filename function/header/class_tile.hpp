#ifndef _CLASS_TILE
#define _CLASS_TILE

#include "class_texture.hpp"
#include "class_texture_button.hpp"
#include "enum_ButtonState.hpp"
#include "game_state.hpp"

#include <vector>

enum tile_type{
    num0, num1, num2, num3, num4, num5, num6, num7, num8, bomb, flag, hidden, revealed
};

class Tile {
    private:
        vector<vector<ButtonState>> state;
        SDL_Texture* tx[12];
        int m, n, k;
        int x, y;
        int w, h, g;
        Uint8 alpha;
        vector<vector<int>> tile_x;
        vector<vector<int>> tile_y;
        vector<vector<int>> tile_w;
        vector<vector<int>> tile_h;

        vector<vector<tile_type>> cover;
        vector<vector<tile_type>> mine;
    public:
        Tile(int _m, int _n, int _k, int _x, int _y, int _w, int _h, int _g);
        bool load(SDL_Renderer* gRenderer, string path);
        void handleEvent(SDL_Event* e);
        GameState render(SDL_Renderer* gRenderer);
        void revealTile(int x, int y);
        void revealAll();
        bool checkWin();
};

#endif