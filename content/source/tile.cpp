#include "tile.hpp"
#include <sstream>
#include <iostream>

using namespace std;

GameState p = PLAY;

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
    generate();
    return true;
}

void Tile::setup(int _m, int _n, int _k, int _x, int _y, int _w, int _h, int _g) {
    isUserPressed = false;
    m = _m; n = _n; k = _k;
    x = _x; y = _y;
    w = _w; h = _h; g = _g;
    for (int i=0; i<m; i++) {
        vector<ButtonState> tmp1;
        vector<TileState> tmp2;
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

        tile.push_back(tmp2);
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

void Tile::handleEvent(SDL_Event* e) {
    if (p == PLAY) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                if (tile[i][j] == hidden || tile[i][j] == flag) {
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
                                bool left = false, right = false;
                                if (e->button.button == SDL_BUTTON_LEFT) {left = true;}
                                if (e->button.button == SDL_BUTTON_RIGHT) {right = true;}
                                if (left && !right) {
                                    state[i][j] = BUTTON_MOUSELEFT_DOWN;
                                } 
                                else if (!left && right) {
                                    state[i][j] = BUTTON_MOUSERIGHT_DOWN;
                                }
                                break;
                            }
                            case SDL_MOUSEBUTTONUP: {
                                bool left = false, right = false;
                                if (e->button.button == SDL_BUTTON_LEFT) {left = true;}
                                if (e->button.button == SDL_BUTTON_RIGHT) {right = true;}
                                if (left && !right) {
                                    state[i][j] = BUTTON_MOUSELEFT_UP;
                                } 
                                else if (!left && right) {
                                    state[i][j] = BUTTON_MOUSERIGHT_UP;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

GameState Tile::render(SDL_Renderer* gRenderer, int fadeSpeed) {
    mAlpha.fade(fadeSpeed);
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            switch (tile[i][j]) {
                case num0: case num1: case num2: case num3: case num4: case num5: case num6: case num7: case num8:
                case bomb: {
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
                case hidden: case flag: {
                    switch (state[i][j]) {
                        case BUTTON_MOUSE_OUT: {
                            if (tile_x[i][j] < x+(w+g)*j && tile_y[i][j] < y+(h+g)*i) {
                                tile_x[i][j] += 1;
                                tile_y[i][j] += 1;
                            }
                            if (tile_w[i][j] > w && tile_h[i][j] > h) {
                                tile_w[i][j] -= 2;
                                tile_h[i][j] -= 2;
                            }
                            break;
                        }
                        case BUTTON_MOUSE_HOVER: {
                            if (tile_x[i][j] > x+(w+g)*j-g/2 && tile_y[i][j] > y+(h+g)*i-g/2) {
                                tile_x[i][j] -= 1;
                                tile_y[i][j] -= 1;
                            }
                            if (tile_w[i][j] < w+g && tile_h[i][j] < h+g) {
                                tile_w[i][j] += 2;
                                tile_h[i][j] += 2;
                            }
                            break;
                        }
                        case BUTTON_MOUSELEFT_DOWN: {
                            if (tile[i][j] == hidden) {
                                if (tile_x[i][j] < x+(w+g)*j+g/2 && tile_y[i][j] < y+(h+g)*i+g/2) {
                                    tile_x[i][j] += 2;
                                    tile_y[i][j] += 2;
                                }
                                if (tile_w[i][j] > w-g && tile_h[i][j] > h-g) {
                                    tile_w[i][j] -= 4;
                                    tile_h[i][j] -= 4;
                                }
                            }
                            break;
                        }
                        case BUTTON_MOUSERIGHT_DOWN: {
                            if (tile_x[i][j] < x+(w+g)*j+g/2 && tile_y[i][j] < y+(h+g)*i+g/2) {
                                tile_x[i][j] += 2;
                                tile_y[i][j] += 2;
                            }
                            if (tile_w[i][j] > w-g && tile_h[i][j] > h-g) {
                                tile_w[i][j] -= 4;
                                tile_h[i][j] -= 4;
                            }
                            break;
                        }
                        case BUTTON_MOUSELEFT_UP: {
                            if (tile[i][j] == hidden) {
                                if (!isUserPressed) {
                                    while (mine[i][j] != num0) {
                                        generate();
                                    } 
                                    isUserPressed = true;
                                }
                                if (mine[i][j] != bomb) {
                                    revealTile(i, j);
                                } else {
                                    revealAll();
                                    p = LOSE;
                                }
                            } else {
                                state[i][j] = BUTTON_MOUSE_HOVER;
                            } 
                            break;
                        }
                        case BUTTON_MOUSERIGHT_UP: {
                            if (tile[i][j] != flag) {
                                tile[i][j] = flag;
                            } else {
                                tile[i][j] = hidden;
                            }
                            state[i][j] = BUTTON_MOUSE_HOVER;
                            break;
                        }
                    }
                    break;
                }
            }
            SDL_Rect pos = {tile_x[i][j], tile_y[i][j], tile_w[i][j], tile_h[i][j]};
            SDL_SetTextureAlphaMod(tx[tile[i][j]], mAlpha.alpha);
            SDL_RenderCopy(gRenderer, tx[tile[i][j]], NULL, &pos);
        }
    }
    if (p != LOSE) {
        if (checkWin()) {
            p = WIN;
        }
    } 
    return p;
}

void Tile::revealTile(int i, int j) {
    tile_x[i][j] = x+(w+g)*j+2*(w/8); 
    tile_y[i][j] = y+(h+g)*i+2*(h/8);
    tile_w[i][j] = w-2*(w/4); 
    tile_h[i][j] = h-2*(h/4);
    tile[i][j] = mine[i][j];
    if (mine[i][j] == num0) {
        for (int a=i-1; a<=i+1; a++) {
            if (a<0 || a>=m) {continue;}
            for (int b=j-1; b<=j+1; b++) {
                if (b<0 || b>=n) {continue;}
                if (tile[a][b] == hidden) {
                    tile[a][b] = mine[a][b];
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
            tile[i][j] = mine[i][j];
        }
    }
}

bool Tile::checkWin() {
    bool check = true;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (tile[i][j] == hidden || tile[i][j] == flag) {
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

void Tile::generate() {
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            mine[i][j] = num0;
        }
    }
    int k_tmp = k;
    while (k_tmp != 0) {
        int a = rand()%m;
        int b = rand()%n;
        if (mine[a][b] != bomb) {
            mine[a][b] = bomb;
            k_tmp--;
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
                mine[i][j] = (TileState)Count;
            }
        }
    }
}

void Tile::reset() {
    mAlpha.reset();
    generate();
    p = PLAY;
    isUserPressed = false;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            tile[i][j] = hidden;
            state[i][j] = BUTTON_MOUSE_OUT;
        }
    }
}

int Tile::getX() {
    return x;
}

void Tile::FadeOut() {
    mAlpha.setFadeState(FADE_OUT);
}