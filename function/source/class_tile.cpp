#include "class_tile.hpp"
#include <sstream>
#include <iostream>

using namespace std;

Tile::Tile(int _m, int _n, int _k, int _x, int _y, int _w, int _h, int _g) {
    alpha = 0;
    m = _m; n = _n; k = _k;
    x = _x; y = _y;
    w = _w; h = _h; g = _g;
    for (int i=0; i<m; i++) {
        vector<ButtonState> tmp1;
        vector<tile_type> tmp2;
        vector<int> tmp3;
        for (int j=0; j<n; j++) {
            tmp1.push_back(BUTTON_MOUSE_OUT);
            tmp2.push_back(hidden);
            tmp3.push_back(0);
        }
        state.push_back(tmp1);
        tile_x.push_back(tmp3);
        tile_y.push_back(tmp3);
        tile_w.push_back(tmp3);
        tile_h.push_back(tmp3);

        cover.push_back(tmp2);
        mine.push_back(tmp2);
    }
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            tile_x[i][j] = x+(w+g)*j;
            tile_y[i][j] = y+(h+g)*i;
            tile_w[i][j] = w;
            tile_h[i][j] = h;
        }
    }
}

bool Tile::load(SDL_Renderer* gRenderer, string pathToFolder) {
    for (int i=0; i<12; i++) {
        stringstream input;
        input << pathToFolder << '/' << i << ".png";
        SDL_Surface* loadedSurface = NULL;
        loadedSurface = IMG_Load(input.str().c_str());
        if (loadedSurface == NULL) {
            return false;
        } else {
            tx[i] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
            SDL_FreeSurface(loadedSurface);
        }
    }
    SDL_SetTextureAlphaMod(tx[hidden], alpha);
    
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            mine[i][j] = num0;
        }
    }
    while (k != 0) {
        int a = rand()%m;
        int b = rand()%n;
        if (mine[a][b] != bomb) {
            mine[a][b] = bomb;
            k--;
        }
    }
    int Count;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            Count=0;
            if (mine[i][j] != bomb) {
                for (int a=i-1; a<=i+1; a++) {
                    if (a<0 || a>=m) {continue;}
                    for (int b=j-1; b<=j+1; b++) {
                        if (b<0 || b >= n) {continue;}
                        if (mine[a][b] == bomb) {
                            Count++;
                        }
                    }
                }
                mine[i][j] = (tile_type)Count;
            }
        }
    }
    return true;
}

void Tile::handleEvent(SDL_Event* e) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (cover[i][j] == hidden) {
                bool inside = true;
                if ((mouseX < x+(w+g)*j) || (mouseX > x+(w+g)*j+w)) {
                    inside = false;
                }
                if ((mouseY < y+(h+g)*i) || (mouseY > y+(h+g)*i+h)) {
                    inside = false;
                }
                if (!inside) {
                    state[i][j] = BUTTON_MOUSE_OUT;
                } else {
                    switch (e->type) {
                        case SDL_MOUSEMOTION: {
                            state[i][j] = BUTTON_MOUSE_HOVER;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN: {
                            if (e->button.button == SDL_BUTTON_RIGHT)
                            state[i][j] = BUTTON_MOUSE_DOWN;
                            break;
                        }
                        case SDL_MOUSEBUTTONUP: {
                            state[i][j] = BUTTON_MOUSE_UP;
                            break;
                        }
                    }
                }
            }
        }
    }
}

