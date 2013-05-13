#ifdef _WIN32
#include "SDL.h"
#else
#include <SDL/SDL.h>
#endif

#include <functional>
#include "TGameTimer.hpp"

#define GET_TIMER_RATE(l)  ((50 - (l)) * 20)

TGameTimer::TGameTimer() {
  level = 0;
  timer_rate = GET_TIMER_RATE(0);
  old_time = 0;
  enabled = true;
  callback_func = NULL;
}

TGameTimer::~TGameTimer() {
}

void TGameTimer::SetCurrentLevel(int curr_level) {
  level = curr_level;
  timer_rate = GET_TIMER_RATE(level);
}

int TGameTimer::GetCurrentLevel() {
  return level;
}

void TGameTimer::SetCallback(std::function<void()> func) {
  callback_func = func;
}

void TGameTimer::OnLoop() {
  if (enabled) {
    if (old_time + timer_rate > SDL_GetTicks())
      return;
    
    old_time = SDL_GetTicks();
    
    if (callback_func)
      callback_func();
  }
}
