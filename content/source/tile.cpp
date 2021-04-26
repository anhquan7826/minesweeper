#include "tile.hpp"
#include <sstream>
#include <iostream>
#include "sound.hpp"

using namespace std;

GameState p = PLAY;
int updateSpeed = 1;

int hover_x = -1;
int hover_y = -1;

bool Tile::load(SDL_Renderer* gRenderer, string pathToFolder) {
    for (int i=0; i<9; i++) {
        stringstream input;
        input << pathToFolder << "/num" << i << ".png";
        SDL_Surface* loadedSurface = NULL;
        loadedSurface = IMG_Load(input.str().c_str());
        if (loadedSurface == NULL) {
            return false;
        } else {
            tx[i] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
            SDL_FreeSurface(loadedSurface);
        }
    }
    {
        SDL_Surface* loadedSurface = IMG_Load("assets/tiles/bomb.png");
        if (loadedSurface == NULL) {
            cout << "Cannot find assets/tiles/bomb.png" << endl;
            return false;
        } else {
            tx[bomb] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
            SDL_FreeSurface(loadedSurface);
        }
    }
    {
        SDL_Surface* loadedSurface = IMG_Load("assets/tiles/bomb_clicked.png");
        if (loadedSurface == NULL) {
            cout << "Cannot find assets/tiles/bomb_clicked.png" << endl;
            return false;
        } else {
            tx[bomb_clicked] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
            SDL_FreeSurface(loadedSurface);
        }
    }
    {
        SDL_Surface* loadedSurface = IMG_Load("assets/tiles/bomb_found.png");
        if (loadedSurface == NULL) {
            cout << "Cannot find assets/tiles/bomb_found.png" << endl;
            return false;
        } else {
            tx[bomb_found] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
            SDL_FreeSurface(loadedSurface);
        }
    }
    {
        SDL_Surface* loadedSurface = IMG_Load("assets/tiles/flag.png");
        if (loadedSurface == NULL) {
            cout << "Cannot find assets/tiles/flag.png" << endl;
            return false;
        } else {
            tx[flag] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
            SDL_FreeSurface(loadedSurface);
        }
    }
    {
        SDL_Surface* loadedSurface = IMG_Load("assets/tiles/hidden.png");
        if (loadedSurface == NULL) {
            cout << "Cannot find assets/tiles/hidden.png" << endl;
            return false;
        } else {
            tx[hidden] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
            sprite[0] = {0, 0, 500, 500};
            sprite[1] = {500, 0, 500, 500};
            sprite[2] = {1000, 0, 500, 500};
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
            tile_x[i][j] = x+(w+1)*j;
            tile_y[i][j] = y+(h+1)*i;
            tile_w[i][j] = w;
            tile_h[i][j] = h;
        }
    }
}

