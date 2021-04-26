#ifndef _SOUND
#define _SOUND

bool SND_load();
void playBackground();
void pauseBackground();
void stopBackground();
void replayBackground();
void playTile();
void playFlag();
void playButton();
void playWin();
void playLose();
void playBomb();
void SND_close();
void SND_reset();

#endif