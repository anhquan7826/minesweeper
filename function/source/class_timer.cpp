#include "class_timer.hpp"
#include <iomanip>

using namespace std;

stringstream X;

Timer::Timer() {
    tick_start = 0;
    tick_pause = 0;
    isStarted = false;
    isPaused = false;
}
void Timer::start() {
    if (!isStarted) {
        isStarted = true;
        isPaused = false;
        tick_start = SDL_GetTicks();
        tick_pause = 0;
    }
}
void Timer::stop() {
    isStarted = false;
    isPaused = false;
    tick_start = 0;
    tick_pause = 0;
}
void Timer::pause() {
    if (isStarted && !isPaused) {
        isPaused = true;
        tick_pause = SDL_GetTicks()-tick_start;
        tick_start = 0;
    }
}
void Timer::unpause() {
    if (isStarted && isPaused) {
        isPaused = false;
        tick_start = SDL_GetTicks()-tick_pause;
        tick_pause = 0;
    }
}
Uint32 Timer::getTicks() {
    Uint32 tick = 0;
    if (isStarted) {
        if (isPaused) {
            tick = tick_pause;
        } else {
            tick = SDL_GetTicks()-tick_start;
        }
    }
    return tick;
}
int Timer::getState() {
    if (!isStarted) {
        return -1;
    }
    if (isStarted && !isPaused) {
        return 1;
    }
    if (isStarted && isPaused) {
        return 0;
    }
    return -2;
}

bool Timer::countDown(int amount) {
    start();
    if (SDL_GetTicks()-tick_start >= amount) {
        stop();
        return true;
    }
    return false;
}

string Timer::getClockCount() {
    int time = getTicks()/1000;
    X.str("");
    X << setw(2) << setfill('0') << time/3600;
    time %= 3600;
    X << ':' << setw(2) << setfill('0') << time/60;
    time %= 60;
    X << ':' << setw(2) << setfill('0') << time;
    return X.str();
}