void Tile::handleEvent(SDL_Event* e) {
    if (p == PLAY) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (mouseX < x || mouseX > x+n*w+(n-1)) {
            hover_x = -1;
            hover_y = -1;
        }
        if (mouseY < y || mouseY > y+m*h+(m-1)) {
            hover_x = -1;
            hover_y = -1;
        }
        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                if (tile[i][j] == hidden || tile[i][j] == flag) {
                    bool inside = true;
                    if ((mouseX < x+(w+1)*j) || (mouseX > x+(w+1)*j+w)) {
                        inside = false;
                    }
                    if ((mouseY < y+(h+1)*i) || (mouseY > y+(h+1)*i+h)) {
                        inside = false;
                    }
                    if (!inside) {
                        state[i][j] = BUTTON_MOUSE_OUT;
                    } else {
                        switch (e->type) {
                            case SDL_MOUSEMOTION: {
                                state[i][j] = BUTTON_MOUSE_HOVER;
                                hover_x = i;
                                hover_y = j;
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
                                    if (tile[i][j] != flag) {playTile();}
                                } 
                                else if (!left && right) {
                                    state[i][j] = BUTTON_MOUSERIGHT_UP;
                                    playFlag();
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

void Tile::revealTile(int i, int j) {
    tile_x[i][j] = x+(w+1)*j+g;
    tile_y[i][j] = y+(h+1)*i+g;
    tile_w[i][j] = w-g*2;
    tile_h[i][j] = h-g*2;
    tile[i][j] = mine[i][j];
    if (mine[i][j] == num0) {
        for (int a=i-1; a<=i+1; a++) {
            if (a<0 || a>=m) {continue;}
            for (int b=j-1; b<=j+1; b++) {
                if (b<0 || b>=n) {continue;}
                if (tile[a][b] == hidden) {
                    if (mine[a][b] != num0) {
/*                         tile_x[a][b] = x+(w+1)*j+g;
                        tile_y[a][b] = y+(h+1)*i+g;
                        tile_w[a][b] = w-g*2;
                        tile_h[a][b] = h-g*2; */
                        tile[a][b] = mine[a][b];
                    }
                    else {
                        revealTile(a, b);
                    }
                }
            }
        }
    }
}

void Tile::revealAll(int a, int b) {
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            tile_x[i][j] = x+(w+1)*j+g;
            tile_y[i][j] = y+(h+1)*i+g;
            tile_w[i][j] = w-g*2;
            tile_h[i][j] = h-g*2;
            if (i == a && j == b) {
                mine[i][j] = bomb_clicked;
            }
            if (tile[i][j] == flag) {
                if (mine[i][j] == bomb) {
                    mine[i][j] = bomb_found;
                }
            } 
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
    SND_reset();
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

GameState Tile::render(SDL_Renderer* gRenderer, int fadeSpeed) {
    mAlpha.fade(fadeSpeed);
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (i != hover_x || j != hover_y) {
                switch (tile[i][j]) {
                    case num0: case num1: case num2: case num3: case num4: case num5: case num6: case num7: case num8:
                    case bomb: case bomb_clicked: case bomb_found: {
                        if (tile_x[i][j] > x+(w+1)*j && tile_y[i][j] > y+(h+1)*i) {
                            if (SDL_GetTicks()%updateSpeed == 0) {
                                tile_x[i][j] -= 1;
                                tile_y[i][j] -= 1;
                            }
                        }
                        if (tile_w[i][j] < w && tile_h[i][j] < h) {
                            if (SDL_GetTicks()%updateSpeed == 0) {
                                tile_w[i][j] += 2;
                                tile_h[i][j] += 2;
                            }
                        } 
                        SDL_Rect pos = {tile_x[i][j], tile_y[i][j], tile_w[i][j], tile_h[i][j]};
                        SDL_SetTextureAlphaMod(tx[tile[i][j]], mAlpha.alpha);
                        SDL_RenderCopy(gRenderer, tx[tile[i][j]], NULL, &pos);
                        break;
                    }
                    case flag: case hidden: {
                        if (tile_x[i][j] < x+(w+1)*j && tile_y[i][j] < y+(h+1)*i) {
                            if (SDL_GetTicks()%updateSpeed == 0) {
                                tile_x[i][j] += 1;
                                tile_y[i][j] += 1;
                            }
                        }
                        if (tile_w[i][j] > w && tile_h[i][j] > h) {
                            if (SDL_GetTicks()%updateSpeed == 0) {
                                tile_w[i][j] -= 2;
                                tile_h[i][j] -= 2;
                            }
                        }
                        SDL_Rect pos = {tile_x[i][j], tile_y[i][j], tile_w[i][j], tile_h[i][j]};
                        SDL_SetTextureAlphaMod(tx[tile[i][j]], mAlpha.alpha);
                        SDL_RenderCopy(gRenderer, tx[tile[i][j]], &sprite[0], &pos);
                        break;
                    }
                }
            }
        }
    }
    if (hover_x != -1 && hover_y != -1) {
        switch (tile[hover_x][hover_y]) {
            case hidden: {
                switch (state[hover_x][hover_y]) {
                    case BUTTON_MOUSE_OUT: {
                        currentSprite = 0;
                        if (tile_x[hover_x][hover_y] < x+(w+1)*hover_y && tile_y[hover_x][hover_y] < y+(h+1)*hover_x) {
                            if (SDL_GetTicks()%updateSpeed == 0) {
                                tile_x[hover_x][hover_y] += 1;
                                tile_y[hover_x][hover_y] += 1;
                            }
                        }
                        if (tile_w[hover_x][hover_y] > w && tile_h[hover_x][hover_y] > h) {
                            if (SDL_GetTicks()%updateSpeed == 0) {
                                tile_w[hover_x][hover_y] -= 2;
                                tile_h[hover_x][hover_y] -= 2;
                            }
                        }
                        break;
                    }
                    case BUTTON_MOUSE_HOVER: {
                        currentSprite = 1;
                        if (tile_x[hover_x][hover_y] > x+(w+1)*hover_y-g && tile_y[hover_x][hover_y] > y+(h+1)*hover_x-g) {
                            if (SDL_GetTicks()%updateSpeed == 0) {
                                tile_x[hover_x][hover_y] -= 1;
                                tile_y[hover_x][hover_y] -= 1;
                            }
                        }
                        if (tile_w[hover_x][hover_y] < w+g*2 && tile_h[hover_x][hover_y] < h+g*2) {
                            if (SDL_GetTicks()%updateSpeed == 0) {
                                tile_w[hover_x][hover_y] += 2;
                                tile_h[hover_x][hover_y] += 2;
                            }
                        }
                        break;
                    }
                    case BUTTON_MOUSELEFT_DOWN: case BUTTON_MOUSERIGHT_DOWN: {
                        currentSprite = 2;
                        if (tile_x[hover_x][hover_y] < x+(w+1)*hover_y+g && tile_y[hover_x][hover_y] < y+(h+1)*hover_x+g) {
                            if (SDL_GetTicks()%updateSpeed == 0) {
                                tile_x[hover_x][hover_y] += 2;
                                tile_y[hover_x][hover_y] += 2;
                            }
                        }
                        if (tile_w[hover_x][hover_y] > w-g*2 && tile_h[hover_x][hover_y] > h-g*2) {
                            if (SDL_GetTicks()%updateSpeed == 0) {
                                tile_w[hover_x][hover_y] -= 4;
                                tile_h[hover_x][hover_y] -= 4;
                            }
                        }
                        break;
                    }
                    case BUTTON_MOUSELEFT_UP: {
                        currentSprite = 1;
                        if (!isUserPressed) {
                            while (mine[hover_x][hover_y] != num0) {
                                generate();
                            } 
                            isUserPressed = true;
                        }
                        if (mine[hover_x][hover_y] != bomb) {
                            revealTile(hover_x, hover_y);
                        } else {
                            playBomb();
                            revealAll(hover_x, hover_y);
                            p = LOSE;
                        }
                        break;
                    }
                    case BUTTON_MOUSERIGHT_UP: {
                        currentSprite = 1;
                        tile[hover_x][hover_y] = flag;
                        state[hover_x][hover_y] = BUTTON_MOUSE_HOVER;
                        break;
                    }
                }
                SDL_Rect pos = {tile_x[hover_x][hover_y], tile_y[hover_x][hover_y], tile_w[hover_x][hover_y], tile_h[hover_x][hover_y]};
                SDL_SetTextureAlphaMod(tx[tile[hover_x][hover_y]], mAlpha.alpha);
                SDL_RenderCopy(gRenderer, tx[tile[hover_x][hover_y]], &sprite[currentSprite], &pos);
                if (state[hover_x][hover_y] == BUTTON_MOUSELEFT_UP) {
                    hover_x = -1;
                    hover_y = -1;
                }
                break;
            }
            case flag: {
                switch (state[hover_x][hover_y]) {
                    case BUTTON_MOUSE_OUT: {
                        currentSprite = 0;
                        if (tile_x[hover_x][hover_y] < x+(w+1)*hover_y && tile_y[hover_x][hover_y] < y+(h+1)*hover_x) {
                            if (SDL_GetTicks()%updateSpeed == 0) {
                                tile_x[hover_x][hover_y] += 1;
                                tile_y[hover_x][hover_y] += 1;
                            }
                        }
                        if (tile_w[hover_x][hover_y] > w && tile_h[hover_x][hover_y] > h) {
                            if (SDL_GetTicks()%updateSpeed == 0) {
                                tile_w[hover_x][hover_y] -= 2;
                                tile_h[hover_x][hover_y] -= 2;
                            }
                        }
                        break;
                    }
                    case BUTTON_MOUSE_HOVER: {
                        currentSprite = 1;
                        if (tile_x[hover_x][hover_y] > x+(w+1)*hover_y-g && tile_y[hover_x][hover_y] > y+(h+1)*hover_x-g) {
                            if (SDL_GetTicks()%updateSpeed == 0) {
                                tile_x[hover_x][hover_y] -= 1;
                                tile_y[hover_x][hover_y] -= 1;
                            }
                        }
                        if (tile_w[hover_x][hover_y] < w+g*2 && tile_h[hover_x][hover_y] < h+g*2) {
                            if (SDL_GetTicks()%updateSpeed == 0) {
                                tile_w[hover_x][hover_y] += 2;
                                tile_h[hover_x][hover_y] += 2;
                            }
                        }
                        break;
                    }
                    case BUTTON_MOUSERIGHT_DOWN: {
                        currentSprite = 2;
                        if (tile_x[hover_x][hover_y] < x+(w+1)*hover_y+g && tile_y[hover_x][hover_y] < y+(h+1)*hover_x+g) {
                            if (SDL_GetTicks()%updateSpeed == 0) {
                                tile_x[hover_x][hover_y] += 2;
                                tile_y[hover_x][hover_y] += 2;
                            }
                        }
                        if (tile_w[hover_x][hover_y] > w-g*2 && tile_h[hover_x][hover_y] > h-g*2) {
                            if (SDL_GetTicks()%updateSpeed == 0) {
                                tile_w[hover_x][hover_y] -= 4;
                                tile_h[hover_x][hover_y] -= 4;
                            }
                        }
                        break;
                    }
                    case BUTTON_MOUSERIGHT_UP: {
                        currentSprite = 1;
                        tile[hover_x][hover_y] = hidden;
                        state[hover_x][hover_y] = BUTTON_MOUSE_HOVER;
                        break;
                    }
                }
                SDL_Rect pos = {tile_x[hover_x][hover_y], tile_y[hover_x][hover_y], tile_w[hover_x][hover_y], tile_h[hover_x][hover_y]};
                SDL_SetTextureAlphaMod(tx[tile[hover_x][hover_y]], mAlpha.alpha);
                SDL_RenderCopy(gRenderer, tx[tile[hover_x][hover_y]], &sprite[currentSprite], &pos);
                break;
            }
        }
    }
    if (p != LOSE) {
        if (checkWin()) {
            p = WIN;
        }
    } 
    return p;
}