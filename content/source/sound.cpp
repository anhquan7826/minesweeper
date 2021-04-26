#include "sound.hpp"
#include <iostream>
#include <SDL_mixer.h>

using namespace std;

Mix_Music* background;
Mix_Chunk* tile;
Mix_Chunk* flag;
Mix_Chunk* button;
Mix_Chunk* bomb;
Mix_Chunk* lose;
Mix_Chunk* win;

bool win_playOnce = false;
bool lose_playOnce = false;

bool SND_load() {
    background = Mix_LoadMUS("assets/sound/music.ogg");
    if (background == NULL) {
        cout << "Cannot load background.ogg!" << endl;
        return false;
    }
    tile = Mix_LoadWAV("assets/sound/tile.ogg");
    if (tile == NULL) {
        cout << "Cannot load tile.ogg!" << endl;
        return false;
    }
    flag = Mix_LoadWAV("assets/sound/flag.ogg");
    if (flag == NULL) {
        cout << "Cannot load flag.ogg!" << endl;
        return false;
    }
    button = Mix_LoadWAV("assets/sound/button.ogg");
    if (button == NULL) {
        cout << "Cannot load button.ogg!" << endl;
        return false;
    }
    lose = Mix_LoadWAV("assets/sound/lose.ogg");
    if (lose == NULL) {
        cout << "Cannot load lose.ogg!" << endl;
        return false;
    }
    win = Mix_LoadWAV("assets/sound/win.ogg");
    if (win == NULL) {
        cout << "Cannot load win.ogg!" << endl;
        return false;
    }
    bomb = Mix_LoadWAV("assets/sound/bomb.ogg");
    if (bomb == NULL) {
        cout << "Cannot load bomb.ogg!" << endl;
        return false;
    }
    return true;
}

void playBackground() {
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(background, -1);
    }
}

void pauseBackground() {
    if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    } else {
        Mix_PauseMusic();
    }
}

void stopBackground() {
    Mix_HaltMusic();
}

void replayBackground() {
    stopBackground();
    playBackground();
}

void playTile() {
    Mix_PlayChannel(-1, tile, 0);
}

void playFlag() {
    Mix_PlayChannel(-1, flag, 0);
}

void playButton() {
    Mix_PlayChannel(-1, button, 0);
}

void playWin() {
    if (!win_playOnce) {
        Mix_PlayChannel(-1, win, 0);
        win_playOnce = true;
    }
}

void playLose() {
    if (!lose_playOnce) {
        Mix_PlayChannel(-1, lose, 0);
        lose_playOnce = true;
    }
}

void playBomb() {
    Mix_PlayChannel(-1, bomb, 0);
}

void SND_close() {
    Mix_FreeMusic(background);
    Mix_FreeChunk(tile);
    Mix_FreeChunk(flag);
    Mix_FreeChunk(button);
    Mix_FreeChunk(win);
    Mix_FreeChunk(lose);
}

void SND_reset() {
    win_playOnce = false;
    lose_playOnce = false;
}