GameState Tile::render(SDL_Renderer* gRenderer) {
    cout << (int)alpha << endl;
    if (alpha < 255) {alpha += 5;}
    GameState p = PLAY;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            switch (cover[i][j]) {
                case revealed: {
                //    if (state[i][j] == BUTTON_MOUSE_UP) {
                        if (tile_x[i][j] > x+(w+g)*j && tile_y[i][j] > y+(h+g)*i) {
                            tile_x[i][j] -= 1;
                            tile_y[i][j] -= 1;
                        }
                        if (tile_w[i][j] < w && tile_h[i][j] < h) {
                            tile_w[i][j] += 2;
                            tile_h[i][j] += 2;
                        }
                //    }
                    SDL_Rect pos = {tile_x[i][j], tile_y[i][j], tile_w[i][j], tile_h[i][j]};
                    SDL_RenderCopy(gRenderer, tx[mine[i][j]], NULL, &pos);
                    break;
                }
                case hidden: {
                    switch (state[i][j]) {
                        case BUTTON_MOUSE_OUT: {
                            if (tile_x[i][j] > x+(w+g)*j && tile_y[i][j] > y+(h+g)*i) {
                                tile_x[i][j] -= 1;
                                tile_y[i][j] -= 1;
                            }
                            if (tile_w[i][j] < w && tile_h[i][j] < h) {
                                tile_w[i][j] += 2;
                                tile_h[i][j] += 2;
                            }
                            break;
                        }
                        case BUTTON_MOUSE_HOVER: {
                            if (tile_x[i][j] < x+(w+g)*j+w/8 && tile_y[i][j] < y+(h+g)*i+h/8) {
                                tile_x[i][j] += 1;
                                tile_y[i][j] += 1;
                            }
                            if (tile_w[i][j] > w-w/4 && tile_h[i][j] > h-h/4) {
                                tile_w[i][j] -= 2;
                                tile_h[i][j] -= 2;
                            }
                            break;
                        }
                        case BUTTON_MOUSE_DOWN: {
                            if (tile_x[i][j] < x+(w+g)*j+2*(w/8) && tile_y[i][j] < y+(h+g)*i+2*(h/8)) {
                                tile_x[i][j] += 2;
                                tile_y[i][j] += 2;
                            }
                            if (tile_w[i][j] > w-2*(w/4) && tile_h[i][j] > h-2*(h/4)) {
                                tile_w[i][j] -= 4;
                                tile_h[i][j] -= 4;
                            }
                            break;
                        }
                        case BUTTON_MOUSE_UP: {
                            if (mine[i][j] != bomb) {
                                revealTile(i, j);
                            } else {
                                revealAll();
                                p = LOSE;
                            }
                            break;
                        }
                    }
                    SDL_Rect pos = {tile_x[i][j], tile_y[i][j], tile_w[i][j], tile_h[i][j]};
                    SDL_SetTextureAlphaMod(tx[hidden], alpha);
                    SDL_RenderCopy(gRenderer, tx[hidden], NULL, &pos);
                    break;
                }
            }
        }
    }
    if (checkWin()) {p = WIN;}
    return p;
}

void Tile::revealTile(int i, int j) {
    tile_x[i][j] = x+(w+g)*j+2*(w/8); 
    tile_y[i][j] = y+(h+g)*i+2*(h/8);
    tile_w[i][j] = w-2*(w/4); 
    tile_h[i][j] = h-2*(h/4);
    cover[i][j] = revealed;
    if (mine[i][j] == num0) {
        for (int a=i-1; a<=i+1; a++) {
            if (a<0 || a>=m) {continue;}
            for (int b=j-1; b<=j+1; b++) {
                if (b<0 || b>=n) {continue;}
                if (cover[a][b] != revealed) {
                    cover[a][b] = revealed;
                    if (mine[a][b] == num0) {
                        revealTile(a, b);
                    }
                }
            }
        }
    }
}

void Tile::revealAll() {
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            tile_x[i][j] = x+(w+g)*j+2*(w/8); 
            tile_y[i][j] = y+(h+g)*i+2*(h/8);
            tile_w[i][j] = w-2*(w/4); 
            tile_h[i][j] = h-2*(h/4);
            cover[i][j] = revealed;
        }
    }
}

bool Tile::checkWin() {
    bool check = true;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (cover[i][j] == hidden) {
                if (mine[i][j] != bomb) {
                    check = false;
                    break;
                }
            }
        }
        if (!check) {break;}
    }
    return check;
}